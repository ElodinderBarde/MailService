#include "BL/manager/MailManager.h"
#include "UI/draw/Render.h"
#include "UI/manager/RenderUtils.h"
#include <iomanip>
#include <iostream>
namespace Messerli
{
using namespace RenderUtils;
MailManager::MailManager() : letterCount_(0), packageCount_(0)
{
}
void MailManager::AddLetter(const Letter& letter)
{
    if (letterCount_ < MAX_LETTERS)
        letters_[letterCount_++] = letter;
}
void MailManager::AddPackage(const Package& package)
{
    if (packageCount_ < MAX_PACKAGES)
        packages_[packageCount_++] = package;
}
void MailManager::RenderLetters(const Strings& s) const
{
    DrawLine('+', UiRender::INNER_W, '-', '+');
    std::cout << "📬 Gespeicherte Briefe (" << letterCount_ << "):\n";
    if (letterCount_ == 0)
    {
        std::cout << "   Keine Briefe vorhanden.\n";
    }
    else
    {
        for (auto i = 0; i < letterCount_; ++i)
        {
            const auto& l = letters_[i];
            std::string status = l.M_Delivered() ? "Zugestellt" : "Ausstehend";
            std::cout << std::setw(3) << i + 1 << ". " << std::setw(15) << std::left << status
                      << " Empfänger: " << l.M_AdressTo().M_Person().M_Firstname() << " "
                      << l.M_AdressTo().M_Person().M_Lastname() << " | ID: " << l.M_Id() << "\n";
        }
    }
    DrawLine('+', UiRender::INNER_W, '-', '+');
}
void MailManager::RenderPackages(const Strings& s) const
{
    DrawLine('+', UiRender::INNER_W, '-', '+');
    std::cout << "📦 Gespeicherte Pakete (" << packageCount_ << "):\n";
    if (packageCount_ == 0)
    {
        std::cout << "   Keine Pakete vorhanden.\n";
    }
    else
    {
        for (auto i = 0; i < packageCount_; ++i)
        {
            const auto& p = packages_[i];
            std::string status = p.M_Delivered() ? "Zugestellt" : "Ausstehend";
            std::cout << std::setw(3) << i + 1 << ". " << std::setw(15) << std::left << status
                      << " Empfänger: " << p.M_AdressTo().M_Person().M_Firstname() << " "
                      << p.M_AdressTo().M_Person().M_Lastname() << " | ID: " << p.M_Id() << "\n";
        }
    }
    DrawLine('+', UiRender::INNER_W, '-', '+');
}
void MailManager::RenderAll(const Strings& s) const
{
    DrawLine('+', UiRender::INNER_W, '-', '+');
    std::cout << "📮 Alle Sendungen:\n";
    if (letterCount_ == 0 && packageCount_ == 0)
    {
        std::cout << "   Keine Sendungen vorhanden.\n";
    }
    else
    {
        auto index = 1;
        for (auto i = 0; i < letterCount_; ++i)
        {
            const auto& l = letters_[i];
            std::string status = l.M_Delivered() ? "Zugestellt" : "Ausstehend";
            std::cout << std::setw(3) << index++ << ". [Brief] " << std::setw(15) << std::left << status
                      << " Empfänger: " << l.M_AdressTo().M_Person().M_Firstname() << " "
                      << l.M_AdressTo().M_Person().M_Lastname() << " | ID: " << l.M_Id() << "\n";
        }
        for (auto i = 0; i < packageCount_; ++i)
        {
            const auto& p = packages_[i];
            std::string status = p.M_Delivered() ? "Zugestellt" : "Ausstehend";
            std::cout << std::setw(3) << index++ << ". [Paket] " << std::setw(15) << std::left << status
                      << " Empfänger: " << p.M_AdressTo().M_Person().M_Firstname() << " "
                      << p.M_AdressTo().M_Person().M_Lastname() << " | ID: " << p.M_Id() << "\n";
        }
    }
    DrawLine('+', UiRender::INNER_W, '-', '+');
}
void MailManager::ToggleDelivered(Letter* letters, int letterCount, Package* packages, int packageCount)
{
    std::cout << "ID zum Umschalten eingeben: ";
    int id;
    std::cin >> id;

    for (auto i = 0; i < letterCount; ++i)
    {
        if (letters[i].M_Id() == id)
        {
            bool state = letters[i].M_Delivered();
            letters[i].SetM_Delivered(!state);
            std::cout << "Brief " << id << ": Status jetzt " << (!state ? "Zugestellt" : "Ausstehend") << "\n";
            return;
        }
    }

    for (auto i = 0; i < packageCount; ++i)
    {
        if (packages[i].M_Id() == id)
        {
            bool state = packages[i].M_Delivered();
            packages[i].SetM_Delivered(!state);
            std::cout << "Paket " << id << ": Status jetzt " << (!state ? "Zugestellt" : "Ausstehend") << "\n";
            return;
        }
    }
    std::cout << "Keine Sendung mit ID " << id << " gefunden.\n";
}
}
