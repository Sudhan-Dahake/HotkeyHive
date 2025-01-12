#ifndef KEY_REMAPPER_H
#define KEY_REMAPPER_H

#include <string>
#include <map>

// Function declarations for key remapping.
void AddKeyRemapping(const std::string& originalKey, const std::string& remappedKey);
bool CheckForConflict(const std::string& targetKey);
std::string GetRemappedKey(const std::string& originalKey);


// Save and Load remappings.
void SaveRemappingsToFile(const std::string& filename);
void LoadRemappingsFromFile(const std::string &filename);

// Getter for KeyRemappings
std::map<std::string, std::string> &GetAllRemappings();

#endif