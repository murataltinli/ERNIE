#ifndef IBD_Event_Generator
#define IBD_Event_Generator

#include "Reactor_Antineutrino_Flux.hh"

extern const double M_p;

double IBDEventMax(int, double, double, FissionFraction, bool);

void IBD_Event_Generate
(
  int,
  int,
  const char*,
  const char*,
  double ,
  double ,
  FissionFraction,
  bool
);

#endif
