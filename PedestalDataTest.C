

void PedestalDataTest()
{

  int nadc = 24;
  int nch = 1536;
  TFile *f_in = new TFile("./pedestal/pedestal-00001779-0000.root","r");
  TTree *t_in = (TTree*) f_in->Get("W");
  
  TH1D *h_ped[1536];

  TH1D *h_ped_avg_ADC[24];
  TH1D *h_ped_var_ADC[24];

 
  for (int i = 0 ; i < nadc ; i++)
    {
      h_ped_avg_ADC[i] = new TH1D();
      h_ped_var_ADC[i] = new TH1D();
    }

  TH1D *h_ped_avg_ALL = new TH1D();
  TH1D *h_ped_var_ALL = new TH1D();

  TNtuple *tn_adc[24];
  TNtuple *tn_all = new TNtuple("tn_all","", "ped_mean:ped_var");
  
  for (int i = 0; i < nadc; i++)
    {
      tn_adc[i] = new TNtuple(Form("tn_adc_%d", i), "", "ped_mean:ped_var");
    }

  TCanvas *c = new TCanvas();
  gPad->SetLogy(1);

  for (int i = 0; i < nch; i++)
    {
  
      std::cout<< "i: "<<i<<std::endl;
      t_in->Draw(Form("pedestal[%d]>>htempo_%d", i, i),Form("pedestal[%d] > 0", i),"goff");
      h_ped[i] = (TH1D*)gDirectory->Get(Form("htempo_%d", i));
      h_ped[i]->SetName(Form("h_ped_%d",i));
  
      tn_all->Fill(h_ped[i]->GetMean(), h_ped[i]->GetRMS());
      tn_adc[static_cast<int>(floor(i/64))]->Fill(h_ped[i]->GetMean(), h_ped[i]->GetRMS());
    }
    
  for (int i = 0; i < nadc; i++)
    {
      
      tn_adc[i]->Draw(Form("ped_mean>>htempa_%d", i),"","goff");
      h_ped_avg_ADC[i] = (TH1D*)gDirectory->Get(Form("htempa_%d",i));
      h_ped_avg_ADC[i]->SetName(Form("h_ped_avg_ADC_%d",i));

      tn_adc[i]->Draw(Form("ped_var>>htempv_%d",i),"","goff");
      h_ped_var_ADC[i] = (TH1D*)gDirectory->Get(Form("htempv_%d",i));
      h_ped_var_ADC[i]->SetName(Form("h_ped_var_ADC_%d",i));

    }

  tn_all->Draw("ped_mean>>htempaa","","goff");
  h_ped_avg_ALL = (TH1D*)gDirectory->Get("htempaa");
  h_ped_avg_ALL->SetName("h_ped_avg_ALL");

  tn_all->Draw("ped_var>>htempav","","goff");
  h_ped_var_ALL = (TH1D*)gDirectory->Get("htempav");
  h_ped_var_ALL->SetName("h_ped_var_ALL");


  TFile *fout = new TFile("pedestal_1779.root","recreate");
  h_ped_avg_ALL->Write();
  h_ped_var_ALL->Write();
  for (int i = 0; i < nadc; i++)
    {
      h_ped_avg_ADC[i]->Write();
      h_ped_var_ADC[i]->Write();
    }
  for (int i = 0; i < nch; i++)
    {
      h_ped[i]->Write();
    }
  fout->Close();
  
}
