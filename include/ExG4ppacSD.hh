#ifndef G4ExppacSD_h
#define G4ExppacSD_h

#include "G4VSensitiveDetector.hh"
#include "ExG4ppacHit.hh"

class ExG4ppacSD : public G4VSensitiveDetector
{
public:
  ExG4ppacSD(G4String name);
  virtual ~ExG4ppacSD();

  virtual void Initialize(G4HCofThisEvent *HCE);
  virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory*ROhist);

private:
  ExG4ppacHitsCollection* fHitsCollection;
  G4int fHCID;
};

#endif
