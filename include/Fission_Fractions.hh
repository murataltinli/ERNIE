#ifndef Fission_Fractions
#define Fission_Fractions

struct FissionFraction
{
  // Mills model parameters
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;
  double g;
  double h; 
  double i;
  double uraniumMass; // tonnes

  // linear interpolation parameters
  double U235_i;
  double U238_i;
  double Pu239_i;
  double Pu241_i;
  double U235_f;
  double U238_f;
  double Pu239_f;
  double Pu241_f;
};

double fissionFractions(int, double, double, FissionFraction);

double fissionFractions(int, double, FissionFraction);

#endif