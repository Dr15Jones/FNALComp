#include <string>
#include "Services/include/Exception.hh"
#include "Services/include/Config.hh"

fc::Config::Config(std::ifstream & configfile,int genData):
  _genData(genData),
  _numberEvents(128),
  _numberTracks(10),
  _seed(1) {

  _initConfig(configfile);
  printConfig(std::cout);

}

void fc::Config::_initConfig(std::ifstream & configfile) {


  if (!configfile){
    throw Exception("Config::_initConfig: can't open configfile.txt file");
  }

  std::string configString;
 

  while(configfile){
    configfile >> configString; 

    if (_genData){
      if (configString == "NumberEvents") {
	configfile >> _numberEvents;
      } else if (configString == "NumberTracks") { 
	configfile >> _numberTracks;
      } else if (configString == "Seed") {
	configfile >> _seed;
      } else if (configString == "RootFileName") {
	configfile >> _rootFileName;
      } else {
	throw Exception("Config::_initConfig: Unrecognized parameter in configfile.txt");
      }
    } else {
      if (configString == "RootFileName") {
	configfile >> _rootFileName;
      } else if (configString == "minCandPTCut") {
	configfile >> _minCandPTCut;
      } else if (configString == "minPTCut") {
	configfile >> _minPTCut;
      } else if (configString == "maxChi2NDofCut") {
	configfile >> _maxChi2NDofCut;
      } else {
	throw Exception("Config::_initConfig: Unrecognized parameter in configfile.txt");
      }

    }

  } // endl while loop through configfile

}


 
void fc::Config::printConfig(std::ostream& out) const {

  out << "Program configuration information" << std::endl;

  if (_genData) {
    out << "gen Data configuration" << std::endl;
    out << "Number Events: " << _numberEvents << std::endl;
    out << "Number Tracks " << _numberTracks << std::endl;
    out << "Random number seed " << _seed << std::endl;
    out << "Root file name " << _rootFileName << std::endl;
  } else {
    out << "reco Data configuration" << std::endl;
    out << "Root file name " << _rootFileName << std::endl;
  }

}
