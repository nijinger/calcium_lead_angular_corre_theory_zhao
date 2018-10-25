#include "ExG4ppacSD.hh"
#include "ExG4ppacHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

ExG4ppacSD::ExG4ppacSD(G4String name)
: G4VSensitiveDetector(name), fHitsCollection(0), fHCID(-1)
{
  G4String HCname = "ppacColl";
  collectionName.insert(HCname);
}

ExG4ppacSD::~ExG4ppacSD()
{}

void ExG4ppacSD::Initialize(G4HCofThisEvent* hce)
{
  fHitsCollection = new ExG4ppacHitsCollection
  (SensitiveDetectorName,collectionName[0]);
  if(fHCID<0) fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
  hce->AddHitsCollection(fHCID,fHitsCollection);
}

G4bool ExG4ppacSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  G4double edep = step->GetTotalEnergyDeposit();
  if(edep==0.) return true;
  G4StepPoint* preStepPoint = step->GetPreStepPoint();

  G4TouchableHistory* touchable
   = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4int copyNo=touchable->GetVolume()->GetCopyNo();
  
  G4ThreeVector worldPos = preStepPoint->GetPosition();
  G4ThreeVector localPos
    = touchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
  G4double hitTime = preStepPoint->GetGlobalTime();

  ExG4ppacHit* hit = new ExG4ppacHit(worldPos,localPos,edep,hitTime,copyNo);

  G4String pname = step->GetTrack()->GetParticleDefinition()->GetParticleName();
  if(pname!="e-")
  fHitsCollection->insert(hit);
  else delete hit;

  return true;
}
