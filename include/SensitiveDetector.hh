#ifndef SensitiveDetector_hh
#define SensitiveDetector_hh

#include "HistoManager.hh"

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
public:
	SensitiveDetector(G4String);
	~SensitiveDetector();
	
    HistoManager *histoManager;

private:
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};

#endif