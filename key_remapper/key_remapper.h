#ifndef KEY_REMAPPER_H
#define KEY_REMAPPER_H

#include <string>
#include <map>
#include <vector>

// Defining a mapping for a specific application.
struct Remapping {
    std::string originalKey;
    std::string remappedKey;
    std::string application;     // Application (or window title).
};

// Function declarations for key remapping.
void AddKeyRemapping(const std::string& application, const std::string& originalKey, const std::string& remappedKey);
bool CheckForConflict(const std::string& application, const std::string& targetKey);
std::string GetRemappedKey(const std::string& application, const std::string& originalKey);


// Save and Load remappings.
void SaveRemappingsToFile(const std::string& filename);
void LoadRemappingsFromFile(const std::string &filename);

// Getter for KeyRemappings
std::map<std::string, std::vector<Remapping>> &GetAllRemappings();

#endif