#include "UI/manager/MailManagerUI.h"
#include "UI/data/LayoutSize.h"
#include "UI/draw/Render.h"
#include <conio.h>
void MailManagerUI::ShowMailManagerMenu(const Theme& t, const Strings& s, Messerli::MailManager& manager)
{
    auto running = true;
    auto selected = 0;
    std::string options[4] = {s.MailManagrLetters, s.MailManagrPackages, s.MailManagrShowAll, s.MailManagrGoBack};

    while (running)
    {
        UiRender::DrawBox(LayoutSize::BOX_LEFT_X, LayoutSize::BOX_TOP_Y, LayoutSize::BOX_WIDTH, LayoutSize::BOX_HEIGHT,
                          "Mail-Manager");
        UiRender::DrawMenu(options, 4, t, s);
        UiRender::DrawBox(LayoutSize::BOX_RIGHT_X, LayoutSize::BOX_TOP_Y, LayoutSize::BOX_WIDTH, LayoutSize::BOX_HEIGHT,
                          "Gespeicherte Sendungen");

        switch (selected)
        {
        case 0:
            manager.RenderLetters(s);
            break;
        case 1:
            manager.RenderPackages(s);
            break;
        case 2:
            manager.RenderAll(s);
            break;
        default:
            break;
        }

        int key = _getwch();
        switch (key)
        {
        case 'w':
        case 'W':
        case 72:
            selected = (selected - 1 + 4) % 4;
            break;
        case 's':
        case 'S':
        case 80:
            selected = (selected + 1) % 4;
            break;
        case '\r':
            if (selected == 3)
                running = false;
            break;
        case 'q':
        case 'Q':
            running = false;
            break;
        }
    }
}
