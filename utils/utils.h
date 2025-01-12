#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

struct ApplicationInfo {
    std::string windowTitle;
    std::string executableName;
};

// Function to get the executable name of the active window.
std::string GetExecutableName(HWND hwnd);

// Function to get the Active Windows Title.
std::string GetActiveWindowTitle();

std::vector<ApplicationInfo> GetRunningApplications();

#endif