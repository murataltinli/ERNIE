#include "Reactor_Antineutrino_Flux.h"
#include "Positron_Angle.h"
#include "Energy_Momentum.h"
#include "IBD_Cross_Section.h"

#include <random>
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"

using namespace std;

#include "HepMC3/GenEvent.h"
#include "HepMC3/GenVertex.h"
#include "HepMC3/GenParticle.h"
#include "HepMC3/Print.h"
#include "HepMC3/Selector.h"
#include "HepMC3/WriterAscii.h"

using namespace HepMC3;

void IBD_Event_Generator
(
  int n = 10000,
  int seed = 1,
  const char* rootFileName = "Reactor_Antineutrino_IBD_Events.root",
  const char* hepmc3FileName = "Reactor_Antineutrino_IBD_Events.hepmc3",
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
  double m_e = 0.511; // positron mass (MeV/c^2)
  double m = 0;
  double x, y, costheta_e, sintheta_e, costheta_n, phi_e,
  E_n, KE_n, E_e, KE_e, p_n, p_e, px_e, px_n, py_e, py_n, pz_e, pz_n, pT_e;

  double b[5] = {};
  int g = 0;
  int par[5] =   {0, // Total
                  5, // U235
                  9, // Pu239
                  8, // U238
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

  TTree *t[5] = {t0, t5, t9, t8, t1};

  WriterAscii asc(hepmc3FileName);

  for(int p = 0; p < 5; ++p)
  {
    t[p]->Branch("Enu",&x);
    t[p]->Branch("cose",&costheta_e);
    t[p]->Branch("cosn",&costheta_n);
    t[p]->Branch("Ee",&E_e);
    t[p]->Branch("Te",&KE_e);
    t[p]->Branch("En",&E_n);
    t[p]->Branch("Tn",&KE_n);
    t[p]->Branch("pe",&p_e);
    t[p]->Branch("pn",&p_n);
    t[p]->Branch("pxe",&px_e);
    t[p]->Branch("pxn",&px_n);
    t[p]->Branch("pye",&py_e);
    t[p]->Branch("pyn",&py_n);
    t[p]->Branch("pze",&pz_e);
    t[p]->Branch("pzn",&pz_n);
    
    while(p > 0)
    { 
      ++b[p];

      x = distribution(generator) * (xmax - xmin) + xmin;
      y = distribution(generator) * RAFlux(xmin,5,power,f5,f8,f9,f1) * IBDSigmaTot0(xmax);
      phi_e = distribution(generator) * 2 * M_PI;

      if(b[p]==b[1] && p>1)
      {
        break;
      }

      if(y <= RAFlux(x,par[p],power,f5,f8,f9,f1) * IBDSigmaTot0(x))
      {    
        costheta_e = positron_Angle(x,10000000 * seed + b[p] + 1); 
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
        t[p]->Fill();
        t0->Fill();

        GenEvent evt(Units::MEV,Units::CM);
        GenParticlePtr p1 = make_shared<GenParticle>(FourVector(0.0, 0.0, 0.0, 938.2720813), 2212,  4); // proton
        GenParticlePtr p2 = make_shared<GenParticle>(FourVector(0.0, 0.0, x, x), -12, 4); // antineutrino
        GenParticlePtr p3 = make_shared<GenParticle>(FourVector(px_n, py_n, pz_n, E_n), 2112, 201); // neutron
        GenParticlePtr p4 = make_shared<GenParticle>(FourVector(px_e, py_e, pz_e, E_e), -11, 201); // positron

        GenVertexPtr v1 = std::make_shared<GenVertex>();
        v1->add_particle_in(p1);
        v1->add_particle_in(p2);
        v1->add_particle_out(p3);
        v1->add_particle_out(p4);

        evt.add_vertex(v1);

        shared_ptr<GenCrossSection> cross_section = make_shared<GenCrossSection>();
        evt.add_attribute("GenCrossSection",cross_section);

        cross_section->set_cross_section(IBDSigmaTot0(x),0);

        
        evt.set_event_number(g);
        g++;
        asc.write_event(evt);
      

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