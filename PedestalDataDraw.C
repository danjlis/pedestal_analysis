#include "dlUtility.h"

void pedestal_draw()
{
  TFile *fin = new TFile("pedestal_out.root", "r");
  
  int nADC = 24;
  
  TCanvas *c = new TCanvas("c","c", 1000, 500);
  c->Divide(2);
  TH1D *h_ped_a;
  TH1D *h_ped_v;

  for (int j = 0; j < nADC; j++)
    {
      h_ped_a = (TH1D*) fin->Get(Form("h_ped_avg_ADC_%d", j));

      h_ped_v = (TH1D*) fin->Get(Form("h_ped_var_ADC_%d", j));

      h_ped_v->SetBins(20, h_ped_v->GetXaxis()->GetXmin(), h_ped_v->GetXaxis()->GetXmax());

      h_ped_a->SetBins(20, h_ped_a->GetXaxis()->GetXmin(), h_ped_a->GetXaxis()->GetXmax());

    
      h_ped_v->Scale(1./h_ped_v->Integral());
  
      h_ped_a->Scale(1./h_ped_a->Integral());
  
      c->cd(0);
  
      SetLineAtt(h_ped_a, kBlue+2, 2, 1);
      SetLineAtt(h_ped_v, kBlue+2, 2, 1);
      h_ped_a->SetFillColorAlpha(kBlue - 2, 0.3);
      h_ped_v->SetFillColorAlpha(kBlue - 2, 0.3);
        
        
      c->cd(1);
      h_ped_a->Draw("hist");
      
      c->cd(2);
      h_ped_v->Draw("hist");
        
      c->SaveAs(Form("pedestal_plots/ped_avg_var_ADC_%d.pdf", j));
    }

  
  return;
}
