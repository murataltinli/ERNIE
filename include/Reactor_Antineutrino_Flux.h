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

// reactor antineutrino flux (antineutrinos/s)
double RAFlux
(
  double E_nu, // antineutrino energy (MeV)
  double par = 0, // 0: Total, 5: U235, 8: U238, 9: Pu239, 1: Pu241
  double power = 3.2 * pow(10, 9), // reactor power (W)
  
  // fission fractions
  double f5 = 0.763, // U235
  double f8 = 0.0476, // U238
  double f9 = 0.162, // Pu239
  double f1 = 0.027 // Pu241  
)
{    
  double x5 = 0, x8 = 0, x9 = 0, x1 = 0;
  double s5, s8, s9, s1;
  
  double Flux5, Flux8, Flux9, Flux1, Flux0;

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
    x5 += a5[p] * pow(E_nu, p);
    x8 += a8[p] * pow(E_nu, p);
    x9 += a9[p] * pow(E_nu, p);
    x1 += a1[p] * pow(E_nu, p);
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

// reactor antineutrino flux (antineutrinos/s)
double RAFlux(double *E_NU /*MeV*/, double *Par)
{
  double E_nu = E_NU[0];
  double par = Par[0];

  return RAFlux(E_nu, par); 
}

// reactor antineutrino flux at the detector
double DFlux(double param = 0)
{
  double d = 50; // m
  double csarea = 1; // m2
  double xmax = 8; //MeV
  double xmin = 1.806; //MeV
  int steps = 25;
  double stepsize = (xmax - xmin) / steps ; // MeV

  double dFlux0, dFlux5, dFlux8, dFlux9, dFlux1;
  double R0, R5, R8, R9, R1; 

  for(int i = 0; i<steps; ++i)
  {
    
    dFlux5 += RAFlux( i * stepsize + xmin, 5);
    dFlux8 += RAFlux( i * stepsize + xmin, 8);
    dFlux9 += RAFlux( i * stepsize + xmin, 9);
    dFlux1 += RAFlux( i * stepsize + xmin, 1);
  
  }

  dFlux0 = dFlux5 + dFlux8 + dFlux9 + dFlux1;

  R5 = dFlux5  * csarea / (4*M_PI*pow(d,2));
  R8 = dFlux8  * csarea / (4*M_PI*pow(d,2));
  R9 = dFlux9  * csarea / (4*M_PI*pow(d,2));
  R1 = dFlux1  * csarea / (4*M_PI*pow(d,2));
  R0 = dFlux0  * csarea / (4*M_PI*pow(d,2));

  if (param == 5){return R5;} // U235
  if (param == 8){return R8;} // U238
  if (param == 9){return R9;} // Pu239
  if (param == 1){return R1;} // Pu241
  if (param == 0){return R0;} // Total
  
  else{return 0;}
}
#endif
