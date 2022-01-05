#ifndef Reactor_Antineutrino_Flux
#define Reactor_Antineutrino_Flux

#include <cmath>

// reactor antineutrino flux (antineutrinos/s)
double RAFlux
(
  double E_nu, // antineutrino energy (MeV)
  double par = 0, // 0: Total, 5: U235, 8: U238, 9: Pu239, 1: Pu241
  double power = 3.2 * pow(10, 9), // reactor thermal power (W)
  
  // fission fractions at the beginning of the reactor fuel cycle
  double f5 = 0.763, // U235
  double f8 = 0.0476, // U238
  double f9 = 0.162, // Pu239
  double f1 = 0.027 // Pu241  
)
{    
  double x5 = 0, x8 = 0, x9 = 0, x1 = 0;
  double s5, s8, s9, s1;

  double mev2j = 1.6 * pow(10, -13);
  
  double Flux5, Flux8, Flux9, Flux1, Flux0;

  double a5[6] = {3.217, -3.111, 1.395, -.3690, .04445, -.002053};
  double a8[6] = {.4833, .1927, -.1283, -.006762, .002233, -.0001536};
  double a9[6] = {6.413, -7.432, 3.535, -.8820, .1025, -.004550};
  double a1[6] = {3.251, -3.204, 1.428, -.3675, .04254, -.001896};



  // energies per fission (J)
  double e5 = 201.7 * mev2j; // U235
  double e8 = 205 * mev2j; // U238
  double e9 = 210 * mev2j; // Pu239
  double e1 = 212.4 * mev2j; // Pu241

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

#endif