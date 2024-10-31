#include "EventAction.hh"

EventAction::EventAction()
: printModule(1000)
{
	eventMessenger = new EventActionMessenger(this);

	Digitizer* digitizer = new Digitizer("SiDigitizer");
	G4DigiManager* digiManager = G4DigiManager::GetDMpointer();
	digiManager->AddNewModule(digitizer);
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

void EventAction::EndOfEventAction(const G4Event*)
{
	G4DigiManager * digiManager = G4DigiManager::GetDMpointer();
	Digitizer* digiModule = static_cast<Digitizer*>(digiManager->FindDigitizerModule("Digitizer"));
	digiModule->Digitize();
}
