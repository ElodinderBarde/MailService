#pragma once
#include "BL/data/PersonType.h"
#include <string>
namespace Messerli
{
class Person
{
  protected:
    std::string m_firstname;
    std::string m_lastname;
    PersonType m_Type{};

  public:
    Person();
    Person(std::string firstname, std::string lastname, PersonType type);
    Person(const Person& other);
    Person(Person&& other) noexcept;
    Person& operator=(const Person& other);
    Person& operator=(Person&& other) noexcept;
    [[nodiscard]] std::string M_Firstname() const;
    void SetM_Firstname(const std::string& m_firstname);
    [[nodiscard]] std::string M_Lastname() const;
    void SetM_Lastname(const std::string& m_lastname);
    [[nodiscard]] PersonType M_Type() const;
    void SetM_Type(PersonType m_type);
    [[nodiscard]] Person M_Person() const;
    void SetM_Streetname(const std::string& m_streetname);
};
}
