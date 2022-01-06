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
  int n,
  int seed,
  const char* rootFileName,
  double power, // reactor thermal power (W)
  double time,

  // fission fractions at the beginning of the reactor fuel cycle
  double f5_i, // U235
  double f8_i, // U238
  double f9_i, // Pu239
  double f1_i,  // Pu241
  // fission fractions at the end of the reactor fuel cycle
  double f5_f, // U235
  double f8_f, // U238
  double f9_f, // Pu239
  double f1_f  // Pu241
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
      y = distribution(generator) * RAFlux(xmin,5,power,time,f5_i,f8_i,f9_i,f1_i,f5_f,f8_f,f9_f,f1_f);

      if(b[p]==b[1] && p>1)
      {
        break;
      }

      if(y <= RAFlux(x,par[p],power,time,f5_i,f8_i,f9_i,f1_i,f5_f,f8_f,f9_f,f1_f))
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