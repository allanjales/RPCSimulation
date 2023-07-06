#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4PolarizationHelper.hh"

SteppingAction::SteppingAction(DetectorConstruction* det, 
	PrimaryGeneratorAction* prim, RunAction* RuAct, HistoManager* Hist)
: detector(det), primary(prim), runAction(RuAct), histoManager(Hist)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
	G4StepPoint* endPoint = aStep->GetPostStepPoint();

	G4String procName = endPoint->GetProcessDefinedStep()->GetProcessName();
	runAction->CountProcesses(procName);
}