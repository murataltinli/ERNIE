/******************************************************************************
Reference:
P. Vogel and J. F. Beacom
“Angular distribution of neutron inverse beta decay”
Phys. Rev. D 60, 053003 (1999)
https://doi.org/10.1103/PhysRevD.60.053003
*******************************************************************************/

#include "Positron_Angle.hh"

#include <random>
#include <cmath>

using namespace std;

double positron_dist(double E_nu, double costheta_e)
{
  const double f = 1;
  const double f2 = 3.706;
  const double g = 1.26;
  const double E_e = E_nu - (Delta); // positron energy (MeV)
  const double p_e = sqrt(pow(E_e,2)-pow(m_e,2)); // positron momentum (MeV/c)
  const double v_e = p_e / E_e; // positron velocity
  const double E_e1 = E_e * (1 - (E_nu / M) * (1 - v_e * costheta_e)) - (y2 / M);
  const double p_e1 = sqrt(pow(E_e1,2)-pow(m_e,2));
  const double v_e1 = p_e1 / E_e1;
  const double G_f = 1.1663787 * pow(10,-11); // Fermi coupling constant (MeV^-2)
  const double costc = 0.974; // cosinus of Cabibbo angle
  const double Delta_R_inner = 0.024; // nucleus independant radiative corrections
  const double sigma0 = (pow(G_f,2) * pow(costc,2) / M_PI) * (1 +  Delta_R_inner);
  const double Gamma = 2 * (f + f2) * g * ((2 * E_e + Delta) * (1 - v_e * costheta_e) - (pow(m_e,2) / E_e))
                + (pow(f,2) + pow(g,2)) * (Delta * (1 + v_e * costheta_e) + (pow(m_e,2) / E_e))
                + (pow(f,2) + 3 * pow(g,2)) * ((E_e + Delta) * (1 - (1 / v_e) * costheta_e) - Delta)
                + (pow(f,2) - pow(g,2)) * ((E_e + Delta) * (1 - (1 / v_e) * costheta_e) - Delta) * v_e * costheta_e;
  const double result = (sigma0 / 2) * ((pow(f,2) + 3 * pow(g,2)) + (pow(f,2) - pow(g,2)) * v_e1 * costheta_e) * E_e1 * p_e1
             - (sigma0 / 2) * (Gamma / M) * E_e * p_e;
  return result;
}

double positron_Angle(double E_nu, default_random_engine& generator)
{   
  uniform_real_distribution<double> uniformDist1(-1.0,1.0);
  uniform_real_distribution<double> uniformDist2(0.0,1.0);

  const double mincostheta_e = -1;

  while(true)
  { 
    double x = uniformDist1(generator);
    double y = uniformDist2(generator) * (positron_dist(E_nu,mincostheta_e));   
    if(y <= positron_dist(E_nu,x))
    {
      return x;
    }    
  } 
}