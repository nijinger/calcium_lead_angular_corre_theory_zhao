#ifndef ParticleDefinition_h
#define ParticleDefinition_h

#include "globals.hh"
#include "G4ThreeVector.hh"
struct Particle
{
  G4int Z;
  G4int A;
  G4double E; //MeV
  G4double excE;// excited Energy
  G4ThreeVector p;//momentum direction
  G4ThreeVector v;//velocity
};

#endif
