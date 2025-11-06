# 📬 Mail Management System (C++ Console Application)

Ein konsolenbasiertes Post- und Versandverwaltungssystem in **C++**, das den Versand und die Verwaltung von **Briefen** und **Paketen** simuliert.
Das Projekt dient als Beispiel für objektorientierte Softwarearchitektur mit klarer Trennung zwischen **Datenmodell**, **Logik** und **Darstellung**.
Alle Komponenten folgen modernen C++-Best Practices (RAII, Move-Semantik, const-Korrektheit, Trennung von Header und Implementierung).

---

## 🧭 Zusammenfassung

Das Programm simuliert eine Poststelle.
Nutzer können Adressen eingeben, Briefe und Pakete verwalten und deren Zustellstatus anzeigen oder umschalten.
Die Benutzeroberfläche wird vollständig in der Konsole gerendert – inklusive Rahmen, Menüs und Unicode-Symbolen (📬, 📦).

Die Architektur trennt Verantwortlichkeiten klar:

* **Business Logic (BL)** kümmert sich um Datenmodelle und Programmlogik.
* **UI (User Interface)** ist verantwortlich für Darstellung und Benutzereingaben.
* **Main** startet die Anwendung und initialisiert UTF-8 sowie Konsolenmodi.

---

## ⚙️ Hauptfunktionen

| Funktion                       | Beschreibung                                                                       |
| ------------------------------ | ---------------------------------------------------------------------------------- |
| **MailManager**                | Verwalten, Anzeigen und Filtern aller Briefe und Pakete                            |
| **Adress & Person**            | Modellierung von Empfänger und Absender mit Validierung                            |
| **Letter / Package**           | Ableitungen von `Mail`, enthalten spezifische Felder wie Gewicht, Größe, Priorität |
| **RenderUtils & UI**           | Zeichnet Tabellen, Rahmen und Text in der Konsole mit ANSI-Farben                  |
| **Functions::InitializeApp()** | Initialisiert UTF-8, aktiviert VT100-Sequenzen und startet die UI-Schleife         |

---

## 🧩 Projektstruktur

```
📦 MailManagementSystem
├── BL/
│   ├── classes/
│   │   ├── adress/
│   │   │   ├── Adress.h / .cpp
│   │   │   ├── Person.h / .cpp
│   │   │   └── PersonType.h
│   │   ├── mail/
│   │   │   ├── Mail.h / .cpp
│   │   │   ├── Letter.h / .cpp
│   │   │   └── Package.h / .cpp
│   ├── manager/
│   │   ├── MailManager.h / .cpp
│   │   └── Functions.h / .cpp
│   └── data/
│       └── Strings.h
│
├── UI/
│   ├── manager/
│   │   ├── ConsoleManager.h
│   │   ├── MailManagerUI.h / .cpp
│   │   ├── RenderUtils.h / .cpp
│   │   ├── UI.h / .cpp
│   │   └── Input.h / .cpp
│   ├── draw/
│   │   ├── Render.h / .cpp
│   │   └── RenderUtils.h / .cpp
│   ├── data/
│   │   ├── LayoutSize.h
│   │   └── Theme.h
│
├── main.cpp
└── README.md
```

---

## 🧠 Code-Erklärung

### 🧾 `main.cpp`

Startpunkt des Programms.
Richtet UTF-8-Kodierung ein, gibt Debug-Infos aus und startet den Programmfluss:

```cpp
int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::ios_base::sync_with_stdio(false);

    std::cout << "[DEBUG] Output Codepage: " << GetConsoleOutputCP() << std::endl;
    Messerli::Functions::InitializeApp();
}
```

---

### ⚙️ `Functions.cpp`

Systeminitialisierung:
Richtet die Konsole so ein, dass UTF-8-Zeichen (wie „ä“, „┌“, „📦“) korrekt angezeigt werden.

```cpp
void Functions::InitializeApp() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);

    std::cout << "[DEBUG] UTF-8 aktiv!\n";
    RenderUtils::PrintConsoleModeDebug();

    UI ui;
    ui.Run(); // Startet Menü
}
```

---

### 💌 `Mail`, `Letter`, `Package`

`Mail` ist die Basisklasse, `Letter` und `Package` leiten davon ab.

```cpp
class Mail {
protected:
    int m_Id;
    Adress m_AdressTo;
    Adress m_AdressFrom;
    bool m_Delivered;
public:
    virtual std::ostream& Print(std::ostream& os) const;
};
```

```cpp
class Letter : public Mail {
    std::string m_LetterSize;
    char m_Priority;
};
```

```cpp
class Package : public Mail {
    std::string m_PackageSize;
    double m_WeightInKg;
};
```

Jede Klasse besitzt:

* Konstruktoren mit Kopier- und Move-Semantik
* Getter/Setter
* `Print()`-Methoden für strukturierte Ausgabe
* Operator-Überladung für `<<`

---

### 👤 `Adress` und `Person`

Datenklassen für Personendaten, die in `Mail` verwendet werden.
Sie validieren Eingaben und bieten Methoden zur Konsoleingabe (`Scan()`).

```cpp
bool Adress::IsValid() const {
    return !m_person.M_Firstname().empty() &&
           !m_Streetname.empty() &&
           !m_Housenumber.empty() &&
           m_PostalCode > 0;
}
```

---

### 📦 `MailManager`

Verwaltet alle Briefe und Pakete im Speicher:

```cpp
void MailManager::AddLetter(const Letter& letter);
void MailManager::AddPackage(const Package& package);
void MailManager::RenderAll(const Strings& s) const;
void MailManager::ToggleDelivered(Letter* letters, int letterCount, Package* packages, int packageCount);
```

Beispielausgabe:

```
📮 Alle Sendungen:
  1. [Brief] Zugestellt  Empfänger: Max Muster | ID: 101
  2. [Paket] Ausstehend Empfänger: Julia Meyer | ID: 202
```

---

### 🖥 `RenderUtils` & `Render.cpp`

Statische Hilfsfunktionen für visuelle Konsolenelemente:

```cpp
namespace RenderUtils {
    void DrawLine(char left, int width, char fill, char right);
    void DrawTextRow(const Strings&, int leftWidth,
                     const std::string& leftText, const std::string& rightText, const Theme& t);
    void PrintConsoleModeDebug();
}
```


### 🎨 `Theme` & `LayoutSize`

Definieren Farben, Layoutbreiten und Zeichenstile.
`Theme` enthält ANSI-Farbcodes, `LayoutSize` definiert z. B. die Breite innerer Tabellen.

---

### ⌨️ `Input`

Zentrale Eingabe-Schnittstelle für Benutzerinteraktion.
Enthält Funktionen zur sicheren Eingabe von Text, Zahlen und Rollen (z. B. Empfänger, Absender).

---

## 🧱 Designprinzipien

| Prinzip                   | Umsetzung                                                         |
| ------------------------- | ----------------------------------------------------------------- |
| **Single Responsibility** | Jede Klasse hat klaren Zweck (z. B. `MailManager`, `RenderUtils`) |
| **Modularität**           | Trennung in BL, UI, Data-Layer                                    |
| **RAII / Move-Semantik**  | Alle Klassen implementieren sichere Kopier- und Move-Operatoren   |
| **Erweiterbarkeit**       | Neue Mailtypen oder UI-Komponenten können leicht ergänzt werden   |
| **UTF-8-Support**         | Windows-Konsolenmodus wird automatisch angepasst                  |

---

## 🧩 Kompilierung

### Voraussetzungen

* Compiler: **MSVC** oder **MinGW (GCC 10+)**
* C++20 aktivieren
* UTF-8-fähige Konsole

### Beispiel (Windows, MinGW)

```bash
g++ -std=c++20 -Wall -Wextra -I./ -o MailApp.exe \
    main.cpp \
    BL/classes/adress/*.cpp \
    BL/classes/mail/*.cpp \
    BL/manager/*.cpp \
    UI/manager/*.cpp \
    UI/draw/*.cpp
```

---

## 🧪 Beispielausgabe

```
[DEBUG] UTF-8 aktiv!
┌────────────┐
│  Menü      │
└────────────┘
📮 Alle Sendungen:
   Keine Sendungen vorhanden.
```

Umschalten eines Zustellstatus:

```
ID zum Umschalten eingeben: 2
Paket 2: Status jetzt Zugestellt
```

---

## 🧭 Zukünftige Erweiterungen

* 📁 Persistente Speicherung (JSON, SQLite)
* 🌐 Netzwerk-basierte Synchronisation
* 🧩 GUI-Frontend (Qt oder ImGui)
* 🧠 Automatische Tests für Eingabevalidierung und Datenmanipulation

---

## 📄 Lizenz

Dieses Projekt steht unter der **MIT-Lizenz**.
Verwendung, Modifikation und Weitergabe sind erlaubt, solange der ursprüngliche Autor genannt wird.

