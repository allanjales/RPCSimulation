#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "G4UserLimits.hh"
#include "G4UnitsTable.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* Detector)
: fDetector(Detector)
{
	eventDir = new G4UIdirectory("/RPCSim/world/");
	eventDir ->SetGuidance("step control");

	PrintCmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/world/maxStepLength", this);
	PrintCmd->SetGuidance("Sets the max step length in the world");
	PrintCmd->SetParameterName("length", false);
	PrintCmd->SetRange("length>0");
	PrintCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

DetectorMessenger::~DetectorMessenger()
{
	delete PrintCmd;
	delete eventDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if (command == PrintCmd)
	{
		G4double maxStepLength = PrintCmd->GetNewDoubleValue(newValue);
        fDetector->UserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the world set to " << G4BestUnit(maxStepLength, "Length") << G4endl;
	}
}