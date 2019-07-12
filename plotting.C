#include "universal.h"

using namespace std;

void getHist(TString directory, TString process, TString distribution,
             Int_t color, THStack* &stack, TLegend* &legend)
{
  TFile* input_file = new TFile(directory + process + "_distributions_2018.root");
  input_file->cd();
  checkFile(input_file);
  TH1D* h = NULL; input_file->GetObject(process + "_" + distribution, h);

  TH1D* hist = new TH1D(process + "_hist", process + "_hist", h->GetNbinsX(),
                        h->GetXaxis()->GetXmin(), h->GetXaxis()->GetXmax());
  hist->Add(h);
  hist->SetFillColor(color);
  hist->SetLineWidth(1);
  hist->SetLineColor(color);

  stack->Add(hist, "HIST");
  legend->AddEntry(hist, process, "f");
}

void plot(TString distribution, TString plot_name)
{
  // Directory                                                                               
  TString directory = "~/distributions/";

  // SETS UP CANVAS                                                                         \
                                                                                             
  Double_t w = 700;
  Double_t h = 750;
  TCanvas* canvas = NULL;
  canvas = new TCanvas("canvas", "canvas", w, h);
  canvas->SetWindowSize(w + (w - canvas->GetWw()), h + (h - canvas->GetWh()));
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.119326);
  canvas->SetFillColor(10);
  canvas->SetGrid();
  canvas->cd();

  // THStack                                                                                 
  THStack* stack_hist = new THStack(distribution + " plot",
                                    plot_name + " Stack Histogram");

  // TLegend                                                                                 
  TLegend* legend = new TLegend(0.7,0.7,0.48,0.9);
  legend->SetHeader(distribution, "C");
  legend->SetNColumns(3);

  //=======================================================================================|
  //=======================================================================================|
  // AREA TO EDIT WHEN ADDING NEW PROCESSES                                                  
  // - when adding a new process, add a string of that process at the end of process_names   
  // - after that add a value for the color of that process at the end of colors             
  // - done, only those 2 steps when adding processes                                        

  // Vector of the names of the process' used in plotting                                    
  vector<TString> process_names =
    {"ttbar", "ttgam", "wjets", "wz", "zz", "dy", "ttz", "ttw", "tZq"};

  vector<Int_t> colors =
    {40, 41, 43, 46, 33, 36, 38, 20, 8};

  //=======================================================================================|
  //=======================================================================================|

  for (Int_t i = 0; i < process_names.size(); i++)
    {
      getHist(directory, process_names[i], distribution, colors[i], stack_hist, legend);
    }

  //=======================================================================================|
  // SIGNAL and DATA                                                                         
  TFile* data_input_file = new TFile(directory + "data_distributions_2018.root");
  checkFile(data_input_file);
  data_input_file->cd();
  TH1D* data = NULL; data_input_file->GetObject("data_" + distribution, data);
  TH1D* data_hist = new TH1D("data_hist", "data_hist", data->GetNbinsX(),
                             data->GetXaxis()->GetXmin(), data->GetXaxis()->GetXmax());
  data_hist->Add(data);
  data_hist->SetMarkerColor(1);
  data_hist->SetMarkerStyle(20);
  data_hist->SetMarkerSize(1);

  Double_t data_max = data_hist->GetMaximum();
  data_hist->SetMinimum(0);
  data_hist->SetMaximum(data_max);

  TFile* signal_input_file = new TFile(directory + "www_distributions_2018.root");
  checkFile(signal_input_file);
  signal_input_file->cd();
  TH1D* signal = NULL; signal_input_file->GetObject("www_" + distribution, signal);
  TH1D* www_hist = new TH1D("www_hist", "www_hist", signal->GetNbinsX(),
                            signal->GetXaxis()->GetXmin(), signal->GetXaxis()->GetXmin());
  www_hist->SetFillColor(47);
  www_hist->SetLineWidth(1);
  www_hist->SetLineColor(47);

  // DRAWS STACK HISTOGRAM                                                                   
  stack_hist->SetMinimum(0);
  stack_hist->SetMaximum(data_max);
  stack_hist->Draw();
  data_hist->Draw("E1, SAME");
  www_hist->Draw("HIST, SAME");
  stack_hist->SetName(distribution + " plot");
  stack_hist->SetTitle(plot_name);
  stack_hist->GetXaxis()->SetTitle(distribution);
  stack_hist->GetXaxis()->CenterTitle(kTRUE);
  stack_hist->GetXaxis()->SetTitleOffset(1.2);
  stack_hist->GetYaxis()->SetTitle("number of events normalized");
  stack_hist->GetYaxis()->CenterTitle(kTRUE);
  stack_hist->GetYaxis()->SetTitleOffset(1.5);

  legend->Draw();
  canvas->Update();
}
