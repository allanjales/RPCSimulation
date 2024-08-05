#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
    histoManager = new HistoManager();
}

SensitiveDetector::~SensitiveDetector()
{
    delete histoManager;
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	// Store info
    histoManager->FillData(aStep, 0);

    return true;
}