#ifndef Reactor_Antineutrino_Flux
#define Reactor_Antineutrino_Flux

struct FissionFraction 
{
  double U235_i;
  double U238_i;
  double Pu239_i;
  double Pu241_i;
  double U235_f;
  double U238_f;
  double Pu239_f;
  double Pu241_f;
};

double RAFlux(double, double, double, double, FissionFraction);

#endif