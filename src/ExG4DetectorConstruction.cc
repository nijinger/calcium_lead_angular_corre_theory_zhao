#include "ExG4DetectorConstruction.hh"
#include "ExG4ppacSD.hh"
//#include "ExG4CsISD.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4ios.hh"
#include <cmath>

ExG4DetectorConstruction::ExG4DetectorConstruction():G4VUserDetectorConstruction(),ftar(0),fball(0),si(0),csi(0),vacuum(0)
{}

ExG4DetectorConstruction::~ExG4DetectorConstruction()
{}

G4VPhysicalVolume* ExG4DetectorConstruction::Construct()
{
  ConstructMaterials();
  
  G4bool checkOverlaps = true;

  //World

  G4VSolid* worldSolid
    = new G4Box("worldBox",0.5*m,0.5*m,0.5*m);
  G4LogicalVolume* worldLogical
    = new G4LogicalVolume(worldSolid,vacuum,"worldLogical");
  G4VPhysicalVolume* worldPhysical
    = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"WorldPhysical",0,false,0,checkOverlaps);

//****************************************************sphere*************************************************
  rotm = new G4RotationMatrix();
  rotm->rotateY(0.);
  //sphere
/*
  G4VSolid* sphere
    = new G4Sphere("sphere",400.*mm,420.*mm,0*deg,360*deg,0*deg,360.*deg);
  ballLogical
    = new G4LogicalVolume(sphere,si,"ballLogical");
  fball
    = new G4PVPlacement(rotm,G4ThreeVector(0,0,0),ballLogical,"ballPhysical",worldLogical,false,0,checkOverlaps);
*/
  //tar
  G4VSolid* tarbox
    = new G4Box("tarbox",1.*mm,1.*mm,1.*um);
  tarLogical
    = new G4LogicalVolume(tarbox,pb,"tarLogical");
  ftar
    = new G4PVPlacement(rotm,G4ThreeVector(0,0,0),tarLogical,"tarPhysical",worldLogical,false,0,checkOverlaps);

//******************ppac*********************
  G4VSolid* lpbox = new G4Trd("lpbox",0.61*cm,4.7*cm,1.6*mm,1.6*mm,10.35*cm);
  lppacLogical = new G4LogicalVolume(lpbox,gas,"lppacLogical");
  G4double length = 12.8*cm;
  G4double zlen = length*cos(49*deg);
  G4double rlen = length*sin(49*deg);
  for(int i=0;i<10;i++){
    rotm = new G4RotationMatrix();
    rotm->rotateZ(36*deg*i);
    rotm->rotateX(49.*deg);
    new G4PVPlacement(rotm, G4ThreeVector(rlen*sin(36*i*deg),rlen*cos(36*i*deg),-zlen),lppacLogical,"lppacLogical",worldLogical,false,i,checkOverlaps);
  }
  
  G4VSolid* rpbox = new G4Trd("rpbox",4.7*cm,0.61*cm,1.6*mm,1.6*mm,10.35*cm);
  rppacLogical = new G4LogicalVolume(rpbox,gas,"rppacLogical");
  for(int i=0;i<10;i++){
    rotm = new G4RotationMatrix();
    rotm->rotateZ(36*deg*i);
    rotm->rotateX(-49.*deg);
    new G4PVPlacement(rotm, G4ThreeVector(rlen*sin(36*i*deg),rlen*cos(36*i*deg),zlen),rppacLogical,"rppacLogical",worldLogical,false,i+10,checkOverlaps);
  }

//**************ppac film*******************
  G4VSolid* lpfbox = new G4Trd("lpfbox",0.61*cm,4.7*cm,0.45*um,0.45*um,10.35*cm);
  lppacfLogical = new G4LogicalVolume(lpfbox,film,"lppacfLogical");
  rotm=new G4RotationMatrix();
  new G4PVPlacement(rotm,G4ThreeVector(0,-1.6*mm-0.45*um,0),lppacfLogical,"lppacfLogical",lppacLogical,false,0,checkOverlaps);

  
  G4VSolid* rpfbox = new G4Trd("rpfbox",4.7*cm,0.61*cm,0.45*um,0.45*um,10.35*cm);
  rppacfLogical = new G4LogicalVolume(rpfbox,film,"rppacfLogical");
  rotm=new G4RotationMatrix();
  new G4PVPlacement(rotm,G4ThreeVector(0,-1.6*mm-0.45*um,0),rppacfLogical,"rppacfLogical",rppacLogical,false,0,checkOverlaps);

//*************Aluminium support frame*************//
  rlen = rlen*12.6/12.8;
  zlen = zlen*12.6/12.8;
  G4VSolid* lpsbox = new G4Trd("lpsbox",0.157*cm,1.22*cm,1*mm,1*mm,10.35*cm);
  G4LogicalVolume* lpsLogical =
    new G4LogicalVolume(lpsbox,al,"lpsLogical");
  
  for(int i=0;i<10;i++){
    rotm = new G4RotationMatrix();
    G4double rotang = 36*deg*i+18*deg;
    rotm->rotateZ(rotang);
    rotm->rotateX(49.*deg);
    new G4PVPlacement(rotm, G4ThreeVector(rlen*sin(rotang),rlen*cos(rotang),-zlen),lpsLogical,"lpsLogical",worldLogical,false,i,checkOverlaps);
  }

  G4VSolid* rpsbox = new G4Trd("rpsbox",1.22*cm, 0.157*cm,1*mm,1*mm,10.35*cm);
  G4LogicalVolume* rpsLogical =
    new G4LogicalVolume(rpsbox,al,"rpsLogical");
  for(int i=0;i<10;i++){
    rotm = new G4RotationMatrix();
    G4double rotang = 36*deg*i+18*deg;
    rotm->rotateZ(rotang);
    rotm->rotateX(-49.*deg);
    new G4PVPlacement(rotm, G4ThreeVector(rlen*sin(rotang),rlen*cos(rotang),zlen),rpsLogical,"rpsLogical",worldLogical,false,i+10,checkOverlaps);
  }

//*****************************************************************//
  G4VisAttributes* visA = new G4VisAttributes(G4Color::Black());
  visA->SetVisibility(false);
  worldLogical->SetVisAttributes(visA);

  visA = new G4VisAttributes(G4Color::White());
  visA->SetVisibility(true);
  tarLogical->SetVisAttributes(visA);
  lpsLogical->SetVisAttributes(visA);
  rpsLogical->SetVisAttributes(visA);

  visA = new G4VisAttributes(G4Color::Green());
  visA->SetVisibility(true);
  lppacLogical->SetVisAttributes(visA);
  rppacLogical->SetVisAttributes(visA);

  visA = new G4VisAttributes(G4Color::Cyan());
  visA->SetVisibility(true);
  lppacfLogical->SetVisAttributes(visA);
  rppacfLogical->SetVisAttributes(visA);


//*********************************************************************//
    return worldPhysical;
}

void ExG4DetectorConstruction::ConstructMaterials()
{
  G4NistManager* nistManager = G4NistManager::Instance();

  si=nistManager->FindOrBuildMaterial("G4_Si");
  csi=nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
//  pb=nistManager->FindOrBuildMaterial("G4_Pb");
  al=nistManager->FindOrBuildMaterial("G4_Al");

  G4Isotope *Pb7 = new G4Isotope("Pb207",82,207,206.9758969*g/mole);
  G4Isotope *Pb8 = new G4Isotope("Pb208",82,208,207.9766521*g/mole);
  G4Element* Pb = new G4Element("Pb_iso","Pb",2);// name,symbol,components number
  Pb->AddIsotope(Pb8,51*perCent);
  Pb->AddIsotope(Pb7,49*perCent);
  pb = new G4Material("Lead",82,207.9766521*g/mole,11.344*g/cm3);

  // vacuum
  nistManager->FindOrBuildMaterial("G4_Galatic");

  // vacuum : air with low density
  G4Material* air = nistManager->FindOrBuildMaterial("G4_AIR");
  G4double density = 1.0e-5*air->GetDensity();
  vacuum = nistManager->BuildMaterialWithNewDensity("VACUUM","G4_AIR",density);

  G4double R_metha = 518.28; // unit: J/(kg*k)
  G4double pres_metha = 3 * 133.3224; // Unit pa 1 torr = 133.3224 par
  G4double temp = 15 + 273.15; // unit: kelvin
  //--------------
  //P=rho*R*T
  //--------------
  density = pres_metha/R_metha/temp*kg/m3;
  gas = nistManager->BuildMaterialWithNewDensity("chicogas","G4_METHANE",density);

  film = nistManager->FindOrBuildMaterial("G4_MYLAR");
  
}

void ExG4DetectorConstruction::ConstructSDandField()
{
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4String SDname;
  //______________________________________
  G4VSensitiveDetector* tar
   = new ExG4ppacSD(SDname="/tar");
  SDman->AddNewDetector(tar);
  tarLogical->SetSensitiveDetector(tar);

  G4VSensitiveDetector* lppac
   = new ExG4ppacSD(SDname="/lppac");
  SDman->AddNewDetector(lppac);
  lppacLogical->SetSensitiveDetector(lppac);

  G4VSensitiveDetector* rppac
   = new ExG4ppacSD(SDname="/rppac");
  SDman->AddNewDetector(rppac);
  rppacLogical->SetSensitiveDetector(rppac);

}
