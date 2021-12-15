#include "Reactor_Antineutrino_Flux.h"
#include "Positron_Angle.h"
#include "Energy_Momentum.h"

#include <random>
#include <iostream>

#include "TFile.h"
#include "TTree.h"

using namespace std;

void Reactor_Antineutrino_Generator
(
  int n = 10000,
  int seed = 1,
  const char* rootFileName = "Reactor_Antineutrino_Events.root",
  double power = 3.2 * pow(10, 9), // reactor power (W)
  
  // fission fractions
  double f5 = 0.763, // U235
  double f8 = 0.0476, // U238
  double f9 = 0.162, // Pu239
  double f1 = 0.027 // Pu241
)  
{
  double xmax = 9;
  double xmin = 1.806;
  double m = 0;
  double x, y;

  double b[5] = {};
  int par[5] =   {0, // Total
                  5, // U235
                  8, // U238
                  9, // Pu239
                  1}; // Pu241

  // pseudorandom number generator
  default_random_engine generator;
  generator.seed(seed);
  uniform_real_distribution<double> distribution(0.0,1.0);

  TTree* t0 = new TTree("Total","E_nu");
  TTree* t5 = new TTree("U235","E_nu");
  TTree* t8 = new TTree("U238","E_nu");
  TTree* t9 = new TTree("Pu239","E_nu");
  TTree* t1 = new TTree("Pu241","E_nu");

  TTree *t[5] = {t0, t5, t8, t9, t1};

  for(int p = 0; p < 5; ++p)
  {
    t[p]->Branch("Enu",&x);
    
    while(p > 0)
    { 
      ++b[p];

      x = distribution(generator) * (xmax - xmin) + xmin;
      y = distribution(generator) * RAFlux(xmin,5,power,f5,f8,f9,f1);

      if(b[p]==b[1] && p>1)
      {
        break;
      }

      if(y <= RAFlux(x,par[p],power,f5,f8,f9,f1))
      {    
        t[p]->Fill();
        t0->Fill();
      
        if(p==1)
        {
          ++m;
          if(m==n)
          {
            break;
          }
        } 
      }
      else
      {
        continue;
      }
    }
  }

  // Open a ROOT file
  TFile f(rootFileName,"RECREATE");
    
  for(int p = 0; p < 5; ++p)
  {
    t[p]->Write();
  }
  
  // Closing the ROOT file
  f.Close();

}
