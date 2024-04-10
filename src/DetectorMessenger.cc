#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "G4UserLimits.hh"
#include "G4UnitsTable.hh"

using namespace std;

DetectorMessenger::DetectorMessenger(DetectorConstruction* Detector)
: fDetector(Detector)
{
	eventDir = new G4UIdirectory("/RPCSim/maxStepLength/");
	eventDir ->SetGuidance("step control");

	worldMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/world", this);
	worldMaxStepLengthcmd->SetGuidance("Sets the max step length in the world");
	worldMaxStepLengthcmd->SetParameterName("length", false);
	worldMaxStepLengthcmd->SetRange("length>0");
	worldMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	polyethyleneMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/polyethylene", this);
	polyethyleneMaxStepLengthcmd->SetGuidance("Sets the max step length in the polyethylene material");
	polyethyleneMaxStepLengthcmd->SetParameterName("length", false);
	polyethyleneMaxStepLengthcmd->SetRange("length>0");
	polyethyleneMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	graphiteMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/graphite", this);
	graphiteMaxStepLengthcmd->SetGuidance("Sets the max step length in the graphite material");
	graphiteMaxStepLengthcmd->SetParameterName("length", false);
	graphiteMaxStepLengthcmd->SetRange("length>0");
	graphiteMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	bakeliteMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/bakelite", this);
	bakeliteMaxStepLengthcmd->SetGuidance("Sets the max step length in the bakelite material");
	bakeliteMaxStepLengthcmd->SetParameterName("length", false);
	bakeliteMaxStepLengthcmd->SetRange("length>0");
	bakeliteMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	gasMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/gas", this);
	gasMaxStepLengthcmd->SetGuidance("Sets the max step length in the gas material");
	gasMaxStepLengthcmd->SetParameterName("length", false);
	gasMaxStepLengthcmd->SetRange("length>0");
	gasMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	aluminiumMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/aluminium", this);
	aluminiumMaxStepLengthcmd->SetGuidance("Sets the max step length in the aluminium material");
	aluminiumMaxStepLengthcmd->SetParameterName("length", false);
	aluminiumMaxStepLengthcmd->SetRange("length>0");
	aluminiumMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

DetectorMessenger::~DetectorMessenger()
{
	delete worldMaxStepLengthcmd;
	delete bakeliteMaxStepLengthcmd;
	delete graphiteMaxStepLengthcmd;
	delete polyethyleneMaxStepLengthcmd;
	delete gasMaxStepLengthcmd;
	delete aluminiumMaxStepLengthcmd;
	
	delete eventDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if (command == worldMaxStepLengthcmd)
	{
		G4double maxStepLength = worldMaxStepLengthcmd->GetNewDoubleValue(newValue);
		fDetector->WorldUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the world        set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
	else if (command == polyethyleneMaxStepLengthcmd)
	{
		G4double maxStepLength = polyethyleneMaxStepLengthcmd->GetNewDoubleValue(newValue);
		fDetector->PolyethyleneUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the polyethylene set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
	else if (command == graphiteMaxStepLengthcmd)
	{
		G4double maxStepLength = graphiteMaxStepLengthcmd->GetNewDoubleValue(newValue);
		fDetector->GraphiteUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the graphite     set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
	else if (command == bakeliteMaxStepLengthcmd)
	{
		G4double maxStepLength = bakeliteMaxStepLengthcmd->GetNewDoubleValue(newValue);
		fDetector->BakeliteUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the bakelite     set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
	else if (command == gasMaxStepLengthcmd)
	{
		G4double maxStepLength = gasMaxStepLengthcmd->GetNewDoubleValue(newValue);
		fDetector->GasUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the gas          set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
	else if (command == aluminiumMaxStepLengthcmd)
	{
		G4double maxStepLength = aluminiumMaxStepLengthcmd->GetNewDoubleValue(newValue);
		fDetector->AluminiumUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the aluminium    set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
}