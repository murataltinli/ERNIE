/*
  Vogel, P., and J. F. Beacom. “Angular Distribution of Neutron Inverse Beta Decay,
   ν ¯ e + p → e + + n.” Physical Review D 60, no. 5 (July 27, 1999): 053003.
    https://doi.org/10.1103/PhysRevD.60.053003.
*/

#ifndef MeanCosTheta
#define MeanCosTheta

#include <cmath>

// inverse beta decay positron scattering angle
double meanCosTheta(double E_nu/*MeV*/, double par = 0)
{
  double M_p = 938.2720813; // proton mass
  double M_n = 939.5654133; // neutron mass
  double M = (M_n + M_p) / 2; // average nucleon mass  
  double E_e = E_nu - (M_n - M_p); // positron energy (MeV)
  double m_e = 0.511; // positron mass (MeV/c^2)
  double p_e = sqrt(pow(E_e,2)-pow(m_e,2)); // positron momentum (MeV/c)
  double v_e = p_e / E_e; // positron velocity
  double mct_e = -0.034 * v_e + 2.4 * E_nu / M; // mean cos theta (positron scattering angle)
  return mct_e;
}

double meanCosTheta(double *E_NU /*MeV*/, double *Par)
{
  double par = Par[0];
  double E_nu = E_NU[0];

  return meanCosTheta(E_nu,par); 
}

#endif
