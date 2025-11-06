#include "BL/Manager/Functions.h"
#include <iostream>
#include <windows.h>
int main()
{

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::ios_base::sync_with_stdio(false);

    UINT cp = GetConsoleOutputCP();
    std::cout << "[DEBUG] Output Codepage: " << cp << std::endl;

    Messerli::Functions::InitializeApp();
}
