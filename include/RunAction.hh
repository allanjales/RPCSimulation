#ifndef RunAction_hh
#define RunAction_hh

#include "G4UserRunAction.hh"
#include "ProcessesCount.hh"
#include "globals.hh"

class DetectorConstruction;
class PrimaryGeneratorAction;
class HistoManager;
class G4Run;

class RunAction : public G4UserRunAction
{
	class ParticleStatistics
	{
	public:
		ParticleStatistics();
		~ParticleStatistics();
		void EventFinished();
		void FillData(G4double kinEnergy, G4double costheta,
			G4double longitudinalPolarization);
		void PrintResults(G4int totalNumberOfEvents);
		void Clear();

	private:
		G4int currentNumber;
		G4int totalNumber, totalNumber2;
		G4double sumEnergy, sumEnergy2;
		G4double sumPolarization, sumPolarization2;
		G4double sumCosTheta, sumCosTheta2;
	};

	public:
		RunAction(DetectorConstruction*, PrimaryGeneratorAction*, HistoManager*);
		virtual ~RunAction();
	
	public:
		void BeginOfRunAction(const G4Run*);
		void EndOfRunAction(const G4Run*);

		void CountProcesses(G4String);
	
		void FillData(const G4String & particleName,
			G4double kinEnergy, G4double costheta, G4double phi,
			G4double longitudinalPolarization);
		void EventFinished();
	private:
		DetectorConstruction* detector;
		PrimaryGeneratorAction* primary;
		ProcessesCount* ProcCounter;
		HistoManager* histoManager;
		
		G4int totalEventCount;

		ParticleStatistics photonStats;
		ParticleStatistics electronStats;
		ParticleStatistics positronStats;
	};

	#endif