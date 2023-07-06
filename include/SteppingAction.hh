#ifndef SteppingAction_hh
#define SteppingAction_hh

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DetectorConstruction;
class PrimaryGeneratorAction;
class RunAction;
class HistoManager;

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(DetectorConstruction*, PrimaryGeneratorAction*, RunAction*,
			HistoManager*);
	~SteppingAction();

	void UserSteppingAction(const G4Step*);

private:
	DetectorConstruction* detector;
	PrimaryGeneratorAction* primary;
	RunAction* runAction;
	HistoManager* histoManager;
};

#endif