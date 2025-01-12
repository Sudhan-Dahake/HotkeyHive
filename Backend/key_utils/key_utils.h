// Defining helper functions like GetReadableKeyName and GetKeyCombination
#ifndef KEY_UTILS_H
#define KEY_UTILS_H

#include <string>
#include <windows.h>

std::string GetReadableKeyName(DWORD vkCode);
std::string GetKeyCombination(KBDLLHOOKSTRUCT *kbStruct);

#endif