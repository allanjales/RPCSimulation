#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4PolarizationHelper.hh"

SteppingAction::SteppingAction(DetectorConstruction* det, 
	PrimaryGeneratorAction* prim, RunAction* ra)
: detector(det), primary(prim), runAction(ra)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
	/*
	G4StepPoint* prePoint = aStep->GetPreStepPoint();
	G4StepPoint* endPoint = aStep->GetPostStepPoint();

	// Is in the gas box
	if (prePoint->GetTouchableHandle()->GetVolume() == detector->GetGasRPC() 
	&& endPoint->GetTouchableHandle()->GetVolume() == detector->GetGasRPC())
	{
		StoreParticleData(aStep, 0);
	}
	*/

	/*
	if (ParticlePassesZPlane(prePoint, endPoint, -3.4 )) StoreParticleData(aStep, 1);
	if (ParticlePassesZPlane(prePoint, endPoint, -3.2 )) StoreParticleData(aStep, 2);
	if (ParticlePassesZPlane(prePoint, endPoint, -3.0 )) StoreParticleData(aStep, 3);
	if (ParticlePassesZPlane(prePoint, endPoint, -1.0 )) StoreParticleData(aStep, 4);
	if (ParticlePassesZPlane(prePoint, endPoint,  1.0 )) StoreParticleData(aStep, 5);
	if (ParticlePassesZPlane(prePoint, endPoint,  3.0 )) StoreParticleData(aStep, 6);
	if (ParticlePassesZPlane(prePoint, endPoint,  3.2 )) StoreParticleData(aStep, 7);
	if (ParticlePassesZPlane(prePoint, endPoint,  3.4 )) StoreParticleData(aStep, 8);
	if (ParticlePassesZPlane(prePoint, endPoint,  3.44)) StoreParticleData(aStep, 9);
	*/
}

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