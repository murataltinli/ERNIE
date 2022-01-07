#include "IBD_Event_Generator.C"
#include "Reactor_Antineutrino_Generator.C"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
  int n, seed;
  bool ibd;
  const char* rootFileName = "Reactor_Antineutrino_IBD_Events.root";
  const char* hepmc3FileName = "Reactor_Antineutrino_IBD_Events.hepmc3";
  const char* cardFileName = nullptr;
  double power; // reactor power (W)
  double time;
  double f5_i, f8_i, f9_i, f1_i, f5_f, f8_f, f9_f, f1_f; // fission fractions
  double gw2w = pow(10,9);
  
  if(argc==1)
  {
    cout << "\033[1;31mError:\033[0m missing argument: parameter card filename." << endl
         << "\033[1;36mUsage:\033[0m ./Generator <parameter_card_filename> "
         << "<root_output_filename> <hepmc3_output_filename>" << endl
         << "\033[1;33mNote:\033[0m Output filename arguments are optional."
         << " If they are not specified default output filenames will be used." << endl;
    return 0;
  }
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
      line.erase(remove(line.begin(), line.end(), ' '), line.end());
      auto delimiterPos = line.find("=");
      auto name = line.substr(0, delimiterPos);
      auto value = line.substr(delimiterPos + 1);
      if(name == "Seed"){seed=stoi(value);}
      else if(name == "N"){n=stoi(value);}
      else if(name == "Power"){power=stof(value)*gw2w;}
      else if(name == "Time"){time=stof(value);}
      else if(name == "U235_i"){f5_i=stof(value);}
      else if(name == "U238_i"){f8_i=stof(value);}
      else if(name == "Pu239_i"){f9_i=stof(value);}
      else if(name == "Pu241_i"){f1_i=stof(value);}
      else if(name == "U235_f"){f5_f=stof(value);}
      else if(name == "U238_f"){f8_f=stof(value);}
      else if(name == "Pu239_f"){f9_f=stof(value);}
      else if(name == "Pu241_f"){f1_f=stof(value);}
      else if(name == "IBD"){ibd=stoi(value);}
    }

    // parameter value errors
    if(f5_i+f8_i+f9_i+f1_i > 1.001 || f5_i+f8_i+f9_i+f1_i < 0.99 ||
       f5_f+f8_f+f9_f+f1_f > 1.001 || f5_f+f8_f+f9_f+f1_f < 0.99 )
    {
      cout << "\033[1;35mWarning:\033[0m Invalid parameter values,"
           << "please check fission fraction parameters in: " 
           << cardFileName << endl;
      return 0;
    }
    else if(power <= 0)
    {
      cout << "\033[1;31mError:\033[0m Invalid parameter value,"
           << "please check reactor thermal power parameter in: " 
           << cardFileName << endl;
      return 0;
    }
    else if(n <= 0)
    {
      cout << "\033[1;31mError:\033[0m Invalid parameter value,"
           << "please check number of events (N) parameter in: " 
           << cardFileName << endl;
      return 0;
    }
    else if(time < 0 || time > 600)
    {
      cout << "\033[1;31mError:\033[0m Invalid parameter value,"
           << "please check time parameter in: " 
           << cardFileName << endl;
      return 0;
    }

    cout << "Using parameters from the file: " << cardFileName << endl;
    
    if(ibd==0)
    {
      if(strcmp(rootFileName, "Reactor_Antineutrino_IBD_Events.root") == 0 && argc < 3)
      {
        rootFileName = "Reactor_Antineutrino_Events.root";
      }
      cout << "Generating Events..." << endl;
      Reactor_Antineutrino_Generator(n,seed,rootFileName,power,time,f5_i,f8_i,f9_i,f1_i,f5_f,f8_f,f9_f,f1_f);
      cout << "Generated events are written into the file:" << endl
           << "=> " << rootFileName << endl;
      return 0;
    }
    else
    {
      cout << "Generating Events..." << endl;
      IBD_Event_Generator(n,seed,rootFileName,hepmc3FileName,power,time,f5_i,f8_i,f9_i,f1_i,f5_f,f8_f,f9_f,f1_f);
      cout << "Generated events are written into the files:" << endl
           << "=> " << rootFileName << endl
           << "=> " << hepmc3FileName << endl;
      return 0;
    }
  }
  else 
  {
    cerr << "\033[1;31mError:\033[0m Couldn't open card file for reading.\n";
  }
}