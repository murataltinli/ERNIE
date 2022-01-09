#include "Reactor_Antineutrino_Flux.h"
#include "Positron_Angle.h"
#include "Energy_Momentum.h"
#include "IBD_Cross_Section.h"

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

void IBD_Event_Generator
(
  int n,
  int seed,
  const char* rootFileName,
  const char* hepmc3FileName,
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
  double m_e = 0.511; // positron mass (MeV/c^2)
  double m = 0;
  double x, y, costheta_e, sintheta_e, costheta_n, phi_e,
  E_n, KE_n, E_e, KE_e, p_n, p_e, px_e, px_n, py_e, py_n, pz_e, pz_n, pT_e;

  int seed2 = seed + 1;
  int g = 0;
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
  }
    
  int p = 0;
  while(true)
  { 
    ++p;
    if(p==5){p=1;}
    ++seed2;

    x = distribution(generator) * (xmax - xmin) + xmin;
    y = distribution(generator) 
        * RAFlux(3.4,5,power,time,f5_i,f8_i,f9_i,f1_i,f5_f,f8_f,f9_f,f1_f) * IBDSigmaTot0(4);
    phi_e = distribution(generator) * 2 * M_PI;

    if(y <= RAFlux(x,par[p],power,time,f5_i,f8_i,f9_i,f1_i,f5_f,f8_f,f9_f,f1_f) * IBDSigmaTot0(x))
    {    
      costheta_e = positron_Angle(x,seed2); 
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
      GenParticlePtr p1 = make_shared<GenParticle>(
        FourVector(0.0, 0.0, 0.0, 938.2720813), 2212,  4); // proton
      GenParticlePtr p2 = make_shared<GenParticle>(
        FourVector(0.0, 0.0, x, x), -12, 4); // antineutrino
      GenParticlePtr p3 = make_shared<GenParticle>(
        FourVector(px_n, py_n, pz_n, E_n), 2112, 1); // neutron
      GenParticlePtr p4 = make_shared<GenParticle>(
        FourVector(px_e, py_e, pz_e, E_e), -11, 1); // positron

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
      
      ++m;
      if(m==n)
      {
        break;
      }
    }
    else
    {
      continue;
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