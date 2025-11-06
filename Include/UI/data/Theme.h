#pragma once
#include <iostream>
#include <string>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#endif
struct Theme
{
    std::string title;
    std::string menu;
    std::string select;
    std::string status;
    std::string reset;
};
// C64-Style (blau/weiß/gelb)
inline const Theme THEME_C64{
    "\x1b[44;97m", // Hintergrund Blau, Text Weiß
    "\x1b[94m",    // Menü: Hellblau
    "\x1b[93m",    // Auswahl: Gelb
    "\x1b[97m",    // Status: Weiß
    "\x1b[0m"      // Reset
};
// Fallback ohne Farben
inline const Theme THEME_MONO{"", "", "", "", ""};
// --- NEU ---
inline void EnableVTColors()
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_TEXT);
    SetConsoleOutputCP(CP_UTF8);

    // VT aktivieren
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE)
    {
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode))
        {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT;
            SetConsoleMode(hOut, mode);
        }
    }
#endif
}
