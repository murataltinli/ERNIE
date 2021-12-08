CC = gcc
CFLAGS = -Wall `root-config --cflags`
LIBS = `root-config --glibs` -lHepMC3 -lstdc++ \
-Wl,-rpath $(ROOTSYS)/lib \
-Wl,-rpath $(HOME)/HepMC3/HepMC3-install/lib
INCLUDES = -I./include
INPUT = Generator.C
OUTPUT = Generator

$(OUTPUT):
	$(CC) $(INPUT) -o $(OUTPUT) $(CFLAGS) $(INCLUDES) $(LIBS)

clean:
	rm -f $(OUTPUT) *.o

install:
	cp $(OUTPUT) /usr/bin

.PHONY: clean install
