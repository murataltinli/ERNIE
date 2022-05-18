CC = gcc
CFLAGS = -Wall `root-config --cflags`
LIBS = `root-config --glibs` -lHepMC3 -lstdc++ \
-Wl,-rpath $(HEPMC3_DIR)/lib
INCLUDES = -I./include -I$(HEPMC3_DIR)/include
OBJECTS = IBD_Event_Generator.o Reactor_Antineutrino_Generator.o Positron_Angle.o \
IBD_Cross_Section.o Energy_Momentum.o Reactor_Antineutrino_Flux.o Fission_Fractions.o \
Reactor_Antineutrino_Spectra.o
INPUT = src/ernie.cc
OUTPUT = ernie

ernie: $(OBJECTS) $(INPUT) include/IBD_Event_Generator.hh \
include/Reactor_Antineutrino_Generator.hh include/Reactor_Antineutrino_Flux.hh
	$(CC) $(INPUT) $(OBJECTS) -o $(OUTPUT) $(CFLAGS) $(INCLUDES) $(LIBS)

IBD_Event_Generator.o: src/IBD_Event_Generator.cc include/IBD_Event_Generator.hh \
include/Reactor_Antineutrino_Flux.hh include/Positron_Angle.hh include/Energy_Momentum.hh \
include/IBD_Cross_Section.hh
ifndef HEPMC3_DIR
	$(error HEPMC3_DIR is undefined, please set it as HEPMC3 installation directory and run make again)
endif
ifndef ROOTSYS
	$(error Can't find ROOT, make sure ROOT is installed)
endif
	$(CC) $(CFLAGS) $(INCLUDES) -c src/IBD_Event_Generator.cc

Reactor_Antineutrino_Generator.o: src/Reactor_Antineutrino_Generator.cc \
include/Reactor_Antineutrino_Generator.hh include/Reactor_Antineutrino_Flux.hh \
include/Positron_Angle.hh include/Energy_Momentum.hh
ifndef ROOTSYS
	$(error Can't find ROOT, make sure ROOT is installed)
endif
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Reactor_Antineutrino_Generator.cc

Positron_Angle.o: src/Positron_Angle.cc include/Positron_Angle.hh include/Energy_Momentum.hh
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Positron_Angle.cc

IBD_Cross_Section.o: src/IBD_Cross_Section.cc include/IBD_Cross_Section.hh include/Energy_Momentum.hh 
	$(CC) $(CFLAGS) $(INCLUDES) -c src/IBD_Cross_Section.cc

Energy_Momentum.o: src/Energy_Momentum.cc include/Energy_Momentum.hh
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Energy_Momentum.cc

Reactor_Antineutrino_Flux.o: src/Reactor_Antineutrino_Flux.cc include/Reactor_Antineutrino_Flux.hh
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Reactor_Antineutrino_Flux.cc

Fission_Fractions.o: src/Fission_Fractions.cc include/Fission_Fractions.hh
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Fission_Fractions.cc

Reactor_Antineutrino_Spectra.o: src/Reactor_Antineutrino_Spectra.cc include/Reactor_Antineutrino_Spectra.hh
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Reactor_Antineutrino_Spectra.cc

clean:
	rm -f $(OUTPUT) $(OBJECTS)

.PHONY: clean
