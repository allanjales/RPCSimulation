#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
	SetUserAction(new RunAction);
}

void ActionInitialization::Build() const
{
	SetUserAction(new PrimaryGeneratorAction);
	SetUserAction(new RunAction);
	SetUserAction(new EventAction);
}