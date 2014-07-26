#ifndef GenTrack_hh
#define GenTrack_hh
//============================================================================
// GenTrack.hh
// header with class definition of the GenTrack
// Used for both generator level tracks
// New version to support track fittering
// See <A HREF="doc/notes/Track.pdf" Track.pdf</A> for more information
//
// GenTrack Helix parameter definition
//
// Units are in GeV 
//
// Author Matt Herndon, University of Wisconsin,
//                       Fermi National Accelerator Laborator
// 2014-07-24
//============================================================================

#include "TVector3.h"
#include "TLorentzVector.h"


namespace fc {

class Helix;


///
/// Class GenTrack: TLorentzVector to track momentum, and TVector3 initial position
/// Author Matt Herndon, University of Wisconsin, Fermi National Accelerator Laboratory 2014-07-24
/// For more information see <a href="../notes/Track.pdf">Track.pdf</a> 
///

class GenTrack {
private:

  TLorentzVector _lorentzVector;
  int _charge;
  TVector3 _dr; // point of clossest approach to 0,0,0cp 

public:

// Constructors

  GenTrack(const TLorentzVector & lorentzVector, int charge, const TVector3 & dr);

  
  // Destructor
  ~GenTrack() {};

  // Get objects

  TLorentzVector  getLorentzVector() const {return _lorentzVector;}
  TVector3 getPosition() const {return _dr;}
  int getCharge() const {return _charge;}

  // convert to helix
  Helix makeHelix(double alpha) const;
  Helix makeHelix() const;

  // Print method

  void print() const;

};
} // end namescape fc

#endif // GenTrack_hh
