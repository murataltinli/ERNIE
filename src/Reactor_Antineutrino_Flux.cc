/****************************************************************************************************

Energy per fission values are from:
Ma, X. B., W. L. Zhong, L. Z. Wang, Y. X. Chen, and J. Cao.
“Improved Calculation of the Energy Release in Neutron-Induced Fission.”
Physical Review C 88, no. 1 (July 12, 2013): 014605.
https://doi.org/10.1103/PhysRevC.88.014605.

*****************************************************************************************************/
#include "Reactor_Antineutrino_Flux.hh"

#include "Reactor_Antineutrino_Spectra.hh"

#include <cmath>

// reactor antineutrino flux (antineutrinos/s)
double RAFlux
(
  double E_nu, // antineutrino energy (MeV)
  int par, // 0: Total, 5: U235, 8: U238, 9: Pu239, 1: Pu241
  double power, // reactor thermal power (W)
  double time, // days
  FissionFraction fFrac,
  bool isParam, // fission fraction model ->  0: linear intepolation, 1: mills model
  int spectrumModel // 0: Huber-Mueller, 1: ILL-Vogel
)
{
  double f5, f8, f9, f1;
  double s5, s8, s9, s1;

  const double mev2j = 1.6 * pow(10, -13);
  
  double Flux5, Flux8, Flux9, Flux1, Flux0;

  // fission fractions
  if(isParam)
  {
    f5 = fissionFractionsMills(5,power,time,fFrac);
    f8 = fissionFractionsMills(8,power,time,fFrac);
    f9 = fissionFractionsMills(9,power,time,fFrac);
    f1 = fissionFractionsMills(1,power,time,fFrac);
  }
  else
  {
    f5 = fissionFractionsLinInt(5,time,fFrac);
    f8 = fissionFractionsLinInt(8,time,fFrac);
    f9 = fissionFractionsLinInt(9,time,fFrac);
    f1 = fissionFractionsLinInt(1,time,fFrac);
  }

  // energies per fission (J)
  double e5 = 202.36 * mev2j; // U235
  double e8 = 205.99 * mev2j; // U238
  double e9 = 211.12 * mev2j; // Pu239
  double e1 = 214.26 * mev2j; // Pu241

  if(spectrumModel == 1)
  { 
    s5 = HMSpectrum(5,E_nu);
    s8 = HMSpectrum(8,E_nu);
    s9 = HMSpectrum(9,E_nu);
    s1 = HMSpectrum(1,E_nu);
  }
  else if(spectrumModel == 2)
  {
    s5 = IVSpectrum(5,E_nu);
    s8 = IVSpectrum(8,E_nu);
    s9 = IVSpectrum(9,E_nu);
    s1 = IVSpectrum(1,E_nu);
  }
  else if(spectrumModel == 3)
  {
    s5 = MSpectrum(5,E_nu);
    s8 = MSpectrum(8,E_nu);
    s9 = MSpectrum(9,E_nu);
    s1 = MSpectrum(1,E_nu);
  }
  else if(spectrumModel == 0)
  {
    s5 = UserSpectrum(5,E_nu);
    s8 = UserSpectrum(8,E_nu);
    s9 = UserSpectrum(9,E_nu);
    s1 = UserSpectrum(1,E_nu);
  }

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
