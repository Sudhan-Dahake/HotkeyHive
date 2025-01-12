#include "key_remapper.h"
#include <iostream>
#include <fstream>
#include <map>

// A data structure to store key remappings
static std::map<std::string, std::string> keyRemappings;

// Function to add new key remappings
void AddKeyRemapping(const std::string& originalKey, const std::string& remappedKey) {
    // Checking for any conflicts.
    if (CheckForConflict(remappedKey)) {
        std::cout << "Conflict detected: " << remappedKey << " is already in use!" << std::endl;

        return;
    };

    // Adding the remapping.
    keyRemappings[originalKey] = remappedKey;

    std::cout << "Remapped " << originalKey << " to " << remappedKey << std::endl;
};


bool CheckForConflict(const std::string& targetKey) {
    for (const auto& pair: keyRemappings) {
        if (pair.second == targetKey)
          return true;
    }

    return false;
};


std::string GetRemappedKey(const std::string &originalKey) {
    if (keyRemappings.find(originalKey) != keyRemappings.end()) {
        return keyRemappings[originalKey];
    };

    return originalKey;
};


// Save remappings to a file.
void SaveRemappingsToFile(const std::string &filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for saving!" << std::endl;

        return;
    };


    for(const auto& pair : keyRemappings) {
        file << pair.first << " " << pair.second << std::endl;
    }

    file.close();

    std::cout << "Remappings saved to " << filename << std::endl;
};


// Load reamppings from a file.
void LoadRemappingsFromFile(const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for loading!" << std::endl;

        return;
    };

    keyRemappings.clear();      // Clear current remappings

    std::string originalKey, remappedKey;

    while(file >> originalKey >> remappedKey) {
        keyRemappings[originalKey] = remappedKey;
    };

    file.close();

    std::cout << "Remappings loaded from " << filename << std::endl;
};


// Getter for KeyRemappings
std::map<std::string, std::string>& GetAllRemappings() {
    return keyRemappings;
};