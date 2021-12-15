#include "Reactor_Antineutrino_Flux0.h"

#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"

void Flux_Graph()
{
  double xmin = 1.8;
  double xmax = 8;
  TCanvas *c1 = new TCanvas("Reactor_Antineutrino_Flux","Reactor Antineutrino Flux");
  
  TF1 *fs = new TF1("3.2 GW_{th} Reactor Antineutrino Flux",RAFlux0,xmin,xmax,2);
  TF1 *f5 = new TF1("Flux",RAFlux0,xmin,xmax,2);
  TF1 *f8 = new TF1("Flux",RAFlux0,xmin,xmax,2);
  TF1 *f9 = new TF1("Flux",RAFlux0,xmin,xmax,2);
  TF1 *f1 = new TF1("Flux",RAFlux0,xmin,xmax,2);
  TF1 *fe = new TF1("Flux",RAFlux0,xmin,xmax,2);
  TF1 *f15 = new TF1("Flux",RAFlux0,xmin,xmax,2);
  TF1 *f18 = new TF1("Flux",RAFlux0,xmin,xmax,2);
  TF1 *f19 = new TF1("Flux",RAFlux0,xmin,xmax,2);
  TF1 *f11 = new TF1("Flux",RAFlux0,xmin,xmax,2);
  
  fs->SetParameter(0,0);
  f5->SetParameter(0,5);
  f8->SetParameter(0,8);
  f9->SetParameter(0,9);
  f1->SetParameter(0,1);
  fe->SetParameter(0,10);
  f15->SetParameter(0,15);
  f18->SetParameter(0,18);
  f19->SetParameter(0,19);
  f11->SetParameter(0,11);

  fs->SetLineColor(kRed);
  f5->SetLineColor(kOrange);
  f8->SetLineColor(kViolet);
  f9->SetLineColor(kGreen);
  f1->SetLineColor(kCyan);
  fe->SetLineColor(kRed+2);
  f15->SetLineColor(kOrange+2);
  f18->SetLineColor(kViolet+2);
  f19->SetLineColor(kGreen+2);
  f11->SetLineColor(kCyan+2);

  auto legend = new TLegend(0.7,0.5,0.9,0.9);
  //legend->SetHeader("","C");
  legend->AddEntry(fs,"Total (start)","l");
  legend->AddEntry(fe,"Total (end)","l");
  legend->AddEntry(f5,"^{235}U (start)","l");
  legend->AddEntry(f15,"^{235}U (end)","l");
  legend->AddEntry(f19,"^{239}Pu (end)","l");
  legend->AddEntry(f9,"^{239}Pu (start)","l");
  legend->AddEntry(f11,"^{241}Pu (end)","l");
  legend->AddEntry(f18,"^{238}U (end)","l");
  legend->AddEntry(f8,"^{238}U (start)","l");
  legend->AddEntry(f1,"^{241}Pu (start)","l");
  
  fs->Draw();
  legend->Draw();
  
  fs->GetHistogram()->GetXaxis()->SetTitle("Energy (MeV)");
  fs->GetHistogram()->GetYaxis()->SetTitle("N_{#bar{#nu}_{e}} / s");
  
  f5->Draw("SAME");
  f8->Draw("SAME");
  f9->Draw("SAME");
  f1->Draw("SAME");
  f15->Draw("SAME");
  f18->Draw("SAME");
  f19->Draw("SAME");
  f11->Draw("SAME");
  fe->Draw("SAME");
  
  c1->Modified();

  c1->Print("Reactor_Antineutrino_Flux_Graph.eps");
}