#ifndef IBD_Event_Generator
#define IBD_Event_Generator

#include "Reactor_Antineutrino_Flux.hh"

void IBD_Event_Generate
(
  int numberOfEvents,
  int seed,
  const char* rootFileName,
  const char* hepmc3FileName,
  double power,
  double time,
  FissionFraction fFrac
);

#endif