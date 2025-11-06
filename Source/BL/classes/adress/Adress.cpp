#include "BL/classes/adress/Adress.h"
#include <iostream>
#include <utility>
namespace Messerli {
Adress::Adress() = default;
Adress::Adress(Person person, std::string streetname, std::string housnumber, int postalCode, std::string country) :
    m_person(std::move(person)),
    m_Streetname(std::move(streetname)),
    m_Housenumber(std::move(housnumber)),
    m_PostalCode(postalCode),
    m_Country(std::move(country))
{
    std::cout << "Adresse wurde erstellt.\n";
}
Adress::~Adress() = default;
Adress::Adress(const Adress& other) :
    m_person(other.m_person),
    m_Streetname(other.m_Streetname),
    m_Housenumber(other.m_Housenumber),
    m_PostalCode(other.m_PostalCode),
    m_Country(other.m_Country)
{
}
Adress::Adress(Adress&& other) noexcept :
    m_person(std::move(other.m_person)),
    m_Streetname(std::move(other.m_Streetname)),
    m_Housenumber(std::move(other.m_Housenumber)),
    m_PostalCode(other.m_PostalCode),
    m_Country(std::move(other.m_Country))
{
}
Adress& Adress::operator=(const Adress& other)
{
    if (this == &other)
        return *this;
    m_person = other.m_person;
    m_Streetname = other.m_Streetname;
    m_Housenumber = other.m_Housenumber;
    m_PostalCode = other.m_PostalCode;
    m_Country = other.m_Country;
    return *this;
}
Adress& Adress::operator=(Adress&& other) noexcept
{
    if (this == &other)
        return *this;
    m_person = std::move(other.m_person);
    m_Streetname = std::move(other.m_Streetname);
    m_Housenumber = std::move(other.m_Housenumber);
    m_PostalCode = other.m_PostalCode;
    m_Country = std::move(other.m_Country);
    return *this;
}
[[nodiscard]] Person Adress::M_Person() const
{
    return m_person;
}
void Adress::SetM_Person(const Person& m_person)
{
    this->m_person = m_person;
}
[[nodiscard]] std::string Adress::M_Streetname() const
{
    return m_Streetname;
}
void Adress::SetM_Streetname(const std::string& m_streetname)
{
    m_Streetname = m_streetname;
}
[[nodiscard]] std::string Adress::M_Housenumber() const
{
    return m_Housenumber;
}
void Adress::SetM_Housenumber(const std::string& m_housenumber)
{
    m_Housenumber = m_housenumber;
}
[[nodiscard]] int Adress::M_PostalCode() const
{
    return m_PostalCode;
}
void Adress::SetM_PostalCode(int m_postal_code)
{
    m_PostalCode = m_postal_code;
}
[[nodiscard]] std::string Adress::M_Country() const
{
    return m_Country;
}
void Adress::SetM_Country(const std::string& m_country)
{
    m_Country = m_country;
}
bool Adress::IsValid() const
{
    return !m_person.M_Firstname().empty() && !m_person.M_Lastname().empty() && !m_Streetname.empty() && !m_Housenumber.empty() && m_PostalCode > 0;
}
bool Adress::Scan(const std::string& role, Strings& strings_)
{
    auto newAdr = Input::InputAdress(role, strings_);
    if (!newAdr.IsValid()) {
        std::cout << "[Scan] Ungültige Adresse (Dummy)\n";
        return false;
    }
    *this = newAdr;
    return true;
}
std::ostream& Adress::Print(std::ostream& os) const
{
    os << "[Print] Adresse: " << m_person.M_Firstname() << " " << m_person.M_Lastname() << ", " << m_Streetname << " " << m_Housenumber << ", " << m_PostalCode << " " << m_Country;
    return os;
}
std::ostream& operator<<(std::ostream& os, const Adress& adr)
{
    return adr.Print(os);
}
} // namespace Messerli
