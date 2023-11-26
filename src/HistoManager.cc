#include <filesystem>

#include "HistoManager.hh"
#include "HistoMessenger.hh"
#include "G4UnitsTable.hh"

HistoManager::HistoManager()
{
	G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();

	AnalysisManager->CreateNtuple("Particles", "Particles");
	AnalysisManager->CreateNtupleIColumn("fParticleID");
	AnalysisManager->CreateNtupleDColumn("fPositionX");
	AnalysisManager->CreateNtupleDColumn("fPositionY");
	AnalysisManager->CreateNtupleDColumn("fPositionZ");
	AnalysisManager->CreateNtupleDColumn("fKinectEnergy");
	AnalysisManager->CreateNtupleDColumn("fCosTheta");
	AnalysisManager->CreateNtupleDColumn("fPhi");
	AnalysisManager->CreateNtupleDColumn("fLongitudinalPolarization");
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

void HistoManager::FillData(G4ParticleDefinition* particle, G4ThreeVector position,
		G4double kinEnergy, G4double costheta, G4double phi, G4ThreeVector polarization)
{
	G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();
	
	AnalysisManager->FillNtupleIColumn(0, 0, particle->GetPDGEncoding());
	AnalysisManager->FillNtupleDColumn(0, 1, position.x());
	AnalysisManager->FillNtupleDColumn(0, 2, position.y());
	AnalysisManager->FillNtupleDColumn(0, 3, position.z());
	AnalysisManager->FillNtupleDColumn(0, 4, kinEnergy);
	AnalysisManager->FillNtupleDColumn(0, 5, costheta);
	AnalysisManager->FillNtupleDColumn(0, 6, phi);
	AnalysisManager->FillNtupleDColumn(0, 7, polarization.z());
	AnalysisManager->AddNtupleRow(0);
}