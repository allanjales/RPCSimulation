#ifndef ActionInitialization_hh
#define ActionInitialization_hh

#include <G4VUserActionInitialization.hh>

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
	ActionInitialization(DetectorConstruction*);;
	~ActionInitialization();

	virtual void Build() const;
	virtual void BuildForMaster() const;
private:
	DetectorConstruction* detector;
	PrimaryGeneratorAction* primary;
};

#endif