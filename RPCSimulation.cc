#include <G4RunManager.hh>
#include <G4MTRunManager.hh>
#include <G4UImanager.hh>
#include <G4VisManager.hh>
#include <G4UIExecutive.hh>	
#include <G4VisExecutive.hh>	

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "DataHandler.hh"

int main(int argc,char** argv)
{
	// #ifdef G4MULTITHREADED
	// 	G4MTRunManager *runManager = new G4MTRunManager();
	// 	runManager->SetNumberOfThreads(12);
	// #else
	// 	G4RunManager *runManager = new G4RunManager();
	// #endif

	G4RunManager *runManager = new G4RunManager();

	DetectorConstruction* detector = new DetectorConstruction();

	runManager->SetUserInitialization(detector);
	runManager->SetUserInitialization(new PhysicsList());
	runManager->SetUserInitialization(new ActionInitialization(detector));

	//If there is no argument, creates a interface
	G4UIExecutive* ui = NULL;
	G4VisManager *visManager = NULL;
	if (argc == 1)
	{
		ui         = new G4UIExecutive(argc, argv);
		visManager = new G4VisExecutive();
		visManager->Initialize();
	}

	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	if (ui)
	{
		// Define UI terminal for interactive mode
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
	}
	else
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);
	}

	UImanager->ApplyCommand("/run/verbose 2");
	UImanager->ApplyCommand("/event/verbose 2");
	UImanager->ApplyCommand("/tracking/verbose 2");

	// Job termination
	delete runManager;
	if (ui) delete ui;
	if (visManager) delete visManager;

	return 0;
}
