#include "Reactor_Antineutrino_Flux.h"
#include <random>
#include <iostream>

#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"
#include "TBenchmark.h"
#include "TStyle.h"

using namespace std;

void Reactor_Antineutrino_Generator()
{
  int seed = 1; // pseudorandom generator seed
  int n = 1000000;
  double weight = 7.7 * pow(10,14);
  double xmax = 8;
  double xmin = 1.806;
  int bin = 31;

  int par[10] =   {0,   10,   5,   15,   19,   9,   11,  18,  8,   1}; 
  int color[10] = {632, 634,  800, 802,  418,  416, 434, 882, 880, 432};
  
  double m = 0;
  double b[10] ={};

  // pseudorandom number generator
  default_random_engine generator;
  generator.seed(seed); 
  uniform_real_distribution<double> distribution(0.0,1.0);
  
  TCanvas *c1 = new TCanvas("Generated_Reactor_Antineutrinos","Reactor_Antineutrinos",200,10,700,500);

  TH1F * h0 = new TH1F("Total (start)","", bin, xmin, xmax - .006);
  TH1F * h5 = new TH1F("U235 (start)","U235 (start)", bin, xmin, xmax- .006);
  TH1F * h8 = new TH1F("U238 (start)","U238 (start)", bin, xmin, xmax- .006);
  TH1F * h9 = new TH1F("Pu239 (start)","Pu239 (start)", bin, xmin, xmax- .006);
  TH1F * h1 = new TH1F("Pu241 (start)","Pu241 (start)", bin, xmin, xmax- .006);
  TH1F * h10 = new TH1F("Total (end)","Total (end)", bin, xmin, xmax- .006);
  TH1F * h15 = new TH1F("U235 (end)","U235 (end)", bin, xmin, xmax- .006);
  TH1F * h18 = new TH1F("U238 (end)","U238 (end)", bin, xmin, xmax- .006);
  TH1F * h19 = new TH1F("Pu239 (end)","Pu239 (end)", bin, xmin, xmax- .006);
  TH1F * h11 = new TH1F("Pu241 (end)","Pu241 (end)", bin, xmin, xmax- .006);

  TH1F *h[10] = {h0, h10, h5, h15, h19, h9, h11, h18, h8, h1};
  
  auto legend = new TLegend(0.5,0.5,0.7,0.9);
  legend->AddEntry(h0,"Total (start)","f");
  legend->AddEntry(h10,"Total (end)","f");
  legend->AddEntry(h5,"^{235}U (start)","f");
  legend->AddEntry(h15,"^{235}U (end)","f");
  legend->AddEntry(h19,"^{239}Pu (end)","f");
  legend->AddEntry(h9,"^{239}Pu (start)","f");
  legend->AddEntry(h11,"^{241}Pu (end)","f");
  legend->AddEntry(h18,"^{238}U (end)","f");
  legend->AddEntry(h8,"^{238}U (start)","f");
  legend->AddEntry(h1,"^{241}Pu (start)","f");

  gBenchmark->Start("H");

  
  for(int p = 2; p<10; ++p)
  {
    while(true)
    { 
      ++b[p];
      
      double x = distribution(generator) * (xmax - xmin) + xmin;
      double y = distribution(generator) * RAFlux(xmin,5);

      if(b[p]==b[2] && p>2)
      {
        break;
      }

      if(y <= RAFlux(x,par[p]))
      {      
        h[p]->Fill(x,weight);
        
        if(p==2)
        {
          ++m;
          if(m==n)
          {
            break;
          }
        }
        
        if(p == 2|| p == 5 || p == 8 ||p == 9)
        {
          h0->Fill(x,weight);
        }
        else
        {
          h10->Fill(x,weight);
        }
      }
      else
      {
        continue;
      }
    }
  }

  // draw histograms
  for(int p=0; p<10; ++p)
  {
    gStyle->SetOptStat(11);
    
    h[p]->SetLineColor(color[p]);
    h[p]->SetFillColor(color[p]);
   
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.9-.08*p);
   
    h[p]->Draw("histsames");
    c1->Update();
  }
  
  h0->GetXaxis()->SetTitle("Energy (MeV)");

  legend->Draw();

  gBenchmark->Show("H");
}