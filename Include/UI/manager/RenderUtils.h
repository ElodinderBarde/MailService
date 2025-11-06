#pragma once
#include "BL/classes/Mail.h"
#include "BL/data/Strings.h"
#include "UI/data/Theme.h"
#include <string>
namespace RenderUtils
{
void DrawLine(char left, int width, char fill, char right);
void DrawDoubleLine(char left, int w1, char f1, char mid, int w2, char f2, char right);
void DrawEmptyRow(const Strings& s, int leftWidth, int rightWidth);
void DrawTextRow(const Strings& s, int leftWidth, const std::string& leftText, const std::string& rightText,
                 const Theme& t = Theme());
void DrawListHeader();
void DrawMailRow(const Messerli::Mail& m);
void DrawSeparator();
void PrintConsoleModeDebug();
};
