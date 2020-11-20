#include "ui/menu/intro/intro_menu.h"

#ifdef _WIN32
#include <windows.h>
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

/**
 * Enable Windows 10 terminal support for ANSI escape codes
 * @return enabling success
 */
int enableVTProcessing(){
#ifdef _WIN32
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return GetLastError();
    }
#endif
    return 0;
}

/**
 * Create a blank store to be displayed in the UI. Show the UI.
 * @return code execution error
 */
int main() {
    enableVTProcessing();
    Store s;
    IntroMenu menu(s);
    menu.show();
}
