#ifndef SensitiveDetector_hh
#define SensitiveDetector_hh

#include <G4VSensitiveDetector.hh>

#include <G4AnalysisManager.hh>
#include <G4RunManager.hh>
#include <G4THitsCollection.hh>
#include <G4SDManager.hh>
#include "TrackerHit.hh"
#include "Digitizer.hh"
#include <filesystem>
#include <G4Electron.hh>

class SensitiveDetector : public G4VSensitiveDetector
{
public:
	SensitiveDetector(G4String);
	~SensitiveDetector();
private:
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
	void Initialize(G4HCofThisEvent*);
	void EndOfEvent(G4HCofThisEvent*);

	void InsertAtTrackerHC(const G4Step*);

	TrackerHitsCollection* trackerHitsCollection = nullptr;
};

#endif