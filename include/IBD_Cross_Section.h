/*
  Vogel, P., and J. F. Beacom. “Angular Distribution of Neutron Inverse Beta Decay,
   ν ¯ e + p → e + + n.” Physical Review D 60, no. 5 (July 27, 1999): 053003.
    https://doi.org/10.1103/PhysRevD.60.053003.

  Vincent Fischer. Beta-decay emitted electronic antineutrinos 
   as a tool for unsolved problems in neutrino oscillation physics.
    Nuclear Experiment [nucl-ex]. Université Pierre et Marie Curie - Paris VI, 2015.
*/
#ifndef IBD_Cross_Section
#define IBD_Cross_Section

#include <cmath>

// inverse beta decay cross section (cm^2)
double IBDSigmaTot0(double E_nu, double par = 0)
{
  double M_p = 938.2720813; //proton mass
  double M_n = 939.5654133; //neutron mass
  double E_e = E_nu - (M_n - M_p); // positron energy (MeV)
  double m_e = 0.511; // positron mass (MeV/c^2)
  double p_e = sqrt(pow(E_e,2)-pow(m_e,2)); // positron momentum (MeV/c)
  double sigmatot0 = 0.0952 * p_e * E_e * pow(10,-42); // cm^2
  return sigmatot0;
}

double IBDSigmaTot0(double *E_NU0 /*MeV*/, double *Par0)
{
  double par = Par0[0];
  double E_nu = E_NU0[0];

  return IBDSigmaTot0(E_nu,par); 
}

#endif
