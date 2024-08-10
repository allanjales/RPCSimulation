#ifndef RunAction_hh
#define RunAction_hh

#include <G4UserRunAction.hh>
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DataHandler.hh"

#include "SensitiveDetector.hh"
#include <G4RunManager.hh>
#include <G4Run.hh>
#include <Randomize.hh>
#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>

class RunAction : public G4UserRunAction
{
	public:
		RunAction(DetectorConstruction*, PrimaryGeneratorAction*);
		virtual ~RunAction();
		
		void BeginOfRunAction(const G4Run*);
		void EndOfRunAction(const G4Run*);
		
	private:
		DetectorConstruction* detector;
		PrimaryGeneratorAction* primary;
		DataHandler* dataHandler;

		int runStartedTime;
	};

#endif