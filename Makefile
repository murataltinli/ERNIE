CC = gcc
CFLAGS = -Wall `root-config --cflags`
LIBS = `root-config --glibs` -lHepMC3 -lstdc++ \
-Wl,-rpath $(HEPMC3_DIR)/lib
INCLUDES = -I./include -I$(HEPMC3_DIR)/include
INPUT = Generator.C
OUTPUT = Generator


$(OUTPUT):
ifndef HEPMC3_DIR
	$(error HEPMC3_DIR is undefined, please set it as HEPMC3 installation directory and run make again)
endif

ifndef ROOTSYS
	$(error Can't find ROOT, make sure ROOT is installed)
endif

	$(CC) $(INPUT) -o $(OUTPUT) $(CFLAGS) $(INCLUDES) $(LIBS) 

clean:
	@rm -f $(OUTPUT)

.PHONY: cleanS