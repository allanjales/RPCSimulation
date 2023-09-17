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
	G4StepPoint* prePoint = aStep->GetPreStepPoint();
	G4StepPoint* endPoint = aStep->GetPostStepPoint();

	G4String procName = endPoint->GetProcessDefinedStep()->GetProcessName();
	runAction->CountProcesses(procName);

	// Left the gas box
	if (prePoint->GetTouchableHandle()->GetVolume() == detector->GetGasRPC())
	{
		G4Track* aTrack = aStep->GetTrack();
		G4String particleName = aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName();
	
		G4ThreeVector position = endPoint->GetPosition();
		G4double positionX = prePoint->GetPosition().x();
		G4double positionY = prePoint->GetPosition().y();

		G4ThreeVector direction = endPoint->GetMomentumDirection();
		G4double kinEnergy = prePoint->GetKineticEnergy();

		G4ThreeVector beamDirection = primary->GetParticleGun()->GetParticleMomentumDirection();
		G4double polZ = endPoint->GetPolarization().z();

		G4double costheta = direction * beamDirection;

		G4double xdir = direction * G4PolarizationHelper::GetParticleFrameX(beamDirection);
		G4double ydir = direction * G4PolarizationHelper::GetParticleFrameY(beamDirection);

		G4double phi = std::atan2(ydir, xdir);

		histoManager->FillHistos(particleName, kinEnergy, costheta, phi, polZ, positionX, positionY);
	}
}