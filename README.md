# Generator
Reactor Antineutrino Inverse Beta Decay Generator

# Compiling
  
  # for bash, sh, ksh shell
  
  export HEPMC3_DIR=/path/to/HepMC3_directory 
  
  make
  
  # for csh, tcsh shell
  setenv HEPMC3_DIR /path/to/HepMC3_directory
  
  make

# Running
  
  ./Generator <parameter_card_filename> <root_output_filename> <hepmc3_output_filename>
