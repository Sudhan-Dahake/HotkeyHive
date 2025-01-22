#ifndef KEYBOARD_HOOK_H
#define KEYBOARD_HOOK_H

#include <Windows.h>
#include <iostream>
#include <atomic>

// This is the hook handle and exit flag.
extern HHOOK keyboardHook;
extern bool exitProgram;

// These are the function declarations.
LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
void InstallKeyboardHook(std::atomic<bool>* ptrToHookRunningLocalVar);
void RemoveKeyboardHook();

#endif