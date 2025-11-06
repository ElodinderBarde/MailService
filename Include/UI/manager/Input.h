#pragma once
#include "BL/classes/mail/Letter.h"
#include "BL/classes/mail/Package.h"
#include "UI/data/Theme.h"
namespace Messerli
{
class Input
{
    Strings strings_;

public:
    static Adress InputAdress(const std::string& role, Strings& strings_);
    static Person InputPerson(const std::string& role, Strings& strings_);
    static Letter InputLetter(Strings& strings_);
    static Package InputPackage(Strings& strings_);
    static Letter InputLetter(const Theme& theme, Strings& strings_);
    static Package InputPackage(const Theme& theme, Strings& strings_);
};
}
