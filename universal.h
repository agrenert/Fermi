#ifndef AUTO_LOOPER_H
#define AUTO_LOOPER_H

#include "TLegend.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TLine.h"
#include "TMath.h"
#include "TChain.h"
#include "TTree.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

void checkFile(TFile* file)
{
  if (file == 0)
    {
      std::cout << "ERROR OPENING FILE" << endl;
      return;
    }
}

#endif
