#ifndef HistoManager_hh
#define HistoManager_hh

#include "globals.hh"
#include "G4AnalysisManager.hh"

class HistoManager
{
public:
	HistoManager();
	~HistoManager();

	void Book(G4String fileName);
	void Save();
	void FillHistos(const G4String &particleName, 
		G4double kinEnergy, G4double costheta, G4double phi,
		G4double longitudinalPolarization,
		G4double posX, G4double posY);
private:
	G4AnalysisManager *AnalysisManager;
};

#endif