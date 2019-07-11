#include "auto_looper.C"

using namespace std;

void chain_looper()
{
  //================================================================================|  
  // DECLARE CHAIN AND ADD FILES BEFORE CALLING "processChain" function                
  // processChain function in "auto_looper.C" uses chain as well as name of the        
  // process to create all desired histograms from any given chain                     
  //================================================================================|  
  // String to find directory of files                                                 
  TString directoryString = "/nfs-7/userdata/phchang/WWW_babies";
  directoryString += "/WWW2018_v5.1.6/merged/";
  cout << directoryString << endl;

  // TTBAR                                                                             
  // Creates TTBAR Chain                                                               
  TChain ttbar_chain("t");
  ttbar_chain.Add(directoryString + "ttbar_1ltbr_madgraph_1.root");
  ttbar_chain.Add(directoryString + "ttbar_1ltop_madgraph_1.root");
  ttbar_chain.Add(directoryString + "ttbar_semilep_powheg_1.root");
  ttbar_chain.Add(directoryString + "ttbar_dilep_powheg_1.root"  );
  ttbar_chain.Add(directoryString + "ttbar_dilep_powheg_2.root"  );
  processChain(ttbar_chain, "ttbar", 0);

  // TTGAM                                                                             
  // Creates TTGAM Chain                                                               
  TChain ttgam_chain("t");
  ttgam_chain.Add(directoryString + "ttgam_1ltbr_madgraph_1.root");
  ttgam_chain.Add(directoryString + "ttgam_1ltop_madgraph_1.root");
  ttgam_chain.Add(directoryString + "ttgam_dilep_madgraph_1.root");
  processChain(ttgam_chain, "ttgam", 0);

  // WZ                                                                                
  // Creates WZ Chain                                                                  
  TChain wz_chain("t");
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_1.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_2.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_3.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_4.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_5.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_6.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_7.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_8.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_9.root" );
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_10.root");
  wz_chain.Add(directoryString + "wz_3lv_amcatnlo_11.root");
  processChain(wz_chain, "wz", 0);

  // WJETS                                                                             
  // Creates WJETS Chain                                                               
  TChain wjets_chain("t");
  wjets_chain.Add(directoryString + "wjets_ht100_madgraph_1.root" );
  wjets_chain.Add(directoryString + "wjets_ht1200_madgraph_1.root");
  wjets_chain.Add(directoryString + "wjets_ht200_madgraph_1.root" );
  wjets_chain.Add(directoryString + "wjets_ht2500_madgraph_1.root");
  wjets_chain.Add(directoryString + "wjets_ht400_madgraph_1.root" );
  wjets_chain.Add(directoryString + "wjets_ht600_madgraph_1.root" );
  wjets_chain.Add(directoryString + "wjets_ht800_madgraph_1.root" );
  wjets_chain.Add(directoryString + "wjets_incl_madgraph_1.root"  );
  processChain(wjets_chain, "wjets", 0);

  // WWW                                                                               
  // Creates WWW Chain                                                                 
  TChain www_chain("t");
  www_chain.Add(directoryString + "www_amcatnlo_dilepfilter_1.root");
  processChain(www_chain, "www", 0);

  // ZZ                                                                                
  // Creates ZZ Chain                                                                  
  TChain zz_chain("t");
  Int_t number_of_zz_files = 81;
  TString zz_file_extention = "zz_4l_powheg_";
  string number; // used to store i as a string                                        
  for (Int_t i = 1; i <= number_of_zz_files; i++)
    {
      number = to_string(i);
      zz_chain.Add(directoryString + zz_file_extention + number + ".root");
    }
  processChain(zz_chain, "zz", 0);

  // DY                                                                                
  // Creates DY Chain                                                                  
  TChain dy_chain("t");
  dy_chain.Add(directoryString + "dy_m1050_madgraph_1.root");
  dy_chain.Add(directoryString + "dy_m50_madgraph_1.root");
  processChain(dy_chain, "dy", 0);
  
  // TTZ                                                                               
  // Creates TTZ Chain                                                                 
  TChain ttz_chain("t");
  ttz_chain.Add(directoryString + "ttz_ll_mll1_amcatnlo_1.root"    );
  ttz_chain.Add(directoryString + "ttz_llvv_mll10_amcatnlo_1.root" );
  ttz_chain.Add(directoryString + "ttz_llvv_mll10_amcatnlo_2.root" );
  ttz_chain.Add(directoryString + "ttz_llvv_mll10_amcatnlo_3.root" );
  ttz_chain.Add(directoryString + "ttz_llvv_mll10_amcatnlo_4.root" );
  ttz_chain.Add(directoryString + "ttz_llvv_mll10_amcatnlo_5.root" );
  ttz_chain.Add(directoryString + "ttz_llvv_mll10_amcatnlo_6.root" );
  ttz_chain.Add(directoryString + "ttz_llvv_mll10_amcatnlo_7.root" );
  ttz_chain.Add(directoryString + "ttz_llvv_mll10_amcatnlo_8.root" );
  ttz_chain.Add(directoryString + "ttz_llvv_mll10_amcatnlo_9.root" );
  ttz_chain.Add(directoryString + "ttz_llvv_mll10_amcatnlo_10.root");
  ttz_chain.Add(directoryString + "ttz_llvv_mll10_amcatnlo_12.root");
  processChain(ttz_chain, "ttz", 0);

  // TTW                                                                               
  // Creates TTW Chain                                                                 
  TChain ttw_chain("t");
  ttw_chain.Add(directoryString + "ttw_lnu_amcatnlo_1.root");
  ttw_chain.Add(directoryString + "ttw_lnu_amcatnlo_2.root");
  ttw_chain.Add(directoryString + "ttw_lnu_amcatnlo_3.root");
  ttw_chain.Add(directoryString + "ttw_lnu_amcatnlo_4.root");
  ttw_chain.Add(directoryString + "ttw_lnu_amcatnlo_5.root");
  processChain(ttw_chain, "ttw", 0);

  // TZQ                                                                               
  // Creates TZQ Chain                                                                 
  TChain tZq_chain("t");
  tZq_chain.Add(directoryString + "tZq_ll_madgraph_1.root" );
  tZq_chain.Add(directoryString + "tZq_ll_madgraph_2.root" );
  tZq_chain.Add(directoryString + "tZq_ll_madgraph_3.root" );
  tZq_chain.Add(directoryString + "tZq_ll_madgraph_4.root" );
  tZq_chain.Add(directoryString + "tZq_ll_madgraph_5.root" );
  tZq_chain.Add(directoryString + "tZq_ll_madgraph_6.root" );
  tZq_chain.Add(directoryString + "tZq_ll_madgraph_7.root" );
  tZq_chain.Add(directoryString + "tZq_ll_madgraph_8.root" );
  tZq_chain.Add(directoryString + "tZq_ll_madgraph_9.root" );
  tZq_chain.Add(directoryString + "tZq_ll_madgraph_10.root");
  tZq_chain.Add(directoryString + "tZq_ll_madgraph_11.root");
  processChain(tZq_chain, "tZq", 0);

  // DATA                                                                              
  // Creates DATA Chain                                                                
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
  processChain(data_chain, "data", 1);
}

