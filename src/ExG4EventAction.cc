#include "ExG4EventAction.hh"
#include "ExG4Analysis.hh"
#include "ExG4ppacHit.hh"
#include "TreeManager.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "Randomize.hh"

#include <cmath>

ExG4EventAction::ExG4EventAction()
: G4UserEventAction(),
  ftarID(-1), lppacID(-1), rppacID(-1)

{
  G4RunManager::GetRunManager()->SetPrintProgress(1);
  ftm=TreeManager::GetTreeManager();
}

ExG4EventAction::~ExG4EventAction()
{}

void ExG4EventAction::BeginOfEventAction(const G4Event*)
{
  if(ftarID==-1||lppacID==-1||rppacID==-1)
  {
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    ftarID = sdManager->GetCollectionID("tar/ppacColl");
    lppacID = sdManager->GetCollectionID("lppac/ppacColl");
    rppacID = sdManager->GetCollectionID("rppac/ppacColl");
  }
}

void ExG4EventAction::EndOfEventAction(const G4Event* event)
{
  G4cout<<"****************End of EventAction !!!!!!!!!!!!!!!!!!!!!!!"<<G4endl;
//  G4double dssd1Reso=0.008/2.35;
  G4double dssd1Reso=0.01/2.35;

  G4HCofThisEvent* hce = event->GetHCofThisEvent();
  if(!hce)
  {
    G4ExceptionDescription msg;
    msg << "No hits collection of this event found. \n";
    G4Exception("ExG4EventAction::EndOfEventAction()","ExG4Cod001",JustWarning,msg);
    return;
  }

  //Get hits collections
  ExG4ppacHitsCollection* dtarHC
    = static_cast<ExG4ppacHitsCollection*>(hce->GetHC(ftarID));
  ExG4ppacHitsCollection* dlppacHC
    = static_cast<ExG4ppacHitsCollection*>(hce->GetHC(lppacID));
  ExG4ppacHitsCollection* drppacHC
    = static_cast<ExG4ppacHitsCollection*>(hce->GetHC(rppacID));


//  ftm->ResetAll();
  G4int n_hit=0;
  G4double Tel1_rot=0.*deg;
  //For u0w
  if(dtarHC) n_hit=dtarHC->entries();
  else n_hit=0;
  for(G4int i=0;i<n_hit;i++)
  {
    ExG4ppacHit* hit = (*dtarHC)[i];
    G4ThreeVector globalPos=hit->GetPos();
    //--------
    //If you need information about energy loss in target, modify below
  }

  
  //For lppac
  n_hit=0;
  if(dlppacHC) n_hit=dlppacHC->entries();
  else n_hit=0;
  for(G4int i=0;i<n_hit;i++)
  {
    ExG4ppacHit* hit = (*dlppacHC)[i];
    G4ThreeVector globalPos=hit->GetPos();
    G4double theta=globalPos.theta()/deg;
    G4double phi = globalPos.phi()/deg;
    G4int id = hit->GetId();
    if(ftm->id1==-1) {
      ftm->id1=id;
      ftm->dthe1=theta;
      ftm->dphi1=phi;
      ftm->dtof1=hit->GetTof();
      ftm->de1+=hit->GetE();
    } else if(ftm->id2==-1&& ftm->id1!=id){
      ftm->id2=id;
      ftm->dthe2=theta;
      ftm->dphi2=phi;
      ftm->dtof2=hit->GetTof();
      ftm->de2+=hit->GetE();
    } else if(ftm->id1==id){
      ftm->de1+=hit->GetE();
    } else if(ftm->id2==id){
      ftm->de2+=hit->GetE();
    }
  }

  //For rppac
  n_hit=0;
  if(drppacHC) n_hit=drppacHC->entries();
  else n_hit=0;
  for(G4int i=0;i<n_hit;i++)
  {
    ExG4ppacHit* hit = (*drppacHC)[i];
    G4ThreeVector globalPos=hit->GetPos();
    G4double theta=globalPos.theta()/deg;
    G4double phi = globalPos.phi()/deg;
    G4int id = hit->GetId();
    if(ftm->id1==-1) {
      ftm->id1=id;
      ftm->dthe1=theta;
      ftm->dphi1=phi;
      ftm->dtof1=hit->GetTof();
      ftm->de1+=hit->GetE();
      ftm->dx1=globalPos.x();
      ftm->dy1=globalPos.y();
      ftm->dz1=globalPos.z();
      ftm->dl1=globalPos.mag();
    } else if(ftm->id2==-1&& ftm->id1!=id){
      ftm->id2=id;
      ftm->dthe2=theta;
      ftm->dphi2=phi;
      ftm->dtof2=hit->GetTof();
      ftm->de2+=hit->GetE();
      ftm->dx2=globalPos.x();
      ftm->dy2=globalPos.y();
      ftm->dz2=globalPos.z();
      ftm->dl2=globalPos.mag();
    } else if(ftm->id1==id){
      ftm->de1+=hit->GetE();
    } else if(ftm->id2==id){
      ftm->de2+=hit->GetE();
    }
  }
  if (ftm->dthe1>-999) ftm->dthe1r=G4RandGauss::shoot(ftm->dthe1,1.6/2.355);
  if (ftm->dthe2>-999) ftm->dthe2r=G4RandGauss::shoot(ftm->dthe2,1.6/2.355);
  if (ftm->dphi1>-999) ftm->dphi1r=G4RandGauss::shoot(ftm->dphi1,2.5/2.355);
  if (ftm->dphi2>-999) ftm->dphi2r=G4RandGauss::shoot(ftm->dphi2,2.5/2.355);
  
//*******************************************************//
  ftm->FillTree();

}
