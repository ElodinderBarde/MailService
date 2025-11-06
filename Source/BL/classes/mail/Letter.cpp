#include "BL/classes/mail/Letter.h"
#include "BL/classes/Mail.h"
#include <iostream>
#include <string>
namespace Messerli
{
Letter::Letter() = default;
Letter::Letter(const std::string& m_letter_size, char m_priority) :
    Mail(),
    m_LetterSize(m_letter_size),
    m_Priority(m_priority)
{
}
Letter::~Letter() = default;
Letter::Letter(const Letter& other) :
    Mail(other),
    m_LetterSize(other . m_LetterSize),
    m_Priority(other . m_Priority)
{
}
Letter::Letter(Letter&& other) noexcept :
    Mail(std::move(other)),
    m_LetterSize(std::move(other . m_LetterSize)),
    m_Priority(other . m_Priority)
{
}
Letter& Letter::operator=(const Letter& other)
{
    if (this == &other)
        return *this;
    Mail::operator=(other);
    m_LetterSize = other . m_LetterSize;
    m_Priority = other . m_Priority;
    return *this;
}
Letter& Letter::operator=(Letter&& other) noexcept
{
    if (this == &other)
        return *this;
    Mail::operator=(std::move(other));
    m_LetterSize = std::move(other . m_LetterSize);
    m_Priority = other . m_Priority;
    return *this;
}
[[nodiscard]] std::string Letter::M_LetterSize() const
{
    return m_LetterSize;
}
void Letter::SetM_LetterSize(const std::string& m_letter_size)
{
    m_LetterSize = m_letter_size;
}
[[nodiscard]] char Letter::M_Priority() const
{
    return m_Priority;
}
void Letter::SetM_Priority(const char m_priority)
{
    m_Priority = m_priority;
}
std::ostream& Letter::Print(std::ostream& os) const
{
    return Mail::Print(os) << "[Letter] Größe: " << m_LetterSize << ", Priorität: " << m_Priority << '\n';
}
std::ostream& operator<<(std::ostream& os, const Letter& l)
{
    return l . Print(os);
}
}
