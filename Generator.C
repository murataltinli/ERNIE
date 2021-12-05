#include "IBD_Event_Generator.C"
#include <iostream>

#include "readline/readline.h"
#include "readline/history.h"

using namespace std;

  /*
  // fission fractions (t = 0)
  f5 = 0.763; // U235
  f8 = 0.0476; // U238
  f9 = 0.162; // Pu239
  f1 = 0.027; // Pu241
  
  // fission fractions (t = end)   
  f5 = 0.423; // U235
  f8 = 0.076; // U238
  f9 = 0.397; // Pu239
  f1 = 0.102; // Pu241
  */

int main(int argc, char** argv)
{
  char* command;
  double mw;
  int n = 10000;
  int seed = 1;
  const char* rootFileName = "Reactor_Antineutrino_IBD_Events.root";
  const char* hepmc3FileName = "Reactor_Antineutrino_IBD_Events.hepmc3";
  double power = 3.2 * pow(10, 9); // reactor power (W)
  double f5 = 0.765;
  double f8 = 0.0476;
  double f9 = 0.162;
  double f1 = 0.027;
  
  cout << "\nWelcome to Reactor Antineutrino IBD Event Generator" << endl
       << "---------------------------------------------------------" << endl
       << "| Command list                                          |" << endl
       << "| 0: run event generation, 1: set event number for U235,|" << endl
       << "| 2: set fission fractions, 3: set reactor power (MW),  |" << endl
       << "| 4: set root output name, 5: set hepmc3 output name,   |" << endl
       << "| 6: set random generator seed, Ctrl + C: exit          |" << endl
       << "---------------------------------------------------------" << endl;

  while(true)
  {
    cout << "Enter command:" << endl;
    command = readline(">> ");
    
    if (atoi(command) == 0) break;
    
    switch(atoi(command))
    {
      case 1:
        cout << "Enter event number for U235:" << endl;
        n = atoi(readline("1:>> "));
        break;
      case 2:
        cout << "Enter fission fraction for U235:" << endl;
        f5 = atof(readline("2:>> "));
        cout << "Enter fission fraction for U238:" << endl;
        f8 = atof(readline("2:>> "));
        cout << "Enter fission fraction for Pu239:" << endl;
        f9 = atof(readline("2:>> "));
        cout << "Enter fission fraction for Pu241:" << endl;
        f1 = atof(readline("2:>> "));
        break;
      case 3:
        cout << "Enter reactor power (MW):" << endl;
        mw = atof(readline("3:>> "));
        power = mw * pow(10,6);
        break;
      case 4:
        cout << "Enter root output file name:" << endl;
        rootFileName = readline("4:>> ");
        break;
      case 5:
        cout << "Enter hepmc3 output file name:" << endl;
        rootFileName = readline("5:>> ");
        break;
      case 6:
        cout << "Enter random generator seed: " << endl;
        seed = atoi(readline("6:>> "));
        break;
      default:
        cout << "error: unrecognized command '" << command << "'" << endl;
    }
  }
  cout << "Generating Events..." << endl;
  IBD_Event_Generator(n,seed,rootFileName,hepmc3FileName,power,f5,f8,f9,f1);
  cout << "Generated events are written into the files:" << endl
       << "=> " << rootFileName << endl
       << "=> " << hepmc3FileName << endl;
  return 0;
}
