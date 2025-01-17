#include "key_remapper.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

// A data structure to store key remappings
static std::map<std::string, std::vector<Remapping>>* appSpecificRemappings;

// Function to add new key remappings
bool AddKeyRemapping(std::map<std::string, std::vector<Remapping>>** ptrToAppSpecificRemappings, const std::string &application, const std::string &originalKey, const std::string &remappedKey)
{
    // Checking for any conflicts.
    if (CheckForConflict(*ptrToAppSpecificRemappings, application, remappedKey)) {
        std::cout << "Conflict detected: " << remappedKey << " is already in use in " << application << "!" << std::endl;

        return false;
    };

    // Adding the remapping.
    (**ptrToAppSpecificRemappings)[application].push_back({originalKey, remappedKey, application});

    std::cout << "Remapped " << originalKey << " to " << remappedKey << " for application: " << application << std::endl;

    return true;
};

bool CheckForConflict(std::map<std::string, std::vector<Remapping>>* ptrToAppSpecificRemappings, const std::string &application, const std::string &targetKey)
{
    if ((*ptrToAppSpecificRemappings).find(application) == (*ptrToAppSpecificRemappings).end()) return false;

    for (const auto& remapping: (*ptrToAppSpecificRemappings)[application]) {
        if (remapping.remappedKey == targetKey) return true;
    };

    return false;
};

// std::string GetRemappedKey(const std::string& application, const std::string &originalKey) {
//     if (appSpecificRemappings.find(application) != appSpecificRemappings.end()) {
//         return originalKey;
//     };

//     for(const auto& remapping : appSpecificRemappings[application]) {
//         if (remapping.originalKey == originalKey) {
//             return remapping.remappedKey;
//         };
//     };

//     return originalKey;
// };


// Save remappings to a file.
void SaveRemappingsToFile(std::map<std::string, std::vector<Remapping>>** ptrToAppSpecificRemappings, const std::string &filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for saving!" << std::endl;

        return;
    };


    for(const auto& [application, remappings] : **(ptrToAppSpecificRemappings)) {
        for(const auto& remapping : remappings) {
            file << application << " " << remapping.originalKey << " " << remapping.remappedKey << std::endl;
        };
    };

    file.close();

    std::cout << "Remappings saved to " << filename << std::endl;
};


// Load reamppings from a file.
void LoadRemappingsFromFile(std::map<std::string, std::vector<Remapping>>** ptrToAppSpecificRemappings, const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for loading!" << std::endl;

        return;
    };

    (**ptrToAppSpecificRemappings).clear(); // Clear current remappings

    std::string application, originalKey, remappedKey;

    while(file >> application >> originalKey >> remappedKey) {
        (**ptrToAppSpecificRemappings)[application].push_back({originalKey, remappedKey, application});

        std::cout << "application: " << application << ", original Key: " << originalKey << ", remapped key: " << remappedKey << std::endl;
    };

    file.close();

    std::cout << "Remappings loaded from " << filename << std::endl;

    appSpecificRemappings = *ptrToAppSpecificRemappings;
};


// Getter for KeyRemappings
std::map<std::string, std::vector<Remapping>> GetAllRemappings() {
    return *appSpecificRemappings;
};