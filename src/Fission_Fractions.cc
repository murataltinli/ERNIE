/*********************************************************************************************

Mills, R.W., B.M. Slingsby, J. Coleman, R. Collins, G. Holt, C. Metelko, and Y. Schnellbach.  
“A Simple Method for Estimating the Major Nuclide Fractional Fission Rates within Light Water
 and Advanced Gas Cooled Reactors.”
Nuclear Engineering and Technology 52, no. 9 (September 2020): 2130–37.
https://doi.org/10.1016/j.net.2020.03.004.

**********************************************************************************************/

#include "Fission_Fractions.hh"

#include <cmath>

// Mills model
double fissionFractionsMills(int par, // 5: U235, 8: U238, 9: Pu239, 1: Pu241 
                        double power, // reactor thermal power (W)
                        double time, // days
                        FissionFraction fPar)
{
  const double w2gw = pow(10,-9);
  double I = power * w2gw * time / fPar.uraniumMass; // burnup (GWd/t)

  double f8 = fPar.c + fPar.b * I + fPar.a * pow(I,2);
  double f9 = pow((1 - exp(-fPar.d * I)),fPar.e) * fPar.f;
  double f1 = pow((1 - exp(-fPar.g * I)),fPar.h) * fPar.i;
  double f5 = 1 - f9 - f1 - f8;
  
  if(par == 5){return f5;}
  if(par == 8){return f8;}
  if(par == 9){return f9;}
  else{return f1;}
}

// linear interpolation
double fissionFractionsLinInt(int par, // 5: U235, 8: U238, 9: Pu239, 1: Pu241 
                        double time,
                        FissionFraction fFrac)
{
  const double tmax = 600;
  const double tmin = 0;

  double f5 = fFrac.U235_i + ((fFrac.U235_f - fFrac.U235_i) / (tmax - tmin)) * time; // U235
  double f8 = fFrac.U238_i + ((fFrac.U238_f - fFrac.U238_i) / (tmax - tmin)) * time; // U238
  double f9 = fFrac.Pu239_i + ((fFrac.Pu239_f - fFrac.Pu239_i) / (tmax - tmin)) * time; // Pu239
  double f1 = fFrac.Pu241_i + ((fFrac.Pu241_f - fFrac.Pu241_i) / (tmax - tmin)) * time; // Pu241

  if(par == 5){return f5;}
  if(par == 8){return f8;}
  if(par == 9){return f9;}
  else{return f1;}
}