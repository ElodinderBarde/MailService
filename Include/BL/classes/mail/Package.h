#pragma once
#include "BL/classes/Mail.h"
#include <string>
namespace Messerli
{
class Package : public Mail
{
  protected:
    std::string m_PackageSize;
    double m_WeightInKg;

  public:
    Package();
    Package(const std::string& m_package_size, double m_weight_in_kg);
    ~Package();
    Package(const Package& other);
    Package(Package&& other) noexcept;
    Package& operator=(const Package& other);
    Package& operator=(Package&& other) noexcept;
    [[nodiscard]] std::string M_PackageSize() const;
    void SetM_PackageSize(const std::string& m_package_size);
    [[nodiscard]] double M_WeightInKg() const;
    void SetM_WeightInKg(double m_weight_in_kg);

    std::ostream& Print(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Package& p);
};
}
