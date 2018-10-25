#ifndef ExG4DetectorConstruction_h
#define ExG4DetectorConstruction_h

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "G4FieldManager.hh"

#include <vector>

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;

//Detector construction
class ExG4DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    ExG4DetectorConstruction();
    virtual ~ExG4DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
    
    void ConstructMaterials();

private:
    G4VPhysicalVolume* ftar;
    G4VPhysicalVolume* fball;
    G4VPhysicalVolume* ppacl;
    G4VPhysicalVolume* ppacr;
    G4VPhysicalVolume* ppaclf;
    G4VPhysicalVolume* ppacrf;

    G4LogicalVolume* tarLogical;
    G4LogicalVolume* ballLogical;
    G4LogicalVolume* lppacLogical;
    G4LogicalVolume* rppacLogical;
    G4LogicalVolume* lppacfLogical;
    G4LogicalVolume* rppacfLogical;


    //Materials
    G4Material* si;
    G4Material* csi;
    G4Material* vacuum;
    G4Material* pb;
    G4Material* gas;
    G4Material* film;
    G4Material* al;

    G4RotationMatrix *rotm;

};

#endif
