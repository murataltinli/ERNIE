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

#include "Reactor_Antineutrino_Spectra.hh"

#include <cmath>

// Huber-Mueller Spectrum
double HMSpectrum(int par, // 5: U235; 8: U238; 9: Pu239; 1: Pu241
                  double E_nu)
{
  double x5 = 0, x8 = 0, x9 = 0, x1 = 0;

  double a5[6] = {4.367, -4.577, 2.100, -.5294, .06186, -.002777};
  double a8[6] = {.4833, .1927, -.1283, -.006762, .002233, -.0001536};
  double a9[6] = {4.757, -5.392, 2.563, -.6596, .07820, -.003536};
  double a1[6] = {2.990, -2.882, 1.278, -.3343, .03905, -.001754};

  for (int i = 0; i < 6; i++)
  { 
    double epow = pow(E_nu,i); 
    x5 += a5[i] * epow;
    x8 += a8[i] * epow;
    x9 += a9[i] * epow;
    x1 += a1[i] * epow;
  }

  double s5 = exp(x5);
  double s8 = exp(x8);
  double s9 = exp(x9);
  double s1 = exp(x1);

  if(par == 5){return s5;}
  else if(par == 8){return s8;}
  else if(par == 9){return s9;}
  else if(par == 1){return s1;}
  else{return 0;}
}

/****************************************************************************************
 Huber, Patrick, and Thomas Schwetz. “Precision Spectroscopy with Reactor Antineutrinos.
 ” Physical Review D 70, no. 5 (September 17, 2004): 053011.
 https://doi.org/10.1103/PhysRevD.70.053011.

 ........

 Schreckenbach, K., G. Colvin, W. Gelletly, and F. Von Feilitzsch.
 “Determination of the Antineutrino Spectrum from 235U Thermal Neutron Fission Products
  up to 9.5 MeV.” 
 Physics Letters B 160, no. 4–5 (October 1985): 325–30.
 https://doi.org/10.1016/0370-2693(85)91337-1.

 Hahn, A.A., K. Schreckenbach, W. Gelletly, F. von Feilitzsch, G. Colvin, and B. Krusche.
 “Antineutrino Spectra from 241Pu and 239Pu Thermal Neutron Fission Products.”
 Physics Letters B 218, no. 3 (February 1989): 365–68.
 https://doi.org/10.1016/0370-2693(89)91598-0.

*****************************************************************************************/

// ILL-Vogel Spectrum
double IVSpectrum(int par, // 5: U235; 8: U238; 9: Pu239; 1: Pu241
                  double E_nu)
{
  double x5 = 0, x8 = 0, x9 = 0, x1 = 0;

  double a5[3] = {.904, -.184, -.0878};
  double a8[3] = {.976, -.162, -.0790};
  double a9[3] = {1.162, -.392, -.0790};
  double a1[3] = {.852, -.126, -.1037};

  for (int i = 0; i < 3; i++)
  { 
    double epow = pow(E_nu,i); 
    x5 += a5[i] * epow;
    x8 += a8[i] * epow;
    x9 += a9[i] * epow;
    x1 += a1[i] * epow;
  }

  double s5 = exp(x5);
  double s8 = exp(x8);
  double s9 = exp(x9);
  double s1 = exp(x1);

  if(par == 5){return s5;}
  else if(par == 8){return s8;}
  else if(par == 9){return s9;}
  else if(par == 1){return s1;}
  else{return 0;}
}