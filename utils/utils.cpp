#include "utils.h"
#include <windows.h>
#include <psapi.h>
#include <vector>

// Callback for EnumWindows.
BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];

    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));

    if (IsWindowVisible(hwnd) && strlen(windowTitle) > 0) {
        std::vector<ApplicationInfo> *applications = reinterpret_cast<std::vector<ApplicationInfo> *>(lParam);

        std::string executableName = GetExecutableName(hwnd);

        if (!executableName.empty()) {
            applications->push_back({windowTitle, executableName});
        };
    };

    return TRUE;
};


// Function to get a List of running applications.
std::vector<ApplicationInfo> GetRunningApplications() {
    std::vector<ApplicationInfo> applications;

    EnumWindows(EnumWindowsCallback, reinterpret_cast<LPARAM>(&applications));

    return applications;
};


std::string GetExecutableName(HWND hwnd) {
    DWORD processId;

    GetWindowThreadProcessId(hwnd, &processId);

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);

    if (hProcess) {
        wchar_t exeName[MAX_PATH];

        if (GetModuleFileNameExW(hProcess, NULL, exeName, MAX_PATH)) {
            CloseHandle(hProcess);

            // Converting wchar_t* to std::wstring.
            std::wstring widePath(exeName);

            std::string fullPath(widePath.begin(), widePath.end());

            size_t pos = fullPath.find_last_of("\\/");

            return (pos != std::string::npos) ? fullPath.substr(pos + 1) : fullPath;
        };

        CloseHandle(hProcess);
    };

    return "";
};

// This function gets the title of the active window.
std::string GetActiveWindowTitle() {
    char windowTitle[256];

    HWND hwnd = GetForegroundWindow();

    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));

    return std::string(windowTitle);
};