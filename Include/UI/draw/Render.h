#pragma once
#include "BL/classes/mail/Letter.h"
#include "BL/classes/mail/Package.h"
#include "BL/data/Strings.h"
#include "UI/data/Theme.h"
#include "UI/manager/RenderUtils.h"
#include "UI/manager/UI.h"
#include <string>
using namespace RenderUtils;
namespace UiRender
{
constexpr auto LEFT_W = 34;
constexpr auto WIDTH = 100;
constexpr int INNER_W = WIDTH - 2;
void Clear();
void PrintAtStart();
void DrawFrame(const Theme& t, const Strings& s);
void DrawMenu(const std::string options[], int selectedIndex, const Theme& t, const Strings& s);
void Redraw(int selectedIndex, const Theme& t, const Strings& s, const std::string& statusTitle,
            const Messerli::Letter* letter = nullptr, const Messerli::Package* package = nullptr,
            int rightPanelHeight = 10, View view_ = View::MainMenu);
void DrawRightPanelInteractive(const Theme& t, const Strings& s, const std::string& title, const std::string fields[],
                               const std::string values[], int fieldCount);
void DrawStatusPanel(const Theme& t, const Strings& s, const std::string& statusTitle,
                     const Messerli::Letter* letter = nullptr, const Messerli::Package* package = nullptr);
void ShowAllMailsInteractive(const Theme& t, const Strings& s, const Messerli::Letter letters[], int letterCount,
                             const Messerli::Package packages[], int packageCount, int selectedIndex);
void ShowThemeSelectionInteractive(int selectedIndex, const Theme& theme, Strings& strings);
void RenderMailManagerMenu(const Strings& strings_, View& view_);
void ShowLetters(const Theme&, const Strings&, const Messerli::Letter*, int);
void ShowPackages(const Theme&, const Strings&, const Messerli::Package*, int);
void DrawBox(int x, int y, int width, int height, const std::string& title);
}
