#ifndef Energy_Momentum
#define Energy_Momentum

const double M_p = 938.2720813; //proton mass (MeV/c^2)
const double M_n = 939.5654133; //neutron mass (MeV/c^2)
const double m_e = 0.511; // positron mass (MeV/c^2)
const double M = ((M_n + M_p) / 2); // average nucleon mass
const double Delta = (M_n - M_p);
const double y2 = ((Delta*Delta) - (m_e*m_e)) / 2;

double positron_Energy(double, double);

double positron_Momentum(double, double);

double neutron_Energy(double, double);

double neutron_Momentum(double, double);

double neutron_Angle(double, double);

double neutron_Kinetic_Energy(double, double);

#endif