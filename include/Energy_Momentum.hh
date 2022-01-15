#ifndef Energy_Momentum
#define Energy_Momentum

extern const double M_p;
extern const double M_n;
extern const double m_e;
extern const double M;
extern const double Delta;
extern const double y2;

double positron_Energy(double, double);

double positron_Momentum(double, double);

double neutron_Energy(double, double);

double neutron_Momentum(double, double);

double neutron_Angle(double, double);

double neutron_Kinetic_Energy(double, double);

#endif