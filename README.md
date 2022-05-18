# ERNIE
Reactor Antineutrino Inverse Beta Decay Generator

# Compiling
  
  # for bash, sh, ksh shell
```
source /path/to/ROOT_directory/bin/thisroot.sh
export HEPMC3_DIR=/path/to/HepMC3_directory
make
```
  # for csh, tcsh shell
``` 
source /path/to/ROOT_directory/bin/thisroot.csh
setenv HEPMC3_DIR /path/to/HepMC3_directory
make
```
# Running
```
./ernie <parameter_card_filename> <root_output_filename> <hepmc3_output_filename>
```
