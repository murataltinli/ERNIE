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
First, `thisroot` file, located in ROOT installation path should be run and `HEPMC3_DIR` environmental variable should be set as HepMC3 installation directory, containing library directory `/lib`, using the following command lines:
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
command inside the directory containing `Makefile`.

# Running
ERNIE runs with 3 arguments. 
```
./ernie <parameter_card_filename> <root_output_filename> <hepmc3_output_filename>
```
The first argument is the input, which is the parameter card file. The program runs using the parameters inside the parameter card file. The second and the third arguments are output file names for ROOT and HepMC3 outputs, respectively. If no output name is specified output files will have default names. 

If the program is used to generate antineutrinos only, without the inverse beta decay interactions, it will not generate a HepMC3 output even if it is specified as an argument.

# Source package structure
The topmost directory contains the README file, the package license, a sample parameter card file and Makefile.

The subdirectory `src/` contains the core set of library sources while
the corresponding headers are located in `include/` directory. `src/` directory also contains main source file `ernie.cc`.

The subdirectory `test/` contains input and output files for two test runs.

# Test runs
Test1 run generates 10k reactor antineutrino events without inverse beta interactions at 100 days into the reactor fuel cycle. It uses Huber-Mueller model for spectrum calculation and the fission fractions are calculated using Mills model. Since fission fractions depend on burnup in Mills model, time is converted to burnup by a conversion parameter.

Test2 run generates 1k inverse beta decay events at the beggining of the reactor fuel cycle. It uses ILL-Vogel model for spectrum calculation and the fission fractions are calculated using linear interpolation.

Details on the parameters used for the test runs can be found in the corresponding card files.

ROOTv6.22/06 and HepMC3.2.4 were used to generate the output files.

# ROOT Output
Inside the ROOT output files, the data generated for U235, U238, Pu239, Pu241 and their total is written in individual trees.

If only reactor antineutinos are generated, without inverse beta decay interactions, the trees in output will have only one branch named `Enu` which holds the energy (MeV) values of the generated antineutrinos.

In the case that inverse beta decay interactions are generated, trees will have branches with the following names:

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