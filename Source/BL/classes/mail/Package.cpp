#include "BL/classes/mail/Package.h"
#include <iostream>
#include <string>
namespace Messerli
{
Package::Package() = default;
Package::Package(const std::string& m_package_size, double m_weight_in_kg)
    : m_PackageSize(m_package_size), m_WeightInKg(m_weight_in_kg)
{
}
Package::~Package() = default;
Package::Package(const Package& other)
    : Mail(other), m_PackageSize(other.m_PackageSize), m_WeightInKg(other.m_WeightInKg)
{
}
Package::Package(Package&& other) noexcept
    : Mail(std::move(other)), m_PackageSize(std::move(other.m_PackageSize)), m_WeightInKg(other.m_WeightInKg)
{
}
Package& Package::operator=(const Package& other)
{
    if (this == &other)
        return *this;
    Mail::operator=(other);
    m_PackageSize = other.m_PackageSize;
    m_WeightInKg = other.m_WeightInKg;
    return *this;
}
Package& Package::operator=(Package&& other) noexcept
{
    if (this == &other)
        return *this;
    Mail::operator=(std::move(other));
    m_PackageSize = std::move(other.m_PackageSize);
    m_WeightInKg = other.m_WeightInKg;
    return *this;
}
[[nodiscard]] std::string Package::M_PackageSize() const
{
    return m_PackageSize;
}
void Package::SetM_PackageSize(const std::string& m_package_size)
{
    m_PackageSize = m_package_size;
}
[[nodiscard]] double Package::M_WeightInKg() const
{
    return m_WeightInKg;
}
void Package::SetM_WeightInKg(const double m_weight_in_kg)
{
    m_WeightInKg = m_weight_in_kg;
}

std::ostream& Package::Print(std::ostream& os) const
{
    return Mail::Print(os) << "[Package] Größe: " << m_PackageSize << ", Gewicht: " << m_WeightInKg << " kg\n";
}
std::ostream& operator<<(std::ostream& os, const Package& p)
{
    return p.Print(os);
}
}
