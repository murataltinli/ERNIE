/*
Mueller, Th A., D. Lhuillier, M. Fallot, A. Letourneau, S. Cormon, M. Fechner, L. Giot, et al.
 “Improved Predictions of Reactor Antineutrino Spectra.” Physical Review C 83,
  no. 5 (May 23, 2011): 054615. https://doi.org/10.1103/PhysRevC.83.054615.

Wen, Liang-Jian, Jun Cao, and Yi-Fang Wang. “Reactor Neutrino Experiments: Present and Future.”
 Annual Review of Nuclear and Particle Science 67,
  no. 1 (October 12, 2017): 183–211. https://doi.org/10.1146/annurev-nucl-101916-123318.

Bernstein, A., G. Baldwin, B. Boyer, M. Goodman, J. Learned, J. Lund, D. Reyna, and R. Svoboda.
 “Nuclear Security Applications of Antineutrino Detectors: Current Capabilities and Future Prospects.”
  Science & Global Security 18, no. 3 (December 10, 2010): 127–92.
   https://doi.org/10.1080/08929882.2010.529785.
*/

#ifndef Reactor_Antineutrino_Flux
#define Reactor_Antineutrino_Flux

#include <cmath>

// reactor antineutrino flux
double RAFlux0(double energy /*MeV*/, double par = 0){  
  
  double f5, f8, f9 ,f1, f15, f18, f19, f11;
  double x5 = 0, x8 = 0, x9 = 0, x1 = 0;
  double s5, s8, s9, s1;
  double power = 3.2 * pow(10, 9); // reactor power (W)
  double Flux5, Flux8, Flux9, Flux1, Flux0,Flux10, Flux15, Flux18, Flux19, Flux11;

  double a5[6] = {3.217, -3.111, 1.395, -.3690, .04445, -.002053};
  double a8[6] = {.4833, .1927, -.1283, -.006762, .002233, -.0001536};
  double a9[6] = {6.413, -7.432, 3.535, -.8820, .1025, -.004550};
  double a1[6] = {3.251, -3.204, 1.428, -.3675, .04254, -.001896};

  // energies per fission (J)
  double e5 = 201.7 * 1.6 * pow(10, -13); // U235
  double e8 = 205 * 1.6 * pow(10, -13); // U238
  double e9 = 210 * 1.6 * pow(10, -13); // Pu239
  double e1 = 212.4* 1.6 * pow(10, -13); // Pu241


  for (int p=0; p<6; p++)
  {  
    x5 += a5[p] * pow(energy, p);
    x8 += a8[p] * pow(energy, p);
    x9 += a9[p] * pow(energy, p);
    x1 += a1[p] * pow(energy, p);
  }

  s5 = exp(x5);
  s8 = exp(x8);
  s9 = exp(x9);
  s1 = exp(x1);

  // fission fractions (t = 0)
  f5 = 0.763; // U235
  f8 = 0.0476; // U238
  f9 = 0.162; // Pu239
  f1 = 0.027; // Pu241
        
  Flux5 = (power / (e5*f5 + e8*f8 + e9*f9 + e1*f1)) * f5 * s5;
  Flux8 = (power / (e5*f5 + e8*f8 + e9*f9 + e1*f1)) * f8 * s8;
  Flux9 = (power / (e5*f5 + e8*f8 + e9*f9 + e1*f1)) * f9 * s9;
  Flux1 = (power / (e5*f5 + e8*f8 + e9*f9 + e1*f1)) * f1 * s1;
  Flux0 = Flux5 + Flux8 + Flux9 + Flux1;
  
  // fission fractions (t = end)   
  f15 = 0.423; // U235
  f18 = 0.076; // U238
  f19 = 0.397; // Pu239
  f11 = 0.102; // Pu241

  Flux15 = (power / (e5*f15 + e8*f18 + e9*f19 + e1*f11)) * f15 * s5;
  Flux18 = (power / (e5*f15 + e8*f18 + e9*f19 + e1*f11)) * f18 * s8;
  Flux19 = (power / (e5*f15 + e8*f18 + e9*f19 + e1*f11)) * f19 * s9;
  Flux11 = (power / (e5*f15 + e8*f18 + e9*f19 + e1*f11)) * f11 * s1;
  Flux10 = Flux15 + Flux18 + Flux19 + Flux11;
  
  // start of fuel cycle
  if (par == 5){return Flux5;} // U235
  if (par == 8){return Flux8;} // U238
  if (par == 9){return Flux9;} // Pu239
  if (par == 1){return Flux1;} // Pu241
  if (par == 0){return Flux0;} // Total
  
  // end of fuel cycle
  if (par == 15){return Flux15;} // U235
  if (par == 18){return Flux18;} // U238
  if (par == 19){return Flux19;} // U239
  if (par == 11){return Flux11;} // Pu241
  if (par == 10){return Flux10;} // Total
  else{return 0;}
}

// reactor antineutrino flux
double RAFlux0(double *Energy /*MeV*/, double *Par)
{
  double energy = Energy[0];
  double par = Par[0];

  return RAFlux0(energy, par); 
}
#endif