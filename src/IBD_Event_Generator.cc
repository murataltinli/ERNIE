#include "IBD_Event_Generator.hh"

#include "Positron_Angle.hh"
#include "Energy_Momentum.hh"
#include "IBD_Cross_Section.hh"

#include <random>
#include <iostream>

#include "TFile.h"
#include "TTree.h"

using namespace std;

#include "HepMC3/GenEvent.h"
#include "HepMC3/GenVertex.h"
#include "HepMC3/GenParticle.h"
#include "HepMC3/WriterAscii.h"

using namespace HepMC3;

void IBD_Event_Generate
(
  int numberOfEvents,
  int seed,
  const char* rootFileName,
  const char* hepmc3FileName,
  double power, // reactor thermal power (W)
  double time,
  FissionFraction fFrac
)  
{
  double xmax = 9; // maximum neutrino energy 
  double xmin = 1.806; // minimum neutrino energy 
  double x, y, costheta_e, sintheta_e, costheta_n, phi_e,
  E_n, KE_n, E_e, KE_e, p_n, p_e, px_e, px_n, py_e, py_n, pz_e, pz_n, pT_e;

  // particle id
  const int pID_p = 2212; // proton
  const int pID_nu = -12; // antineutrino
  const int pID_n = 2112; // neutron
  const int pID_e = -11; // positron

  int eventNumber = 0;
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

  WriterAscii asc(hepmc3FileName);

  for(int i = 0; i < 5; ++i)
  {
    tree[i]->Branch("Enu",&x);
    tree[i]->Branch("cose",&costheta_e);
    tree[i]->Branch("cosn",&costheta_n);
    tree[i]->Branch("Ee",&E_e);
    tree[i]->Branch("Te",&KE_e);
    tree[i]->Branch("En",&E_n);
    tree[i]->Branch("Tn",&KE_n);
    tree[i]->Branch("pe",&p_e);
    tree[i]->Branch("pn",&p_n);
    tree[i]->Branch("pxe",&px_e);
    tree[i]->Branch("pxn",&px_n);
    tree[i]->Branch("pye",&py_e);
    tree[i]->Branch("pyn",&py_n);
    tree[i]->Branch("pze",&pz_e);
    tree[i]->Branch("pzn",&pz_n);
  }

  double counter = 0;
  while(counter<numberOfEvents)
  {  
    for(int i = 1; i < 5; i++)
    {
      x = uniformDist(generator) * (xmax - xmin) + xmin; // choose neutrino energy
      y = uniformDist(generator) * RAFlux(3.4,5,power,time,fFrac) * IBDSigmaTot0(4);
      phi_e = uniformDist(generator) * 2 * M_PI;
      
      if(y <= RAFlux(x,par[i],power,time,fFrac) * IBDSigmaTot0(x))
      { 
        ++counter;

        costheta_e = positron_Angle(x,generator); 
        sintheta_e =  sqrt(1-pow(costheta_e,2));
        E_e = positron_Energy(x,costheta_e);
        KE_e = E_e - m_e;
        p_e = positron_Momentum(x,costheta_e);
        E_n =  neutron_Energy(x,costheta_e);
        KE_n = neutron_Kinetic_Energy(x,costheta_e);
        p_n = neutron_Momentum(x,costheta_e);
        costheta_n = neutron_Angle(x,costheta_e);
        pT_e = p_e * sintheta_e;
        pz_e = p_e * costheta_e;
        pz_n = p_n * costheta_n;
        px_e = pT_e * cos(phi_e);
        py_e = pT_e * sin(phi_e);
        px_n = - px_e;
        py_n = - py_e;
        tree[i]->Fill();
        tree0->Fill();
        
        GenEvent event(Units::MEV,Units::CM);
        GenParticlePtr particle1 = make_shared<GenParticle>(FourVector(0.0, 0.0, 0.0, M_p), pID_p,  4);
        GenParticlePtr particle2 = make_shared<GenParticle>(FourVector(0.0, 0.0, x, x), pID_nu, 4);
        GenParticlePtr particle3 = make_shared<GenParticle>(FourVector(px_n, py_n, pz_n, E_n), pID_n, 1);
        GenParticlePtr particle4 = make_shared<GenParticle>(FourVector(px_e, py_e, pz_e, E_e), pID_e, 1);

        GenVertexPtr vertex1 = std::make_shared<GenVertex>();
        vertex1->add_particle_in(particle1);
        vertex1->add_particle_in(particle2);
        vertex1->add_particle_out(particle3);
        vertex1->add_particle_out(particle4);

        event.add_vertex(vertex1);

        shared_ptr<GenCrossSection> cross_section = make_shared<GenCrossSection>();
        event.add_attribute("GenCrossSection",cross_section);

        cross_section->set_cross_section(IBDSigmaTot0(x),0);
          
        event.set_event_number(eventNumber);
        eventNumber++;
        asc.write_event(event);
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