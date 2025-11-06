#pragma once
#include "BL/data/Strings.h"
#include "adress/Adress.h"
namespace Messerli
{
class Mail
{
  protected:
    int m_Id;
    Adress m_AdressTo;
    Adress m_AdressFrom;

  public:
    bool m_Delivered = false;
    Mail();
    Mail(int m_id, Adress m_adress_to, Adress m_adress_from, bool m_delivered);
    ~Mail();
    Mail(const Mail& other);
    Mail(Mail&& other) noexcept;
    Mail& operator=(const Mail& other);
    Mail& operator=(Mail&& other) noexcept;
    [[nodiscard]] int M_Id() const;
    void SetM_Id(int m_Id);
    [[nodiscard]] Adress M_AdressTo() const;
    void SetM_AdressTo(const Adress& m_adress_to);
    [[nodiscard]] Adress M_AdressFrom() const;
    void SetM_AdressFrom(const Adress& m_adress_from);
    [[nodiscard]] bool M_Delivered() const;
    void SetM_Delivered(bool m_delivered);
    bool ScanFrom(std::string& role, Strings& strings_);
    bool ScanTo(std::string& role, Strings& strings_);
    std::ostream& Print(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Mail& mail);
};
}
