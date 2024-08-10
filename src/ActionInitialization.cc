#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* detector)
: detector(detector)
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
	RunAction *runAction = new RunAction(detector, primary);
	SetUserAction(runAction);
}

void ActionInitialization::Build() const
{
	PrimaryGeneratorAction* primary = new PrimaryGeneratorAction();
	SetUserAction(primary);

	RunAction* runAction = new RunAction(detector, primary);
	SetUserAction(runAction);

	SetUserAction(new EventAction(runAction));
	SetUserAction(new SteppingAction(detector, primary, runAction));
}