#pragma once
#include "BL/Manager/Functions.h"
#include "BL/classes/mail/Letter.h"
#include "BL/classes/mail/Package.h"
#include "BL/manager/MailManager.h"
#include "UI/data/Theme.h"
enum class View
{
    MainMenu,
    CreateLetter,
    CreatePackage,
    List,
    Details,
    Track,
    Settings,
    RightPanelActive,
    ShowAllMails,
    MailManager
};
class UI
{
  public:
    UI();
    void Run();
    static constexpr auto MAX_MAILS = 10;
    Messerli::Letter letters_[MAX_MAILS];
    Messerli::Package packages_[MAX_MAILS];
    int letterCount_ = 0;
    int packageCount_ = 0;
    Messerli::Letter currentLetter_;
    bool hasCurrentLetter_ = false;
    Messerli::Package currentPackage_;
    bool hasCurrentPackage_ = false;

  private:
    bool running_ = true;
    int selectedIndex_ = 0;
    View view_ = View::MainMenu;
    Strings strings_;
    Theme theme_ = THEME_C64;
    Messerli::Functions functions_;
    void HandleKey(int key);
    void HandleSelect();
    void Redraw() const;
    Messerli::MailManager manager;
};
