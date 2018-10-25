#include "ExG4DetectorConstruction.hh"
#include "ExG4PhysicsList.hh"
#include "TreeManager.hh"
#include "ExG4ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"


#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "Randomize.hh"

int main(int argc,char** argv)
{

  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // construct the default run manager

//#ifdef G4MULTITHREADED
//  G4MTRunManager* runManager = new G4MTRunManager;
//  runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
//#else
  G4RunManager* runManager = new G4RunManager;
//#endif
 

  // set mandatory initialization classes
  runManager->SetUserInitialization(new ExG4DetectorConstruction);
  runManager->SetUserInitialization(new ExG4PhysicsList);

//  TreeManager *tm=new TreeManager();
  runManager->SetUserInitialization(new ExG4ActionInitialization);

  // initialize G4 kernel
  runManager->Initialize();

#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();
  if(argc==1)
  {
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc,argv);
#ifdef G4VIS_USE
    UI->ApplyCommand("/control/execute init_vis.mac");
#else
    UI->ApplyCommand("/run/verbose 1");
    UI->ApplyCommand("/event/verbose 1");
    UI->ApplyCommand("/tracking/verbose 1");
#endif
    ui->SessionStart();
    delete ui;
#endif
  }
  else
  {
    //batch mode
    G4String command="/control/execute ";
    G4String fileName=argv[1];
    UI->ApplyCommand(command+fileName);
  }

  // start a run
//  int numberOfEvent = 3;
//  runManager->BeamOn(numberOfEvent);

  // job termination
#ifdef G4VIS_USE
  delete visManager;
#endif

  delete runManager;
  return 0;
}
