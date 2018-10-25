#ifndef ExG4RunAction_h
#define ExG4RunAction_h

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class TreeManager;

class ExG4RunAction : public G4UserRunAction
{
public:
  ExG4RunAction();
  virtual ~ExG4RunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

private:
  TreeManager *fTreeM;
};

#endif
