#include<iostream>
#include<cmath>
#include<string>
#include "Geometry/include/DetectorGeometry.hh"
#include "DataObjects/include/Track.hh"
#include "DataObjects/include/TrackSet.hh"
#include "DataObjects/include/GenTrack.hh"
#include "DataObjects/include/GenTrackSet.hh"
#include "Modules/include/TrackCompareModule.hh"
#include "TH1F.h"
#include "Services/include/UniqueRootDirectory.hh"

fc::TrackCompareModule::TrackCompareModule(int debugLevel, 
				       const std::string& inputGenTracksLabel,
				       const std::string& inputRecTracksLabel,
				       const DetectorGeometry & detectorGeometry ):
  _debugLevel(debugLevel),
  _detectorGeometry(detectorGeometry),
  _genTracksLabel(inputGenTracksLabel),
  _recTracksLabel(inputRecTracksLabel){

  initializeHistograms();
}

void fc::TrackCompareModule::initializeHistograms(){

  UniqueRootDirectory tdir("TrackCompare");


  deltaD0    = new TH1F("TrackDeltaD0", "Delta d0;delta d0(m);N",100, -0.001, 0.001);
  deltaPhi0  = new TH1F("TrackDeltaPhi0", "Delta phi0;delta phi0(rad);N",100, -0.005, 0.005);
  deltaKappa = new TH1F("TrackDeltaKappa", "Delta kappa; delta kappa (1/GeV);N",100, -0.01, 0.01);
  deltaZ0    = new TH1F("TrackDeltaZ0", "Delta z0;delta z0 (m); N",100, -0.001, 0.001);
  deltaTanL  = new TH1F("TrackDeltaTanL", "Delta tanL;delta tanL;N",100, -0.001, 0.001);

  deltaD0Pull    = new TH1F("TrackDeltaD0Pull", "Delta d0 Pull;delta d0  Pull);N",100, -4.0, 4.0);
  deltaPhi0Pull  = new TH1F("TrackDeltaPhi0Pull", "Delta phi0 Pull;delta phi0 Pull);N",100, -4.0, 4.0);
  deltaKappaPull = new TH1F("TrackDeltaKappaPull", "Delta kappa Pull; delta kappa  Pull;N",100, -4.0, 4.0);
  deltaZ0Pull    = new TH1F("TrackDeltaZ0Pull", "Delta z0 Pull;delta z0  Pull; N",100, -4.0, 4.0);
  deltaTanLPull  = new TH1F("TrackDeltaTanLPull", "Delta tanL Pull;delta tanL PUll;N",100, -4.0, 4.0);

}



void fc::TrackCompareModule::processEvent(Event& event)
{
 Handle<GenTrackSet> genTrackSet = event.get<GenTrackSet>(_genTracksLabel);
 Handle<TrackSet> recoTrackSet = event.get<TrackSet>(_recTracksLabel);

 compareTracks(*genTrackSet,*recoTrackSet);

  // Function to histogram results

}

void fc::TrackCompareModule::compareTracks(const GenTrackSet & genTrackSet, const TrackSet& recoTrackSet) const{

  
  if (recoTrackSet.getTracks().begin() == recoTrackSet.getTracks().end()) return;

  for (genTrackSet::const_iterator genTrackIter =  genTrackSet.getGenTracks().begin(); genTrackIter !=  genTrackSet.getGenTracks().end(); ++genTrackIter){

    const Track& recoTrack = matchTrack(*genTrackIter,recoTrackSet);
    TVectorD bestDeltaHP = deltaHP(*genTrackIter,recoTrack);
    fillHistograms(bestDeltaHP,recoTrack);


  }
}


const fc::Track & fc::TrackCompareModule::matchTrack(const GenTrack & genTrack, const TrackSet& recoTrackSet) const{

  double bestDeltaTracks = 1000.0;
  double tmpDeltaTracks;
  int trackNumber=0;
  int bestTrack=-1;

  for (trackSet::const_iterator recoTrackIter =  recoTrackSet.getTracks().begin(); recoTrackIter !=  recoTrackSet.getTracks().end(); ++recoTrackIter,++trackNumber){

    tmpDeltaTracks = deltaTracks(genTrack,*recoTrackIter);

    if (tmpDeltaTracks < bestDeltaTracks) {
      bestDeltaTracks = tmpDeltaTracks;
      bestTrack = trackNumber;
    }
  }

  return recoTrackSet.getTracks()[bestTrack];

}

double fc::TrackCompareModule::deltaTracks(const GenTrack & genTrack, const Track& recoTrack) const{

  return std::sqrt((genTrack.makeHelix().getKappa()-recoTrack.getHelix().getKappa())*(genTrack.makeHelix().getKappa()-recoTrack.getHelix().getKappa())+
		   (genTrack.makeHelix().getPhi0()-recoTrack.getHelix().getPhi0())*(genTrack.makeHelix().getPhi0()-recoTrack.getHelix().getPhi0()));

}

TVectorD fc::TrackCompareModule::deltaHP(const GenTrack & genTrack, const Track& recoTrack) const{


  return recoTrack.getHelix().getHelix() - genTrack.makeHelix().getHelix();

}

void fc::TrackCompareModule::fillHistograms(const TVectorD & deltaHP, const Track& recoTrack) const{

  deltaD0->Fill(deltaHP(0));
  deltaPhi0->Fill(deltaHP(1));
  deltaKappa->Fill(deltaHP(2));
  deltaZ0->Fill(deltaHP(3));
  deltaTanL->Fill(deltaHP(4));

  // adjust for 3 parameters

  deltaD0Pull->Fill(deltaHP(0)/recoTrack.getSigmaD0());
  deltaPhi0Pull->Fill(deltaHP(1)/recoTrack.getSigmaPhi0());
  deltaKappaPull->Fill(deltaHP(2)/recoTrack.getSigmaKappa());
  deltaZ0Pull->Fill(deltaHP(3)/recoTrack.getSigmaZ0());
  deltaTanLPull->Fill(deltaHP(4)/recoTrack.getSigmaTanL());


}

void fc::TrackCompareModule::endJob(){
}
