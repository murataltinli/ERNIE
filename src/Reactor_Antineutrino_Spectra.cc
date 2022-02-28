#include "Reactor_Antineutrino_Spectra.hh"

#include <cmath>

double Spectrum(double E_nu, double* a)
{
  double x = 0;

  for (int i = 0; i < 6; i++)
  { 
    double epow = pow(E_nu,i); 
    x += a[i] * epow;
  }

  double spectrum = exp(x);

  return spectrum;
}

// User Defined Spectrum
// calculates reactor antineutrino spectrum using coefficient values given by the user
// coefficient values for each isotope (U235, U238, Pu239, Pu241) should be defined to use
double UserSpectrum(int par, // 5: U235; 8: U238; 9: Pu239; 1: Pu241
                    double E_nu)
{
  // coefficient values (to be defined by the user)
  double a5[6] = {.0, .0, .0, .0, .0, .0}; // U235 coefficients
  double a8[6] = {.0, .0, .0, .0, .0, .0}; // U238 coefficients
  double a9[6] = {.0, .0, .0, .0, .0, .0}; // Pu239 coefficients
  double a1[6] = {.0, .0, .0, .0, .0, .0};  // Pu241 coefficients
  
  double *a[10] = {0,a1,0,0,0,a5,0,0,a8,a9};
 
  return Spectrum(E_nu,a[par]);
}

/***********************************************************************************************

Mueller, Th A., D. Lhuillier, M. Fallot, A. Letourneau, S. Cormon, M. Fechner, L. Giot, et al.
“Improved Predictions of Reactor Antineutrino Spectra.”
Physical Review C 83, no. 5 (May 23, 2011): 054615.
https://doi.org/10.1103/PhysRevC.83.054615.

Huber, Patrick.
“On the Determination of Anti-Neutrino Spectra from Nuclear Reactors.”
Physical Review C 84, no. 2 (August 29, 2011): 024617.
https://doi.org/10.1103/PhysRevC.84.024617.

************************************************************************************************/

// Huber-Mueller Spectrum
double HMSpectrum(int par, // 5: U235; 8: U238; 9: Pu239; 1: Pu241
                  double E_nu)
{
  double a5[6] = {4.367, -4.577, 2.100, -.5294,   .06186,  -.002777};
  double a8[6] = {.4833, .1927, -.1283, -.006762, .002233, -.0001536};
  double a9[6] = {4.757, -5.392, 2.563, -.6596,   .07820,  -.003536};
  double a1[6] = {2.990, -2.882, 1.278, -.3343,   .03905,  -.001754};
  double *a[10] = {0,a1,0,0,0,a5,0,0,a8,a9};
  
  return Spectrum(E_nu,a[par]);
}

// Mueller Spectrum
double MSpectrum(int par, // 5: U235; 8: U238; 9: Pu239; 1: Pu241
                double E_nu)
{
  double a5[6] = {3.217, -3.111,  1.395, -.3690,   .04445,  -.002053};
  double a8[6] = {.4833,  .1927, -.1283, -.006762, .002233, -.0001536};
  double a9[6] = {6.413, -7.432,  3.535, -.8820,   .1025,    .004550};
  double a1[6] = {3.251, -3.204,  1.428, -.3675,   .04254,  -.001896};
  double *a[10] = {0,a1,0,0,0,a5,0,0,a8,a9};
  
  return Spectrum(E_nu,a[par]);
}

/****************************************************************************************
 Huber, Patrick, and Thomas Schwetz. “Precision Spectroscopy with Reactor Antineutrinos.
 ” Physical Review D 70, no. 5 (September 17, 2004): 053011.
 https://doi.org/10.1103/PhysRevD.70.053011.

*****************************************************************************************/

// ILL-Vogel Spectrum
double IVSpectrum(int par, // 5: U235; 8: U238; 9: Pu239; 1: Pu241
                  double E_nu)
{
  double a5[6] = {.904,  -.184, -.0878, .0, .0, .0};
  double a8[6] = {.976,  -.162, -.0790, .0, .0, .0};
  double a9[6] = {1.162, -.392, -.0790, .0, .0, .0};
  double a1[6] = {.852,  -.126, -.1037, .0, .0, .0};
  double *a[10] = {0,a1,0,0,0,a5,0,0,a8,a9};

  return Spectrum(E_nu,a[par]);
}