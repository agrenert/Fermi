#include "looper.h"

using namespace std;

void el_pt_looper()
{
  //===============================================================================|
  // TTBAR LOOPER (BACKGROUND)
  //===============================================================================|
  // Root directory String
  TString directoryString = "/nfs-7/userdata/phchang/WWW_babies";
  directoryString += "/WWW2018_v5.1.6/merged/";

  cout << directoryString << endl;
  // Creates TChain to read in files for ttbar
  TChain ttbar_chain("t");
  ttbar_chain.Add(directoryString + "ttbar_1ltbr_madgraph_1.root");
  ttbar_chain.Add(directoryString + "ttbar_1ltop_madgraph_1.root");
  ttbar_chain.Add(directoryString + "ttbar_semilep_powheg_1.root");
  ttbar_chain.Add(directoryString + "ttbar_dilep_powheg_1.root"  );
  ttbar_chain.Add(directoryString + "ttbar_dilep_powheg_2.root"  );

  // Sets all used branches to active status
  ttbar_chain.SetBranchStatus("*", 0);
  ttbar_chain.SetBranchStatus("el_pt", 1);
  ttbar_chain.SetBranchStatus("evt_scale1fb", 1);
  ttbar_chain.SetBranchStatus("met_pt", 1);
  ttbar_chain.SetBranchStatus("lep_pt", 1);
  ttbar_chain.SetBranchStatus("nb", 1);
  ttbar_chain.SetBranchStatus("MjjL", 1);
  ttbar_chain.SetBranchStatus("jets30_p4", 1);

  // Creates histograms to store data from TChain
  TH1D* ttbar_el_pt_hist = new TH1D("ttbar_el_pt",
                                    "ttbar background electron momentum",
                                    100, 20, 200);
  TH1D* ttbar_jets30_hist = new TH1D("ttbar_jets30", "ttbar amount of jets",
                                     8, 0, 32);
  TH1D* ttbar_MjjL_hist = new TH1D("ttbar_MjjL", "ttbar leading MjjL",
                                   100, 20, 500);
  TH1D* ttbar_met_pt_hist = new TH1D("ttbar_met_pt", "ttbar met momentum",
                                     100, 20, 200);
  TH1D* ttbar_lep_pt_hist_1 = new TH1D("ttbar_lep_pt_1", "ttbar lep momentum 1",
                                     100, 20, 200);
  TH1D* ttbar_lep_pt_hist_2 = new TH1D("ttbar_lep_pt_2", "ttbar lep momentum 2",
                                     100, 20, 200);
  TH1D* ttbar_nb_hist = new TH1D("ttbar_nb", "ttbar number of b jets",
                                 6, 0, 6);

  // Sets all branch addresses and declares reference variables
  Float_t  ttbar_el_pt;
  TBranch* ttbar_el_pt_br;
  ttbar_chain.SetBranchAddress("el_pt", &ttbar_el_pt, &ttbar_el_pt_br);

  Float_t  ttbar_evt_scale1fb;
  TBranch* ttbar_evt_scale1fb_br;
  ttbar_chain.SetBranchAddress("evt_scale1fb", &ttbar_evt_scale1fb,
                               &ttbar_evt_scale1fb_br);

  vector<Int_t>* ttbar_jets30 = NULL;
  TBranch*         ttbar_jets30_br;
  ttbar_chain.SetBranchAddress("jets30_p4", &ttbar_jets30, &ttbar_jets30_br);

  Float_t  ttbar_MjjL;
  TBranch* ttbar_MjjL_br;
  ttbar_chain.SetBranchAddress("MjjL", &ttbar_MjjL, &ttbar_MjjL_br);

  Float_t  ttbar_met_pt;
  TBranch* ttbar_met_pt_br;
  ttbar_chain.SetBranchAddress("met_pt", &ttbar_met_pt, &ttbar_met_pt_br);

  vector<Float_t>* ttbar_lep_pt = NULL;
  TBranch*         ttbar_lep_pt_br;
  ttbar_chain.SetBranchAddress("lep_pt", &ttbar_lep_pt, &ttbar_lep_pt_br);

  Int_t    ttbar_nb;
  TBranch* ttbar_nb_br;
  ttbar_chain.SetBranchAddress("nb", &ttbar_nb, &ttbar_nb_br);

  // loops through ttbar data and fills various histograms
  Int_t ttbar_n_entries = ttbar_chain.GetEntries();
  Int_t entry_count = 0; // used for displaying entries to screen
  for (UInt_t i = 0; i < ttbar_n_entries; i++)
    {
      ttbar_chain.GetEntry(i);

      if (ttbar_el_pt > 20 && ttbar_el_pt < 200)
        {
          entry_count++;
          ttbar_el_pt_hist->Fill(ttbar_el_pt, 59 * ttbar_evt_scale1fb);
        }
      if (ttbar_nb > 0)
        ttbar_nb_hist->Fill(ttbar_nb, 59 * ttbar_evt_scale1fb);

      if (ttbar_MjjL > 20)
        ttbar_MjjL_hist->Fill(ttbar_MjjL, 59 * ttbar_evt_scale1fb);

      if (ttbar_met_pt > 20 && ttbar_met_pt < 200)
        ttbar_met_pt_hist->Fill(ttbar_met_pt, 59 * ttbar_evt_scale1fb);

      if (ttbar_lep_pt->at(0) > 20 && ttbar_lep_pt->at(0) < 200)
        ttbar_lep_pt_hist_1->Fill(ttbar_lep_pt->at(0), 59 * ttbar_evt_scale1fb);

      if (ttbar_lep_pt->at(1) > 20 && ttbar_lep_pt->at(1) < 200)
        ttbar_lep_pt_hist_2->Fill(ttbar_lep_pt->at(1), 59 * ttbar_evt_scale1fb);

      if (ttbar_jets30->size() > 0)
        ttbar_jets30_hist->Fill(ttbar_jets30->size(), 59 * ttbar_evt_scale1fb);
    }
  // Displays number of events in histogram
  cout << "==========================" << endl;
  cout << "ttbar: " << entry_count << " events." << endl;
  cout << "==========================" << endl;

  // Output File
  TFile* ttbar_output_file = new TFile("ttbar_distributions_2018.root", "recreate");
  ttbar_output_file->cd();
  ttbar_el_pt_hist->Write();
  ttbar_nb_hist->Write();
  ttbar_MjjL_hist->Write();
  ttbar_met_pt_hist->Write();
  ttbar_lep_pt_hist_1->Write();
  ttbar_lep_pt_hist_2->Write();
  ttbar_jets30_hist->Write();
  ttbar_output_file->Write();
  ttbar_output_file->Close();
  //===============================================================================|

  //===============================================================================|
  // WZ LOOPER (BACKGROUND)
  //===============================================================================|
  // Creates Chain for WZ background el pt
  TChain wz_chain("t");
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_1.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_3.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_4.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_5.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_6.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_7.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_8.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_9.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_10.root");
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_11.root");

  // Sets all used branches to active status
  wz_chain.SetBranchStatus("*", 0);
  wz_chain.SetBranchStatus("el_pt", 1);
  wz_chain.SetBranchStatus("evt_scale1fb", 1);
  wz_chain.SetBranchStatus("met_pt", 1);
  wz_chain.SetBranchStatus("lep_pt", 1);
  wz_chain.SetBranchStatus("nb", 1);
  wz_chain.SetBranchStatus("MjjL", 1);
  wz_chain.SetBranchStatus("jets30_p4", 1);

  // Creates all histograms for wz TChain
  TH1D* wz_el_pt_hist = new TH1D("wz_el_pt",
                                    "wz background electron momentum",
                                    100, 20, 200);
  TH1D* wz_jets30_hist = new TH1D("wz_jets30", "wz amount of jets",
                                     8, 0, 32);
  TH1D* wz_MjjL_hist = new TH1D("wz_MjjL", "wz leading MjjL",
                                   100, 20, 500);
  TH1D* wz_met_pt_hist = new TH1D("wz_met_pt", "wz met momentum",
                                     100, 20, 200);
  TH1D* wz_lep_pt_hist_1 = new TH1D("wz_lep_pt_1", "wz lep momentum 1",
                                       100, 20, 200);
  TH1D* wz_lep_pt_hist_2 = new TH1D("wz_lep_pt_2", "wz lep momentum 2",
                                       100, 20, 200);
  TH1D* wz_nb_hist = new TH1D("wz_nb", "wz number of b jets",
                                 6, 0, 6);

  // Sets branch addresses
  Float_t  wz_el_pt;
  TBranch* wz_el_pt_br;
  wz_chain.SetBranchAddress("el_pt", &wz_el_pt, &wz_el_pt_br);

  Float_t  wz_evt_scale1fb;
  TBranch* wz_evt_scale1fb_br;
  wz_chain.SetBranchAddress("el_pt", &wz_el_pt, &wz_el_pt_br);

  Float_t  wz_evt_scale1fb;
  TBranch* wz_evt_scale1fb_br;
  wz_chain.SetBranchAddress("evt_scale1fb", &wz_evt_scale1fb,
                               &wz_evt_scale1fb_br);

  vector<Int_t>* wz_jets30 = NULL;
  TBranch*         wz_jets30_br;
  wz_chain.SetBranchAddress("jets30_p4", &wz_jets30, &wz_jets30_br);

  Float_t  wz_MjjL;
  TBranch* wz_MjjL_br;
  wz_chain.SetBranchAddress("MjjL", &wz_MjjL, &wz_MjjL_br);

  Float_t  wz_met_pt;
  TBranch* wz_met_pt_br;
  wz_chain.SetBranchAddress("met_pt", &wz_met_pt, &wz_met_pt_br);

  vector<Float_t>* wz_lep_pt = NULL;
  TBranch*         wz_lep_pt_br;
  wz_chain.SetBranchAddress("lep_pt", &wz_lep_pt, &wz_lep_pt_br);

  Int_t    wz_nb;
  TBranch* wz_nb_br;
  wz_chain.SetBranchAddress("nb", &wz_nb, &wz_nb_br);

  // Loops through all data for wz
  Int_t wz_n_entries = wz_chain.GetEntries();
  entry_count = 0;

  for (UInt_t j = 0; j < wz_n_entries; j++)
    {
      wz_chain.GetEntry(j);

      if (wz_el_pt > 20 && wz_el_pt < 200)
        {
          entry_count++;
          wz_el_pt_hist->Fill(wz_el_pt, 59 * wz_evt_scale1fb);
        }
      if (wz_nb > 0)
        wz_nb_hist->Fill(wz_nb, 59 * wz_evt_scale1fb);

      if (wz_MjjL > 20)
        wz_MjjL_hist->Fill(wz_MjjL, 59 * wz_evt_scale1fb);
    
      if (wz_met_pt > 20 && wz_met_pt < 200)
        wz_met_pt_hist->Fill(wz_met_pt, 59 * wz_evt_scale1fb);

      if (wz_lep_pt->at(0) > 20 && wz_lep_pt->at(0) < 200)
        wz_lep_pt_hist_1->Fill(wz_lep_pt->at(0), 59 * wz_evt_scale1fb);

      if (wz_lep_pt->at(1) > 20 && wz_lep_pt->at(1) < 200)
        wz_lep_pt_hist_2->Fill(wz_lep_pt->at(1), 59 * wz_evt_scale1fb);

      if (wz_jets30->size() > 0)
        wz_jets30_hist->Fill(wz_jets30->size(), 59 * wz_evt_scale1fb);

    }

  // Displays number of events in histogram  
  cout << "==========================" << endl;
  cout << "wz: " << entry_count << " events." << endl;
  cout << "==========================" << endl;

  // Output File
  TFile* wz_output_file = new TFile("wz_distributions_2018.root", "recreate");
  wz_output_file->cd();
  wz_el_pt_hist->Write();
  wz_nb_hist->Write();
  wz_MjjL_hist->Write();
  wz_met_pt_hist->Write();
  wz_lep_pt_hist_1->Write();
  wz_lep_pt_hist_2->Write();
  wz_jets30_hist->Write();
  wz_output_file->Write();
  wz_output_file->Close();
  //===============================================================================|

  //===============================================================================|
  // WJETS LOOPER (BACKGROUND)
  //===============================================================================|
  // Creates Chain for wjets
  TChain wjets_chain("t");
  wjets_chain.Add(directoryString + "wjets_ht100_madgraph_1.root" );
  wjets_chain.Add(directoryString + "wjets_ht1200_madgraph_1.root");
  wjets_chain.Add(directoryString + "wjets_ht200_madgraph_1.root" );
  wjets_chain.Add(directoryString + "wjets_ht2500_madgraph_1.root");
  wjets_chain.Add(directoryString + "wjets_ht400_madgraph_1.root" );
  wjets_chain.Add(directoryString + "wjets_ht600_madgraph_1.root" );
  wjets_chain.Add(directoryString + "wjets_ht800_madgraph_1.root" );
  wjets_chain.Add(directoryString + "wjets_incl_madgraph_1.root"  );

  // Sets used branches to active status
  wjets_chain.SetBranchStatus("*", 0);
  wjets_chain.SetBranchStatus("el_pt", 1);
  wjets_chain.SetBranchStatus("evt_scale1fb", 1);
  wjets_chain.SetBranchStatus("met_pt", 1);
  wjets_chain.SetBranchStatus("lep_pt", 1);
  wjets_chain.SetBranchStatus("nb", 1);
  wjets_chain.SetBranchStatus("MjjL", 1);
  wjets_chain.SetBranchStatus("jets30_p4", 1);

  // Creates all histograms for wjets TChain
  TH1D* wjets_el_pt_hist = new TH1D("wjets_el_pt",
                                    "wjets background electron momentum",
                                    100, 20, 200);
  TH1D* wjets_jets30_hist = new TH1D("wjets_jets30", "wjets amount of jets",
                                     8, 0, 32);
  TH1D* wjets_MjjL_hist = new TH1D("wjets_MjjL", "wjets leading MjjL",
                                   100, 20, 500);
  TH1D* wjets_met_pt_hist = new TH1D("wjets_met_pt", "wjets met momentum",
                                     100, 20, 200);
  TH1D* wjets_lep_pt_hist_1 = new TH1D("wjets_lep_pt_1", "wjets lep momentum 1",
                                       100, 20, 200);
  TH1D* wjets_lep_pt_hist_2 = new TH1D("wjets_lep_pt_2", "wjets lep momentum 2",
                                       100, 20, 200);
  TH1D* wjets_nb_hist = new TH1D("wjets_nb", "wjets number of b jets",
                                 6, 0, 6);

  // Sets branch addresses
  Float_t  wjets_el_pt;
  TBranch* wjets_el_pt_br;
  wjets_chain.SetBranchAddress("el_pt", &wjets_el_pt, &wjets_el_pt_br);

  Float_t  wjets_evt_scale1fb;
  TBranch* wjets_evt_scale1fb_br;
  wjets_chain.SetBranchAddress("evt_scale1fb", &wjets_evt_scale1fb,
                               &wjets_evt_scale1fb_br);

  vector<Int_t>*   wjets_jets30 = NULL;
  TBranch*         wjets_jets30_br;
  wjets_chain.SetBranchAddress("jets30_p4", &wjets_jets30, &wjets_jets30_br);

  Float_t  wjets_MjjL;
  TBranch* wjets_MjjL_br;
  wjets_chain.SetBranchAddress("MjjL", &wjets_MjjL, &wjets_MjjL_br);

  Float_t  wjets_met_pt;
  TBranch* wjets_met_pt_br;
  wjets_chain.SetBranchAddress("met_pt", &wjets_met_pt, &wjets_met_pt_br);

  vector<Float_t>* wjets_lep_pt = NULL;
  TBranch*         wjets_lep_pt_br;
  wjets_chain.SetBranchAddress("lep_pt", &wjets_lep_pt, &wjets_lep_pt_br);

  Int_t    wjets_nb;
  TBranch* wjets_nb_br;
  wjets_chain.SetBranchAddress("nb", &wjets_nb, &wjets_nb_br);

  // Loops through all data for wjets
  Int_t wjets_n_entries = wjets_chain.GetEntries();
  entry_count = 0;

  for (UInt_t k = 0; k < wjets_n_entries; k++)
    {
      wjets_chain.GetEntry(k);

      if (wjets_el_pt > 20 && wjets_el_pt < 200)
        {
          entry_count++;
          wjets_el_pt_hist->Fill(wjets_el_pt, 59 * wjets_evt_scale1fb);
        }
      if (wjets_nb > 0)
        wjets_nb_hist->Fill(wjets_nb, 59 * wjets_evt_scale1fb);

      if (wjets_MjjL > 20)
        wjets_MjjL_hist->Fill(wjets_MjjL, 59 * wjets_evt_scale1fb);

      if (wjets_met_pt > 20 && wjets_met_pt < 200)
        wjets_met_pt_hist->Fill(wjets_met_pt, 59 * wjets_evt_scale1fb);

      if (wjets_lep_pt->at(0) > 20 && wjets_lep_pt->at(0) < 200)
        wjets_lep_pt_hist_1->Fill(wjets_lep_pt->at(0), 59 * wjets_evt_scale1fb);

      if (wjets_lep_pt->at(1) > 20 && wjets_lep_pt->at(1) < 200)
        wjets_lep_pt_hist_2->Fill(wjets_lep_pt->at(1), 59 * wjets_evt_scale1fb);

      if (wjets_jets30->size() > 0)
        wjets_jets30_hist->Fill(wjets_jets30->size(), 59 * wjets_evt_scale1fb);
  
    }

  // Displays number of events in histogram                                      
  cout << "==========================" << endl;
  cout << "wjets: " << entry_count << " events." << endl;
  cout << "==========================" << endl;

  // Output File
  TFile* wjets_output_file = new TFile("wjets_distributions_2018.root", "recreate");
  wjets_output_file->cd();
  wjets_el_pt_hist->Write();
  wjets_nb_hist->Write();
  wjets_MjjL_hist->Write();
  wjets_met_pt_hist->Write();
  wjets_lep_pt_hist_1->Write();
  wjets_lep_pt_hist_2->Write();
  wjets_jets30_hist->Write();
  wjets_output_file->Write();
  wjets_output_file->Close();
  //===============================================================================|

  //===============================================================================|
  // WWW LOOPER (SIGNAL)
  //===============================================================================|
  // Creates Chain
  TChain www_chain("t");
  www_chain.Add(directoryString + "www_amcatnlo_dilepfilter_1.root");

  // Sets all used branches to active status
  www_chain.SetBranchStatus("*", 0);
  www_chain.SetBranchStatus("el_pt", 1);
  www_chain.SetBranchStatus("evt_scale1fb", 1);
  www_chain.SetBranchStatus("met_pt", 1);
  www_chain.SetBranchStatus("lep_pt", 1);
  www_chain.SetBranchStatus("nb", 1);
  www_chain.SetBranchStatus("MjjL", 1);
  www_chain.SetBranchStatus("jets30_p4", 1);

  // Creates all histograms for www TChain
  TH1D* www_el_pt_hist = new TH1D("www_el_pt",
                                    "www signal electron momentum",
                                    100, 20, 200);
  TH1D* www_jets30_hist = new TH1D("www_jets30", "www amount of jets",
                                     8, 0, 32);
  TH1D* www_MjjL_hist = new TH1D("www_MjjL", "www leading MjjL",
                                   100, 20, 500);
  TH1D* www_met_pt_hist = new TH1D("www_met_pt", "www met momentum",
                                     100, 20, 200);
  TH1D* www_lep_pt_hist_1 = new TH1D("www_lep_pt_1", "www lep momentum 1",
                                       100, 20, 200);
  TH1D* www_lep_pt_hist_2 = new TH1D("www_lep_pt_2", "www lep momentum 2",
                                       100, 20, 200);
  TH1D* www_nb_hist = new TH1D("www_nb", "www number of b jets",
                                 6, 0, 6);
  // Sets all branch addresses
  Float_t  www_el_pt;
  TBranch* www_el_pt_br;
  www_chain.SetBranchAddress("el_pt", &www_el_pt, &www_el_pt_br);

  Float_t  www_evt_scale1fb;
  TBranch* www_evt_scale1fb_br;
  www_chain.SetBranchAddress("evt_scale1fb", &www_evt_scale1fb,
                               &www_evt_scale1fb_br);

  vector<Int_t>*   www_jets30 = NULL;
  TBranch*         www_jets30_br;
  www_chain.SetBranchAddress("jets30_p4", &www_jets30, &www_jets30_br);

  Float_t  www_MjjL;
  TBranch* www_MjjL_br;
  www_chain.SetBranchAddress("MjjL", &www_MjjL, &www_MjjL_br);

  Float_t  www_met_pt;
  TBranch* www_met_pt_br;
  www_chain.SetBranchAddress("met_pt", &www_met_pt, &www_met_pt_br);

  vector<Float_t>* www_lep_pt = NULL;
  TBranch*         www_lep_pt_br;
  www_chain.SetBranchAddress("lep_pt", &www_lep_pt, &www_lep_pt_br);

  Int_t    www_nb;
  TBranch* www_nb_br;
  www_chain.SetBranchAddress("nb", &www_nb, &www_nb_br);

  // Loops through all data for www
  Int_t www_n_entries = www_chain.GetEntries();
  entry_count = 0;

  for (UInt_t m = 0; m < www_n_entries; m++)
    {
      www_chain.GetEntry(m);

      if (www_el_pt > 20 && www_el_pt < 200)
        {
          entry_count++;
          www_el_pt_hist->Fill(www_el_pt, 59 * www_evt_scale1fb);
        }
      if (www_nb > 0)
        www_nb_hist->Fill(www_nb, 59 * www_evt_scale1fb);

      if (www_MjjL > 20)
        www_MjjL_hist->Fill(www_MjjL, 59 * www_evt_scale1fb);

      if (www_met_pt > 20 && www_met_pt < 200)
        www_met_pt_hist->Fill(www_met_pt, 59 * www_evt_scale1fb);

      if (www_lep_pt->at(0) > 20 && www_lep_pt->at(0) < 200)
        www_lep_pt_hist_1->Fill(www_lep_pt->at(0), 59 * www_evt_scale1fb);

      if (www_lep_pt->at(1) > 20 && www_lep_pt->at(1) < 200)
        www_lep_pt_hist_2->Fill(www_lep_pt->at(1), 59 * www_evt_scale1fb);

      if (www_jets30->size() > 0)
        www_jets30_hist->Fill(www_jets30->size(), 59 * www_evt_scale1fb);

    }

  // Displays number of events in histogram  
  cout << "==========================" << endl;
  cout << "www: " << entry_count << " events." << endl;
  cout << "==========================" << endl;

  // Output file
  TFile* www_output_file = new TFile("www_distributions_2018.root", "recreate");
  www_output_file->cd();
  www_el_pt_hist->Write();
  www_nb_hist->Write();
  www_MjjL_hist->Write();
  www_met_pt_hist->Write();
  www_lep_pt_hist_1->Write();
  www_lep_pt_hist_2->Write();
  www_jets30_hist->Write();
  www_output_file->Write();
  www_output_file->Close();
  //===============================================================================|

  //===============================================================================|
  // DATA LOOPER
  //===============================================================================|
  // Creates Chain
  TChain data_chain("t");
  data_chain.Add(directoryString + "data_Run2018Av1_em_1.root");
  data_chain.Add(directoryString + "data_Run2018Av2_ee_1.root");
  data_chain.Add(directoryString + "data_Run2018Av2_mm_1.root");
  data_chain.Add(directoryString + "data_Run2018Bv1_ee_1.root");
  data_chain.Add(directoryString + "data_Run2018Bv1_em_1.root");
  data_chain.Add(directoryString + "data_Run2018Bv1_mm_1.root");
  data_chain.Add(directoryString + "data_Run2018Cv1_ee_1.root");
  data_chain.Add(directoryString + "data_Run2018Cv1_em_1.root");
  data_chain.Add(directoryString + "data_Run2018Cv1_mm_1.root");
  data_chain.Add(directoryString + "data_Run2018Dv2_ee_1.root");
  data_chain.Add(directoryString + "data_Run2018Dv2_em_1.root");
  data_chain.Add(directoryString + "data_Run2018Dv2_mm_1.root");

  // Sets all used branches to active status
  data_chain.SetBranchStatus("*", 0);
  data_chain.SetBranchStatus("el_pt", 1);
  data_chain.SetBranchStatus("evt_scale1fb", 1);
  data_chain.SetBranchStatus("met_pt", 1);
  data_chain.SetBranchStatus("lep_pt", 1);
  data_chain.SetBranchStatus("nb", 1);
  data_chain.SetBranchStatus("MjjL", 1);
  data_chain.SetBranchStatus("jets30_p4", 1);

  // Creates histograms data TChain
  TH1D* data_el_pt_hist = new TH1D("data_el_pt",
                                    "data electron momentum",
                                    100, 20, 200);
  TH1D* data_jets30_hist = new TH1D("data_jets30", "data amount of jets",
                                     8, 0, 32);
  TH1D* data_MjjL_hist = new TH1D("data_MjjL", "data leading MjjL",
                                   100, 20, 500);
  TH1D* data_met_pt_hist = new TH1D("data_met_pt", "data met momentum",
                                     100, 20, 200);
  TH1D* data_lep_pt_hist_1 = new TH1D("data_lep_pt_1", "data lep momentum 1",
                                       100, 20, 200);
  TH1D* data_lep_pt_hist_2 = new TH1D("data_lep_pt_2", "data lep momentum 2",
                                       100, 20, 200);
  TH1D* data_nb_hist = new TH1D("data_nb", "data number of b jets",
                                 6, 0, 6);

  // Sets all branch addresses
  Float_t  data_el_pt;
  TBranch* data_el_pt_br;
  data_chain.SetBranchAddress("el_pt", &data_el_pt, &data_el_pt_br);

  Float_t  data_evt_scale1fb;
  TBranch* data_evt_scale1fb_br;
  data_chain.SetBranchAddress("evt_scale1fb", &data_evt_scale1fb,
                             &data_evt_scale1fb_br);

  vector<Int_t>* data_jets30 = NULL;
  TBranch*         data_jets30_br;
  data_chain.SetBranchAddress("jets30_p4", &data_jets30, &data_jets30_br);

  Float_t  data_MjjL;
  TBranch* data_MjjL_br;
  data_chain.SetBranchAddress("MjjL", &data_MjjL, &data_MjjL_br);

  Float_t  data_met_pt;
  TBranch* data_met_pt_br;
  data_chain.SetBranchAddress("met_pt", &data_met_pt, &data_met_pt_br);

  vector<Float_t>* data_lep_pt = NULL;
  TBranch*         data_lep_pt_br;
  data_chain.SetBranchAddress("lep_pt", &data_lep_pt, &data_lep_pt_br);

  Int_t    data_nb;
  TBranch* data_nb_br;
  data_chain.SetBranchAddress("nb", &data_nb, &data_nb_br);

  // Loops through data for data
  Int_t data_n_entries = data_chain.GetEntries();
  entry_count = 0;

  for (UInt_t n = 0; n < data_n_entries; n++)
    {
      data_chain.GetEntry(n);

      if (data_el_pt > 20 && data_el_pt < 200)
        {
          entry_count++;
          data_el_pt_hist->Fill(data_el_pt);
        }
      if (data_nb > 0)
        data_nb_hist->Fill(data_nb);

      if (data_MjjL > 20)
        data_MjjL_hist->Fill(data_MjjL);

      if (data_met_pt > 20 && data_met_pt < 200)
        data_met_pt_hist->Fill(data_met_pt);

      if (data_lep_pt->at(0) > 20 && data_lep_pt->at(0) < 200)
        data_lep_pt_hist_1->Fill(data_lep_pt->at(0));

      if (data_lep_pt->at(1) > 20 && data_lep_pt->at(1) < 200)
        data_lep_pt_hist_2->Fill(data_lep_pt->at(1));

      if (data_jets30->size() > 0)
        data_jets30_hist->Fill(data_jets30->size());
    }

  // Displays number of events in histogram 
  cout << "==========================" << endl;
  cout << "data: " << entry_count << " events." << endl;
  cout << "==========================" << endl;

  // Output file
  TFile* data_output_file = new TFile("data_distributions_2018.root", "recreate");
  data_output_file->cd();
  data_el_pt_hist->Write();
  data_nb_hist->Write();
  data_MjjL_hist->Write();
  data_met_pt_hist->Write();
  data_lep_pt_hist_1->Write();
  data_lep_pt_hist_2->Write();
  data_jets30_hist->Write();
  data_output_file->Write();
  data_output_file->Close();
  //===============================================================================|
}
