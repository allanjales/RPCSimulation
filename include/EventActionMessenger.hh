#ifndef EventActionMessenger_hh
#define EventActionMessenger_hh

#include "G4UImessenger.hh"
#include "globals.hh"

class EventAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

class EventActionMessenger: public G4UImessenger
{
public:
	EventActionMessenger(EventAction*);
	~EventActionMessenger();

	void SetNewValue(G4UIcommand*, G4String);

private:
	EventAction*          eventAction;

	G4UIdirectory*        eventDir;
	G4UIcmdWithAnInteger* PrintCmd;
};

#endif