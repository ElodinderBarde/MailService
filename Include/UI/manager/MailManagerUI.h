#pragma once
#include "BL/data/Strings.h"
#include "BL/manager/MailManager.h"
#include "UI/data/Theme.h"
class MailManagerUI
{
  public:
    static void ShowMailManagerMenu(const Theme& t, const Strings& s, Messerli::MailManager& manager);
};
