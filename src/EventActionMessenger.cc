#include "EventActionMessenger.hh"

#include "EventAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

EventActionMessenger::EventActionMessenger(EventAction* EventAction)
: eventAction(EventAction)
{
	eventDir = new G4UIdirectory("/RPCSim/event/");
	eventDir ->SetGuidance("event control");

	PrintCmd = new G4UIcmdWithAnInteger("/RPCSim/event/printModule", this);
	PrintCmd->SetGuidance("Sets the event printing frequency");
	PrintCmd->SetParameterName("EventNumber", false);
	PrintCmd->SetRange("EventNumber>0");
	PrintCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

EventActionMessenger::~EventActionMessenger()
{
	delete PrintCmd;
	delete eventDir;
}

void EventActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if (command == PrintCmd)
	{
		G4int printModule = PrintCmd->GetNewIntValue(newValue);
		eventAction->SetPrintModule(printModule);
		G4cout << "Print module set to " << printModule << G4endl;
	}
}