#ifndef ExG4PrimaryGeneratorAction_hh
#define ExG4PrimaryGeneratorAction_hh

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

#include "CLHEP/Units/SystemOfUnits.h"

class G4ParticleGun;
class G4Event;
class ParticleSource;
class ParticleDecay;

class ExG4PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  ExG4PrimaryGeneratorAction(
    const G4String& particleName = "geantino",
    G4double energy = 1.*CLHEP::MeV,
    G4ThreeVector position= G4ThreeVector(0,0,-40.*CLHEP::cm),
    G4ThreeVector momentumDirection = G4ThreeVector(0,0,1));
  ~ExG4PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);

private:
  G4ParticleGun* fParticleGun;
  FILE *pfile;

};

#endif
