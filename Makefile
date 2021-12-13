CC = gcc
CFLAGS = -Wall `root-config --cflags`
LIBS = `root-config --glibs` -lstdc++ \
-Wl,-rpath $(ROOTSYS)/lib \
libs/libHepMC3-static.a
INCLUDES = -I./include
INPUT = Generator.C
OUTPUT = Generator

$(OUTPUT):
	$(CC) $(INPUT) -o $(OUTPUT) $(CFLAGS) $(INCLUDES) $(LIBS)

clean:
	rm -f $(OUTPUT)

install:
	cp $(OUTPUT) /usr/bin

.PHONY: clean install
