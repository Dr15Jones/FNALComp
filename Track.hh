#ifndef Track_hh
#define Track_hh
//============================================================================
// Track.hh
// header with class definition of the Track
// Used for both generator level and reconstructed tracks
// New version to support track fittering
// See <A HREF="doc/notes/Track.pdf">Track.pdf</A> for more information
//
// Track Helix parameter definition
//
// Units are in m, GeV  and Tesla such that alpha = 1.0e9/(_bField[2]*2.99792458e8)
//
//      x = x0 + drho * cos(phi0) + rho * (cos(phi0) - cos(phi0 + phi))
//      y = y0 + drho * sin(phi0) + rho * (sin(phi0) - cos(sin0 + phi))
//      z = z0 + dz               - rho * tan(lambda) * phi
//
// Such that phi0 is the angle to the point of closest approach and the radius of curvature rho = alpha/kappa
//
// Standard track parameter diffinition
//          pT = 1/abs(kappa)
//          cot(theata) = 1/tan(lambda)
// standard phi0 = helix phi0 + PI/2
//          d0 = drho aka dr 
//          z0 = dz
//
// Author Matt Herndon, University of Wisconsin,
//                       Fermi National Accelerator Laborator
// 2014-06-18
//============================================================================

#include "TVector3.h"
#include "TMatrixD.h"
#include "TLorentzVector.h"
#include <map>

class DetectorGeometry;
class HitSet;

namespace fc {

typedef std::map<int, int> trackHitMap; //!< Map of hit number and layer

///
/// Class Track: TLorentzVector to track physics properties and THGeoHelix to track tracking and helix properties
/// Author Matt Herndon, University of Wisconsin, Fermi National Accelerator Laboratory 2014-06-06
/// For more information see <a href="../notes/Track.pdf">Track.pdf</a> 
///

class Track {
private:

   // _mDim is the number of measurement dimentions for the hitss.  2: r and phi
   // _sDim is the number of helix paramters. 5
  static const int _mDim = 2; //!< Measurement dimention of hits
  static const int _sDim = 5;     //!< helix dimention

  double _dr;        // dr, drho
  double _phi0;      // phi0
  double _kappa;     // kappa, signed curvature
  double _dz;        // dz
  double _tanL;      // tanl

  TVector3 _primaryVertex;      // primary vertex or pivot point

  TVector3 _initialPosition;

  TMatrixD * _covMatrix;

  trackHitMap _trackHitMap;
  
  const DetectorGeometry & _detectorGeometry;

  TVector3 _bField;

  double _alpha; // 1/curvatureC

  int _debugLevel;


public:

// Constructors

  Track();
  Track(double kappa, double dr, double dz, double phi0, double tanl, const TVector3 & v0, const DetectorGeometry & detectorGeometry, const TVector3 & bField);
  Track(const TLorentzVector & lorentzVector, int charge, const TVector3 & initialPosition, const TVector3 & primaryVertex, const DetectorGeometry & detectorGeometry, const TVector3 & bField);
  Track(const TVector3 & x1, const TVector3 & x2, const TVector3 & x3, const TVector3 & primaryVertex, const DetectorGeometry & detectorGeometry,int debugLevel);

  Track(const Track&);
  
  // Destructor
  ~Track() {};
 

  // Utility functions

  bool intersectWithLayer(TVector3 & hitPosition, int layer, const DetectorGeometry & detectorGeometry) const;
  bool intersectWithPlane(TVector3 & hitPosition, const TVector3 & center, const TVector3 & normal,double & phi) const;


  TVector3 calcXAt(double phi) const;
  TMatrixD calcDxDHC(double phi) const;
  TMatrixD calcDxDphi(double phi) const;
  TMatrixD calcDXZDHC(const TVector3   & hitPosition, const TMatrixD &dxphiadHC)  const;


  TMatrixD expectedMeasurementVectorXZ(int layer, const DetectorGeometry & detectorGeometry) const;
  TMatrixD expectedMeasurementDerivativedXZdHC(int layer, const DetectorGeometry & detectorGeometry) const;
  TMatrixD invMeasurementRes2XZ(int layer, const DetectorGeometry & detectorGeometry) const;
  TMatrixD measurementVectorXZ(const TVector3 & hitPosition) const;

  // Fit function
  void FitToHelix(const HitSet & hitSet, const DetectorGeometry & detectorGeometry,bool withPrimaryVertex);


  //void MoveTo(const TVector & x0, TMatrixD & propMatrix, TMatrixD & covMatrix); 



  // Get objects
  TLorentzVector  getLorentzVector(void) const;

  const TVector3& getConstInitialPosition(void) const {return _initialPosition;};




  int getCharge(void) const {return -_kappa/std::abs(_kappa);};




  // Hit/measurement point information

  const trackHitMap& getTrackHitMap(void) const {return _trackHitMap;};

  void insertHit(int,int);

  void print(void) const;

};
} // end namescape fc

#endif // Track_hh

