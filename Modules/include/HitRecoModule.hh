#ifndef Modules_HitRecoModule_hh
#define Modules_HitRecoModule_hh
//============================================================================
// HitRecoModule.hh
// Module for reconstructing hits from strip infomation
// 
// Author Matt Herndon, University of Wisconsin,
//                       Fermi National Accelerator Laborator
// 2014-06-11
//============================================================================

#include "Framework/include/Module.hh"
#include "DataObjects/include/StripSet.hh"
#include "TVector3.h"
#include <vector>
#include <string>


namespace fc {

class DetectorGeometry;
class HitSet;


///
/// Class HitRecoModule  Module for reconstructing hits from strip infomation
/// Author Matt Herndon, University of Wisconsin, Fermi National Accelerator Laborator 2014-06-11
///

class HitRecoModule : public Module {

public:

  HitRecoModule(int, const std::string& iInputStripsLabel, const std::string& iOutputHitsLabel, const DetectorGeometry &);

  void processEvent(Event& ) override;


private:

  int _debugLevel;
  const std::string _inStripsLabel;
  const std::string _outHitsLabel;

  // Detector information
  const DetectorGeometry & _detectorGeometry;

  void recoHits(HitSet &, const StripSet &) const;

  void recoHitsLayer(HitSet &, const StripSet &, int, int &) const;

  void findCluster(int &,int, std::vector<int> &,layerStripMap::const_iterator &,layerStripMap::const_iterator &,const StripSet &) const;

  double calculateStripHitPositionFromCluster(int, const std::vector<int> &) const;

};
} // end namespace fc

#endif // Modules_HitRecoModule_hh
