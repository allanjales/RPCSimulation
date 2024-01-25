#ifndef HistoManager_hh
#define HistoManager_hh

#include "globals.hh"
#include "G4AnalysisManager.hh"
#include "G4ParticleDefinition.hh"

class HistoManager
{
public:
	HistoManager();
	~HistoManager();

	void Book(G4String fileName);
	void Save();
	void FillData(G4ParticleDefinition*, G4int, G4int, G4ThreeVector, G4double, G4double, G4double, G4double);
private:
	G4AnalysisManager *AnalysisManager;
};

#endif