#include "EventAction.hh"

EventAction::EventAction()
: printModule(1000)
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
