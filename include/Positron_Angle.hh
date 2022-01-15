#ifndef Positron_Angle
#define Positron_Angle

#include <random>

extern const double m_e;
extern const double M;
extern const double Delta;
extern const double y2;

double positron_dist(double, double);

double positron_Angle(double, std::default_random_engine&);

#endif