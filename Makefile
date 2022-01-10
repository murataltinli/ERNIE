CC = gcc
CFLAGS = -Wall `root-config --cflags`
LIBS = `root-config --glibs` -lHepMC3 -lstdc++ \
-Wl,-rpath $(HEPMC3_DIR)/lib
INCLUDES = -I./include -I$(HEPMC3_DIR)/include
OBJECTS = IBD_Event_Generator.o Reactor_Antineutrino_Generator.o Positron_Angle.o \
IBD_Cross_Section.o Energy_Momentum.o Reactor_Antineutrino_Flux.o
INPUT = Generator.cc
OUTPUT = Generator

$(OUTPUT): $(OBJECTS)
ifndef ROOTSYS
	$(error Can't find ROOT, make sure ROOT is installed)
endif

ifndef HEPMC3_DIR
	$(error HEPMC3_DIR is undefined, please set it as HEPMC3 installation directory and run make again)
endif

	$(CC) $(INPUT) $(OBJECTS) -o $(OUTPUT) $(CFLAGS) $(INCLUDES) $(LIBS) && rm -f $(OBJECTS)

IBD_Event_Generator.o: src/IBD_Event_Generator.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c src/IBD_Event_Generator.cc

Reactor_Antineutrino_Generator.o: src/Reactor_Antineutrino_Generator.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Reactor_Antineutrino_Generator.cc

Positron_Angle.o: src/Positron_Angle.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Positron_Angle.cc

IBD_Cross_Section.o: src/IBD_Cross_Section.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c src/IBD_Cross_Section.cc

Energy_Momentum.o: src/Energy_Momentum.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Energy_Momentum.cc

Reactor_Antineutrino_Flux.o: src/Reactor_Antineutrino_Flux.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Reactor_Antineutrino_Flux.cc

clean:
	rm -f $(OUTPUT) $(OBJECTS)

.PHONY: clean