#include "key_utils.h"

std::string GetReadableKeyName(DWORD vkCode) {
    if (vkCode >= 'A' && vkCode <= 'Z') return std::string(1, char(vkCode));

    switch (vkCode) {
        case VK_RETURN: return "Enter";
        case VK_SPACE: return "Space";
        case VK_ESCAPE: return "Escape";
        case VK_TAB: return "Tab";
        case VK_CONTROL: return "Ctrl";
        case VK_LCONTROL: return "Left Ctrl";
        case VK_RCONTROL: return "Right Ctrl";
        case VK_SHIFT: return "Shift";
        case VK_MENU: return "Alt";
        case VK_LMENU: return "Left Alt";
        case VK_RMENU: return "Right Alt";
        case VK_BACK: return "Backspace";
        case VK_DELETE: return "Delete";

        default: return "key(" + std::to_string(vkCode) + ")";
    };
};


// This function detects full key combinations and not just individual key presses.
std::string GetKeyCombination(KBDLLHOOKSTRUCT* kbStruct) {
    std::string keyCombo;

    // Checking for modifier keys
    if (GetAsyncKeyState(VK_CONTROL) & 0x8000) keyCombo += "Ctrl+";
    if (GetAsyncKeyState(VK_SHIFT) & 0x8000)   keyCombo += "Shift+";
    if (GetAsyncKeyState(VK_MENU) & 0x8000)    keyCombo += "Alt+";

    // Append the main key.
    keyCombo += GetReadableKeyName(kbStruct->vkCode);

    return keyCombo;
};