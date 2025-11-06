#pragma once
#include <iostream>
#include <string>
#include <windows.h>
class ConsoleManager
{
  public:
    enum class BorderStyle
    {
        Utf8,
        Ascii
    };
    static void Initialize(BorderStyle preferred = BorderStyle::Utf8)
    {
        setUTF8Mode();
        enableVirtualTerminal();

        std::cout << "[DEBUG] Output Codepage: " << GetConsoleOutputCP() << "\n";
        std::cout << "[DEBUG] Input Codepage: " << GetConsoleCP() << "\n";

        BorderStyle used = preferred;
        if (preferred == BorderStyle::Utf8 && !testUnicodeSupport())
        {
            std::cout << "[WARN] Unicode-Zeichen werden nicht korrekt dargestellt.\n";
            std::cout << "[INFO] Fallback auf ASCII aktiviert.\n";
            used = BorderStyle::Ascii;
        }

        activeStyle = used;
        printTestFrame();
    }
    static std::string TL()
    {
        return getChar("┌", "+");
    }
    static std::string TR()
    {
        return getChar("┐", "+");
    }
    static std::string BL()
    {
        return getChar("└", "+");
    }
    static std::string BR()
    {
        return getChar("┘", "+");
    }
    static std::string H()
    {
        return getChar("─", "-");
    }
    static std::string V()
    {
        return getChar("│", "|");
    }

  private:
    static inline auto activeStyle = BorderStyle::Ascii;
    static std::string getChar(const std::string& unicode, const std::string& ascii)
    {
        return (activeStyle == BorderStyle::Utf8) ? unicode : ascii;
    }
    static void setUTF8Mode()
    {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        std::ios_base::sync_with_stdio(false);
    }
    static void enableVirtualTerminal()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode))
        {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, mode);
        }
        std::cout << "[DEBUG] Current Console Mode: " << mode << "\n";
    }
    static bool testUnicodeSupport()
    {
        std::cout << "[DEBUG] Testausgabe: ┌─┐│└┘\n";
        std::cout << "Bitte prüfe visuell: Werden Box-Zeichen korrekt angezeigt (┌─┐│└┘)? [j/n]: ";
        char ans;
        std::cin >> ans;
        return (ans == 'j' || ans == 'J' || ans == 'y' || ans == 'Y');
    }
    static void printTestFrame()
    {
        std::string tl = TL(), tr = TR(), bl = BL(), br = BR(), h = H(), v = V();
        std::cout << "[DEBUG] Beispielrahmen:\n";
        std::cout << tl << h << h << h << tr << "\n";
        std::cout << v << "X" << "X" << "X" << v << "\n";
        std::cout << bl << h << h << h << br << "\n";
    }
};
