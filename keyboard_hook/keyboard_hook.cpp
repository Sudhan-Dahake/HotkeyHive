#include "keyboard_hook.h"
#include "../key_utils/key_utils.h"
#include "../utils/utils.h"
#include <iostream>

HHOOK keyboardHook; // This is the hook handle.

bool exitProgram = false; // Flag to exit the program;

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

            // Outputting the key combination and the active window title.
            std::cout << "Key Pressed: " << keyCombo
                      << " | Active Window: " << GetActiveWindowTitle() << std::endl;

            // Detect Ctrl+C and process it for remapping
            if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (kbStruct->vkCode == 'C')) {
                std::cout << "Ctrl+C detected. Ready for remapping!" << std::endl;

                return 1; // Blocking the default console behaviour.
            };
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