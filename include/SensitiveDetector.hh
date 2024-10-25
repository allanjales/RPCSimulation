#ifndef SensitiveDetector_hh
#define SensitiveDetector_hh

#include <G4VSensitiveDetector.hh>

#include <G4AnalysisManager.hh>
#include <G4RunManager.hh>

class SensitiveDetector : public G4VSensitiveDetector
{
public:
	SensitiveDetector(G4String);
	~SensitiveDetector();
private:
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);

	void FillData(const G4Step*);

	//void Initialize(G4HCofThisEvent*);
	//void EndOfEvent(G4HCofThisEvent*);
};

#endif