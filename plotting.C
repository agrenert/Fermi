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
#include <vector>

using namespace std;

void plotting()
{
  // Opens file to read info from                                                          
  TString inputFileName = "www_amcatnlo_signalfilter_1.root";

  TFile* inputFile = new TFile(inputFileName);
  if (inputFile == 0)
    {
      cout << "Fatal error: file '" << inputFileName << "' was unable to open" << endl;
      return;
    }
  inputFile->cd();


  // retrieves histograms                                                                  
  TH1D* el_hist  = NULL; inputFile->GetObject("el_hist" , el_hist );
  TH1D* mu_hist  = NULL; inputFile->GetObject("mu_hist" , mu_hist );
  TH1D* el_mu_90 = NULL; inputFile->GetObject("el_mu_90", el_mu_90);

  // Sets up canvas and graphs                                                             
  Double_t w = 1350;
  Double_t h = 450;
  TCanvas* canvas = NULL;
  canvas = new TCanvas("canvas", "electron and muon transverse momentum", w, h);
  canvas->SetWindowSize(w + (w - canvas->GetWw()), h + (h - canvas->GetWh()));
  canvas->Divide(3,1);
  
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.119326);
  canvas->cd(1);

  el_hist->Draw();
  el_hist->SetName("el_pt plot");
  el_hist->SetTitle("Plot of Electron Momentum");
  el_hist->SetFillColor(46);
  el_hist->SetLineColor(2);
  el_hist->SetLineWidth(2);
  el_hist->GetXaxis()->SetTitle("el_pt [GeV]");
  el_hist->GetYaxis()->SetTitle("number of entries");
  el_hist->GetXaxis()->CenterTitle(kTRUE);
  el_hist->GetYaxis()->CenterTitle(kTRUE);
  el_hist->GetXaxis()->SetTitleOffset(1.2);
  el_hist->GetYaxis()->SetTitleOffset(1.8);

  canvas->cd(2);

  mu_hist->Draw();
  mu_hist->SetName("mu_pt plot");
  mu_hist->SetTitle("Plot of Muon Momentum");
  mu_hist->SetFillColor(38);
  mu_hist->SetLineColor(9);
  mu_hist->SetLineWidth(2);
  mu_hist->GetXaxis()->SetTitle("mu_pt [GeV]");
  mu_hist->GetYaxis()->SetTitle("number of entries");
  mu_hist->GetXaxis()->CenterTitle(kTRUE);
  mu_hist->GetYaxis()->CenterTitle(kTRUE);
  mu_hist->GetXaxis()->SetTitleOffset(1.2);
  mu_hist->GetYaxis()->SetTitleOffset(1.8);

  canvas->cd(3);

  el_mu_90->Draw();
  el_mu_90->SetName("el and mu pt plot");
  el_mu_90->SetTitle("Muon + Electron Momentum (80-90)");
  el_mu_90->SetFillColor(41);
  el_mu_90->SetLineColor(5);
  el_mu_90->SetLineWidth(2);
  el_mu_90->GetXaxis()->SetTitle("el_pt + mu_pt [GeV]");
  el_mu_90->GetYaxis()->SetTitle("number of entries");
  el_mu_90->GetXaxis()->CenterTitle(kTRUE);
  el_mu_90->GetYaxis()->CenterTitle(kTRUE);
  el_mu_90->GetXaxis()->SetTitleOffset(1.2);
  el_mu_90->GetYaxis()->SetTitleOffset(1.6);
}
