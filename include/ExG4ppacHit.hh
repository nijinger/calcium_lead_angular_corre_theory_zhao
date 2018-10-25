#ifndef ExG4ppacHit_h
#define ExG4ppacHit_h

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4Attdef;
class G4AttValue;

//ppac Hit
//
//Records:
// - the hit position
// - the deposited energy
// ======================================

class ExG4ppacHit : public G4VHit
{
public:
  ExG4ppacHit(G4ThreeVector pos, G4ThreeVector lpos,G4double de,G4double tof,G4int id);
  virtual ~ExG4ppacHit() {}

  inline void *operator new(size_t);
  inline void operator delete(void*aHit);

  void Print();
  G4ThreeVector GetPos() const { return fPos; }
  G4ThreeVector GetLPos() const { return fLPos; }
  G4double GetE() const { return fE;}
  G4double GetTof() const { return fTof;}
  G4int GetId() const {return fId;}

private:
  G4ThreeVector fPos;
  G4ThreeVector fLPos;
  G4double fE;
  G4double fTof;
  G4int fId;
};

typedef G4THitsCollection<ExG4ppacHit> ExG4ppacHitsCollection;

extern G4ThreadLocal G4Allocator<ExG4ppacHit>* ExG4ppacHitAllocator;

inline void* ExG4ppacHit::operator new(size_t)
{
  if (!ExG4ppacHitAllocator)
     ExG4ppacHitAllocator = new G4Allocator<ExG4ppacHit>;
     return (void*)ExG4ppacHitAllocator->MallocSingle();
}

inline void ExG4ppacHit::operator delete(void*aHit)
{
  ExG4ppacHitAllocator->FreeSingle((ExG4ppacHit*)aHit);
}
#endif
