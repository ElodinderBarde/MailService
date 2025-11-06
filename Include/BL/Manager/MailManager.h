#pragma once
#include "BL/classes/mail/Letter.h"
#include "BL/classes/mail/Package.h"
#include "BL/data/Strings.h"
namespace Messerli
{
class MailManager
{
  public:
    static constexpr auto MAX_LETTERS = 50;
    static constexpr auto MAX_PACKAGES = 50;
    MailManager();
    // Verwaltung
    void AddLetter(const Letter& letter);
    void AddPackage(const Package& package);
    // Zugriff
    const Letter* GetLetters() const
    {
        return letters_;
    }
    int GetLetterCount() const
    {
        return letterCount_;
    }
    const Package* GetPackages() const
    {
        return packages_;
    }
    int GetPackageCount() const
    {
        return packageCount_;
    }
    // Anzeige
    void RenderLetters(const Strings& s) const;
    void RenderPackages(const Strings& s) const;
    void RenderAll(const Strings& s) const;
    static void ToggleDelivered(Letter* letters, int letterCount, Package* packages, int packageCount);

  private:
    Letter letters_[MAX_LETTERS];
    Package packages_[MAX_PACKAGES];
    int letterCount_;
    int packageCount_;
};
} // namespace Messerli
