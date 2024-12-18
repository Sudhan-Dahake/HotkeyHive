#include "utils.h"
#include <windows.h>

// This function gets the title of the active window.
std::string GetActiveWindowTitle() {
    char windowTitle[256];

    HWND hwnd = GetForegroundWindow();

    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));

    return std::string(windowTitle);
};