#include "BL/classes/adress/Person.h"
#include <iostream>
namespace Messerli
{
Person::Person() = default;
Person::Person(std::string firstname, std::string lastname, const PersonType type)
    : m_firstname(std::move(firstname)), m_lastname(std::move(lastname)), m_Type(type)
{
    std::cout << "Person wurde erstellt.\n";
}
Person::Person(const Person& other) : m_firstname(other.m_firstname), m_lastname(other.m_lastname), m_Type(other.m_Type)
{
}
Person::Person(Person&& other) noexcept
    : m_firstname(std::move(other.m_firstname)), m_lastname(std::move(other.m_lastname)), m_Type(other.m_Type)
{
}
Person& Person::operator=(const Person& other)
{
    if (this == &other)
        return *this;
    m_firstname = other.m_firstname;
    m_lastname = other.m_lastname;
    m_Type = other.m_Type;
    return *this;
}
Person& Person::operator=(Person&& other) noexcept
{
    if (this == &other)
        return *this;
    m_firstname = std::move(other.m_firstname);
    m_lastname = std::move(other.m_lastname);
    m_Type = other.m_Type;
    return *this;
}
[[nodiscard]] std::string Person::M_Firstname() const
{
    return m_firstname;
}
void Person::SetM_Firstname(const std::string& m_firstname)
{
    this->m_firstname = m_firstname;
}
[[nodiscard]] std::string Person::M_Lastname() const
{
    return m_lastname;
}
void Person::SetM_Lastname(const std::string& m_lastname)
{
    this->m_lastname = m_lastname;
}
[[nodiscard]] PersonType Person::M_Type() const
{
    return m_Type;
}
void Person::SetM_Type(const PersonType m_type)
{
    m_Type = m_type;
}
}
