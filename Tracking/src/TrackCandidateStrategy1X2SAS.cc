#define _USE_MATH_DEFINES
#include<cmath>
#include <iostream>
#include "Geometry/include/DetectorGeometry.hh"
#include "DataObjects/include/Track.hh"
#include "DataObjects/include/HitSet.hh"
#include "Algorithms/include/InitializeHelix.hh"
#include "Tracking/include/TrackCandidateStrategy1X2SAS.hh"


fc::TrackCandidateStrategy1X2SAS::TrackCandidateStrategy1X2SAS(int debugLevel,const DetectorGeometry& detectorGeometry,double minCandPTCut):
  TrackCandidateStrategy(debugLevel,detectorGeometry,minCandPTCut) {
}


// !!!!! Could improve to use more than outer layers
// !!!!! control seed layers from config
void fc::TrackCandidateStrategy1X2SAS::findHitCadidates(std::vector<fc::trackHitSet>& trackHitCandidates,const HitSet& hitSet) const{
 
  int hitNumberO = 0;

  // Form 4-3,9 hit candidates
  for (hitSet::const_iterator hitIterO = hitSet.getHits().begin(); hitIterO != hitSet.getHits().end(); ++hitIterO,++hitNumberO) {

    if (hitIterO->getLayer() == 4) {

      int hitNumberI = 0;
 
      for (hitSet::const_iterator hitIterI = hitSet.getHits().begin(); hitIterI != hitSet.getHits().end(); ++hitIterI,++hitNumberI) {

	if (hitIterI->getLayer() == 3) {

	  int hitNumberOSAS = 0;

	  for (hitSet::const_iterator hitIterOSAS = hitSet.getHits().begin(); hitIterOSAS != hitSet.getHits().end(); ++hitIterOSAS,++hitNumberOSAS) {

	    if (hitIterOSAS->getLayer() == 9) {

	      TVector3 zIntersection;
	      bool goodIntersection = intersectStrips(*hitIterO,*hitIterOSAS,zIntersection,_detectorGeometry);
	      if (goodIntersection) {

                TVector3 primaryVertex(0.0,0.0,0.0);
		Helix helix = initializeHelix(primaryVertex,hitIterO->getHitPosition(),hitIterI->getHitPosition(),zIntersection,_detectorGeometry);
		if (goodCandidate(helix)) {
		  //avoids a copy
		  trackHitCandidates.push_back( std::vector<int>{hitNumberO,hitNumberI,hitNumberOSAS} );
		}
	      }

	    }

	  }

	}

      }

    }

  }
}

void fc::TrackCandidateStrategy1X2SAS::filterTrackCandidates(trackSet& trackCandidateSet,const HitSet& hitSet) const{
  // could be used in cases where more layers are used to candidate construction

}

