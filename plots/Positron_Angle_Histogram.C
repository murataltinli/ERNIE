/*
  Vogel, P., and J. F. Beacom. “Angular Distribution of Neutron Inverse Beta Decay,
   ν ¯ e + p → e + + n.” Physical Review D 60, no. 5 (July 27, 1999): 053003.
    https://doi.org/10.1103/PhysRevD.60.053003.
*/

#include <random>
#include <cmath>
#include <string>

#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"

#include "MeanCosTheta.h"
#include "Positron_Angle.h"

using namespace std;

void Positron_Angle_Histogram(double E_nu = 2.51, int nmax = 100000, int seed = 1)
{
  default_random_engine gen;
  gen.seed(seed); 

  string title = "cos#theta_{e} distribution at E_{#nu}= " + to_string(E_nu) + " MeV";
  
  uniform_real_distribution<double> d1(-1.0,1.0);
  uniform_real_distribution<double> d2(0.0,1.0);
   
  TCanvas *c1 = new TCanvas("positron angle distribution"); 
  TH1F * h = new TH1F("cos#theta_{e}",title.c_str(), 80, -1, 1);
  h->GetXaxis()->SetTitle("cos#theta_{e}");

  for(int n=0; n<nmax;++n)
  { 
    double x = d1(gen);
    
    if(meanCosTheta(E_nu) < 0)
    {
      double y = d2(gen) * (positron_dist(E_nu,-1));   
      if(y <= positron_dist(E_nu,x))
      {
        h->Fill(x);
        h->Draw();
      }
      else
      {
        nmax++;
        continue;
      }  
    }
    else
    {
      double y = d2(gen) * (positron_dist(E_nu,1));
      if(y <= positron_dist(E_nu,x))
      {
        h->Fill(x);
        h->Draw();
      }
      else
      {
        nmax++;
        continue;
      }  
    }
  } 
  c1->Print("Positron_Angle_Histogram.eps");
}