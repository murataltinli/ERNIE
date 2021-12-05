/*
  Vogel, P., and J. F. Beacom. “Angular Distribution of Neutron Inverse Beta Decay,
   ν ¯ e + p → e + + n.” Physical Review D 60, no. 5 (July 27, 1999): 053003.
    https://doi.org/10.1103/PhysRevD.60.053003.
*/

#ifndef Positron_Angle
#define Positron_Angle

#include <iostream>
#include <random>
#include <cmath>

#include "MeanCosTheta.h"

using namespace std;

double positron_dist(double E_nu, double costheta_e)
{
  double f = 1;
  double f2 = 3.706;
  double g = 1.26;
  double M_p = 938.2720813; //proton mass (MeV/c^2)
  double M_n = 939.5654133; //neutron mass (MeV/c^2)
  double m_e = 0.511; // positron mass (MeV/c^2)
  double Delta = M_n - M_p; 
  double M = (M_n + M_p) / 2; // average nucleon mass
  double y = sqrt((pow(Delta,2) - pow(m_e,2)) / 2);
  double E_e = E_nu - (Delta); // positron energy (MeV)
  double p_e = sqrt(pow(E_e,2)-pow(m_e,2)); // positron momentum (MeV/c)
  double v_e = p_e / E_e; // positron velocity
  double E_e1 = E_e * (1 - (E_nu / M) * (1 - v_e * costheta_e)) - (pow(y,2) / M);
  double p_e1 = sqrt(pow(E_e1,2)-pow(m_e,2));
  double v_e1 = p_e1 / E_e1;
  double G_f = 1.1663787 * pow(10,-11); // Fermi coupling constant
  double costc = 0.974; // cosinus of cabbibo angle
  double Delta_R_inner = 0.024;
  double sigma0 = (pow(G_f,2) * pow(costc,2) / M_PI) * (1 +  Delta_R_inner);
  double Gamma = 2 * (f + f2) * g * ((2 * E_e + Delta) * (1 - v_e * costheta_e) - (pow(m_e,2) / E_e))
                + (pow(f,2) + pow(g,2)) * (Delta * (1 + v_e * costheta_e) + (pow(m_e,2) / E_e))
                + (pow(f,2) + 3 * pow(g,2)) * ((E_e + Delta) * (1 - (1 / v_e) * costheta_e) - Delta)
                + (pow(f,2) - pow(g,2)) * ((E_e + Delta) * (1 - (1 / v_e) * costheta_e) - Delta) * v_e * costheta_e;
  double result = (sigma0 / 2) * ((pow(f,2) + 3 * pow(g,2)) + (pow(f,2) - pow(g,2)) * v_e1 * costheta_e) * E_e1 * p_e1
             - (sigma0 / 2) * (Gamma / M) * E_e * p_e;
  return result;
}

double positron_Angle(double E_nu, int seed = 1)
{
  default_random_engine gen;
  gen.seed(seed); 
  
  uniform_real_distribution<double> d1(-1.0,1.0);
  uniform_real_distribution<double> d2(0.0,1.0);

  while(true)
  { 
    double x = d1(gen);
    
    if(meanCosTheta(E_nu) < 0)
    {
      double y = d2(gen) * (positron_dist(E_nu,-1));   
      if(y <= positron_dist(E_nu,x))
      {
        return x;
        break;
      }
      else
      {
        continue;
      }  
    }
    else
    {
      double y = d2(gen) * (positron_dist(E_nu,1));
      if(y <= positron_dist(E_nu,x))
      {
        return x;
        break;
      }
      else
      {
        continue;
      }  
    }
  } 
}

#endif
