#pragma once
#include "BL/classes/Mail.h"
#include <string>
namespace Messerli
{
class Letter : public Mail
{
  protected:
    std::string m_LetterSize;
    char m_Priority = 0;

  public:
    Letter();
    Letter(const std::string& m_LetterSize, char m_priority);
    ~Letter();
    Letter(const Letter& other);
    Letter(Letter&& other) noexcept;
    Letter& operator=(const Letter& other);
    Letter& operator=(Letter&& other) noexcept;
    [[nodiscard]] std::string M_LetterSize() const;
    void SetM_LetterSize(const std::string& m_letter_size);
    [[nodiscard]] char M_Priority() const;
    void SetM_Priority(char m_priority);
    std::ostream& Print(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Letter& l);
};
}
