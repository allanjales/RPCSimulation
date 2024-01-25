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
	DetectorConstruction* det;
	PrimaryGeneratorAction* prim;
	RunAction* run;

	HistoManager* histo = new HistoManager();

	G4RunManager *runManager = new G4RunManager;

	runManager->SetUserInitialization(det = new DetectorConstruction());
	runManager->SetUserInitialization(new PhysicsList());
	
	runManager->SetUserAction(prim = new PrimaryGeneratorAction());
	runManager->SetUserAction(run = new RunAction(det, prim, histo));
	runManager->SetUserAction(new EventAction(run));
	runManager->SetUserAction(new SteppingAction(det, prim, run, histo));

	G4UIExecutive* ui = 0;

	//If there is no argument, creates a interface
	if (argc == 1)
		ui = new G4UIExecutive(argc, argv);

	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();

	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	if (argc==1)
	// Define UI terminal for interactive mode
	{
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
	}
	else
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}

	// Job termination
	if (visManager)
		delete visManager;
	delete histo;
	delete runManager;

	return 0;
}
