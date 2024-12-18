#include "keyboard_hook/keyboard_hook.h"
#include <iostream>

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

    InstallKeyboardHook();

    MSG msg;

    // Message loop to keep the hook alive.
    while (!exitProgram) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Cleanup -> Removing the hook.
    RemoveKeyboardHook();
    
    std::cout << "Exiting Program..." << std::endl;

    return 0;
}