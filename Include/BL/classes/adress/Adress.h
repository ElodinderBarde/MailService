#pragma once
#include "BL/data/Strings.h"
#include "Person.h"
#include <string>
namespace Messerli
{
class Adress
{
  protected:
    Person m_person;
    std::string m_Streetname;
    std::string m_Housenumber;
    int m_PostalCode{};
    std::string m_Country;

  public:
    Adress();
    Adress(Person person, std::string streetname, std::string housnumber, int postalCode, std::string country);
    ~Adress();
    Adress(const Adress& other);
    Adress(Adress&& other) noexcept;
    Adress& operator=(const Adress& other);
    Adress& operator=(Adress&& other) noexcept;
    [[nodiscard]] Person M_Person() const;
    void SetM_Person(const Person& m_person);
    [[nodiscard]] std::string M_Streetname() const;
    void SetM_Streetname(const std::string& m_streetname);
    [[nodiscard]] std::string M_Housenumber() const;
    void SetM_Housenumber(const std::string& m_housenumber);
    [[nodiscard]] int M_PostalCode() const;
    void SetM_PostalCode(int m_postal_code);
    [[nodiscard]] std::string M_Country() const;
    void SetM_Country(const std::string& m_country);
    [[nodiscard]] bool IsValid() const;
    bool Scan(const std::string&, Strings& strings_);
    std::ostream& Print(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Adress& adr);
};
}
