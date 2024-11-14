#ifndef RunAction_hh
#define RunAction_hh

#include <G4UserRunAction.hh>

#include "SensitiveDetector.hh"
#include <G4RunManager.hh>
#include <G4Run.hh>
#include <Randomize.hh>
#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>
#include <filesystem>

class RunAction : public G4UserRunAction
{
	public:
		RunAction();
		virtual ~RunAction();
		
		void BeginOfRunAction(const G4Run*);
		void EndOfRunAction(const G4Run*);
		
	private:
		int runStartedTime;

		/// @brief Open the output file and create the ntuple
		void Book();
	};

#endif