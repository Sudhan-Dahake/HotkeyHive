#include "keyboard_hook/keyboard_hook.h"
#include "key_remapper/key_remapper.h"
#include "utils/utils.h"
#include <iostream>
#include <algorithm>

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
    auto applications = GetRunningApplications();

    if (applications.empty()) {
        std::cout << "No running applications detected." << std::endl;

        return;
    };

    // Display running applications.
    std::cout << "Select an applicaiton to remap keys for:" << std::endl;

    for (size_t i = 0; i < applications.size(); i++) {
        std::cout << i + 1 << ". " << applications[i].windowTitle
                  << " (" << applications[i].executableName << ")" << std::endl;
    };

    int choice;

    std::cout << "Enter your choice (number): ";
    std::cin >> choice;

    if ((choice <= 0) || (choice > applications.size())) {
        std::cout << "Invalid choice." << std::endl;

        return;
    };

    std::string application = applications[choice - 1].executableName;
    std::string originalKey, remappedKey;

    std::cout << "Enter the original key combination (e.g., Ctrl+C): ";
    std::cin >> originalKey;

    std::cout << "Enter the new key combination (e.g., Ctrl+Shift+P): ";
    std::cin >> remappedKey;

    AddKeyRemapping(application, originalKey, remappedKey);
};


void ViewRemappings() {
    std::cout << "\n--- Current Remappings ---\n";

    const std::map<std::string, std::vector<Remapping>> &appSpecificRemappings = GetAllRemappings();

    for(const auto& [application, remappings] : appSpecificRemappings) {
        std::cout << "Application: " << application << std::endl;

        for(const auto& remapping : remappings) {
            std::cout << "  " << remapping.originalKey << " -> " << remapping.remappedKey << std::endl;
        };
    };


    if (appSpecificRemappings.empty()) {
        std::cout << "No remappings available" << std::endl;
    };
};


void DeleteRemapping() {
    std::string application, originalKey;

    // Get the application and key combination from the user.
    std::cout << "Enter the application name (e.g., MS Word): ";
    std::cin.ignore(); // Clear the input buffer.
    std::getline(std::cin, application);

    std::cout << "Enter the original key combination to delete (e.g., Ctrl + C): ";
    std::cin >> originalKey;

    std::map<std::string, std::vector<Remapping>> &appSpecificRemappings = GetAllRemappings();

    // Checking to see if the application exists in the map.
    if (appSpecificRemappings.find(application) != appSpecificRemappings.end()) {
        auto &remappings = appSpecificRemappings[application];

        // Find the remapping in the vector.
        auto it = std::remove_if(remappings.begin(), remappings.end(),
                                 [&originalKey](const Remapping &remapping)
                                 {
                                     return remapping.originalKey == originalKey;
                                 });

        if (it != remappings.end()) {
            remappings.erase(it, remappings.end());     // Erasing the matched remapping.

            std::cout << "Remapping for " << originalKey << " in " << application << " deleted." << std::endl;

            if (remappings.empty()) {
                appSpecificRemappings.erase(application);
            }
        }

        else {
            std::cout << "No remapping for " << originalKey << " found in " << application << "." << std::endl;
        };
    }

    else {
        std::cout << "No remappings found for application: " << application << "." << std::endl;
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