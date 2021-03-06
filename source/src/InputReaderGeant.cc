#include "InputReaderGeant.hh"

//ClassImp(InputReaderGeant);

//------------------------------------------------------------------
/// Default constructor.
InputReaderGeant::InputReaderGeant() : InputReader() {
  Clear();
  cout << "##### Warning in InputReaderGeant constructor!" << endl;
  cout << "You are usinf default constructor." << endl;
}
//------------------------------------------------------------------
/// Standard constructor.
///\param path (TString) - path to the input file.
InputReaderGeant::InputReaderGeant(TString path) : InputReader(path) {

 if (!AccessTree("Setup", "Events")) {
    throw "##### Exception in InputReaderGeant constructor!";
  }
///these two below belong to when neither RealPosition_e nor RealPosition_p are vector, 
///but only TVector3./////////////

//  fPositionScat = new TVector3();
//  fPositionAbs = new TVector3();
  
//////////////////////////////////////  
  fDirectionScat = new TVector3();
  fComptonPosition = new TVector3();
  
  fPositionScatReco = new TVector3();
  fPositionAbsReco = new TVector3();
  fDirectionScatReco = new TVector3();
  
  fPositionSource = new TVector3();
  fDirectionSource = new TVector3();

  fScatPlanePos = new TVector3();
  fAbsPlanePos = new TVector3();
  
  //fClusterPos = new TVector3();
}
//------------------------------------------------------------------
/// Default destructor.
InputReaderGeant::~InputReaderGeant() {
  if (fFile->IsOpen()) fFile->Close();
}
//------------------------------------------------------------------
bool InputReaderGeant::AccessTree(TString name, TString name1) {

  fTree = (TTree*)fFile->Get(name);
  fTree1 = (TTree*)fFile->Get(name1);
  //fTree2 = (TTree*)fFile->Get(name2);
  if (fTree == NULL) {
    cout << "##### Error in InputReaderGeant::AccessTree()!" << endl;
    cout << "Could not access the tree!" << endl;
    return false;
  }
  if (fTree1 == NULL) {
    cout << "##### Error in InputReaderGeant4::AccessTree()!" << endl;
    cout << "Could not access the tree!" << endl;
    return false;
  }
//   if (fTree2 == NULL) {
//     cout << "##### Error in InputReaderGeant::AccessTree()!" << endl;
//     cout << "Could not access the tree!" << endl;
//     return false;
//   }
  
  fRecoEnergy_e = new PhysicVar();
  fRecoEnergy_p = new PhysicVar();
  fRecoPosition_e = new PhysicVec();
  fRecoPosition_p = new PhysicVec();
  fRecoDirection_scatter = new PhysicVec();
  
  fRecoClusterPositions = 0;
  fRecoClusterEnergies = 0;
  
/////// new version of file//////////////////
  
   fRealPosition_e = new vector<TVector3>;
   fRealInteractions_e = new vector<int>;
   fRealPosition_p = new vector<TVector3>;
   fRealInteractions_p = new vector<int>;
  
///////////////////////////////////////////////  
 
  fRealPosition_source = new TVector3();
  fRealDirection_source = new TVector3();
///these two below belong to when neither RealPosition_e nor RealPosition_p are vector, 
///but only TVector3.
  
//  fRealPosition_e = new TVector3();
//  fRealPosition_p = new TVector3();
  
//////////////////////////////////////////  
  fRealComptonPosition = new TVector3();
  fRealDirection_scatter = new TVector3();
  
  fScattererPosition = new TVector3();
  fAbsorberPosition = new TVector3();

  fTree->SetBranchAddress("ScattererThickness_x", &fScattererThickness_x);
  fTree->SetBranchAddress("ScattererThickness_y", &fScattererThickness_y);
  fTree->SetBranchAddress("ScattererThickness_z", &fScattererThickness_z);
  fTree->SetBranchAddress("AbsorberThickness_x", &fAbsorberThickness_x);
  fTree->SetBranchAddress("AbsorberThickness_y", &fAbsorberThickness_y);
  fTree->SetBranchAddress("AbsorberThickness_z", &fAbsorberThickness_z);
  fTree->SetBranchAddress("ScattererPosition", &fScattererPosition);
  fTree->SetBranchAddress("AbsorberPosition", &fAbsorberPosition);
  fTree->SetBranchAddress("NumberOfSimulatedEvents",
                           &fNumberOfSimulatedEvents);
  
  fTree1->SetBranchAddress("EventNumber", &fEventNumber);
  fTree1->SetBranchAddress("Energy_Primary", &fEnergy_Primary);
  fTree1->SetBranchAddress("RealEnergy_e", &fRealEnergy_e);
  fTree1->SetBranchAddress("RealEnergy_p", &fRealEnergy_p);
  fTree1->SetBranchAddress("RealPosition_source", &fRealPosition_source);
  fTree1->SetBranchAddress("RealDirection_source", &fRealDirection_source);
  fTree1->SetBranchAddress("RealComptonPosition", &fRealComptonPosition);
  fTree1->SetBranchAddress("RealDirection_scatter", &fRealDirection_scatter);
  fTree1->SetBranchAddress("RealPosition_e", &fRealPosition_e);
  fTree1->SetBranchAddress("RealInteractions_e", &fRealInteractions_e);
  fTree1->SetBranchAddress("RealPosition_p", &fRealPosition_p);
  fTree1->SetBranchAddress("RealInteractions_p", &fRealInteractions_p);
  fTree1->SetBranchAddress("Identified", &fIdentified);
  fTree1->SetBranchAddress("PurCrossed", &fPurCrossed);
  fTree1->SetBranchAddress("RecoEnergy_e", &fRecoEnergy_e);
  fTree1->SetBranchAddress("RecoEnergy_p", &fRecoEnergy_p);
  fTree1->SetBranchAddress("RecoPosition_e", &fRecoPosition_e);
  fTree1->SetBranchAddress("RecoPosition_p", &fRecoPosition_p);
  fTree1->SetBranchAddress("RecoDirection_scatter", &fRecoDirection_scatter);
  fTree1->SetBranchAddress("RecoClusterPositions", &fRecoClusterPositions);
  fTree1->SetBranchAddress("RecoClusterEnergies", &fRecoClusterEnergies);

  cout << "\n\nIn InputReaderGeant::AccessTree()." << endl;
  cout << fTree->GetName() << " Setup tree accessed.\n" << endl;

  cout << "\n\nIn InputReaderGeant::AccessTree()." << endl;
  cout << fTree1->GetName() << " Event tree accessed.\n" << endl;
  
//   cout << "\n\nIn InputReaderGeant::AccessTree()." << endl;
//   cout << fTree2->GetName() << " tree accessed.\n" << endl;
  
  return true;
}
//------------------------------------------------------------------
bool InputReaderGeant::LoadEvent(int i) {

  int imax1 = fTree->GetEntries();
  fTree->GetEntry(i);
  
//   int imax2 = fTree2->GetEntries();
//   if (i > imax2) {
//     cout << "##### Error in InputReaderGeant::LoadEvent() in reconstruction tree!" << endl;
//     cout << "Requested event number larger than number of events in the tree!"
//          << endl;
//     return false;
//   }
//   fTree2->GetEntry(i);
  
  //return fIdentified;
  
  int imax = fTree1->GetEntries();
  if (i > imax) {
     cout << "##### Error in InputReaderGeant::LoadEvent() in Event tree!" << endl;
     cout << "Requested event number larger than number of events in the tree!"
          << endl;
     return false;
   }
// 
 fTree1->GetEntry(i);
 
/*  if (0 == fRealPosition_e->X() || 0 == fRealPosition_p->X()) {
      
     // cout << " Pos_e.X : " << fRealPosition_e->X() << " , " << " Pos_p.X : " << fRealPosition_p->X() << endl;
     return false;
  }*/
 //if (0 == fRealPosition_e->Y() || 0 == fRealPosition_p->Y()) return false;
 //if (0 == fRealPosition_e->Z() || 0 == fRealPosition_p->Z()) return false;

  return true;
}
//------------------------------------------------------------------
TVector3* InputReaderGeant::GetPositionPrimary(void) {
  //cout << "##### Warning in InputReaderGeant::GetPositionPrimary()!" << endl;
  //cout << "\t Position of gamma source is unknown!" << endl;
  fPositionSource->SetX(fRealPosition_source->X());
  fPositionSource->SetY(fRealPosition_source->Y());
  fPositionSource->SetZ(fRealPosition_source->Z());
  return fPositionSource;
  // return NULL;
}
//------------------------------------------------------------------
/*
TVector3* InputReaderGeant::GetElectronPosition(void) {
  fPositionScat->SetX(fRealPosition_e->X());
  fPositionScat->SetY(fRealPosition_e->Y());
  fPositionScat->SetZ(fRealPosition_e->Z());
  return fPositionScat;
}*/
//----------new version of file--------------------------------------------------------

vector<TVector3>* InputReaderGeant::GetElectronPosition(void) { 
    
    return fRealPosition_e; }
//------------------------------------------------------------------

int InputReaderGeant::GetRealPosESize(void) { return fRealPosition_e->size(); }    
//------------------------------------------------------------------

vector<int>* InputReaderGeant::GetRealInteractionE(void) { 
    
    return fRealInteractions_e; }
//------------------------------------------------------------------
TVector3* InputReaderGeant::GetPositionScatteringReco(void) {
  fPositionScatReco->SetX(fRecoPosition_e->position.X());
  fPositionScatReco->SetY(fRecoPosition_e->position.Y());
  fPositionScatReco->SetZ(fRecoPosition_e->position.Z());
  return fPositionScatReco;
}
//------------------------------------------------------------------
/*
TVector3* InputReaderGeant::GetPhotonPosition(void) {
  fPositionAbs->SetX(fRealPosition_p->X());
  fPositionAbs->SetY(fRealPosition_p->Y());
  fPositionAbs->SetZ(fRealPosition_p->Z());
  return fPositionAbs;
}*/
//--------------new version of file----------------------------------------------------

vector<TVector3>* InputReaderGeant::GetPhotonPosition(void) { 
    
    return fRealPosition_p; }
//------------------------------------------------------------------    
int InputReaderGeant::GetRealPosPSize(void) { return fRealPosition_p->size(); }      
//------------------------------------------------------------------
vector<int>* InputReaderGeant::GetRealInteractionP(void) { 
    
    return fRealInteractions_p; }
//------------------------------------------------------------------
TVector3* InputReaderGeant::GetPositionAbsorptionReco(void) {
  fPositionAbsReco->SetX(fRecoPosition_p->position.X());
  fPositionAbsReco->SetY(fRecoPosition_p->position.Y());
  fPositionAbsReco->SetZ(fRecoPosition_p->position.Z());
  return fPositionAbsReco;
}
//------------------------------------------------------------------
TVector3* InputReaderGeant::GetRealComptonPosition(void) {
  fComptonPosition->SetX(fRealComptonPosition->X());
  fComptonPosition->SetY(fRealComptonPosition->Y());
  fComptonPosition->SetZ(fRealComptonPosition->Z());
  return fComptonPosition;
}
//----------------------------------------------------------------
TVector3* InputReaderGeant::GetGammaDirPrimary(void) {
  // cout << "##### Warning in InputReaderGeant::GetGammaDirPrimary()!" << endl;
  // cout << "\t Direction of primary gamma is unknown!" << endl;
  fDirectionSource->SetX(fRealDirection_source->X());
  fDirectionSource->SetY(fRealDirection_source->Y());
  fDirectionSource->SetZ(fRealDirection_source->Z());
  return fDirectionSource;
  // return NULL;
}
//------------------------------------------------------------------
TVector3* InputReaderGeant::GetGammaDirScattered(void) {
  // TVector3* temp = new TVector3();
  fDirectionScat->SetX(fRealDirection_scatter->X());
  fDirectionScat->SetY(fRealDirection_scatter->Y());
  fDirectionScat->SetZ(fRealDirection_scatter->Z());
  return fDirectionScat;
}
//------------------------------------------------------------------
TVector3* InputReaderGeant::GetGammaDirScatteredReco(void) {
  
  fDirectionScatReco->SetX(fRecoDirection_scatter->position.X());
  fDirectionScatReco->SetY(fRecoDirection_scatter->position.Y());
  fDirectionScatReco->SetZ(fRecoDirection_scatter->position.Z());
  return fDirectionScatReco;
}
//------------------------------------------------------------------
TVector3* InputReaderGeant::GetScattererPosition(void) {
  fScatPlanePos->SetX(fScattererPosition->X());
  fScatPlanePos->SetY(fScattererPosition->Y());
  fScatPlanePos->SetZ(fScattererPosition->Z());
  return fScatPlanePos;
}
//------------------------------------------------------------------
TVector3* InputReaderGeant::GetAbsorberPosition(void) {
  fAbsPlanePos->SetX(fAbsorberPosition->X());
  fAbsPlanePos->SetY(fAbsorberPosition->Y());
  fAbsPlanePos->SetZ(fAbsorberPosition->Z());
  return fAbsPlanePos;
}
//------------------------------------------------------------------
int InputReaderGeant::GetIdentified(void) { return fIdentified; }
//------------------------------------------------------------------
int InputReaderGeant::GetRecoClusterPosSize(void) { return fRecoClusterPositions->size(); }
//------------------------------------------------------------------
double InputReaderGeant::GetEnergyPrimary(void) {
  double sum = fRealEnergy_e + fRealEnergy_p;
  return sum;
}
//------------------------------------------------------------------
double InputReaderGeant::GetEnergyPrimaryReco(void) {
  double sum = fRecoEnergy_e->value + fRecoEnergy_p->value;
  return sum;
}
//------------------------------------------------------------------
double InputReaderGeant::GetEP(void) { return fEnergy_Primary; }
//------------------------------------------------------------------
double InputReaderGeant::GetEnergyLoss(void) { return fRealEnergy_e; }
//------------------------------------------------------------------
double InputReaderGeant::GetEnergyLossReco(void) { return fRecoEnergy_e->value; }
//------------------------------------------------------------------
double InputReaderGeant::GetEnergyLossRecoUncer(void) { return fRecoEnergy_e->uncertainty; }
//------------------------------------------------------------------
double InputReaderGeant::GetEnergyScattered(void) { return fRealEnergy_p; }
//------------------------------------------------------------------
double InputReaderGeant::GetEnergyScatteredReco(void) { return fRecoEnergy_p->value; }
//------------------------------------------------------------------
double InputReaderGeant::GetEnergyScatteredRecoUncer(void) { return fRecoEnergy_p->uncertainty; }
//------------------------------------------------------------------
vector<PhysicVec>* InputReaderGeant::GetRecoClusterPosition(void) { 
    
    return fRecoClusterPositions; }
//------------------------------------------------------------------
vector<PhysicVar>* InputReaderGeant::GetRecoClusterEnergy(void) { 
    
    return fRecoClusterEnergies; }
//------------------------------------------------------------------
double InputReaderGeant::GetScatThickx(void) { return fScattererThickness_x; }
//------------------------------------------------------------------
double InputReaderGeant::GetScatThicky(void) { return fScattererThickness_y; }
//------------------------------------------------------------------
double InputReaderGeant::GetScatThickz(void) { return fScattererThickness_z; }
//------------------------------------------------------------------
double InputReaderGeant::GetAbsThickx(void) { return fAbsorberThickness_x; }
//------------------------------------------------------------------
double InputReaderGeant::GetAbsThicky(void) { return fAbsorberThickness_y; }
//------------------------------------------------------------------
double InputReaderGeant::GetAbsThickz(void) { return fAbsorberThickness_z; }
//------------------------------------------------------------------
void InputReaderGeant::Clear(void) {
  fEventNumber = -1;
  fIdentified = -1000;
  fPurCrossed = false;
  fEnergy_Primary = -1000;
  fRealEnergy_e = -1000;
  fRealEnergy_p = -1000;
  
  fRealPosition_e = NULL;
  fRealPosition_p = NULL;
  
  fRealInteractions_e = NULL;
  fRealInteractions_p = NULL;
  
  fPositionScat = NULL;
  fPositionAbs = NULL;
  fComptonPosition = NULL;
  fDirectionScat = NULL;
  fDirectionSource = NULL;
  fPositionSource = NULL;
  fTree = NULL;
  fTree1 = NULL;
  //fTree2 = NULL;
  fFile = NULL;
  fRealDirection_scatter = NULL;
  fRealDirection_source = NULL;
  fRealPosition_source = NULL;
  
  fRecoEnergy_e = NULL;
  fRecoEnergy_p = NULL;
  fRecoPosition_e = NULL;
  fRecoPosition_p = NULL;
  fPositionScatReco = NULL;
  fPositionAbsReco = NULL;
  fDirectionScatReco = NULL;
  if (!fRecoClusterPositions->empty()) fRecoClusterPositions->clear();
  if (!fRecoClusterEnergies->empty()) fRecoClusterEnergies->clear();

  
  fNumberOfSimulatedEvents = -1;
  fScattererThickness_x = -1000;
  fScattererThickness_y = -1000;
  fScattererThickness_z = -1000;
  fAbsorberThickness_x = -1000;
  fAbsorberThickness_y = -1000;
  fAbsorberThickness_z = -1000;

  fScattererPosition = NULL;
  fAbsorberPosition = NULL;
  fScatPlanePos = NULL;
  fAbsPlanePos = NULL;
  
  //fClusterPos = NULL;

  return;
}
//------------------------------------------------------------------
