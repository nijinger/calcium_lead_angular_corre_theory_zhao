#include "ExG4PrimaryGeneratorAction.hh"
#include "ParticleDefinition.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
//#include "TF1.h"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "TreeManager.hh"
#include <cstdio>


ExG4PrimaryGeneratorAction::ExG4PrimaryGeneratorAction(
            const G4String& particleName,
            G4double energy,
            G4ThreeVector position,
            G4ThreeVector momentumDirection)
      :  G4VUserPrimaryGeneratorAction(),
         fParticleGun(0)
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);
//  pfile = fopen("CaPb-Newdata.DAT","r");
//  pfile = fopen("CaPb-0213-PM.DAT","r");
//  pfile = fopen("CaPb-0215.DAT","r");
//  pfile = fopen("Ca+Pb.DAT","r");
//  pfile = fopen("Sys130260036119+084.DAT","r");
//  pfile = fopen("SECOND-DECAY.DAT","r");
//  pfile = fopen("Sys160230036119+084.DAT","r");
  pfile = fopen("Sys160230032055-100.DAT","r");
  if(pfile==NULL){
    G4cout<<"cannot open particle data file!"<<G4endl;
    exit(1);
  }
}

ExG4PrimaryGeneratorAction::~ExG4PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void ExG4PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
  static int cnt=-1;
  cnt++;
  TreeManager *ftm= TreeManager::GetTreeManager();
  ftm->ResetAll();
  G4cout<<" **************!!!!!!!!!!!!!!!!!!!!!!!******************"<<G4endl;
  
  G4ParticleDefinition* particle; 
  G4ThreeVector position(0,0,0);


//  int ret=fscanf(pfile,"%i %i %lf %lf %i %i %lf %lf %lf\n",&(ftm->z1),&(ftm->a1),&(ftm->e1),&(ftm->the1),&(ftm->z2),&(ftm->a2),&(ftm->e2),&(ftm->the2));
  int ret=fscanf(pfile,"%i %i %i %i %i %lf %lf %i %i %lf %lf %lf %lf %lf\n",&(ftm->index[0]),&(ftm->index[1]),&(ftm->index[2]),&(ftm->z1),&(ftm->a1),&(ftm->the1),&(ftm->e1),&(ftm->z2),&(ftm->a2),&(ftm->the2),&(ftm->e2),&(ftm->exE1),&(ftm->exE2),&(ftm->cross));
//  int ret=fscanf(pfile,"%i %i %lf %lf %i %i %lf %lf %lf\n",&(ftm->z1),&(ftm->a1),&(ftm->the1),&(ftm->e1),&(ftm->z2),&(ftm->a2),&(ftm->the2),&(ftm->e2),&(ftm->cross));
//  int ret=fscanf(pfile,"%i %i %lf %lf %i %i %lf %lf %lf \n",&(ftm->z1),&(ftm->a1),&(ftm->the1),&(ftm->e1), &(ftm->z2),&(ftm->a2),&(ftm->the2),&(ftm->e2),&(ftm->cross));
  if(ret==EOF) return;
  else if(ret!=8&&ret!=9&&ret!=14&&ret!=7) return;
  if(ftm->z1==0||ftm->z2==0) return;
  ftm->e1=ftm->e1*MeV;
  ftm->e2=ftm->e2*MeV;
  ftm->the1=ftm->the1*deg;
  ftm->the2=ftm->the2*deg;
//  G4double phi = G4UniformRand()*360*deg;
  G4double phi = 5*deg;

  G4double ioncharge = ftm->z1*CLHEP::eplus;
  particle = G4IonTable::GetIonTable()->GetIon(ftm->z1,ftm->a1,0); 
  if(particle==0) G4cout<<"cannot find element Z A: "<<ftm->z1<<" "<<ftm->a1<<G4endl;
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(ftm->e1);
  fParticleGun->SetParticlePosition(position);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sin(ftm->the1)*cos(phi),sin(ftm->the1)*sin(phi),cos(ftm->the1)));
  fParticleGun->SetParticleCharge(ioncharge);
  fParticleGun->GeneratePrimaryVertex(anEvent);
      
  phi=phi+180*deg;
  ioncharge = ftm->z2*CLHEP::eplus;
  particle = G4IonTable::GetIonTable()->GetIon(ftm->z2,ftm->a2,0); 
  if(particle==0) G4cout<<"cannot find element Z A: "<<ftm->z2<<" "<<ftm->a2<<G4endl;
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(ftm->e2);
  fParticleGun->SetParticlePosition(position);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sin(ftm->the2)*cos(phi),sin(ftm->the2)*sin(phi),cos(ftm->the2)));
  fParticleGun->SetParticleCharge(ioncharge);
  fParticleGun->GeneratePrimaryVertex(anEvent);

}
