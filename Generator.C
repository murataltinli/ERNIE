#include "IBD_Event_Generator.C"
#include "Reactor_Antineutrino_Generator.C"
#include <iostream>
#include <fstream>
#include <algorithm>

#include "readline/readline.h"
#include "readline/history.h"

using namespace std;

int main(int argc, char** argv)
{
  int n, seed;
  bool ibd;
  const char* rootFileName = "Reactor_Antineutrino_IBD_Events.root";
  const char* hepmc3FileName = "Reactor_Antineutrino_IBD_Events.hepmc3";
  const char* cardFileName = "default_card.txt";
  double power; // reactor power (W)
  double f5, f8, f9, f1; // fission fractions

  if(argc>1){cardFileName=argv[1];}
  if(argc>2){rootFileName=argv[2];}
  if(argc>3){hepmc3FileName=argv[3];}

  ifstream cFile (cardFileName);
  if (cFile.is_open())
  {
    string line;
    while(getline(cFile, line))
    {
      if( line.empty() || line[0] == '#' )
      {
        continue;
      }
      auto delimiterPos = line.find("=");
      auto name = line.substr(0, delimiterPos);
      auto value = line.substr(delimiterPos + 1);
      if(name == "Seed"){seed=stoi(value);}
      else if(name == "N"){n=stoi(value);}
      else if(name == "Power"){power=stof(value)*pow(10,6);}
      else if(name == "U235"){f5=stof(value);}
      else if(name == "U238"){f8=stof(value);}
      else if(name == "Pu239"){f9=stof(value);}
      else if(name == "Pu241"){f1=stof(value);}
      else if(name == "IBD"){ibd=stoi(value);}
    }
    cout << "Generating Events..." << endl;
    if(ibd==0)
    {
      Reactor_Antineutrino_Generator(n,seed,rootFileName,power,f5,f8,f9,f1);
      cout << "Generated events are written into the file:" << endl
           << "=> " << rootFileName << endl;
      return 0;
    }
    else
    {
      IBD_Event_Generator(n,seed,rootFileName,hepmc3FileName,power,f5,f8,f9,f1);
      cout << "Generated events are written into the files:" << endl
           << "=> " << rootFileName << endl
           << "=> " << hepmc3FileName << endl;
      return 0;
    }
  }
  else 
  {
    cerr << "Couldn't open card file for reading.\n";
  }
}