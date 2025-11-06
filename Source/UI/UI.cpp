#include "UI/manager/UI.h"
#include "BL/Manager/Functions.h"
#include "BL/classes/adress/Adress.h"
#include "BL/classes/adress/Person.h"
#include "BL/classes/mail/Letter.h"
#include "BL/classes/mail/Package.h"
#include "BL/data/Strings.h"
#include "BL/manager/MailManager.h"
#include "UI/data/Theme.h"
#include "UI/draw/Render.h"
#include "UI/manager/Input.h"
#include "UI/manager/MailManagerUI.h"
#include <iostream>
#ifdef _WIN32
#include <conio.h>
#endif
UI::UI()
    : letterCount_(0), packageCount_(0), running_(true), selectedIndex_(0), view_(View::MainMenu),
      manager() // Konstruktor des MailManagers
{
    EnableVTColors();
    strings_.ApplyDesign(DesignSet::ASCII);

    Messerli::Person empfaenger1("Roberto", "Marchese", PersonType::empfaenger);
    Messerli::Adress adrEmpf1(empfaenger1, "Bahnhofstrasse", "10", 8001, "Schweiz");

    Messerli::Person absender1("Max", "Müller", PersonType::absender);
    Messerli::Adress adrAbs1(absender1, "Hauptstrasse", "22", 3000, "Schweiz");

    Messerli::Letter letter1;
    letter1.SetM_AdressFrom(adrAbs1);
    letter1.SetM_AdressTo(adrEmpf1);
    letter1.SetM_Id(101);
    letter1.SetM_Priority(L'A');
    letter1.SetM_LetterSize("A4");
    letter1.SetM_Delivered(false);

    for (auto i = 0; i < 3; ++i)
    {
        Messerli::Letter copy = letter1;
        copy.SetM_Id(101 + i);
        copy.SetM_AdressTo(Messerli::Adress(
            Messerli::Person("Empf" + std::to_string(i), "Nach" + std::to_string(i), PersonType::empfaenger),
            "Strasse" + std::to_string(i), "1" + std::to_string(i), 4000 + i, "Schweiz"));
        letters_[letterCount_++] = copy;
    }

    // Pakete
    Messerli::Person empfaenger2("Luca", "Testero", PersonType::empfaenger);
    Messerli::Adress adrEmpf2(empfaenger2, "Via Roma", "23", 10100, "Italien");

    Messerli::Person absender2("Anna", "Beispiel", PersonType::absender);
    Messerli::Adress adrAbs2(absender2, "Seestrasse", "7", 6000, "Schweiz");

    Messerli::Package pack1;
    pack1.SetM_AdressFrom(adrAbs2);
    pack1.SetM_AdressTo(adrEmpf2);
    pack1.SetM_Id(202);
    pack1.SetM_WeightInKg(2.5);
    pack1.SetM_PackageSize("30 x 20 x 15 cm");
    pack1.SetM_Delivered(false);

    for (auto i = 0; i < 2; ++i)
    {
        Messerli::Package copy = pack1;
        copy.SetM_Id(202 + i);
        copy.SetM_AdressTo(Messerli::Adress(
            Messerli::Person("PaketEmpf" + std::to_string(i), "Nach" + std::to_string(i), PersonType::empfaenger),
            "Paketweg" + std::to_string(i), "9" + std::to_string(i), 5000 + i, "Schweiz"));
        packages_[packageCount_++] = copy;
    }

    Messerli::Person absender5("Max", "Mustermann", PersonType::absender);
    Messerli::Person empfaenger5("Erika", "Musterfrau", PersonType::empfaenger);

    Messerli::Adress adrAbs5(absender1, "Bahnhofstrasse", "10A", 8000, "Schweiz");
    Messerli::Adress adrEmpf5(empfaenger1, "Hauptstrasse", "22B", 4000, "Schweiz");

    // Brief A4 - Priorität A
    Messerli::Letter briefA("A4", 'A');
    briefA.SetM_Id(101);
    briefA.SetM_AdressFrom(adrAbs1);
    briefA.SetM_AdressTo(adrEmpf1);
    briefA.SetM_Delivered(true);
    letters_[letterCount_++] = briefA;

    // Brief A4 - Priorität B
    Messerli::Person empfaenger6("Lara", "Beispiel", PersonType::empfaenger);
    Messerli::Adress adrEmpf6(empfaenger2, "Seestrasse", "5", 6005, "Schweiz");

    Messerli::Letter briefB("A4", 'B');
    briefB.SetM_Id(102);
    briefB.SetM_AdressFrom(adrAbs1);
    briefB.SetM_AdressTo(adrEmpf2);
    briefB.SetM_Delivered(false);
    letters_[letterCount_++] = briefB;

    // Brief A3 - Priorität A
    Messerli::Person empfaenger3("Jonas", "Keller", PersonType::empfaenger);
    Messerli::Adress adrEmpf3(empfaenger3, "Gartenweg", "12", 7000, "Schweiz");

    Messerli::Letter briefC("A3", 'A');
    briefC.SetM_Id(103);
    briefC.SetM_AdressFrom(adrAbs1);
    briefC.SetM_AdressTo(adrEmpf3);
    briefC.SetM_Delivered(false);
    letters_[letterCount_++] = briefC;

    //
    // --- 📦 PAKETE ---
    //

    // 🧍 Absender / Empfänger 2
    Messerli::Person absender4("Anna", "Beispiel", PersonType::absender);
    Messerli::Person empfaenger4("Marco", "Testini", PersonType::empfaenger);

    Messerli::Adress adrAbs4(absender2, "Industriestrasse", "33", 9000, "Schweiz");
    Messerli::Adress adrEmpf4(empfaenger4, "Via Roma", "8", 10100, "Italien");

    // Paket A
    Messerli::Package paketA("50 x 30 x 20 cm", 0.5);
    paketA.SetM_Id(202);
    paketA.SetM_AdressFrom(adrAbs2);
    paketA.SetM_AdressTo(adrEmpf4);
    paketA.SetM_Delivered(true);
    packages_[packageCount_++] = paketA;

    // Paket B
    Messerli::Person empfaenger7("Chiara", "Bianchi", PersonType::empfaenger);
    Messerli::Adress adrEmpf7(empfaenger5, "Via Lago", "17", 6900, "Schweiz");

    Messerli::Package paketB("60 x 40 x 25 cm", 1.5);
    paketB.SetM_Id(203);
    paketB.SetM_AdressFrom(adrAbs2);
    paketB.SetM_AdressTo(adrEmpf5);
    paketB.SetM_Delivered(false);
    packages_[packageCount_++] = paketB;

    std::cout << "[DEBUG] Dummy-Daten initialisiert: " << letterCount_ << " Briefe, " << packageCount_ << " Pakete."
              << std::endl;

    for (auto i = 0; i < letterCount_; ++i)
    {
        manager.AddLetter(letters_[i]);
    }

    for (auto i = 0; i < packageCount_; ++i)
    {
        manager.AddPackage(packages_[i]);
    }
}
void UI::Run()
{
    while (running_)
    {
        Redraw();
#ifdef _WIN32
        int key = _getwch();
#else
        int key = getchar();
#endif
        HandleKey(key);
    }
}
void UI::HandleKey(const int key)
{
#ifdef _WIN32
    if (key == 224)
    {
        int k = _getwch();
        if (k == 72 && selectedIndex_ > 0)
            --selectedIndex_;
        else if (k == 80 && selectedIndex_ < 5)
            ++selectedIndex_;
        return;
    }
#endif

    // 1️⃣ Prüfen: Sind wir im MailManager?
    if (view_ == View::MailManager)
    {
        switch (key)
        {
        case L'1':
            UiRender::ShowLetters(theme_, strings_, letters_, letterCount_);
            break;
        case L'2':
            UiRender::ShowPackages(theme_, strings_, packages_, packageCount_);
            break;
        case L'3':
            MailManagerUI::ShowMailManagerMenu(theme_, strings_, manager);
            break;
        case L'4': // zurück
            view_ = View::MainMenu;
            break;
        case L'd':
        case L'D':
            Messerli::MailManager::ToggleDelivered(letters_, letterCount_, packages_, packageCount_);
            break;
        case L'q':
        case L'Q':
            view_ = View::MainMenu;
            break;
        default:
            break;
        }
        return;
    }

    switch (key)
    {
    case L'1':
        selectedIndex_ = 0;
        break;
    case L'2':
        selectedIndex_ = 1;
        break;
    case L'3':
        selectedIndex_ = 2;
        break;
    case L'4':
        selectedIndex_ = 3;
        break;
    case L'5':
        selectedIndex_ = 4;
        break;
    case L'6':
        selectedIndex_ = 5;
        break;

    case L'\r':
        HandleSelect();
        break;

    case L'q':
    case L'Q':
        if (view_ == View::RightPanelActive)
            view_ = View::MainMenu;
        else
            running_ = false;
        break;

    default:
        break;
    }
}
void UI::HandleSelect()
{

    switch (selectedIndex_)
    {
    case 0: {
        if (letterCount_ >= MAX_MAILS)
        {
            UiRender::Redraw(selectedIndex_, theme_, strings_, "Speicher voll – kein neuer Brief möglich!");
            Messerli::Functions::WaitABit();
            break;
        }

        view_ = View::RightPanelActive;
        UiRender::Redraw(selectedIndex_, theme_, strings_, "Erstelle neuen Brief...");

        Messerli::Letter letter = Messerli::Input::InputLetter(theme_, strings_);

        letters_[letterCount_++] = letter;
        currentLetter_ = letter;
        hasCurrentLetter_ = true;

        strings_.TitleStatus = strings_.TitleStatusLetters;

        UiRender::Redraw(selectedIndex_, theme_, strings_, strings_.TitleStatus, &currentLetter_);
        Messerli::Functions::WaitABit();
        break;
    }

    case 1: {
        if (packageCount_ >= MAX_MAILS)
        {
            UiRender::Redraw(selectedIndex_, theme_, strings_, "Speicher voll – kein neues Paket möglich!");
            Messerli::Functions::WaitABit();
            break;
        }

        view_ = View::RightPanelActive;
        UiRender::Redraw(selectedIndex_, theme_, strings_, "Erstelle neues Paket...");

        Messerli::Package package = Messerli::Input::InputPackage(theme_, strings_);

        packages_[packageCount_++] = package;
        currentPackage_ = package;
        hasCurrentPackage_ = true;

        strings_.TitleStatus = strings_.TitleStatusPackages;
        UiRender::Redraw(selectedIndex_, theme_, strings_, strings_.TitleStatus, nullptr, &currentPackage_);
        Messerli::Functions::WaitABit();
        break;
    }

    case 2: {
        // UiRender::ShowAllMailsInteractive(theme_, strings_, letters_, letterCount_, packages_, packageCount_, 0)

        view_ = View::MailManager;
        MailManagerUI::ShowMailManagerMenu(theme_, strings_, manager);

        selectedIndex_ = 0;
        UiRender::Redraw(selectedIndex_, theme_, strings_, "Mail-Manager aktiv");
        break;
    }

    case 3: {
        view_ = View::RightPanelActive;
        strings_.TitleStatus = "Design auswählen";
        UiRender::ShowThemeSelectionInteractive(selectedIndex_, theme_, strings_);
        break;
    }

    case 4:
        running_ = false;
        break;

    default:
        break;
    }
}
void UI::Redraw() const
{
    UiRender::Redraw(selectedIndex_, theme_, strings_, strings_.TitleStatus,
                     hasCurrentLetter_ ? &currentLetter_ : nullptr, hasCurrentPackage_ ? &currentPackage_ : nullptr,
                     10);
}
