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
  int numberOfEvents,
  int seed,
  const char* rootFileName,
  double power, // reactor thermal power (W)
  double time,
  FissionFraction fFrac
)  
{
  double xmax = 9;
  double xmin = 1.806;
  double x, y;

  int par[5] =   {0, // Total
                  5, // U235
                  8, // U238
                  9, // Pu239
                  1}; // Pu241

  // pseudorandom number generator
  default_random_engine generator;
  generator.seed(seed);
  uniform_real_distribution<double> uniformDist(0.0,1.0);

  TTree* t0 = new TTree("Total","E_nu");
  TTree* t5 = new TTree("U235","E_nu");
  TTree* t8 = new TTree("U238","E_nu");
  TTree* t9 = new TTree("Pu239","E_nu");
  TTree* t1 = new TTree("Pu241","E_nu");

  TTree *tree[5] = {t0, t5, t8, t9, t1};

  for(int i = 0; i < 5; ++i)
  {
    tree[i]->Branch("Enu",&x);
  }  
  
  double counter = 0;
  while(counter<numberOfEvents)
  { 
    for(int i = 1; i < 5; i++)
    {
      x = uniformDist(generator) * (xmax - xmin) + xmin;
      y = uniformDist(generator) * RAFlux(xmin,5,power,time,fFrac);
      
      if(y <= RAFlux(x,par[i],power,time,fFrac))
      {    
        ++counter;

        tree[i]->Fill();
        t0->Fill();       
      }
    }
  }

  TFile file(rootFileName,"RECREATE");
    
  for(int i = 0; i < 5; ++i)
  {
    tree[i]->Write();
  }

  file.Close();

}