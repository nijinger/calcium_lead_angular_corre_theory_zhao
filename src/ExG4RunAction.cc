#include "ExG4RunAction.hh"
#include "ExG4Analysis.hh"
#include "TreeManager.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

ExG4RunAction::ExG4RunAction()
: G4UserRunAction()
{
 
  fTreeM=TreeManager::GetTreeManager();

//  analysisManager->CreateNtupleDColumn("OAngle");    //colume ID = 28
//  analysisManager->CreateNtupleDColumn("CAngle");    //colume ID = 29
//  analysisManager->CreateNtupleDColumn("dssd1t");    //colume ID = 14
}

ExG4RunAction::~ExG4RunAction()
{
  delete G4AnalysisManager::Instance();
}

void ExG4RunAction::BeginOfRunAction(const G4Run*)
{
  fTreeM->book("tele.root");
}

void ExG4RunAction::EndOfRunAction(const G4Run*)
{
  fTreeM->save();
}
