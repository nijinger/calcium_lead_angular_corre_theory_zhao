#include "ExG4ppacHit.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

G4ThreadLocal G4Allocator<ExG4ppacHit>* ExG4ppacHitAllocator;

ExG4ppacHit::ExG4ppacHit(G4ThreeVector pos,G4ThreeVector lpos,G4double de, G4double tof,G4int id)
: G4VHit(), fPos(pos), fLPos(lpos), fE(de), fTof(tof) ,fId(id)
{}

void ExG4ppacHit::Print()
{

}
