#ifndef ExG4EventAction_h
#define ExG4EventAction_h

#include "G4UserEventAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "ExG4ppacHit.hh"

class TreeManager;

class ExG4EventAction : public G4UserEventAction
{
public:
  ExG4EventAction();
  virtual ~ExG4EventAction();

  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);

private:
  G4int ftarID;  //target
  G4int lppacID;  //chico ball left side ppacs
  G4int rppacID;  //chico ball right side ppacs


  TreeManager* ftm;
};

#endif
