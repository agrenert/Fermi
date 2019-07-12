# auto_looper.C
 This contains the function "processChain" which is called in chain_looper.C
 This function loops through all the desired distributions defined in the function of the chain defined in the parameters.
 
# chain_looper.C
  This file creates all the chains by reading files of the various desired processes, then calls function in auto_looper.C to create output histograms and files
  
# plotting.C
  This file contains 2 functions. "plot" is used in plotting_program.C to plot any user inputed distribution that exists in the list of distributions defined in auto_looper.C, plotting options are defined in the plot function
  
# plotting_program.C
This file is a User Interface for plotting the various distributions of the different proccesses.

# universal.h
Contains all the includes as well as a usefule function for use in the other files,
All other files include this file
