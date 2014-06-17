#ifndef DataInputModule_hh
#define DataInputModule_hh
//============================================================================
// DataInputModule.hh
// Module for reading raw detector data from the
// sensors of a 5 layer planor silicon detector.
// See detectorGeometry.pdf for detector description
// Strip data is stored in bianary format
// See  dataFormat.pdf for data format information
// 
// Author Matt Herndon, University of Wisconsin,
//                       Fermi National Accelerator Laborator
// 2014-06-03
//============================================================================

#include <fstream>
#include <iostream>

class TrackSet;
class HitSet;
class StripSet;


///
/// Class DataInputModule
/// Author Matt Herndon, University of Wisconsin, Fermi National Accelerator Laborator 2014-06-03
///

namespace fc {

class DataInputModule {

public:

  DataInputModule(int, int, std::ifstream&);
  ~DataInputModule() {};

   void processEvent(TrackSet&, HitSet&, StripSet&);


private:

  int _debugLevel;
  int _detectorGeometryVersion;
  // Input event data file
  std::ifstream & _inputeventdatafile;

 



};
} // end namespace fc

#endif // DataInputModule_hh