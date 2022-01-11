#ifndef Energy_Momentum
#define Energy_Momentum

struct ParticleMass
{
  double p = 938.2720813; //proton mass (MeV/c^2)
  double n = 939.5654133; //neutron mass (MeV/c^2)
  double e = 0.511; // positron mass (MeV/c^2)
  double M = (n + p) / 2; // average nucleon mass
  double Delta = n - p; 
};

double positron_Energy(double, double);

double positron_Momentum(double, double);

double neutron_Energy(double, double);

double neutron_Momentum(double, double);

double neutron_Angle(double, double);

double neutron_Kinetic_Energy(double, double);

#endif