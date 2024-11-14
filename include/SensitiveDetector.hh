#ifndef SensitiveDetector_hh
#define SensitiveDetector_hh

#include <G4VSensitiveDetector.hh>

#include <G4AnalysisManager.hh>
#include <G4RunManager.hh>
#include <G4THitsCollection.hh>
#include <G4SDManager.hh>
#include <filesystem>
#include <G4Electron.hh>

#include "TrackerHit.hh"
#include "Digitizer.hh"
#include "ElectronFirstHit.hh"

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
	void InsertAtElectronFirstHC(const G4Step*);

	void FillTrackerHitNtuple();
	void FillElectronFirstHitNtuple();

	TrackerHitsCollection* trackerHitsCollection;
	ElectronFirstHitsCollection* electronFirstHitsCollection;

	/// @brief Ignored track IDs that have already been processed by Electron First Hits
	std::set<G4int> ignoredTrackIDs;
	bool ShouldIgnoreTrackID(int trackID) { return ignoredTrackIDs.find(trackID) != ignoredTrackIDs.end(); }
	void IgnoreTrackID(int trackID) { ignoredTrackIDs.insert(trackID); }
};

#endif