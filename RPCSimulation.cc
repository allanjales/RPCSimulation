#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "Randomize.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "HistoManager.hh"

int main(int argc,char** argv)
{
	G4RunManager *runManager = new G4RunManager;

	DetectorConstruction* det = new DetectorConstruction();

	runManager->SetUserInitialization(det);
	runManager->SetUserInitialization(new PhysicsList());
	
	PrimaryGeneratorAction* prim  = new PrimaryGeneratorAction();
	HistoManager*           histo = new HistoManager();
	RunAction*              run   = new RunAction(det, prim, histo);
	runManager->SetUserAction(prim);
	runManager->SetUserAction(run);
	runManager->SetUserAction(new EventAction(run));
	runManager->SetUserAction(new SteppingAction(det, prim, run, histo));

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
	if (argc == 1)
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

	// Job termination
	delete runManager;
	if (ui) delete ui;
	if (visManager) delete visManager;

	return 0;
}
