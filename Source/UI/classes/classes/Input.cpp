#include "UI/manager/Input.h"
#include "BL/classes/adress/Adress.h"
#include "UI/data/Theme.h"
#include "UI/draw/Render.h"
#include <iostream>
#include <string>
namespace Messerli
{
Adress Input::InputAdress(const std::string& role, Strings& strings_)
{
    std::string street, house, country;
    std::string postalStr;
    auto postal = 0;

    std::cout << strings_.InfoStreetFor << role << ":\n";
    std::cout << strings_.InfoStreet;
    std::getline(std::cin, street);
    std::cout << strings_.InfoHouseNumber;
    std::getline(std::cin, house);
    std::cout << strings_.InfoPostalCode;
    std::getline(std::cin, postalStr);
    try
    {
        postal = std::stoi(postalStr);
    }
    catch (...)
    {
        postal = 0;
    }
    std::cout << strings_.InfoCountry;
    std::getline(std::cin, country);

    Person person = InputPerson(role, strings_);
    return Adress(person, street, house, postal, country);
}
Person Input::InputPerson(const std::string& role, Strings& strings_)
{
    std::string firstname, lastname;
    std::cout << strings_.InfoFirstName << role;
    std::getline(std::cin, firstname);
    std::cout << strings_.InfoLastName << role;
    std::getline(std::cin, lastname);

    PersonType t = (role == strings_.InfoReceiver) ? PersonType::empfaenger : PersonType::absender;
    return Person(firstname, lastname, t);
}
Letter Input::InputLetter(Strings& strings_)
{
    std::cout << "\n--- Brief erstellen ---\n";
    Adress sender = InputAdress("Absender", strings_);
    Adress receiver = InputAdress("Empfänger", strings_);

    std::string size;
    char priority;

    std::cout << strings_.InfoLetterType;
    std::getline(std::cin, size);
    std::cout << strings_.InfoLetterPriority;
    std::cin >> priority;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Puffer leeren

    Letter letter;
    letter.SetM_AdressFrom(sender);
    letter.SetM_AdressTo(receiver);
    letter.SetM_LetterSize(size);
    letter.SetM_Priority(priority);
    letter.SetM_Delivered(false);
    letter.SetM_Id(rand() % 1000 + 1);
    return letter;
}
Package Input::InputPackage(Strings& strings_)
{
    std::cout << "\n--- Paket erstellen ---\n";
    Adress sender = InputAdress("Absender", strings_);
    Adress receiver = InputAdress("Empfänger", strings_);

    std::string weightStr, lengthStr, widthStr, heightStr;
    double weight = 0, length = 0, width = 0, height = 0;

    std::cout << "Gewicht in kg: ";
    std::getline(std::cin, weightStr);
    try
    {
        weight = std::stod(weightStr);
    }
    catch (...)
    {
        weight = 0;
    }

    std::cout << "Länge (cm): ";
    std::getline(std::cin, lengthStr);
    std::cout << "Breite (cm): ";
    std::getline(std::cin, widthStr);
    std::cout << "Höhe (cm): ";
    std::getline(std::cin, heightStr);

    try
    {
        length = std::stod(lengthStr);
        width = std::stod(widthStr);
        height = std::stod(heightStr);
    }
    catch (...)
    {
    }

    char buffer[64];
    sprintf_s(buffer, 64, "%.0f x %.0f x %.0f cm", length, width, height);
    std::string size(buffer);

    Package pack;
    pack.SetM_AdressFrom(sender);
    pack.SetM_AdressTo(receiver);
    pack.SetM_WeightInKg(weight);
    pack.SetM_PackageSize(size);
    pack.SetM_Id(rand() % 1000 + 1);
    pack.SetM_Delivered(false);
    return pack;
}
Letter Input::InputLetter(const Theme& theme, Strings& strings_)
{
    constexpr auto count = 16;
    std::string felder[count] = {
        strings_.InfoReceiver,    strings_.InfoFirstName,  strings_.InfoLastName,       strings_.InfoStreet,
        strings_.InfoHouseNumber, strings_.InfoPostalCode, strings_.InfoCountry,        strings_.InfoSender,
        strings_.InfoFirstName,   strings_.InfoLastName,   strings_.InfoStreet,         strings_.InfoHouseNumber,
        strings_.InfoPostalCode,  strings_.InfoCountry,    strings_.InfoLetterPriority, strings_.InfoLetterType};
    std::string werte[count];

    std::string input;
    UiRender::DrawRightPanelInteractive(theme, strings_, "Brief erstellen", felder, werte, count);

    for (auto i = 0; i < count; ++i)
    {

        if (i == 7 || i == 0)
        {
            continue;
        }
        std::cout << felder[i] << "> ";
        std::getline(std::cin, input);
        werte[i] = input;
        if (werte[i].empty())
        {
            std::cout << "Bitte Feld erneut eingeben: ";
            --i;
        }
        UiRender::DrawRightPanelInteractive(theme, strings_, "Brief erstellen", felder, werte, count);
    }

    Person empfaenger(werte[1], werte[2], PersonType::empfaenger);
    Adress adrEmpf(empfaenger, werte[3], werte[4], std::stoi(werte[5]), werte[6]);

    Person absender(werte[8], werte[9], PersonType::absender);
    Adress adrAbsender(absender, werte[10], werte[11], std::stoi(werte[12]), werte[13]);

    char prio = werte[14].empty() ? L'C' : werte[10][0];
    std::string size = werte[15];

    Letter letter;
    letter.SetM_AdressFrom(adrAbsender);
    letter.SetM_AdressTo(adrEmpf);
    letter.SetM_Priority(prio);
    letter.SetM_LetterSize(size);
    letter.SetM_Delivered(false);
    letter.SetM_Id(rand() % 1000 + 1);
    return letter;
}
Package Input::InputPackage(const Theme& theme, Strings& strings_)
{
    constexpr auto count = 18;
    std::string felder[count] = {strings_.InfoReceiver,
                                 strings_.InfoFirstName,
                                 strings_.InfoLastName,
                                 strings_.InfoStreet,
                                 strings_.InfoHouseNumber,
                                 strings_.InfoPostalCode,
                                 strings_.InfoCountry,
                                 strings_.InfoSender,
                                 strings_.InfoFirstName,
                                 strings_.InfoLastName,
                                 strings_.InfoStreet,
                                 strings_.InfoHouseNumber,
                                 strings_.InfoPostalCode,
                                 strings_.InfoCountry,
                                 "Gewicht (kg)",
                                 "Länge (cm)",
                                 "Breite (cm)",
                                 "Höhe (cm)"};
    std::string werte[count];

    std::string input;
    UiRender::DrawRightPanelInteractive(theme, strings_, "Paket erstellen", felder, werte, count);

    for (auto i = 0; i < count; ++i)
    {
        if (i == 0 || i == 7)
            continue;

        std::cout << felder[i] << "> ";
        std::getline(std::cin, input);
        werte[i] = input;

        if (werte[i].empty())
        {
            std::cout << "Bitte Feld erneut eingeben: ";
            --i;
            continue;
        }

        UiRender::DrawRightPanelInteractive(theme, strings_, "Paket erstellen", felder, werte, count);
    }

    Person empfaenger(werte[1], werte[2], PersonType::empfaenger);
    Adress adrEmpf(empfaenger, werte[3], werte[4], std::stoi(werte[5]), werte[6]);

    Person absender(werte[8], werte[9], PersonType::absender);
    Adress adrAbsender(absender, werte[10], werte[11], std::stoi(werte[12]), werte[13]);

    double weight = 0, length = 0, width = 0, height = 0;

    try
    {
        weight = std::stod(werte[14]);
    }
    catch (...)
    {
    }
    try
    {
        length = std::stod(werte[15]);
    }
    catch (...)
    {
    }
    try
    {
        width = std::stod(werte[16]);
    }
    catch (...)
    {
    }
    try
    {
        height = std::stod(werte[17]);
    }
    catch (...)
    {
    }

    char buffer[64];
    sprintf_s(buffer, 64, "%.0f x %.0f x %.0f cm", length, width, height);
    std::string size(buffer);

    Package pack;
    pack.SetM_AdressFrom(adrAbsender);
    pack.SetM_AdressTo(adrEmpf);
    pack.SetM_WeightInKg(weight);
    pack.SetM_PackageSize(size);
    pack.SetM_Id(rand() % 1000 + 1);
    pack.SetM_Delivered(false);

    return pack;
}
}
