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
bool AddKeyRemapping(std::map<std::string, std::vector<Remapping>>** appSpecificRemappings, const std::string &application, const std::string &originalKey, const std::string &remappedKey);
bool CheckForConflict(std::map<std::string, std::vector<Remapping>>* ptrToAppSpecificRemappings, const std::string& application, const std::string& targetKey);
// std::string GetRemappedKey(const std::string& application, const std::string& originalKey);


// Save and Load remappings.
void SaveRemappingsToFile(std::map<std::string, std::vector<Remapping>>** ptrToAppSpecificRemappings, const std::string& filename);
void LoadRemappingsFromFile(std::map<std::string, std::vector<Remapping>> **ptrToAppSpecificRemappings, const std::string &filename);

// Getter for KeyRemappings
std::map<std::string, std::vector<Remapping>> GetAllRemappings();

#endif