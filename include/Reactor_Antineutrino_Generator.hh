#ifndef Reactor_Antineutrino_Generator
#define Reactor_Antineutrino_Generator

#include "Reactor_Antineutrino_Flux.hh"

void Reactor_Antineutrino_Generate
(
  int numberOfEvents,
  int seed,
  const char* rootFileName,
  double power,
  double time,
  FissionFraction fFrac
);

#endif