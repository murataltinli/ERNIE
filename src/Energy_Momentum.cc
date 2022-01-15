#include "Energy_Momentum.hh"

#include <cmath>

const double M_p = 938.2720813; // proton mass (MeV/c^2)
const double M_n = 939.5654133; // neutron mass (MeV/c^2)
const double m_e = 0.511; // positron mass (MeV/c^2)
const double M = ((M_n + M_p) / 2); // average nucleon mass
const double Delta = M_n - M_p; // M_n - M_p
const double y2 = ((Delta*Delta) - (m_e*m_e)) / 2;

// positron energy (MeV)
double positron_Energy(double E_nu /*MeV*/, double costheta_e)
{
  double E_e = E_nu - (Delta); // positron energy (MeV)
  double p_e = sqrt(pow(E_e,2)-pow(m_e,2)); // positron momentum (MeV/c)
  double v_e = p_e / E_e; // positron velocity
  double E_e1 = E_e * (1 - (E_nu / M) * (1 - v_e * costheta_e)) - (y2 / M);
  return E_e1;
}

// positron momentum (MeV/c)
double positron_Momentum(double E_nu /*MeV*/, double costheta_e)
{
  double E_e1 = positron_Energy(E_nu, costheta_e); // positron energy (MeV)
  double p_e1 = sqrt(pow(E_e1,2)-pow(m_e,2));
  return p_e1;
}

// neutron energy (MeV)
double neutron_Energy(double E_nu /*MeV*/, double costheta_e)
{
  double E_n = E_nu + M_p - positron_Energy(E_nu, costheta_e);
  return E_n;
}

// neutron momentum (MeV/c)
double neutron_Momentum(double E_nu /*MeV*/, double costheta_e)
{
  double p_n = sqrt(pow(neutron_Energy(E_nu, costheta_e),2)-pow(M_n,2));
  return p_n;
}

// cos(neutron angle)
double neutron_Angle(double E_nu, double costheta_e)
{
  double costheta_n = (E_nu - positron_Momentum(E_nu,costheta_e) * costheta_e)
                      / neutron_Momentum(E_nu,costheta_e);
  return costheta_n;
}

// neutron kinetic energy (MeV)
double neutron_Kinetic_Energy(double E_nu, double costheta_e)
{
  double E_e = E_nu - (Delta); // positron energy (MeV)
  double p_e = sqrt(pow(E_e,2)-pow(m_e,2)); // positron momentum (MeV/c)
  double v_e = p_e / E_e; // positron velocity
  double KE_n = (((E_nu * E_e) / M) * (1 - v_e * costheta_e) + (y2 / M));
  return KE_n;
}