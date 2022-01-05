CC = gcc
CFLAGS = -Wall `root-config --cflags`
LIBS = `root-config --glibs` -lHepMC3 -lstdc++ \
-Wl,-rpath $(HEPMC3_DIR)/lib
INCLUDES = -I./include -I$(HEPMC3_DIR)/include
INPUT = Generator.C
OUTPUT = Generator

$(OUTPUT): checkhepmc3
	@$(CC) $(INPUT) -o $(OUTPUT) $(CFLAGS) $(INCLUDES) $(LIBS) 

checkhepmc3: checkroot
ifndef HEPMC3_DIR
	$(error HEPMC3_DIR is undefined, please set it as HEPMC3 installation directory and run make again)
endif

checkroot:
ifndef ROOTSYS
	$(error Can't find ROOT, make sure ROOT is installed)
endif

clean:
	@rm -f $(OUTPUT)

.PHONY: clean checkhepmc3 checkroot
