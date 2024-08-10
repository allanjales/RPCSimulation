#ifndef DataHandler_hh
#define DataHandler_hh

#include <globals.hh>
#include <G4Step.hh>
#include <G4AnalysisManager.hh>
#include "DataHandlerMessenger.hh"

#include <G4RunManager.hh>
#include <filesystem>

class DataHandler
{
public:
	DataHandler();
	~DataHandler();

	void Book(G4String fileName);
	void FillData(const G4Step* aStep, G4int regionID);
	void Save();
private:
	G4AnalysisManager* analysisManager;
	DataHandlerMessenger* dataHandlerMessenger;
};

#endif