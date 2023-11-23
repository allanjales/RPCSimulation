#include <filesystem>

#include "HistoManager.hh"
#include "HistoMessenger.hh"
#include "G4UnitsTable.hh"

HistoManager::HistoManager()
{
	G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();

	AnalysisManager->CreateNtuple("Particles", "Particles");
	AnalysisManager->CreateNtupleIColumn("fParticleID");
	AnalysisManager->CreateNtupleDColumn("fKinectEnergy");
	AnalysisManager->CreateNtupleDColumn("fCosTheta");
	AnalysisManager->CreateNtupleDColumn("fPhi");
	AnalysisManager->CreateNtupleDColumn("fLongitudinalPolarization");
	AnalysisManager->CreateNtupleDColumn("fPositionX");
	AnalysisManager->CreateNtupleDColumn("fPositionY");
	AnalysisManager->FinishNtuple(0); //Ntuple nº 0
}

HistoManager::~HistoManager()
{}

void HistoManager::Book(G4String fileName)
{
	G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();

	std::filesystem::create_directories("./results/");
	AnalysisManager->OpenFile("results/" + fileName + ".root");
}

void HistoManager::Save()
{
	G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();

	AnalysisManager->Write();
	AnalysisManager->CloseFile();
}


void HistoManager::FillData(const G4String &particleName, G4ThreeVector position,
		G4double kinEnergy, G4double costheta, G4double phi, G4ThreeVector polarization)
{
	G4int id = 1;
	if (particleName=="gamma") id = 1;
	else if (particleName=="e-") id = 5;
	else if (particleName=="e+") id = 9;
	else return;

	G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();
	AnalysisManager->FillNtupleIColumn(0, 0, id);
	AnalysisManager->FillNtupleDColumn(0, 1, kinEnergy);
	AnalysisManager->FillNtupleDColumn(0, 2, costheta);
	AnalysisManager->FillNtupleDColumn(0, 3, phi);
	AnalysisManager->FillNtupleDColumn(0, 4, polarization.z());
	AnalysisManager->FillNtupleDColumn(0, 5, position.x());
	AnalysisManager->FillNtupleDColumn(0, 6, position.y());
	AnalysisManager->AddNtupleRow(0);
}