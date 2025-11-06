#include "UI/draw/Render.h"
#include "BL/Manager/Functions.h"
#include "BL/classes/mail/Letter.h"
#include "BL/classes/mail/Package.h"
#include "BL/data/Strings.h"
#include "UI/data/Theme.h"
#include "UI/manager/RenderUtils.h"
#include "UI/manager/UI.h"
#include <iomanip>
#include <iostream>
#include <utility>
using namespace RenderUtils;
namespace UiRender
{
void Clear()
{
    std::cout << "\x1b[2J";
}
void PrintAtStart()
{
    std::cout << "\x1b[H";
}
void DrawBox(int x, int y, int width, int height, const std::string& title)
{
    Messerli::Functions::SetCursorPosition(x, y);
    std::cout << "+" << std::string(width - 2, '-') << "+\n";

    Messerli::Functions::SetCursorPosition(x, y + 1);
    std::cout << "| " << std::left << std::setw(width - 4) << title << " |\n";

    for (auto i = 0; i < height - 3; ++i)
    {
        Messerli::Functions::SetCursorPosition(x, y + 2 + i);
        std::cout << "|" << std::string(width - 2, ' ') << "|\n";
    }

    Messerli::Functions::SetCursorPosition(x, y + height - 1);
    std::cout << "+" << std::string(width - 2, '-') << "+\n";
}
static void DrawHeader(const Theme& t, const Strings& s)
{
    DrawDoubleLine(s.BorderTopLeft[0], LEFT_W, s.BorderHorizontal[0], s.BorderTT[0], INNER_W - LEFT_W - 1,
                   s.BorderHorizontal[0], s.BorderTopRight[0]);
    DrawTextRow(s, LEFT_W, t.title + s.Title + t.reset, t.title + s.TitleStatus + t.reset, t);
    DrawDoubleLine(s.BorderTLeft[0], LEFT_W, s.BorderHorizontal[0], s.BorderCross[0], INNER_W - LEFT_W - 1,
                   s.BorderHorizontal[0], s.BorderTRight[0]);
}
static void DrawFooter(const Theme& t, const Strings& s)
{
    std::string hint = s.OptionButton + " " + s.OptionNavigation + " " + s.OptionEnter + " " + s.OptionExit;

    DrawDoubleLine(s.BorderTLeft[0], LEFT_W, s.BorderHorizontal[0], s.BorderTB[0], INNER_W - LEFT_W - 1,
                   s.BorderHorizontal[0], s.BorderTRight[0]);

    DrawTextRow(s, INNER_W, hint, "", t);
    DrawLine(s.BorderBottomLeft[0], INNER_W, s.BorderHorizontal[0], s.BorderBottomRight[0]);
}
void DrawFrame(const Theme& t, const Strings& s)
{
    Clear();
    PrintAtStart();
    DrawHeader(t, s);
}
static void DrawMenuItem(int i, int idx, const Theme& t, const Strings& s, const std::string& text)
{
    bool sel = (i == idx);
    std::cout << s.BorderVertical[0] << " ";
    if (sel)
        std::cout << t.select << "> " << t.reset;
    else
        std::cout << "  ";
    std::cout << (sel ? t.select : t.menu) << std::left << std::setw(LEFT_W - 4) << text << t.reset
              << s.BorderVertical[0] << "\n";
}
void Redraw(int idx, const Theme& t, const Strings& s, const std::string& status, const Messerli::Letter* letter,
            const Messerli::Package* package, int height, View view_)
{
    if (view_ == View::MailManager)
    {
        RenderMailManagerMenu(s, view_);
    }
    else
    {

        std::cout << "[DEBUG] BorderTopLeft bytes: ";
        for (unsigned char c : s.BorderTopLeft)
        {
            std::cout << std::hex << std::showbase << static_cast<int>(c) << " ";
        }
        std::cout << std::dec << "\n";

        DrawFrame(t, s);
        const std::string menuItems[] = {s.MenuNewLetter, s.MenuNewPack, s.MenuShowMails, s.MenuSettings, s.MenuExit};
        constexpr int count = std::size(menuItems);
        for (auto i = 0; i < count; ++i)
        {
            DrawMenuItem(i, idx, t, s, menuItems[i]);
        }

        DrawTextRow(s, LEFT_W, "", "", t);

        for (auto i = 0; i < height; ++i)
        {
            DrawEmptyRow(s, LEFT_W, INNER_W - LEFT_W - 1);
        }

        DrawFooter(t, s);

        PrintConsoleModeDebug();
    }
}
static void DrawDetailPanel(const Theme& t, const Strings& s, const std::string& title, const std::string* fields,
                            const std::string* values, int count)
{
    Clear();
    PrintAtStart();

    DrawDoubleLine(s.BorderTopLeft[0], LEFT_W, s.BorderHorizontal[0], s.BorderTT[0], INNER_W - LEFT_W - 1,
                   s.BorderHorizontal[0], s.BorderTopRight[0]);

    DrawTextRow(s, LEFT_W, "", title, t);

    DrawDoubleLine(s.BorderTLeft[0], LEFT_W, s.BorderHorizontal[0], s.BorderCross[0], INNER_W - LEFT_W - 1,
                   s.BorderHorizontal[0], s.BorderTRight[0]);

    for (auto i = 0; i < count; ++i)
    {
        DrawTextRow(s, LEFT_W, "", fields[i] + " " + values[i], t);
    }

    DrawDoubleLine(s.BorderBottomLeft[0], LEFT_W, s.BorderHorizontal[0], s.BorderTB[0], INNER_W - LEFT_W - 1,
                   s.BorderHorizontal[0], s.BorderBottomRight[0]);
}
void UiRender::DrawMenu(const std::string* options, int count, const Theme& t, const Strings& s)
{
    std::cout << "\n";
    for (auto i = 0; i < count; ++i)
    {
        std::cout << " " << std::setw(2) << i + 1 << ". " << options[i] << "\n";
    }
}
void DrawRightPanelInteractive(const Theme& t, const Strings& s, const std::string& title, const std::string fields[],
                               const std::string values[], int fieldCount)
{
    Clear();
    PrintAtStart();

    DrawDoubleLine(s.BorderTopLeft[0], LEFT_W, s.BorderHorizontal[0], s.BorderTT[0], INNER_W - LEFT_W - 1,
                   s.BorderHorizontal[0], s.BorderTopRight[0]);

    DrawTextRow(s, LEFT_W, "", title, t);

    DrawDoubleLine(s.BorderTLeft[0], LEFT_W, s.BorderHorizontal[0], s.BorderCross[0], INNER_W - LEFT_W - 1,
                   s.BorderHorizontal[0], s.BorderTRight[0]);

    for (auto i = 0; i < fieldCount; ++i)
    {
        DrawTextRow(s, LEFT_W, "", fields[i] + " " + values[i], t);
    }

    DrawDoubleLine(s.BorderBottomLeft[0], LEFT_W, s.BorderHorizontal[0], s.BorderTB[0], INNER_W - LEFT_W - 1,
                   s.BorderHorizontal[0], s.BorderBottomRight[0]);
}
void ShowAllMailsInteractive(const Theme& t, const Strings& s, const Messerli::Letter letters[], int lCount,
                             const Messerli::Package packages[], const int pCount, const int sel)
{
    const int total = lCount + pCount;
    if (total == 0)
    {
        Redraw(sel, t, s, "Keine gespeicherten Sendungen.", nullptr, nullptr, 10);
        Messerli::Functions::WaitABit();
        return;
    }

    auto idx = 0;
    auto inList = true;

    while (inList)
    {
        DrawFrame(t, s);

        const std::string menuItems[] = {s.MenuNewLetter, s.MenuNewPack, s.MenuShowMails, s.MenuSettings, s.MenuExit};
        constexpr int countMenu = std::size(menuItems);
        for (auto i = 0; i < countMenu; ++i)
        {
            DrawMenuItem(i, sel, t, s, menuItems[i]);
        }

        std::cout << s.BorderVertical[0] << std::string(LEFT_W, ' ') << s.BorderVertical[0] << t.title
                  << " Gespeicherte Sendungen:" << t.reset << "\n";

        constexpr auto visible = 8;
        int start = std::max(0, idx - visible / 2);
        int end = std::min(total, start + visible);

        for (int i = start; i < end; ++i)
        {
            bool selected = (i == idx);
            bool isLetter = (i < lCount);
            std::cout << s.BorderVertical[0] << std::string(LEFT_W, ' ') << s.BorderVertical[0]
                      << (selected ? t.select : t.menu);

            if (isLetter)
            {
                const auto& l = letters[i];
                std::string delivered = l.M_Delivered() ? "\x1b[32mZugestellt\x1b[0m" : "\x1b[33mAusstehend\x1b[0m";

                std::cout << (selected ? "> " : "  ") << std::setw(15) << delivered
                          << ": "
                             "ID: "
                          << l.M_Id() << ", Typ: Brief, Empfänger: " << l.M_AdressTo().M_Person().M_Firstname() << " "
                          << l.M_AdressTo().M_Person().M_Lastname();
            }
            else
            {

                const auto& p = packages[i - lCount];
                std::string delivered = p.M_Delivered() ? "\x1b[32mZugestellt\x1b[0m" : "\x1b[33mAusstehend\x1b[0m";

                std::cout << (selected ? "> " : "  ") << std::setw(15) << delivered << ": " << "ID: " << p.M_Id()
                          << ", Typ: Paket, Empfänger: " << p.M_AdressTo().M_Person().M_Firstname() << " "
                          << p.M_AdressTo().M_Person().M_Lastname();
            }

            std::cout << t.reset << "\n";
        }

        for (int i = end; i < start + visible; ++i)
        {
            std::cout << s.BorderVertical[0] << std::string(LEFT_W, L' ') << s.BorderVertical[0] << "\n";
        }

        DrawFooter(t, s);

#ifdef _WIN32
        int key = _getwch();
#else
        int key = getchar();
#endif

        if (key == 224)
        {
#ifdef _WIN32
            int k = _getwch();
#else
            int k = getchar();
#endif
            if (k == 72 && idx > 0)
                --idx;
            else if (k == 80 && idx < total - 1)
                ++idx;
        }
        else if (std::cmp_equal(key, L'\r'))
        {
            bool isLetter = (idx < lCount);
            std::string delivered;
            if (isLetter)
            {
                const auto& l = letters[idx];
                constexpr auto count = 17;

                if (l.M_Delivered())
                {
                    delivered = "Zugestellt";
                }
                else
                {
                    delivered = "Zustellung ausstehend";
                }

                std::string f[count] = {s.InfoReceiver,
                                        s.InfoFirstName,
                                        s.InfoLastName,
                                        s.InfoStreet,
                                        s.InfoHouseNumber,
                                        s.InfoPostalCode,
                                        s.InfoCountry,
                                        s.InfoSender,
                                        s.InfoFirstName,
                                        s.InfoLastName,
                                        s.InfoStreet,
                                        s.InfoHouseNumber,
                                        s.InfoPostalCode,
                                        s.InfoCountry,
                                        s.InfoLetterPriority,
                                        s.InfoLetterType,
                                        ""};
                std::string v[count] = {"",
                                        l.M_AdressTo().M_Person().M_Firstname(),
                                        l.M_AdressTo().M_Person().M_Lastname(),
                                        l.M_AdressTo().M_Streetname(),
                                        l.M_AdressTo().M_Housenumber(),
                                        std::to_string(l.M_AdressTo().M_PostalCode()),
                                        l.M_AdressTo().M_Country(),
                                        "",
                                        l.M_AdressFrom().M_Person().M_Firstname(),
                                        l.M_AdressFrom().M_Person().M_Lastname(),
                                        l.M_AdressFrom().M_Streetname(),
                                        l.M_AdressFrom().M_Housenumber(),
                                        std::to_string(l.M_AdressFrom().M_PostalCode()),
                                        l.M_AdressFrom().M_Country(),
                                        std::string(1, l.M_Priority()),
                                        l.M_LetterSize(),
                                        delivered};

                DrawDetailPanel(t, s, "Briefdetails", f, v, count);
            }
            else
            {

                const auto& p = packages[idx - lCount];
                constexpr auto count = 16;

                if (p.M_Delivered())
                {
                    delivered = "Zugestellt";
                }
                else
                {
                    delivered = "Zustellung ausstehend";
                }

                const std::string f[count] = {s.InfoReceiver,    s.InfoFirstName,  s.InfoLastName, s.InfoStreet,
                                              s.InfoHouseNumber, s.InfoPostalCode, s.InfoCountry,  s.InfoSender,
                                              s.InfoFirstName,   s.InfoLastName,   s.InfoStreet,   s.InfoHouseNumber,
                                              s.InfoPostalCode,  s.InfoCountry,    s.InfoWeight,   ""};
                const std::string v[count] = {"",
                                              p.M_AdressTo().M_Person().M_Firstname(),
                                              p.M_AdressTo().M_Person().M_Lastname(),
                                              p.M_AdressTo().M_Streetname(),
                                              p.M_AdressTo().M_Housenumber(),
                                              std::to_string(p.M_AdressTo().M_PostalCode()),
                                              p.M_AdressTo().M_Country(),
                                              "",
                                              p.M_AdressFrom().M_Person().M_Firstname(),
                                              p.M_AdressFrom().M_Person().M_Lastname(),
                                              p.M_AdressFrom().M_Streetname(),
                                              p.M_AdressFrom().M_Housenumber(),
                                              std::to_string(p.M_AdressFrom().M_PostalCode()),
                                              p.M_AdressFrom().M_Country(),
                                              std::to_string(p.M_WeightInKg()),
                                              delivered};
                DrawDetailPanel(t, s, "Paketdetails", f, v, count);
            }
            Messerli::Functions::WaitABitLonger();
        }
        else if (key == L'q' || key == L'Q')
        {
            inList = false;
        }
    }
}
void ShowThemeSelectionInteractive(int sel, const Theme& t, Strings& s)
{
    const std::string opts[5] = {"ASCII", "BOX", "DOUBLE", "LIGHT", "SIMPLE"};
    auto idx = 0;
    auto selecting = true;
    constexpr auto count = 5;
    constexpr auto spacing = 4;
    constexpr int height = count + spacing;

    while (selecting)
    {
        Redraw(sel, t, s, "Design auswählen", nullptr, nullptr, height);
        int startX = LEFT_W + 4;
        auto startY = 5;

        Messerli::Functions::SetCursorPosition(startX, startY);
        std::cout << t.select << "Gespeicherte Designs:" << t.reset;

        for (auto i = 0; i < count; ++i)
        {
            Messerli::Functions::SetCursorPosition(startX, startY + 2 + i);
            std::cout << (i == idx ? t.select + "> " + opts[i] + t.reset : t.menu + "  " + opts[i] + t.reset);
        }

#ifdef _WIN32
        int key = _getwch();
#else
        int key = getchar();
#endif

        if (key == 224)
        {
#ifdef _WIN32
            int k = _getwch();
#else
            int k = getchar();
#endif
            if (k == 72 && idx > 0)
                --idx;
            else if (k == 80 && idx < count - 1)
                ++idx;
        }
        else if (key == L'\r')
        {
            switch (idx)
            {
            case 0:
                s.ApplyDesign(DesignSet::ASCII);
                break;
            case 1:
                s.ApplyDesign(DesignSet::BOX);
                break;
            case 2:
                s.ApplyDesign(DesignSet::DOUBLE);
                break;
            case 3:
                s.ApplyDesign(DesignSet::LIGHT);
                break;
            case 4:
                s.ApplyDesign(DesignSet::SIMPLE);
                break;
            }
            Redraw(sel, t, s, "Design geändert!", nullptr, nullptr, height);
            Messerli::Functions::WaitABit();
            selecting = false;
        }
        else if (key == L'q' || key == L'Q')
        {
            selecting = false;
        }
    }
}
void RenderMailManagerMenu(const Strings& strings_, View& view_)
{

    DrawLine('+', INNER_W, '-', '+');
    std::cout << strings_.MailManagrLetters;
    std::cout << strings_.MailManagrPackages;
    std::cout << strings_.MailManagrShowAll;
    std::cout << strings_.MailManagrGoBack;
    std::cout << strings_.OptionDelivered;
    DrawLine('+', INNER_W, '-', '+');
}
void UiRender::ShowLetters(const Theme& t, const Strings& s, const Messerli::Letter* letters, int count)
{
    DrawBox(2, 2, 40, 15, "Briefe");
    for (auto i = 0; i < count; ++i)
    {
        std::cout << "ID: " << letters[i].M_Id() << "  Empf: " << letters[i].M_AdressTo().M_Person().M_Firstname()
                  << " " << letters[i].M_AdressTo().M_Person().M_Lastname() << "\n";
    }
}
void UiRender::ShowPackages(const Theme& t, const Strings& s, const Messerli::Package* packages, int count)
{
    DrawBox(2, 2, 40, 15, "Pakete");
    for (auto i = 0; i < count; ++i)
    {
        std::cout << "ID: " << packages[i].M_Id() << "  Empf: " << packages[i].M_AdressTo().M_Person().M_Firstname()
                  << " " << packages[i].M_AdressTo().M_Person().M_Lastname() << "  (" << packages[i].M_WeightInKg()
                  << " kg)\n";
    }
}
}
