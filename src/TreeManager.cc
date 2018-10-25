#include "TreeManager.hh"

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <G4Threading.hh>
#include <stdio.h>

TreeManager* TreeManager::fMasterInstance=0;
G4ThreadLocal TreeManager* TreeManager::fInstance=0;

TreeManager* TreeManager::GetTreeManager()
{
  if( fInstance==0) 
  {
    G4bool isMaster = ! G4Threading::IsWorkerThread();
    fInstance = new TreeManager(isMaster);
  }
  return fInstance;
}

//TreeManager::TreeManager()
//: fRootFile(0), tree(0)
//{
//  ResetAll();
//}

TreeManager::TreeManager(G4bool isMaster)
: fRootFile(0), tree(0)
{
  if(isMaster) fMasterInstance = this;
  fInstance=this;
  ResetAll();
}

TreeManager::~TreeManager()
{
  if(fRootFile) fRootFile->Close();
}

bool TreeManager::book(const char *filename)
{
  fRootFile = new TFile(filename,"recreate");
  if(!fRootFile) {
    G4cout<<" TreeManager::book :"
    << " cannot create the ROOT TFile"
    <<G4endl;
    return false;
  }

  tree= new TTree("tree","tree");

  if(!tree) 
  {
    G4cout<<" Cannot Create the tree"<<G4endl;
    return false;
  }

  tree->Branch("z1",&z1,"z1/I");
  tree->Branch("a1",&a1,"a1/I");
  tree->Branch("z2",&z2,"z2/I");
  tree->Branch("a2",&a2,"a2/I");
  tree->Branch("e1",&e1,"e1/D");
  tree->Branch("e2",&e2,"e2/D");
  tree->Branch("exE1",&exE1,"exE1/D");
  tree->Branch("exE2",&exE2,"exE2/D");
  tree->Branch("the1",&the1,"the1/D");
  tree->Branch("the2",&the2,"the2/D");
  tree->Branch("de1",&de1,"de1/D");
  tree->Branch("de2",&de2,"de2/D");
  tree->Branch("dthe1",&dthe1,"dthe1/D");
  tree->Branch("dthe2",&dthe2,"dthe2/D");
  tree->Branch("dphi1",&dphi1,"dphi1/D");
  tree->Branch("dphi2",&dphi2,"dphi2/D");
  tree->Branch("dthe1r",&dthe1r,"dthe1r/D");
  tree->Branch("dthe2r",&dthe2r,"dthe2r/D");
  tree->Branch("dphi1r",&dphi1r,"dphi1r/D");
  tree->Branch("dphi2r",&dphi2r,"dphi2r/D");
  tree->Branch("dtof1",&dtof1,"dtof1/D");
  tree->Branch("dtof2",&dtof2,"dtof2/D");
  tree->Branch("dx1",&dx1,"dx1/D");
  tree->Branch("dx2",&dx2,"dx2/D");
  tree->Branch("dy1",&dy1,"dy1/D");
  tree->Branch("dy2",&dy2,"dy2/D");
  tree->Branch("dz1",&dz1,"dz1/D");
  tree->Branch("dz2",&dz2,"dz2/D");
  tree->Branch("dl1",&dl1,"dl1/D");
  tree->Branch("dl2",&dl2,"dl2/D");
  tree->Branch("id1",&id1,"id1/I");
  tree->Branch("id2",&id2,"id2/I");
  tree->Branch("cross",&cross,"cross/D");
  tree->Branch("index",&index,"index[3]/I");
  
  return true;
}

void TreeManager::ResetAll()
{
  z1=-1;
  a1=-1;
  z2=-1;
  a2=-1;
  e1=0;e2=0;
  the1=-999;the2=-999;
  de1=0;de2=0;
  exE1=0;exE2=0;
  dthe1=-999;dthe2=-999;
  dtof1=-999;dtof2=-999;
  id1=-1;id2=-1;
  dphi1=-999;dphi2=-999;
  dx1=dx2=dy1=dy2=-1;
  dz1=dz2=dl1=dl2=-1;
  dthe1r=dthe2r=dphi1r=dphi2r=-999;
  cross=0;
}

void TreeManager::FillTree()
{
  fRootFile->cd();
  tree->Fill();
}

void TreeManager::save()
{
  fRootFile->cd();
  tree->Write();
}
