# Looper
looper.h has various includes as well as a few functions for use in looper.C.
looper.C: Opens all the various files in chains and writes histograms from ttbar, wz, wjets, www, and data each to their own file. The different distributions used in the looper are:
  - el_pt
  - met_pt
  - lep_pt[0]
  - lep_pt[1]
  - MjjL
  - jets30 (size)
  - nb
 
 # Plotters
 plotter.h contains various includes as well as a helpfule function for use in various plotter files
 each plotter file plots a different distribution stack plot for all the proccesses, corresponds to name of file.
