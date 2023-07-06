#include "StepMaxMessenger.hh"

#include "StepMax.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

StepMaxMessenger::StepMaxMessenger(StepMax* stepM)
: pStepMax(stepM)
{
	StepMaxCmd = new G4UIcmdWithADoubleAndUnit("/testem/stepMax",this);
	StepMaxCmd->SetGuidance("Set max allowed step length");
	StepMaxCmd->SetParameterName("mxStep",false);
	StepMaxCmd->SetRange("mxStep>0.");
	StepMaxCmd->SetUnitCategory("Length");
}

StepMaxMessenger::~StepMaxMessenger()
{
	delete StepMaxCmd;
}

void StepMaxMessenger::SetNewValue(G4UIcommand* command,
	G4String newValue)
{
	if (command == StepMaxCmd)
		pStepMax->SetMaxStep(StepMaxCmd->GetNewDoubleValue(newValue));
}