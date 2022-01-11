#ifndef Energy_Momentum
#define Energy_Momentum

#define M_p 938.2720813 //proton mass (MeV/c^2)
#define M_n 939.5654133 //neutron mass (MeV/c^2)
#define m_e 0.511 // positron mass (MeV/c^2)
#define M ((M_n + M_p) / 2) // average nucleon mass
#define Delta (M_n - M_p)

double positron_Energy(double, double);

double positron_Momentum(double, double);

double neutron_Energy(double, double);

double neutron_Momentum(double, double);

double neutron_Angle(double, double);

double neutron_Kinetic_Energy(double, double);

#endif
