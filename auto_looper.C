#include "universal.h"

using namespace std;

void processChain(TChain &chain, TString process, Bool_t isData)
{
  // Sets all used branches to active status                                           
  chain.SetBranchStatus("*", 0);
  chain.SetBranchStatus("el_pt", 1);
  chain.SetBranchStatus("evt_scale1fb", 1);
  chain.SetBranchStatus("met_pt", 1);
  chain.SetBranchStatus("lep_pt", 1);
  chain.SetBranchStatus("nb", 1);
  chain.SetBranchStatus("MjjL", 1);
  chain.SetBranchStatus("nj30", 1);
  chain.SetBranchStatus("mu_pt", 1);

  // Creates histograms to store data from the chain                                   
  TH1D* el_pt_hist    = new TH1D(process + "_el_pt" , process + " electron momentum",
                                 100, 20 , 200);
  TH1D* mu_pt_hist    = new TH1D(process + "_mu_pt" , process + " muon momentum",
                                 100, 20 , 200);
  TH1D* nj30_hist     = new TH1D(process + "_nj30"  , process + " amount of jets"   ,
                                 9  , 0.5, 9.5);
  TH1D* MjjL_hist     = new TH1D(process + "_MjjL"  , process + " leading MjjL"     ,
                                 100, 20 , 500);
  TH1D* met_pt_hist   = new TH1D(process + "_met_pt", process + " met momentum"     ,
                                 100, 20 , 200);
  TH1D* lep_pt_hist_1 = new TH1D(process + "_lep_pt_1", process + " lep momentum 1" ,
                                 100, 20 , 200);
  TH1D* lep_pt_hist_2 = new TH1D(process + "_lep_pt_2", process + " lep momentum 2" ,
                                 100, 20 , 200);
  TH1D* nb_hist       = new TH1D(process + "_nb"    , process + " number of b jets" ,
                                 5  , 0.5, 5.5);
  TH1D* n_lep_hist    = new TH1D(process + "_n_lep" , process + " number of leptons",
                                 2  , 1.5, 3.5);

  // Sets all branch addresses and declares reference variables                        
  Float_t  el_pt;
  TBranch* el_pt_br;
  chain.SetBranchAddress("el_pt", &el_pt, &el_pt_br);

  Float_t  mu_pt;
  TBranch* mu_pt_br;
  chain.SetBranchAddress("mu_pt", &mu_pt, &mu_pt_br);

  Float_t  evt_scale1fb;
  TBranch* evt_scale1fb_br;
  chain.SetBranchAddress("evt_scale1fb", &evt_scale1fb,
                               &evt_scale1fb_br);

  Int_t    nj30;
  TBranch* nj30_br;
  chain.SetBranchAddress("nj30", &nj30, &nj30_br);

  Float_t  MjjL;
  TBranch* MjjL_br;
  chain.SetBranchAddress("MjjL", &MjjL, &MjjL_br);

  Float_t  met_pt;
  TBranch* met_pt_br;
  chain.SetBranchAddress("met_pt", &met_pt, &met_pt_br);

  vector<Float_t>* lep_pt = NULL;
  TBranch*         lep_pt_br;
  chain.SetBranchAddress("lep_pt", &lep_pt, &lep_pt_br);
  
  Int_t    nb;
  TBranch* nb_br;
  chain.SetBranchAddress("nb", &nb, &nb_br);

  // loops through all data and fills the desired histograms                           
  Int_t n_entries = chain.GetEntries();
  int entry_count = 0;

  // sets the weight                                                                   
  Float_t LUMI_2018 = 59.00;
  Float_t weight;
  for (UInt_t i = 0; i < n_entries; i++)
    {
      chain.GetEntry(i);

      if (isData == 0)
        weight = LUMI_2018 * evt_scale1fb;
      else if (isData == 1)
        weight = 1;

      if (el_pt > 20 && el_pt < 200)
        {
          entry_count++;
          el_pt_hist->Fill(el_pt, weight);
        }

      if (mu_pt > 20 && mu_pt < 200)
        mu_pt_hist->Fill(mu_pt, weight);

      if (nb > 0)
        nb_hist->Fill(nb, weight);

      if (MjjL > 20)
        MjjL_hist->Fill(MjjL, weight);

      if (met_pt > 20 && met_pt < 200)
        met_pt_hist->Fill(met_pt, weight);

      if (lep_pt->at(0) > 20 && lep_pt->at(0) < 200)
        lep_pt_hist_1->Fill(lep_pt->at(0), weight);

      if (lep_pt->at(1) > 20 && lep_pt->at(1) < 200)
        lep_pt_hist_2->Fill(lep_pt->at(1), weight);
        
      if (nj30 > 0)
        nj30_hist->Fill(nj30, weight);

      if (lep_pt->size() > 0)
        n_lep_hist->Fill(lep_pt->size(), weight);
    }

  // Displays number of events in histograms                                           
  cout << "|================================|" << endl;
  cout << "| " << process << ": " << entry_count << " events." << endl;
  cout << "|================================|" << endl;

  // Output File                                                                       
  TString save_directory = "~/distributions/";
  TString output_file_name = "_distributions_2018.root";
  output_file_name = process + output_file_name;
  TFile* output_file = new TFile(save_directory + output_file_name, "recreate");
  output_file->cd();
  el_pt_hist->Write();
  mu_pt_hist->Write();
  nb_hist->Write();
  MjjL_hist->Write();
  met_pt_hist->Write();
  lep_pt_hist_1->Write();
  lep_pt_hist_2->Write();
  nj30_hist->Write();
  n_lep_hist->Write();
  output_file->Write();
  output_file->Close();
}
