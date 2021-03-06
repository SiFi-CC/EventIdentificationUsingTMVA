#ifndef __InputReaderGeant_H_
#define __InputReaderGeant_H_ 1
#include "DR_GenerallStructs.hh"
//#include "G4Input.hh"
#include "InputReader.hh"
#include <iostream>

using namespace std;

/// Class for accessing data from Geant4 simulation performed by JK.
/// This is class derived from InputReader class. It opens requested
/// ROOT file containing tree with simulation results and via set of
/// getter function passes information to reconstruction classes, i.e.
/// CCREconstruction and CCMLEM.

class InputReaderGeant : public InputReader {

public:
  InputReaderGeant();
  InputReaderGeant(TString path);
  ~InputReaderGeant();

  bool LoadEvent(int i);
  void Clear(void);
  TVector3* GetPositionPrimary(void);
//////////// old version/////////// 
  
//  TVector3* GetElectronPosition(void);
//  TVector3* GetPhotonPosition(void);
  
//////////////////////////////////////
  
  TVector3* GetPositionScatteringReco(void);
  
  TVector3* GetPositionAbsorptionReco(void);
  TVector3* GetRealComptonPosition(void);
  TVector3* GetGammaDirPrimary(void);
  TVector3* GetGammaDirScattered(void);
  TVector3* GetGammaDirScatteredReco(void);
  int GetRecoClusterPosSize(void);
  TVector3* GetClusterPosition(void);
  
/////  new version of file///////////////
  
  vector<TVector3>* GetElectronPosition(void);
  vector<TVector3>* GetPhotonPosition(void);
  
  int GetRealPosESize(void);
  int GetRealPosPSize(void);
  
  vector<int>* GetRealInteractionE(void);
  vector<int>* GetRealInteractionP(void);
  
////////////////////////////////////////////////
  
  double GetEP(void);
  double GetEnergyPrimary(void);
  double GetEnergyPrimaryReco(void);
  double GetEnergyLoss(void);
  double GetEnergyLossReco(void);
  double GetEnergyLossRecoUncer(void);
  double GetEnergyScattered(void);
  double GetEnergyScatteredReco(void);
  double GetEnergyScatteredRecoUncer(void);
  int GetIdentified(void);
  vector<PhysicVec>* GetRecoClusterPosition(void);
  vector<PhysicVar>* GetRecoClusterEnergy(void);

  TVector3* GetScattererPosition(void);
  TVector3* GetAbsorberPosition(void);

  double GetScatThickx(void);
  double GetScatThicky(void);
  double GetScatThickz(void);
  double GetAbsThickx(void);
  double GetAbsThicky(void);
  double GetAbsThickz(void);

private:
  int fEventNumber; ///< Event number
  int fIdentified; ///< Flag indicating whether the event was labeled or not
  bool fPurCrossed;
  Double_t fEnergy_Primary;
  Double_t fRealEnergy_e; ///< Electron energy + uncertainty [MeV]
  Double_t fRealEnergy_p; ///< Photon energy + uncertainty [MeV]
  TVector3* fRealPosition_source;
  TVector3* fRealDirection_source;
/////////////////////old version//////////////////////
  
//  TVector3* fRealPosition_e; ///< Electron creation position + uncertainty
//  TVector3* fRealPosition_p; ///< Photon energy deposition position + incertainty
  
////////////////////////////////////////////////////

  TVector3* fRealDirection_scatter; ///< Direction of the scattered photon +
                                    ///< uncertainty
                                    
  TVector3* fRealComptonPosition;
  
///// new version of file////////////
  
  vector<TVector3>* fRealPosition_e;
  vector<TVector3>* fRealPosition_p;
  
  vector<int>* fRealInteractions_e;
  vector<int>* fRealInteractions_p;
  
//////////////////////////////////// 
  
  PhysicVar* fRecoEnergy_e;   ///< Electron energy + uncertainty [MeV]
  PhysicVar* fRecoEnergy_p;   ///< Photon energy + uncertainty [MeV]
  PhysicVec* fRecoPosition_e; ///< Electron creation position + uncertainty
  PhysicVec* fRecoPosition_p; ///< Photon energy deposition position + incertainty
  PhysicVec* fRecoDirection_scatter; ///< Direction of the scattered photon +
                                     ///< uncertainty
                                     
  PhysicVec RecoClusterPositions;                                   
  vector<PhysicVec>*
      fRecoClusterPositions; ///< Positions cluster with uncertainties
  vector<PhysicVar>*
      fRecoClusterEnergies; ///< Energies cluster with uncertainties


  TVector3* fPositionScat;  ///< Position of interaction in scatterer
  TVector3* fPositionAbs;   ///< Position of interaction in absorber
  TVector3* fDirectionScat; ///< Direction of scattered gamma
  
  TVector3* fComptonPosition;
  
  TVector3* fPositionScatReco;
  TVector3* fPositionAbsReco;
  TVector3* fDirectionScatReco;
  
  TVector3* fPositionSource;
  TVector3* fDirectionSource;

  TVector3* fScattererPosition;
  TVector3* fAbsorberPosition;

  TVector3* fScatPlanePos;
  TVector3* fAbsPlanePos;
  
  //TVector3* fClusterPos;

  Double_t fScattererThickness_x;
  Double_t fScattererThickness_y;
  Double_t fScattererThickness_z;
  Double_t fAbsorberThickness_x;
  Double_t fAbsorberThickness_y;
  Double_t fAbsorberThickness_z;
  Double_t fNumberOfSimulatedEvents;

  bool AccessTree(TString name, TString name1);
  TTree* fTree1;
  TTree* fTree;

  //ClassDef(InputReaderGeant, 0)
};

#endif
