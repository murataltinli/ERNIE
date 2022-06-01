# ERNIE
ESTÜ Reactor Neutrino and Inverse beta decay Event generator

# Introduction
ERNIE generates nuclear reactor electron antineutrinos, and inverse beta decay events induced by these particles, using the Monte Carlo method. The program allows usage of different antineutrino energy spectra models and can simulate the time evolution of the overall antineutrino spectrum. 

ERNIE uses a parameter card file as input and outputs the generated data in ROOT and HepMC3 formats.

# Required libraries
Since ERNIE uses ROOT and HepMC3 formats to output generated data, ROOT and HepMC3 must be installed to use this program.

ROOT: https://root.cern/ 

HepMC3: https://gitlab.cern.ch/hepmc/HepMC3

# Compiling
Before compiling, make sure ROOT and HEPMC3 environment variables are properly set:

### for bash, sh, ksh shell
```
source /path/to/ROOT_directory/bin/thisroot.sh
export HEPMC3_DIR=/path/to/HepMC3_directory
```
### for csh, tcsh shell
``` 
source /path/to/ROOT_directory/bin/thisroot.csh
setenv HEPMC3_DIR /path/to/HepMC3_directory
```

Then, program is compiled using the 
```
make
```
command inside the directory containing `Makefile`. This should create the executable `ernie`.

# Running
ERNIE accepts three command line arguments. 
```
./ernie <parameter_card_filename> <root_output_filename> <hepmc3_output_filename>
```
The first argument is the parameter card file which configures `ernie`. The second and the third arguments are the ROOT and HepMC3 output file names. These are optional arguments and if not provided default file names will be used. 

If the program is used with the IBD option turned off, it will not generate a HepMC3 output even if a file name is specified as an argument.

# Source package structure
The topmost directory contains the README file, the package license, a sample parameter card file and Makefile.

The subdirectory `src/` contains the core set of library sources while
the corresponding headers are located in `include/` directory. `src/` directory also contains main source file `ernie.cc`.

The subdirectory `test/` contains input and output files for two test runs.

# Testing `ernie`
Card files and outputs of two test runs are provided under the `test` folder

Test1 run generates 10k reactor antineutrino events without inverse beta interactions at 100 days into the reactor fuel cycle. It uses Huber-Mueller model for spectrum calculation and the fission fractions are calculated using Mills model. Since fission fractions depend on burnup in Mills model, time is converted to burnup by using average daily burnup as parameter.

Test2 run generates 1k inverse beta decay events at the begginning of the reactor fuel cycle. It uses ILL-Vogel model for spectrum calculation and the fission fractions are calculated using linear interpolation.

Details on the parameters used for the test runs can be found in the corresponding card files.

The output files included in the package were generated using ROOTv6.22/06 and HepMC3.2.4.

# ROOT Output
Inside the ROOT output files, the data generated for U235, U238, Pu239, Pu241 and their total is written in individual trees.

If `ernie` was run with the IBD option turned off, the trees in the output will have only one branch named `Enu` which holds the energy (MeV) values of the generated antineutrinos.

If the IBD option is turned on, trees will have the following additional branches:

`Enu`: antineutrino energy (MeV)

`cose`: cosinus of positron angle with antineutrino direction (+z) 

`cosn`: cosinus of neutron angle with antineutrino direction (+z)

`Ee`: positron energy (MeV)

`Te`: positron kinetic energy (MeV)

`En`: neutron energy (MeV)

`Tn`: neutron kinetic energy (MeV)

`pe`: positron momentum size (MeV/c)

`pn`: neutron momentum size (MeV/c)

`pxe`: positron momentum (MeV/c) in x direction 

`pxn`: neutron momentum (MeV/c) in x direction 

`pye`: positron momentum (MeV/c) in y direction 

`pyn`: neutron momentum (MeV/c) in y direction

`pze`: positron momentum (MeV/c) in z direction
 
`pzn`: neutron momentum (MeV/c) in z direction
