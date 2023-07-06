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

	//histoMessenger = new HistoMessenger(this);
}


HistoManager::~HistoManager()
{
	//delete histoMessenger;
}

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


void HistoManager::FillHistos(const G4String& particleName,
	G4double kinEnergy, G4double costheta,
	G4double phi, G4double longitudinalPolarization,
	G4double posX, G4double posY)
{

	G4int id = 1;
	if (particleName=="gamma") id = 1;
	else if (particleName=="e-") id = 5;
	else if (particleName=="e+") id = 9;
	else return;

	//if (costheta >= 1.) costheta = .99999999;
	//if (costheta < -1.) costheta = -1.;

	G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();
	AnalysisManager->FillNtupleIColumn(0, 0, id);
	AnalysisManager->FillNtupleDColumn(0, 1, kinEnergy);
	AnalysisManager->FillNtupleDColumn(0, 2, costheta);
	AnalysisManager->FillNtupleDColumn(0, 3, phi);
	AnalysisManager->FillNtupleDColumn(0, 4, longitudinalPolarization);
	AnalysisManager->FillNtupleDColumn(0, 5, posX);
	AnalysisManager->FillNtupleDColumn(0, 6, posY);
	AnalysisManager->AddNtupleRow(0);
}