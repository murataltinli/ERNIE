#include "Reactor_Antineutrino_Flux.hh"

#include "Reactor_Antineutrino_Spectra.hh"

#include <cmath>

// reactor antineutrino flux (antineutrinos/s)
double RAFlux
(
  double E_nu, // antineutrino energy (MeV)
  int par, // 0: Total, 5: U235, 8: U238, 9: Pu239, 1: Pu241
  double time, // days
  FissionFraction fFrac,
  bool isParam, // fission fraction model ->  0: linear intepolation, 1: mills model
  int spectrumModel // 0: User-Defined, 1: Huber-Mueller, 2: ILL-Vogel, 3: Mueller  
)
{
  double f5, f8, f9, f1;
  double s5, s8, s9, s1;
  
  double Flux5, Flux8, Flux9, Flux1, Flux0;

  // fission fractions
  if(isParam)
  {
    f5 = fissionFractionsMills(5,time,fFrac);
    f8 = fissionFractionsMills(8,time,fFrac);
    f9 = fissionFractionsMills(9,time,fFrac);
    f1 = fissionFractionsMills(1,time,fFrac);
  }
  else
  {
    f5 = fissionFractionsLinInt(5,time,fFrac);
    f8 = fissionFractionsLinInt(8,time,fFrac);
    f9 = fissionFractionsLinInt(9,time,fFrac);
    f1 = fissionFractionsLinInt(1,time,fFrac);
  }

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
  else
  {
    s5 = UserSpectrum(5,E_nu);
    s8 = UserSpectrum(8,E_nu);
    s9 = UserSpectrum(9,E_nu);
    s1 = UserSpectrum(1,E_nu);
  }

  Flux5 = f5 * s5;
  Flux8 = f8 * s8;
  Flux9 = f9 * s9;
  Flux1 = f1 * s1;
  Flux0 = Flux5 + Flux8 + Flux9 + Flux1;

  if (par == 5){return Flux5;} // U235
  if (par == 8){return Flux8;} // U238
  if (par == 9){return Flux9;} // Pu239
  if (par == 1){return Flux1;} // Pu241
  if (par == 0){return Flux0;} // Total
  else{return 0;}
}
