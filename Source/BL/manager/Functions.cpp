#include "BL/Manager/Functions.h"
#include "UI/manager/ConsoleManager.h"
#include "UI/manager/RenderUtils.h"
#include "UI/manager/UI.h"
#include <corecrt_io.h>
#include <fcntl.h>
#include <iostream>
namespace Messerli
{
void Functions::WaitABit()
{
    Sleep(500);
}
void Functions::WaitABitLonger()
{
    Sleep(10000);
}
void Functions::InitializeApp()
{
#ifdef _WIN32
    // UTF-8 Console Setup
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_TEXT);

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

    std::cout << "[DEBUG] UTF-8 aktiv!\n";
    std::cout << "┌────────────┐\n";
    std::cout << "│  Menü      │\n";
    std::cout << "└────────────┘\n";
    std::cout << "\xE2\x94\x8C\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2"
                 "\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x90\n";
    std::cout << "\xE2\x94\x82  Men\xC3\xBC      \xE2\x94\x82\n";
    std::cout << "\xE2\x94\x94\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2"
                 "\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x98\n";

    RenderUtils::PrintConsoleModeDebug();
    UI ui;
    ui.Run();
}
void Functions::SetCursorPosition(int x, int y)
{
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
}
