#include "Reactor_Antineutrino_Generator.hh"

#include "Positron_Angle.hh"
#include "Energy_Momentum.hh"

#include <random>
#include <iostream>

#include "TFile.h"
#include "TTree.h"

using namespace std;

void Reactor_Antineutrino_Generate
(
  int numberOfEvents,
  int seed,
  const char* rootFileName,
  double power, // reactor thermal power (W)
  double time,
  FissionFraction fFrac,
  bool Mills
)  
{
  const double xmax = 9;
  const double xmin = 1.806;
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

  TTree* tree0 = new TTree("Total","E_nu");
  TTree* tree5 = new TTree("U235","E_nu");
  TTree* tree8 = new TTree("U238","E_nu");
  TTree* tree9 = new TTree("Pu239","E_nu");
  TTree* tree1 = new TTree("Pu241","E_nu");

  TTree *tree[5] = {tree0, tree5, tree8, tree9, tree1};

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
      y = uniformDist(generator) * RAFlux(xmin,par[1],power,time,fFrac,Mills);
      
      if(y <= RAFlux(x,par[i],power,time,fFrac,Mills))
      {    
        ++counter;

        tree[i]->Fill();
        tree0->Fill();       
      }
      if(counter==numberOfEvents)
      {
        break;
      }
    }
  }

  TFile file(rootFileName,"RECREATE");
    
  for(int i = 0; i < 5; ++i)
  {
    if(tree[i]->GetEntries() == 0)
    { 
      cout << "\033[1;35mWarning:\033[0m " << tree[i]->GetName() << " tree is empty!" << endl;
      continue;
    }
    tree[i]->Write();    
  }

  file.Close();

}