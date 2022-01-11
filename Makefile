CC = gcc
CFLAGS = -Wall `root-config --cflags`
LIBS = `root-config --glibs` -lHepMC3 -lstdc++ \
-Wl,-rpath $(HEPMC3_DIR)/lib
INCLUDES = -I./include -I$(HEPMC3_DIR)/include
OBJECTS = IBD_Event_Generator.o Reactor_Antineutrino_Generator.o Positron_Angle.o \
IBD_Cross_Section.o Energy_Momentum.o Reactor_Antineutrino_Flux.o
INPUT = src/Generator.cc
OUTPUT = Generator

$(OUTPUT): $(OBJECTS)
	$(CC) $(INPUT) $(OBJECTS) -o $(OUTPUT) $(CFLAGS) $(INCLUDES) $(LIBS)

IBD_Event_Generator.o:
ifndef HEPMC3_DIR
	$(error HEPMC3_DIR is undefined, please set it as HEPMC3 installation directory and run make again)
endif
ifndef ROOTSYS
	$(error Can't find ROOT, make sure ROOT is installed)
endif
	$(CC) $(CFLAGS) $(INCLUDES) -c src/IBD_Event_Generator.cc

Reactor_Antineutrino_Generator.o:
ifndef ROOTSYS
	$(error Can't find ROOT, make sure ROOT is installed)
endif
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Reactor_Antineutrino_Generator.cc

Positron_Angle.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Positron_Angle.cc

IBD_Cross_Section.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c src/IBD_Cross_Section.cc

Energy_Momentum.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Energy_Momentum.cc

Reactor_Antineutrino_Flux.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Reactor_Antineutrino_Flux.cc

clean:
	rm -f $(OUTPUT) $(OBJECTS)

.PHONY: clean
