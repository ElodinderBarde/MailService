#include "BL/classes/Mail.h"
#include <iostream>
namespace Messerli
{
Mail::Mail() = default;
Mail::Mail(int m_id, Adress m_adress_to, Adress m_adress_from, bool m_delivered)
    : m_Id(m_id), m_AdressTo(std::move(m_adress_to)), m_AdressFrom(std::move(m_adress_from)), m_Delivered(m_delivered)
{
    std::cout << "Objekt Mail wurde erstellt.\n";
}
Mail::~Mail() = default;
Mail::Mail(const Mail& other)
    : m_Id(other.m_Id), m_AdressTo(other.m_AdressTo), m_AdressFrom(other.m_AdressFrom), m_Delivered(other.m_Delivered)
{
}
Mail::Mail(Mail&& other) noexcept
    : m_Id(other.m_Id), m_AdressTo(std::move(other.m_AdressTo)), m_AdressFrom(std::move(other.m_AdressFrom)),
      m_Delivered(other.m_Delivered)
{
}
Mail& Mail::operator=(const Mail& other)
{
    if (this == &other)
        return *this;
    m_Id = other.m_Id;
    m_AdressTo = other.m_AdressTo;
    m_AdressFrom = other.m_AdressFrom;
    m_Delivered = other.m_Delivered;
    return *this;
}
Mail& Mail::operator=(Mail&& other) noexcept
{
    if (this == &other)

        return *this;
    m_Id = other.m_Id;
    m_AdressTo = std::move(other.m_AdressTo);
    m_AdressFrom = std::move(other.m_AdressFrom);
    m_Delivered = other.m_Delivered;
    return *this;
}
[[nodiscard]] int Mail::M_Id() const
{
    return m_Id;
}
void Mail::SetM_Id(int m_Id)
{
    this->m_Id = m_Id;
}
[[nodiscard]] Adress Mail::M_AdressTo() const
{
    return m_AdressTo;
}
void Mail::SetM_AdressTo(const Adress& m_adress_to)
{
    m_AdressTo = m_adress_to;
}
[[nodiscard]] Adress Mail::M_AdressFrom() const
{
    return m_AdressFrom;
}
void Mail::SetM_AdressFrom(const Adress& m_adress_from)
{
    m_AdressFrom = m_adress_from;
}
[[nodiscard]] bool Mail::M_Delivered() const
{
    return m_Delivered;
}
void Mail::SetM_Delivered(const bool m_delivered)
{
    m_Delivered = m_delivered;
}
bool Mail::ScanFrom(std::string& role, Strings& strings_)
{
    std::cout << "[ScanFrom] Eingabe Absenderadresse:\n";
    return m_AdressFrom.Scan(role, strings_);
}
bool Mail::ScanTo(std::string& role, Strings& strings_)
{
    std::cout << "[ScanTo] Eingabe Empfängeradresse:\n";
    return m_AdressTo.Scan(role, strings_);
}
std::ostream& Mail::Print(std::ostream& os) const
{
    os << "[Mail-ID: " << m_Id << "]\n";
    os << "Von: " << m_AdressFrom << "\n";
    os << "An: " << m_AdressTo << "\n";
    os << "Zugestellt: " << (m_Delivered ? "Ja" : "Nein") << "\n";
    return os;
}
}
