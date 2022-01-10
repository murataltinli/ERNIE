/****************************************************************************************************

Antineutrino spectrum is from:
Mueller, Th A., D. Lhuillier, M. Fallot, A. Letourneau, S. Cormon, M. Fechner, L. Giot, et al.
“Improved Predictions of Reactor Antineutrino Spectra.”
Physical Review C 83, no. 5 (May 23, 2011): 054615.
https://doi.org/10.1103/PhysRevC.83.054615.

Huber, Patrick.
“On the Determination of Anti-Neutrino Spectra from Nuclear Reactors.”
Physical Review C 84, no. 2 (August 29, 2011): 024617.
https://doi.org/10.1103/PhysRevC.84.024617.

Energy per fission values are from:
Ma, X. B., W. L. Zhong, L. Z. Wang, Y. X. Chen, and J. Cao.
“Improved Calculation of the Energy Release in Neutron-Induced Fission.”
Physical Review C 88, no. 1 (July 12, 2013): 014605.
https://doi.org/10.1103/PhysRevC.88.014605.

*****************************************************************************************************/
#include "Reactor_Antineutrino_Flux.hh"

#include <cmath>

// reactor antineutrino flux (antineutrinos/s)
double RAFlux
(
  double E_nu, // antineutrino energy (MeV)
  double par, // 0: Total, 5: U235, 8: U238, 9: Pu239, 1: Pu241
  double power, // reactor thermal power (W)
  double time,
  FissionFraction fFrac
)
{    
  double x5 = 0, x8 = 0, x9 = 0, x1 = 0;
  double s5, s8, s9, s1;

  double mev2j = 1.6 * pow(10, -13);
  
  double Flux5, Flux8, Flux9, Flux1, Flux0;

  double tmax = 600;
  double tmin = 0;

  // fission fractions
  double f5 = fFrac.U235_i + ((fFrac.U235_f - fFrac.U235_i) / (tmax - tmin)) * time; // U235
  double f8 = fFrac.U238_i + ((fFrac.U238_f - fFrac.U238_i) / (tmax - tmin)) * time; // U238
  double f9 = fFrac.Pu239_i + ((fFrac.Pu239_f - fFrac.Pu239_i) / (tmax - tmin)) * time; // Pu239
  double f1 = fFrac.Pu241_i + ((fFrac.Pu241_f - fFrac.Pu241_i) / (tmax - tmin)) * time; // Pu241

  double a5[6] = {4.367, -4.577, 2.100, -.5294, .06186, -.002777};
  double a8[6] = {.4833, .1927, -.1283, -.006762, .002233, -.0001536};
  double a9[6] = {4.757, -5.392, 2.563, -.6596, .07820, -.003536};
  double a1[6] = {2.990, -2.882, 1.278, -.3343, .03905, -.001754};

  

  // energies per fission (J)
  double e5 = 202.36 * mev2j; // U235
  double e8 = 205.99 * mev2j; // U238
  double e9 = 211.12 * mev2j; // Pu239
  double e1 = 214.26 * mev2j; // Pu241

  for (int p=0; p<6; p++)
  { 
    double epow = pow(E_nu,p); 
    x5 += a5[p] * epow;
    x8 += a8[p] * epow;
    x9 += a9[p] * epow;
    x1 += a1[p] * epow;
  }

  s5 = exp(x5);
  s8 = exp(x8);
  s9 = exp(x9);
  s1 = exp(x1);

  Flux5 = (power / (e5*f5 + e8*f8 + e9*f9 + e1*f1)) * f5 * s5;
  Flux8 = (power / (e5*f5 + e8*f8 + e9*f9 + e1*f1)) * f8 * s8;
  Flux9 = (power / (e5*f5 + e8*f8 + e9*f9 + e1*f1)) * f9 * s9;
  Flux1 = (power / (e5*f5 + e8*f8 + e9*f9 + e1*f1)) * f1 * s1;
  Flux0 = Flux5 + Flux8 + Flux9 + Flux1;

  if (par == 5){return Flux5;} // U235
  if (par == 8){return Flux8;} // U238
  if (par == 9){return Flux9;} // Pu239
  if (par == 1){return Flux1;} // Pu241
  if (par == 0){return Flux0;} // Total
  else{return 0;}
}