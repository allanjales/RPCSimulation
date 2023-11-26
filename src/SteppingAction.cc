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

	// Is in the gas box
	if (prePoint->GetTouchableHandle()->GetVolume() == detector->GetGasRPC() 
	&& endPoint->GetTouchableHandle()->GetVolume() == detector->GetGasRPC())
	{
		G4Track* aTrack = aStep->GetTrack();
		G4ParticleDefinition* particle = aTrack->GetDynamicParticle()->GetDefinition();
	
		G4ThreeVector prePosition = prePoint->GetPosition();
		G4ThreeVector endPosition = endPoint->GetPosition();

		G4double kinEnergy = endPoint->GetKineticEnergy();

		G4ThreeVector beamDirectionVec = primary->GetParticleGun()->GetParticleMomentumDirection();
		G4ThreeVector directionVec     = endPoint->GetMomentumDirection();
		G4double costheta = directionVec * beamDirectionVec;

		G4double xDirection = directionVec * G4PolarizationHelper::GetParticleFrameX(beamDirectionVec);
		G4double yDirection = directionVec * G4PolarizationHelper::GetParticleFrameY(beamDirectionVec);
		G4double phi = std::atan2(yDirection, xDirection);

		G4ThreeVector polarization = endPoint->GetPolarization();

		histoManager->FillData(particle, prePosition, kinEnergy, costheta, phi, polarization);
	}
}