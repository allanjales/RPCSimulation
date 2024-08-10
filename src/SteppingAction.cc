#include "SteppingAction.hh"

SteppingAction::SteppingAction(DetectorConstruction* det, 
	PrimaryGeneratorAction* prim, RunAction* ra)
: detector(det), primary(prim), runAction(ra)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{}

bool SteppingAction::ParticlePassesZPlane(G4Track* track, G4double zPlane)
{
	G4StepPoint* prePoint = track->GetStep()->GetPreStepPoint();
	G4StepPoint* endPoint = track->GetStep()->GetPostStepPoint();

	return ParticlePassesZPlane(prePoint, endPoint, zPlane);
}

bool SteppingAction::ParticlePassesZPlane(G4StepPoint* prePoint, G4StepPoint* endPoint, G4double zPlane)
{
	G4double preZ = prePoint->GetPosition().z();
	G4double endZ = endPoint->GetPosition().z();

	//return (preZ < zPlane && endZ > zPlane) || (preZ > zPlane && endZ < zPlane);
	return (preZ - zPlane) * (endZ - zPlane) < 0;
}