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

class SensitiveDetector : public G4VSensitiveDetector
{
public:
	SensitiveDetector(G4String);
	~SensitiveDetector();
private:
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
	void Initialize(G4HCofThisEvent*);
	void EndOfEvent(G4HCofThisEvent*);

	void FillData(const G4Step*);

	TrackerHitsCollection* fHitCollection;

	// Temporary variables
	G4double fEdep;
    G4double fPosX, fPosY, fPosZ;
	G4int fParticleID;
	G4double fKineticEnergy;
	G4double fTotalEnergy;
	G4double fTheta;
	G4double fPhi;
	G4double fCosTheta;
	G4double fMomentum;
	G4double fPt;
	G4double fEta;
};

#endif