#ifndef HistoManager_hh
#define HistoManager_hh

#include "globals.hh"
#include "G4AnalysisManager.hh"
#include "G4ParticleDefinition.hh"

#include <G4StepPoint.hh>
#include <G4Track.hh>

class HistoManager
{
public:
	HistoManager();
	~HistoManager();

	void Book(G4String fileName);
	void Save();
	void FillData(const G4Step* aStep, G4int regionID);
private:
	G4AnalysisManager *AnalysisManager;
};

#endif