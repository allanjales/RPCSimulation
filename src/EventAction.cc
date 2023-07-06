#include "EventAction.hh"

#include "EventActionMessenger.hh"

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"

#include "G4Trajectory.hh"
#include "G4VVisManager.hh"

#include "G4UnitsTable.hh"
#include "RunAction.hh"

EventAction::EventAction(RunAction* ra)
: printModule(10000), eventMessenger(0), runAction(ra)
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
		G4cout << "\n---> Begin of Event: " << eventNumber << G4endl;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
	if (runAction)
		runAction->EventFinished();

	if  (G4VVisManager::GetConcreteInstance())
	{
		G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
		G4int trajectoriesNumber = 0;

		if (trajectoryContainer) trajectoriesNumber = trajectoryContainer->entries();
		{
			for (G4int i = 0; i < trajectoriesNumber; i++)
			{
				G4Trajectory* trajectory = (G4Trajectory*)((*(event->GetTrajectoryContainer()))[i]);
				trajectory->DrawTrajectory(); //Na referência, tem 1000 de argumento (?)
			}
		}
	}
}

