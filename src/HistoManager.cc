#include <filesystem>

#include "HistoManager.hh"
#include "HistoMessenger.hh"
#include "G4UnitsTable.hh"

HistoManager::HistoManager()
{
	G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();

	AnalysisManager->CreateNtuple("DetectedParticles", "DetectedParticles");
	AnalysisManager->CreateNtupleIColumn("fParticleID");
	AnalysisManager->CreateNtupleIColumn("fEvent");
	AnalysisManager->CreateNtupleIColumn("fRegionID");
	AnalysisManager->CreateNtupleDColumn("fPositionX");
	AnalysisManager->CreateNtupleDColumn("fPositionY");
	AnalysisManager->CreateNtupleDColumn("fPositionZ");
	AnalysisManager->CreateNtupleDColumn("fKinectEnergy");
	AnalysisManager->CreateNtupleDColumn("fCosTheta");
	AnalysisManager->CreateNtupleDColumn("fPhi");
	AnalysisManager->CreateNtupleDColumn("fStepLength");
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

void HistoManager::FillData(G4ParticleDefinition* particle, G4int eventID, G4int regionID,
	G4ThreeVector position, G4double stepLength, G4double kinEnergy, G4double costheta, G4double phi)
{
	G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();
	
	AnalysisManager->FillNtupleIColumn(0, 0, particle->GetPDGEncoding());
	AnalysisManager->FillNtupleIColumn(0, 1, eventID);
	AnalysisManager->FillNtupleIColumn(0, 2, regionID);
	AnalysisManager->FillNtupleDColumn(0, 3, position.x());
	AnalysisManager->FillNtupleDColumn(0, 4, position.y());
	AnalysisManager->FillNtupleDColumn(0, 5, position.z());
	AnalysisManager->FillNtupleDColumn(0, 6, kinEnergy);
	AnalysisManager->FillNtupleDColumn(0, 7, costheta);
	AnalysisManager->FillNtupleDColumn(0, 8, phi);
	AnalysisManager->FillNtupleDColumn(0, 9, stepLength);
	AnalysisManager->AddNtupleRow(0);
}