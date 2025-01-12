#include "keyboard_hook.h"
#include "../key_utils/key_utils.h"
#include "../utils/utils.h"
#include "../key_remapper/key_remapper.h"
#include <iostream>
#include <vector>

HHOOK keyboardHook; // This is the hook handle.

bool exitProgram = false; // Flag to exit the program;


// Function to simulate a key combination.
void SimulateKeyCombination(const std::string& keyCombo) {
    INPUT inputs[10];

    int inputCount = 0;

    // Clearing the input array.
    ZeroMemory(inputs, sizeof(inputs));

    // Split the keyCombo String (e.g.)
    size_t pos = 0;
    std::string token;
    std::string delimiter = "+";
    std::vector<std::string> keys;

    std::string keyComboCopy = keyCombo;

    while((pos = keyComboCopy.find(delimiter)) != std::string::npos) {
        token = keyComboCopy.substr(0, pos);

        keys.push_back(token);

        keyComboCopy.erase(0, pos + delimiter.length());
    };

    // Adding the last key.
    keys.push_back(keyComboCopy);


    // Press modifier keys first (e.g., Ctrl, Alt, Shift).
    for(const auto& key : keys) {
        WORD vkCode = 0;

        if (key == "Left Ctrl") vkCode = VK_LCONTROL;
        else if (key == "Right Ctrl") vkCode = VK_RCONTROL;
        else if (key == "Shift") vkCode = VK_SHIFT;
        else if (key == "Alt") vkCode = VK_MENU;
        else if (key == "Left Alt") vkCode = VK_LMENU;
        else if (key == "Right Alt") vkCode = VK_RMENU;
        else vkCode = key[0];       // Assuming Single Character for now.

        inputs[inputCount].type = INPUT_KEYBOARD;
        inputs[inputCount].ki.wVk = vkCode;
        inputCount++;
    };

    // Release Modifier keys.
    for (auto it = keys.rbegin(); it != keys.rend(); ++it) {
        WORD vkCode = 0;

        if (*it == "Left Ctrl") vkCode = VK_LCONTROL;
        else if (*it == "Right Ctrl") vkCode = VK_RCONTROL;
        else if (*it == "Shift") vkCode = VK_SHIFT;
        else if (*it == "Alt") vkCode = VK_MENU;
        else if (*it == "Left Alt") vkCode = VK_LMENU;
        else if (*it == "Right Alt") vkCode = VK_RMENU;
        else vkCode = (*it)[0];       // Assuming Single Character for now.

        inputs[inputCount].type = INPUT_KEYBOARD;
        inputs[inputCount].ki.wVk = vkCode;
        inputs[inputCount].ki.dwFlags = KEYEVENTF_KEYUP;
        inputCount++;
    };

    // Send the Input.
    SendInput(inputCount, inputs, sizeof(INPUT));
}


// Keyboard hook callback function.
LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *kbStruct = (KBDLLHOOKSTRUCT *)lParam;

        if ((wParam == WM_KEYDOWN) || (wParam == WM_SYSKEYDOWN)) {
            if (kbStruct->vkCode == VK_ESCAPE) {
                exitProgram = true;
            };

            // Detect Full key combinations.
            std::string keyCombo = GetKeyCombination(kbStruct);

            // Check for remapping
            std::string remappedKey = GetRemappedKey(keyCombo);

            if (remappedKey != keyCombo) {
                std::cout << "Key Pressed: " << keyCombo
                          << " -> Remapped to: " << remappedKey << std::endl;

                // Simulate the remapped key combination.
                SimulateKeyCombination(remappedKey);

                return 1;
            };

            // Outputting the key combination and the active window title.
            std::cout << "Key Pressed: " << keyCombo
                      << " | Active Window: " << GetActiveWindowTitle() << std::endl;

            // // Detect Ctrl+C and process it for remapping
            // if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (kbStruct->vkCode == 'C')) {
            //     std::cout << "Ctrl+C detected. Ready for remapping!" << std::endl;

            //     return 1; // Blocking the default console behaviour.
            // };
        };
    };

    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
};

void InstallKeyboardHook() {
    // Installing the keyboard hook.
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);

    if (!keyboardHook) {
        std::cerr << "Failed to install hook! Error: " << GetLastError() << std::endl;
    };
};


void RemoveKeyboardHook() {
    UnhookWindowsHookEx(keyboardHook);
}