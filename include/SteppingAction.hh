#ifndef SteppingAction_hh
#define SteppingAction_hh

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <G4StepPoint.hh>
#include <G4Track.hh>

class DetectorConstruction;
class PrimaryGeneratorAction;
class RunAction;
class HistoManager;

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(DetectorConstruction*, PrimaryGeneratorAction*, RunAction*, HistoManager*);
	~SteppingAction();
	void UserSteppingAction(const G4Step*);

	bool ParticlePassesZPlane(G4Track* track, G4double zPlane);
	bool ParticlePassesZPlane(G4StepPoint* prePoint, G4StepPoint* endPoint, G4double zPlane);
	void StoreParticleData(const G4Step* aStep, G4int regionID);

private:
	DetectorConstruction* detector;
	PrimaryGeneratorAction* primary;
	RunAction* runAction;
	HistoManager* histoManager;
};

#endif