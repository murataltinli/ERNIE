#include "IBD_Events.h"

#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"

void IBD_Events_Graph()
{
  double xmin = 1.8;
  double xmax = 10;
  
  TCanvas *c1 = new TCanvas("IBD_Events","IBD_Events");
  
  TF1 *f0 = new TF1("IBD Events",IBDEvents,xmin,xmax,2);
  TF1 *f5 = new TF1("IBD",IBDEvents,xmin,xmax,2);
  TF1 *f8 = new TF1("IBD",IBDEvents,xmin,xmax,2);
  TF1 *f9 = new TF1("IBD",IBDEvents,xmin,xmax,2);
  TF1 *f1 = new TF1("IBD",IBDEvents,xmin,xmax,2);

  f0->SetParameter(0,0);
  f5->SetParameter(0,5);
  f8->SetParameter(0,8);
  f9->SetParameter(0,9);
  f1->SetParameter(0,1);

  f0->SetLineColor(kRed);
  f5->SetLineColor(kOrange);
  f8->SetLineColor(kViolet);
  f9->SetLineColor(kGreen);
  f1->SetLineColor(kCyan);

  auto legend = new TLegend(0.7,0.5,0.9,0.9);
  //legend->SetHeader("","C");
  legend->AddEntry(f0,"Total","l");
  legend->AddEntry(f5,"^{235}U","l");
  legend->AddEntry(f9,"^{239}Pu","l");
  legend->AddEntry(f8,"^{238}U","l");
  legend->AddEntry(f1,"^{241}Pu","l");
  
  f0->Draw();
  legend->Draw();
  
  f0->GetHistogram()->GetXaxis()->SetTitle("Energy (MeV)");
  f0->GetHistogram()->GetYaxis()->SetTitle("Events");
  f0->GetHistogram()->GetXaxis()->SetRangeUser(0.,10.);
  
  f5->Draw("SAME");
  f8->Draw("SAME");
  f9->Draw("SAME");
  f1->Draw("SAME");
  
  c1->Modified();
}
