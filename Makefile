CC = gcc
CFLAGS = -Wall `root-config --cflags`
LIBS = `root-config --glibs` -lHepMC3 -lstdc++ \
-Wl,-rpath $(HEPMC3_DIR)/lib
INCLUDES = -I./include -I$(HEPMC3_DIR)/include
INPUT = Generator.C
OUTPUT = Generator

$(OUTPUT):
	$(CC) $(INPUT) -o $(OUTPUT) $(CFLAGS) $(INCLUDES) $(LIBS) 

clean:
	rm -f $(OUTPUT)

install:
	cp $(OUTPUT) /usr/bin

.PHONY: clean install
