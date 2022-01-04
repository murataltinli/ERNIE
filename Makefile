CC = gcc
CFLAGS = -Wall `root-config --cflags`
LIBS = `root-config --glibs` -lHepMC3 -lstdc++ \
-Wl,-rpath $(HEPMC3_DIR)/lib
INCLUDES = -I./include -I$(HEPMC3_DIR)/include
INPUT = Generator.C
OUTPUT = Generator

$(OUTPUT): err1
	@$(CC) $(INPUT) -o $(OUTPUT) $(CFLAGS) $(INCLUDES) $(LIBS) 

err1: err2
	@if [ ! -d "$(HEPMC3_DIR)" ];\
	 then echo "\033[1;31mError:\033[0m HEPMC3_DIR path is not set.\n\
\033[1;36mSolution:\033[0m Set HEPMC3_DIR as the HepMC3 installation directory and run make again.";\
exit 1; fi

err2: 
	@if [ ! -d "$(ROOTSYS)" ];\
	 then echo "\033[1;31mError:\033[0m Can't find ROOT. Make sure ROOT is installed."; \
exit 2; fi

clean:
	@rm -f $(OUTPUT)

install:
	@cp $(OUTPUT) /usr/bin

.PHONY: clean install err1 err2
