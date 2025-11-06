#pragma once
#include <string>
enum class DesignSet
{
    ASCII,
    BOX,
    DOUBLE,
    LIGHT,
    SIMPLE
};
struct Strings
{
    std::string MailManagrLetters = "[1] Briefe anzeigen.\n";
    std::string MailManagrPackages = "[2] Packete anzeigen \n";
    std::string MailManagrShowAll = "[3] Alle Sendungen \n";
    std::string MailManagrGoBack = "[4] Zurück\n"; 

    std::string StatusError = "Ein Fehler ist aufgetreten.\n";
    std::string StatusRunning = "Alle Daten wurden geladen.\n";
    std::string StatusLoading = "Daten werden geladen.\n";
    std::string OptionDelivered = "D = Zustellungsstatus Ändern \n"; 
    std::string OptionButton = "Tasten:\n";
    std::string OptionNavigation = "Arrow Up / Arrow Down = Navigation\n";
    std::string OptionEnter = "Enter = Auswahl\n";
    std::string OptionExit = "Q = Beenden\n";
    std::string Title = "*** MESSERLI MAIL SERVICE ***";
    std::string TitleStatus = "STATUS / ANSICHT";
    std::string TitleStatusLetters = "STATUS / Briefansicht";
    std::string TitleStatusPackages = "STATUS / Packetansicht";
    std::string MenuNewLetter = "[1] Neuen Brief erstellen";
    std::string MenuNewPack = "[2] Neues Paket erstellen";
    std::string MenuShowMails = "[3] Alle Mails anzeigen";
    std::string MenuSettings = "[4] Einstellungen";
    std::string MenuExit = "[5] Beenden";
    std::string ShowSelected = "Aktuelle Auswahl: ";
    std::string InfoType = "Typ: ";
    std::string InfoLetterType = "Größe (z. B. A4, A5): ";
    std::string InfoLetterPriority = "Priorität (A, B, C): ";
    std::string InfoID = "ID: ";
    std::string InfoFirstName = "Vorname: ";
    std::string InfoLastName = "Nachname: ";
    std::string InfoStreet = "Strasse: ";
    std::string InfoStreetFor = "Adresse von ";
    std::string InfoHouseNumber = "Hausnummer: ";
    std::string InfoPostalCode = "PLZ: ";
    std::string InfoCountry = "Land: ";
    std::string InfoReceiver = "Empfaenger: ";
    std::string InfoSender = "Absender: ";
    std::string InfoWeight = "Gewicht: ";
    std::string InfoKg = " kg";
    std::string InfoDate = "Erzeugt am: ";
    std::string InfoStatus = "Versandstatus: ";
    std::string InfoStatusSend = "Versendet";
    std::string InfoStatusNotSend = "Nicht versendet";
    std::string InfoStatusDelivered = "Zugestellt";
    std::string BorderTopLeft;
    std::string BorderTopRight;
    std::string BorderBottomLeft;
    std::string BorderBottomRight;
    std::string BorderHorizontal;
    std::string BorderVertical;
    std::string BorderCross;
    std::string BorderTLeft;
    std::string BorderTRight;
    std::string BorderTT;
    std::string BorderTB;
    DesignSet ActiveDesign = DesignSet::BOX;
    void ApplyDesign(DesignSet set)
    {
        ActiveDesign = set;
        switch (set)
        {
        case DesignSet::ASCII:
            BorderTopLeft = "+";
            BorderTopRight = "+";
            BorderBottomLeft = "+";
            BorderBottomRight = "+";
            BorderHorizontal = "-";
            BorderVertical = "|";
            BorderCross = "+";
            BorderTLeft = "+";
            BorderTRight = "+";
            BorderTT = "+";
            BorderTB = "+";
            break;

        case DesignSet::BOX:
            BorderTopLeft = "\xE2\x94\x8C";     // ┌
            BorderTopRight = "\xE2\x94\x90";    // ┐
            BorderBottomLeft = "\xE2\x94\x94";  // └
            BorderBottomRight = "\xE2\x94\x98"; // ┘
            BorderHorizontal = "\xE2\x94\x80";  // ─
            BorderVertical = "\xE2\x94\x82";    // │
            BorderCross = "\xE2\x94\xBC";       // ┼
            BorderTLeft = "\xE2\x94\x9C";       // ├
            BorderTRight = "\xE2\x94\xA4";      // ┤
            BorderTT = "\xE2\x94\xAC";          // ┬
            BorderTB = "\xE2\x94\xB4";          // ┴
            break;

        case DesignSet::DOUBLE:
            BorderTopLeft = "\xE2\x95\x94";     // ╔
            BorderTopRight = "\xE2\x95\x97";    // ╗
            BorderBottomLeft = "\xE2\x95\x9A";  // ╚
            BorderBottomRight = "\xE2\x95\x9D"; // ╝
            BorderHorizontal = "\xE2\x95\x90";  // ═
            BorderVertical = "\xE2\x95\x91";    // ║
            BorderCross = "\xE2\x95\xAC";       // ╬
            BorderTLeft = "\xE2\x95\xA0";       // ╠
            BorderTRight = "\xE2\x95\xA3";      // ╣
            BorderTT = "\xE2\x95\xA6";          // ╦
            BorderTB = "\xE2\x95\xA9";          // ╩
            break;

        case DesignSet::LIGHT:
            BorderTopLeft = "\xE2\x94\x8F";     // ┏
            BorderTopRight = "\xE2\x94\x93";    // ┓
            BorderBottomLeft = "\xE2\x94\x97";  // ┗
            BorderBottomRight = "\xE2\x94\x9B"; // ┛
            BorderHorizontal = "\xE2\x94\x81";  // ━
            BorderVertical = "\xE2\x94\x83";    // ┃
            BorderCross = "\xE2\x95\x8B";       // ╋
            BorderTLeft = "\xE2\x94\xA3";       // ┣
            BorderTRight = "\xE2\x94\xAB";      // ┫
            BorderTT = "\xE2\x94\xAF";          // ┳
            BorderTB = "\xE2\x94\xB7";          // ┻
            break;

        case DesignSet::SIMPLE:
            BorderTopLeft = " ";
            BorderTopRight = " ";
            BorderBottomLeft = " ";
            BorderBottomRight = " ";
            BorderTLeft = " ";
            BorderTRight = " ";
            BorderCross = " ";
            BorderTT = " ";
            BorderTB = " ";
            BorderVertical = "|";
            BorderHorizontal = "-";
            break;
        }
    }
};
