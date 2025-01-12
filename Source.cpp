#include "keyboard_hook/keyboard_hook.h"
#include "key_remapper/key_remapper.h"
#include <iostream>

#define FILENAME "remappings.txt"

void DisplayMenu() {
    std::cout << "\n--- Key Remapper Menu ---\n";
    std::cout << "1. Add a New Key Remapping" << std::endl;
    std::cout << "2. View Existing Remappings" << std::endl;
    std::cout << "3. Delete a Key Remapping" << std::endl;
    std::cout << "4. Start Hook (Listen for Key Presses)" << std::endl;
    std::cout << "5. Exit Program" << std::endl;

    std::cout << "Enter you choice: ";
};

void AddNewRemapping() {
    std::string originalKey, remappedKey;

    std::cout << "Enter the original key combination (e.g., Ctrl+C): ";
    std::cin >> originalKey;

    std::cout << "Enter the new key combination (e.g., Ctrl+Shift+P): ";
    std::cin >> remappedKey;

    AddKeyRemapping(originalKey, remappedKey);
};


void ViewRemappings() {
    std::cout << "\n--- Current Remappings ---\n";

    const std::map<std::string, std::string> &remappings = GetAllRemappings();

    for(const std::pair<std::string, std::string>& pair : remappings) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    };


    if (remappings.empty()) {
        std::cout << "No remappings available" << std::endl;
    };
};


void DeleteRemapping() {
    std::string originalKey;

    std::cout << "Enter the original key combination to delete (e.g., Ctrl + C): ";
    std::cin >> originalKey;

    std::map<std::string, std::string> &remappings = GetAllRemappings();

    if (remappings.erase(originalKey)) {
        std::cout << "Remapping for " << originalKey << " deleted." << std::endl;
    }

    else {
        std::cout << "No remapping found for " << originalKey << std::endl;
    };
};


int main(void) {
    // Disabling Ctrl+C termination Signal.
    SetConsoleCtrlHandler([](DWORD fdwCtrlType) -> BOOL {
        if (fdwCtrlType == CTRL_C_EVENT) {
            std::cout << "Ctrl+C signal ignored (console)." << std::endl;
            return TRUE;
        }
        return FALSE;
    }, TRUE);

    std::cout << "Starting keyboard Hook. Press ESC to exit." << std::endl;

    // Load remappings from file.
    LoadRemappingsFromFile(FILENAME);

    // // Adding test remappings
    // AddKeyRemapping("Ctrl+C", "Ctrl+Shift+P");
    // AddKeyRemapping("Alt+Tab", "Ctrl+Alt+T");

    int choice = 0;

    while(choice != 5) {
        DisplayMenu();

        std::cin >> choice;

        switch (choice) {
            case 1:
                AddNewRemapping();

                break;

            case 2:
                ViewRemappings();

                break;

            case 3:
                DeleteRemapping();

                break;

            case 4:
                std::cout << "Starting Keyboard Hook. Press ESC to exit." << std::endl;

                InstallKeyboardHook();

                MSG msg;

                // Message loop to keep the hook alive.
                while (!exitProgram)
                {
                    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                    {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }

                // Cleanup -> Removing the hook.
                RemoveKeyboardHook();

                exitProgram = false;

                break;

            case 5:
                std::cout << "Saving remappings and exiting..." << std::endl;

                // Save remappings.
                SaveRemappingsToFile(FILENAME);

                break;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;

                break;
        };
    };

    return 0;
};