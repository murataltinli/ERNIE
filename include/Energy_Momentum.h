#ifndef Energy_Momentum
#define Energy_Momentum

#include <cmath>

// positron energy (MeV)
double positron_Energy(double E_nu /*MeV*/, double costheta_e)
{
  double M_p = 938.2720813; //proton mass (MeV/c^2)
  double M_n = 939.5654133; //neutron mass (MeV/c^2)
  double m_e = 0.511; // positron mass (MeV/c^2)
  double Delta = M_n - M_p; 
  double M = (M_n + M_p) / 2; // average nucleon mass
  double y = sqrt((pow(Delta,2) - pow(m_e,2)) / 2);
  double E_e = E_nu - (Delta); // positron energy (MeV)
  double p_e = sqrt(pow(E_e,2)-pow(m_e,2)); // positron momentum (MeV/c)
  double v_e = p_e / E_e; // positron velocity
  double E_e1 = E_e * (1 - (E_nu / M) * (1 - v_e * costheta_e)) - (pow(y,2) / M);
  return E_e1;
}

// positron momentum (MeV/c)
double positron_Momentum(double E_nu /*MeV*/, double costheta_e)
{
  double m_e = 0.511; // positron mass (MeV/c^2)
  double E_e1 = positron_Energy(E_nu, costheta_e); // positron energy (MeV)
  double p_e1 = sqrt(pow(E_e1,2)-pow(m_e,2));
  return p_e1;
}

// neutron energy (MeV)
double neutron_Energy(double E_nu /*MeV*/, double costheta_e)
{
  double M_p = 938.2720813; //proton mass (MeV/c^2)
  double E_n = E_nu + M_p - positron_Energy(E_nu, costheta_e);
  return E_n;
}

// neutron momentum (MeV/c)
double neutron_Momentum(double E_nu /*MeV*/, double costheta_e)
{
  double M_n = 939.5654133; //neutron mass (MeV/c^2)
  double p_n = sqrt(pow(neutron_Energy(E_nu, costheta_e),2)-pow(M_n,2));
  return p_n;
}

// cos(neutron angle)
double neutron_Angle(double E_nu, double costheta_e)
{
  double costheta_n = (E_nu - positron_Momentum(E_nu,costheta_e) * costheta_e)/ neutron_Momentum(E_nu,costheta_e);
  return costheta_n;
}

// neutron kinetic energy (MeV)
double neutron_Kinetic_Energy(double E_nu, double costheta_e)
{
  double M_p = 938.2720813; //proton mass (MeV/c^2)
  double M_n = 939.5654133; //neutron mass (MeV/c^2)
  double m_e = 0.511; // positron mass (MeV/c^2)
  double Delta = M_n - M_p; 
  double M = (M_n + M_p) / 2; // average nucleon mass
  double y = sqrt((pow(Delta,2) - pow(m_e,2)) / 2);
  double E_e = E_nu - (Delta); // positron energy (MeV)
  double p_e = sqrt(pow(E_e,2)-pow(m_e,2)); // positron momentum (MeV/c)
  double v_e = p_e / E_e; // positron velocity
  double KE_n = (((E_nu * E_e) / M) * (1 - v_e * costheta_e) + (pow(y,2) / M)); // neutron kinetic energy (keV)
  return KE_n;
}

#endif
