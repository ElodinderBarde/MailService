#include "BL/data/Strings.h"
#include "UI/data/Theme.h"
#include "UI/draw/Render.h"
#include <iomanip>
#include <iostream>
namespace RenderUtils
{
void DrawLine(char left, int width, char fill, char right)
{
    std::cout << left << std::string(width, fill) << right << "\n";
}
void DrawDoubleLine(char left, int w1, char f1, char mid, int w2, char f2, char right)
{
    std::cout << left << std::string(w1, f1) << mid << std::string(w2, f2) << right << "\n";
}
void DrawEmptyRow(const Strings& s, int leftWidth, int rightWidth)
{
    std::cout << s . BorderVertical[0] << std::setw(leftWidth) << " " << s . BorderVertical[0] << std::setw(rightWidth)
        << " " << s . BorderVertical[0] << "\n";
}
void DrawTextRow(const Strings& s, int leftWidth, const std::string& leftText, const std::string& rightText,
                 const Theme& t)
{
    std::cout << s . BorderVertical[0] << std::left << std::setw(leftWidth) << leftText << s . BorderVertical[0] << t .
        menu << std::left << std::setw(UiRender::INNER_W - leftWidth - 1) << rightText << t . reset << s .
        BorderVertical[0] << "\n";
}
void PrintConsoleModeDebug()
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode))
    {
        std::wcerr << "\n[DEBUG] GetConsoleMode failed with error " << GetLastError() << "\n";
        return;
    }

    // Neue Zeile unterhalb des Rahmens
    std::cout << "\n\n[DEBUG] Current Windows Console Mode: " << mode << "\n";

    if (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)
        std::cout << "  -> ENABLE_VIRTUAL_TERMINAL_PROCESSING ✅\n";
    if (mode & ENABLE_PROCESSED_OUTPUT)
        std::cout << "  -> ENABLE_PROCESSED_OUTPUT ✅\n";
    if (mode & ENABLE_WRAP_AT_EOL_OUTPUT)
        std::cout << "  -> ENABLE_WRAP_AT_EOL_OUTPUT ✅\n";
    if (mode & ENABLE_VIRTUAL_TERMINAL_INPUT)
        std::cout << "  -> ENABLE_VIRTUAL_TERMINAL_INPUT ✅\n";

    std::cout . flush();
#else
    struct termios t; if (tcgetattr(STDOUT_FILENO, &t) == -1)
    {
        std::wcerr << "\n[DEBUG] tcgetattr() failed\n";
        return;
    } std::cout << "\n\n[DEBUG] Linux/Unix terminal flags: " << t . c_lflag << "\n"; if (t . c_lflag & ECHO)
        std::cout << "  -> ECHO enabled ✅\n"; if (t . c_lflag & ICANON)
        std::cout << "  -> ICANON enabled ✅\n"; if (t . c_lflag & ISIG)
        std::cout << "  -> ISIG enabled ✅\n"; std::cout . flush();
#endif
}
}
