#include <string>
#include <array>
#include <limits>
#include "Services/include/Exception.hh"
#include "DataObjects/include/GenTrackSet.hh"
#include "Algorithms/include/GenTrackSetIO.hh"

fc::GenTrackSetIO::GenTrackSetIO():
  _version(1){

}

void fc::GenTrackSetIO::writeEvent(const GenTrackSet& genTrackSet, std::ofstream& gentrackdata) const{

  // set precision output to precision of a doulbe + 2 digits to avoid rounding problems
  gentrackdata.precision(std::numeric_limits<double>::digits10 + 2);

  gentrackdata << "GenTrackSet" << std::endl;
  gentrackdata << _version << std::endl;

  genTrackSet::size_type numberGenTracks = genTrackSet.getGenTracks().size();
  gentrackdata << numberGenTracks << std::endl;

  int genTrackNumber =0;

  for (genTrackSet::const_iterator genTrackIter =  genTrackSet.getGenTracks().begin(); genTrackIter != genTrackSet.getGenTracks().end(); ++genTrackIter, ++genTrackNumber){

    // Extract a copy of the lorentzVector since functions in it are not const
    TLorentzVector lorentzVector = genTrackIter->getLorentzVector();

    gentrackdata << genTrackNumber << std::endl;

    gentrackdata << genTrackIter->getCharge() << std::endl;

    gentrackdata << lorentzVector.Px() << std::endl;
    gentrackdata << lorentzVector.Py() << std::endl;
    gentrackdata << lorentzVector.Pz() << std::endl;
    gentrackdata << lorentzVector.E()  << std::endl;

    // Point of clossest approach to the the reference point 0 0 0 and sign


    gentrackdata << genTrackIter->getPosition().X() <<std::endl;
    gentrackdata << genTrackIter->getPosition().Y() <<std::endl;
    gentrackdata << genTrackIter->getPosition().Z() <<std::endl;

    // !!!!! replace with is in opp hemispere from phi0
    //int d0Sign;
    //if (std::signbit(genTrackIter->getPosition.Y()) {d0Sign = -1;} else {d0Sign = 1;}
    //gentrackdata << d0Sign << std::endl;


  } // end track loop
}

void fc::GenTrackSetIO::readEvent(GenTrackSet & genTrackSet, std::ifstream & gentrackdata) {

  std::string eventDataObject;
  int version;
  int numberTracks;
  int genTrackNumber;
  int charge;
  std::array<double,4> p4;
  std::array<double,3> x3;

  gentrackdata >> eventDataObject;

  if (eventDataObject != "GenTrackSet"){
    std::string wrongEventDataObject = "GenTrackSet::readEvent: attempted to read wrong data object" + eventDataObject;
    throw Exception(wrongEventDataObject);  
  }

  gentrackdata >> version;

  if (version != _version) {
    std::string wrongStreamerVersion = "GenTrackSet::readEvent: attempted to read version " + std::to_string(version) + " using streamer version " + std::to_string(_version);
    throw Exception(wrongStreamerVersion);  
  }

  gentrackdata >> numberTracks;

  for (int ii_track = 0; ii_track < numberTracks; ++ii_track) {
 
    gentrackdata >> genTrackNumber;

    gentrackdata >> charge;

    gentrackdata >> p4[0];
    gentrackdata >> p4[1];
    gentrackdata >> p4[2];
    gentrackdata >> p4[3];

    TLorentzVector p(p4[0],p4[1],p4[2],p4[3]);
 
    gentrackdata >> x3[0];
    gentrackdata >> x3[1];
    gentrackdata >> x3[2];

    TVector3 dr(x3[0],x3[1],x3[2]);
 

    GenTrack genTrack(p,charge,dr);
 
    genTrackSet.insertTrack(genTrack);

  } // end track loop 

}
