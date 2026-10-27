# Windows Keyboard Hook Demonstration

A small C++/Win32 example showing how a low-level keyboard hook receives keyboard events and how Windows can translate key presses into characters.

## What the source does

[`index.cpp`](./index.cpp) installs a `WH_KEYBOARD_LL` hook and processes key-down events. It writes translated characters and a few labels for special keys (such as Enter, Tab, and Backspace) to standard output. Modifier keys are not printed by themselves.

The hook is system-wide: it can observe keyboard input while other applications are in use. The program does not identify the active window or limit collection to a particular application. It writes output to the console; the source does not include file logging, network transmission, or persistence.

## Limitations

- Character translation depends on the active Windows keyboard state and layout.
- This is a minimal demonstration, not a complete text-input or keyboard-layout implementation.
- It does not provide application-level scoping, input filtering, or a consent prompt.

## Safety and privacy

Keyboard input can contain passwords, messages, and other sensitive information. Use this example only in a controlled environment on a device you own or are authorized to test, with everyone affected informed and consenting. Do not use it to monitor other people or capture real credentials or private data.

This project is intended for learning about Win32 keyboard hooks, not for covert monitoring or production use.

## Project contents

- `index.cpp` — Win32 keyboard-hook demonstration.
