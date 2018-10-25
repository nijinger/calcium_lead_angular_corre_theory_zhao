#ifndef ExG4PhysicsList_h
#define ExG4PhysicsList_h

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class ExG4PhysicsList : public G4VModularPhysicsList
{
public:
  ExG4PhysicsList();
  virtual ~ExG4PhysicsList();


  virtual void ConstructParticle();
  virtual void ConstructProcess();
};

#endif
