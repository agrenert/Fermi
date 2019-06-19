#include "TCanvas.h"
#include "TH2.h"
#include "TMath.h"
#include "TROOT.h"
#include "TDirectory.h"
#include "TChain.h"
#include "TTree.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void looper()
{
  // Input and Output Setup                                                                
  TString inputFileName = "www_amcatnlo_dilepfilter_1.root";
  TString outputFileName = "www_amcatnlo_signalfilter_1.root";
  TString treeName = "t_www"; // signal event tree                                         

  TFile* inputFile = new TFile(inputFileName);
  TFile* outputFile = new TFile(outputFileName,"recreate");

  // checks if file opened correctly                                                       
  if (inputFileName == 0)
    {
      cout << "Fatal error: file '" << inputFileName << "' does not exist." << endl;
      return;
    }
  inputFile->cd();

  // Finds tree                                                                            
  TTree* tree;
  inputFile->GetObject(treeName,tree);
  if (tree == 0)
    {
      cout << "Error: TTree \"tree\" was not found." << endl;
      return;
    }

  else
    {
    // Output tree                                                                       
    TTree* out_tree = new TTree("Mu_el_pt_t_www","Output tree");

    // gets number of entries in tree                                                    
    Int_t numberOfEntries = tree->GetEntriesFast();

    // Defines the branches of the tree that we are interested in                        
    TBranch* el_pt_branch;
    TBranch* mu_pt_branch;

    // Variables that we will read from branched                                         
    Float_t el_pt;
    Float_t mu_pt;

    // connects the branches with the tree                                               
    tree->SetBranchAddress("el_pt" , &el_pt , &el_pt_branch );
    tree->SetBranchAddress("mu_pt" , &mu_pt , &mu_pt_branch );
    
    out_tree->Branch("el_pt", &el_pt);
    out_tree->Branch("mu_pt", &mu_pt);

    // creates histograms to fill                                                        
    TH1D* el_hist  = new TH1D("el_hist" ,"el_hist" , 100, 0, 400);
    TH1D* mu_hist  = new TH1D("mu_hist" ,"mu_hist" , 100, 0, 400);
    TH1D* el_mu_90 = new TH1D("el_mu_90","el_mu_90", 100, 80, 90);

    // Loop to fill histogram(s)                                                         
    for (Int_t i = 0; i < numberOfEntries; i++)
      {
        // gets current loop entry                                                       
        tree->GetEntry(i);

        // applies cuts                                                                  
        if (el_pt > 0 && mu_pt > 0)
          {
            el_hist->Fill (el_pt );
            mu_hist->Fill (mu_pt );
          }
        if ((el_pt + mu_pt) >= 80 && (el_pt + mu_pt <= 90))
          {
            el_mu_90->Fill(el_pt + mu_pt);
          }

      }
    // Writes to output file                                                             
    outputFile->cd();
    out_tree->Write();
    el_hist->Write();
    mu_hist->Write();
    el_mu_90->Write();
    outputFile->Close();
    inputFile->Close();
  }
}
