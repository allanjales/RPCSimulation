#ifndef RunAction_hh
#define RunAction_hh

#include "G4UserRunAction.hh"
#include "globals.hh"

class DetectorConstruction;
class PrimaryGeneratorAction;
class HistoManager;
class G4Run;

class RunAction : public G4UserRunAction
{
	public:
		RunAction(DetectorConstruction*, PrimaryGeneratorAction*, HistoManager*);
		virtual ~RunAction();
	
	public:
		void BeginOfRunAction(const G4Run*);
		void EndOfRunAction(const G4Run*);
	private:
		DetectorConstruction* detector;
		PrimaryGeneratorAction* primary;
		HistoManager* histoManager;
	};

#endif