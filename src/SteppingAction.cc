#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4PolarizationHelper.hh"

SteppingAction::SteppingAction(DetectorConstruction* det, 
	PrimaryGeneratorAction* prim, RunAction* ra, HistoManager* hist)
: detector(det), primary(prim), runAction(ra), histoManager(hist)
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
		StoreParticleData(aStep, 0);
	}

	/*
	if      (ParticlePassesZPlane(prePoint, endPoint, -3.4 *mm)) StoreParticleData(aStep, 1);
	else if (ParticlePassesZPlane(prePoint, endPoint, -3.2 *mm)) StoreParticleData(aStep, 2);
	else if (ParticlePassesZPlane(prePoint, endPoint, -3.0 *mm)) StoreParticleData(aStep, 3);
	else if (ParticlePassesZPlane(prePoint, endPoint, -1.0 *mm)) StoreParticleData(aStep, 4);
	else if (ParticlePassesZPlane(prePoint, endPoint,  1.0 *mm)) StoreParticleData(aStep, 5);
	else if (ParticlePassesZPlane(prePoint, endPoint,  3.0 *mm)) StoreParticleData(aStep, 6);
	else if (ParticlePassesZPlane(prePoint, endPoint,  3.2 *mm)) StoreParticleData(aStep, 7);
	else if (ParticlePassesZPlane(prePoint, endPoint,  3.4 *mm)) StoreParticleData(aStep, 8);
	else if (ParticlePassesZPlane(prePoint, endPoint,  3.44*mm)) StoreParticleData(aStep, 9);
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

void SteppingAction::StoreParticleData(const G4Step* aStep, G4int regionID)
{
	G4StepPoint* prePoint = aStep->GetPreStepPoint();
	G4StepPoint* endPoint = aStep->GetPostStepPoint();

	G4Track* aTrack = aStep->GetTrack();
	G4ParticleDefinition* particle = aTrack->GetDynamicParticle()->GetDefinition();

	G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	G4ThreeVector prePosition = prePoint->GetPosition();
	G4ThreeVector endPosition = endPoint->GetPosition();

	G4double kinEnergy = endPoint->GetKineticEnergy();

	G4ThreeVector beamDirectionVec = primary->GetParticleGun()->GetParticleMomentumDirection();
	G4ThreeVector directionVec     = endPoint->GetMomentumDirection();
	G4double costheta = directionVec * beamDirectionVec;

	G4double xDirection = directionVec * G4PolarizationHelper::GetParticleFrameX(beamDirectionVec);
	G4double yDirection = directionVec * G4PolarizationHelper::GetParticleFrameY(beamDirectionVec);
	G4double phi = std::atan2(yDirection, xDirection);

	G4double stepLength = aStep->GetStepLength();

	histoManager->FillData(particle, eventID, regionID, endPosition, stepLength, kinEnergy, costheta, phi);
}