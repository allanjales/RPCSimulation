#ifndef EventAction_hh
#define EventAction_hh

#include <G4UserEventAction.hh>
#include <globals.hh>

#include <G4Event.hh>
#include "EventActionMessenger.hh"
#include "Digitizer.hh"

class EventAction : public G4UserEventAction
{
public:
	EventAction();
	~EventAction() override;

	void BeginOfEventAction(const G4Event* event) override;
	void EndOfEventAction(const G4Event* event) override;

	void SetPrintModulo(G4int val) {printModulo = val;}

private:
	G4int                 printModulo;
	EventActionMessenger* eventMessenger;
};

#endif