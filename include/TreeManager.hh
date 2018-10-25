#ifndef TreeManager_h
#define TreeManager_h

#include "globals.hh"
#include <TROOT.h>

class TFile;
class TTree;
class TH1D;

class TreeManager
{
public:
//  TreeManager();
  TreeManager(G4bool isMaster=true);
  ~TreeManager();

  static TreeManager* GetTreeManager();

  bool book(const char *filename="ExG4.root");
  void save();

  void ResetAll();

  void FillTree();

  Int_t z1,a1,z2,a2;
  Double_t e1,e2,the1,the2;
  
  Double_t de1,de2,dthe1,dthe2,exE1,exE2;
  Double_t dtof1,dtof2;
  Double_t dx1,dx2,dy1,dy2;
  Double_t dl1,dl2,dz1,dz2;
  Int_t id1,id2;
  Double_t dphi1,dphi2;
  Double_t dthe1r,dthe2r,dphi1r,dphi2r;
  Double_t cross;

  Int_t index[3];

private:

  static TreeManager* fMasterInstance;
  static G4ThreadLocal TreeManager* fInstance;
  TFile *fRootFile;
  TTree *tree;

  // data members
};

#endif
