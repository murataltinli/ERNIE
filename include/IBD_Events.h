#ifndef IBD_Events
#define IBD_Events

#include "IBD_Cross_Section.h"
#include "Reactor_Antineutrino_Flux.h"
#include "Energy_Momentum.h"
#include "MeanCosTheta.h"

double epf
(
  double par = 0, // 0: Total, 5: U235, 8: U238, 9: Pu239, 1: Pu241

  // fission fractions
  double f5 = 0.763, // U235
  double f8 = 0.0476, // U238
  double f9 = 0.162, // Pu239
  double f1 = 0.027 // Pu241 

)
{
  // energies per fission (MeV)
  double e5 = 201.7; // U235
  double e8 = 205; // U238
  double e9 = 210; // Pu239
  double e1 = 212.4; // Pu241
  double e0 = ((f5*e5) + (f8*e8) + (f9*e9) + (f1*e1)) / (f5+f8+f9+f1);
  if(par == 0){return e0;}
  if(par == 5){return e5;}
  if(par == 8){return e8;}
  if(par == 9){return e9;}
  if(par == 1){return e1;}
  else{return 0;}


}

double IBDEvents
(
  double E_nu, // antineutrino energy (MeV)
  double par = 0,
  double power = 3.2 * pow(10, 9), // reactor power (W)
  
  // fission fractions
  double f5 = 0.763, // U235
  double f8 = 0.0476, // U238
  double f9 = 0.162, // Pu239
  double f1 = 0.027 // Pu241 
)
{
  double csarea = 1; // detector cross sectional area (m^2)
  double d = 50; // distance to detector (m)
  double n_p = 5.17 * pow(10,22); // free proton number per cm^3
  double V_D = 1; // detector volume (m^3) 
  double N_p = n_p * V_D * pow(10,6); // free proton number in detector
  double time = 60 * 60 * 24; // time (seconds)
  double eff = 1; // detection efficiency

  

  return RAFlux(E_nu,par,power,f5,f8,f9,f1) * (csarea / (4 * M_PI * pow(d,2)))
         * IBDSigmaTot0(E_nu) * N_p * time * eff / epf(par,f5,f8,f9,f1); 
}

double IBDEvents(double *E_NU0 /*MeV*/, double *Par0)
{
  double par = Par0[0];
  double E_nu = E_NU0[0];
  return IBDEvents(E_nu,par);
}

#endif
