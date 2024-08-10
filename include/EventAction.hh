#ifndef EventAction_hh
#define EventAction_hh

#include <G4UserEventAction.hh>
#include <globals.hh>
#include "RunAction.hh"

#include <G4Event.hh>
#include "EventActionMessenger.hh"

class EventAction : public G4UserEventAction
{
public:
	EventAction(RunAction* runAction);
	~EventAction() override;

	void BeginOfEventAction(const G4Event* event) override;
	void EndOfEventAction(const G4Event* event) override;

	void SetPrintModule(G4int val) {printModule = val;}

private:
	G4int                 printModule;
	EventActionMessenger* eventMessenger;
	RunAction*            runAction;
};

#endif