#include "EventAction.hh"

#include "EventActionMessenger.hh"

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"

#include "G4Trajectory.hh"
#include "G4VVisManager.hh"

#include "G4UnitsTable.hh"
#include "RunAction.hh"

EventAction::EventAction(RunAction* ra)
: printModule(1000), eventMessenger(0), runAction(ra)
{
	eventMessenger = new EventActionMessenger(this);
}

EventAction::~EventAction()
{
	delete eventMessenger;
}

void EventAction::BeginOfEventAction(const G4Event* event)
{
	G4int eventNumber = event->GetEventID();	

	if (eventNumber % printModule == 0)
		G4cout << "-> Begin of Event: " << eventNumber << G4endl;
}

void EventAction::EndOfEventAction(const G4Event* event)
{}
