#ifndef Tracking_TrackCandidateStrategy1X2SAS_hh
#define Tracking_TrackCandidateStrategy1X2SAS_hh
//============================================================================
// TrackCandidateStategy1X2SAS.hh
// header with function definitions of the TrackCandidateStategy1X2SAS 
//   track candidate finding stratgy
//
// Author Matt Herndon, University of Wisconsin,
//                       Fermi National Accelerator Laborator
// 2014-07-23
//============================================================================

#include "Tracking/include/TrackCandidateStrategy.hh"


namespace fc {

class HitSet;
class DetectorGeometry;

  class TrackCandidateStrategy1X2SAS : public TrackCandidateStrategy{

  public:

    TrackCandidateStrategy1X2SAS(int,const DetectorGeometry&,double);

  private:

    void findHitCadidates(std::vector<fc::trackHitSet>& trackHitCandidates,const HitSet& hitSet) const override;
    void filterTrackCandidates(trackSet& trackCandidateSet,const HitSet& hitSet) const override;

  };


} // end namescape fc

#endif // Tracking_TrackCandidateStrategy1X2SAS_hh

