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
	void FillData(G4ParticleDefinition* particle, G4ThreeVector position,
		G4double kinEnergy, G4double costheta, G4double phi, G4ThreeVector polarization);
private:
	G4AnalysisManager *AnalysisManager;
};

#endif