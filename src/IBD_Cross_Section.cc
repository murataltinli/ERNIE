#include <cmath>

#include "IBD_Cross_Section.hh"
#include "Energy_Momentum.hh"

// inverse beta decay cross section (cm^2)
double IBDSigmaTot0(double E_nu)
{
  double E_e = E_nu - (M_n - M_p); // positron energy (MeV)
  double p_e = sqrt(pow(E_e,2)-pow(m_e,2)); // positron momentum (MeV/c)
  double sigmatot0 = 0.0952 * p_e * E_e * pow(10,-42); // cm^2
  return sigmatot0;
}
