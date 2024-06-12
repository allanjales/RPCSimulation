#include <filesystem>

#include "HistoManager.hh"
#include "HistoMessenger.hh"
#include "G4UnitsTable.hh"

#include "G4RunManager.hh"

HistoManager::HistoManager()
{
	G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();

	AnalysisManager->CreateNtuple("DetectedParticles", "DetectedParticles");
	AnalysisManager->CreateNtupleIColumn("ParticleID");
	AnalysisManager->CreateNtupleIColumn("Event");
	AnalysisManager->CreateNtupleIColumn("RegionID");

	// Pre Step
	AnalysisManager->CreateNtupleDColumn("PreStepPositionX");
	AnalysisManager->CreateNtupleDColumn("PreStepPositionY");
	AnalysisManager->CreateNtupleDColumn("PreStepPositionZ");

	// Step
	AnalysisManager->CreateNtupleDColumn("StepLength");

	// Post Step
	AnalysisManager->CreateNtupleDColumn("PositionX");
	AnalysisManager->CreateNtupleDColumn("PositionY");
	AnalysisManager->CreateNtupleDColumn("PositionZ");

	AnalysisManager->CreateNtupleDColumn("KinectEnergy");
	AnalysisManager->CreateNtupleDColumn("TotalEnergy");
	AnalysisManager->CreateNtupleDColumn("Theta");
	AnalysisManager->CreateNtupleDColumn("Phi");
	AnalysisManager->CreateNtupleDColumn("MomentumMagnitude");

	AnalysisManager->CreateNtupleDColumn("Pseudorapidity");
	AnalysisManager->CreateNtupleDColumn("CosTheta");

	AnalysisManager->CreateNtupleDColumn("OldCosTheta");
	AnalysisManager->FinishNtuple();
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

void HistoManager::FillData(const G4Step* aStep, G4int regionID)
{
	G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	G4StepPoint* prePoint = aStep->GetPreStepPoint();
	G4StepPoint* endPoint = aStep->GetPostStepPoint();

	G4ThreeVector prePosition = prePoint->GetPosition();
	G4ThreeVector endPosition = endPoint->GetPosition();

	G4Track* aTrack = aStep->GetTrack();
	G4ParticleDefinition* particle = aTrack->GetDynamicParticle()->GetDefinition();
	G4ThreeVector position = aTrack->GetPosition();
	G4ThreeVector momentum = aTrack->GetMomentum();

	//G4ThreeVector beamDirectionVec = primary->GetParticleGun()->GetParticleMomentumDirection();
	G4ThreeVector directionVec = endPoint->GetMomentumDirection();
	//G4double costheta = directionVec * beamDirectionVec;
	G4double costheta = directionVec * G4ThreeVector(0., 0., 1.);

	G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();

	AnalysisManager->FillNtupleIColumn(0,  particle->GetPDGEncoding());
	AnalysisManager->FillNtupleIColumn(1,  eventID);
	AnalysisManager->FillNtupleIColumn(2,  regionID);

	// Pre Step
	AnalysisManager->FillNtupleDColumn(3,  prePosition.x());
	AnalysisManager->FillNtupleDColumn(4,  prePosition.y());
	AnalysisManager->FillNtupleDColumn(5,  prePosition.z());

	// Step
	AnalysisManager->FillNtupleDColumn(6, aStep->GetStepLength());

	// Track
	AnalysisManager->FillNtupleDColumn(7, position.x());
	AnalysisManager->FillNtupleDColumn(8, position.y());
	AnalysisManager->FillNtupleDColumn(9, position.z());

	AnalysisManager->FillNtupleDColumn(10, aTrack->GetKineticEnergy());
	AnalysisManager->FillNtupleDColumn(11, aTrack->GetTotalEnergy());
	AnalysisManager->FillNtupleDColumn(12, aTrack->GetMomentumDirection().theta());
	AnalysisManager->FillNtupleDColumn(13, aTrack->GetMomentumDirection().phi());
	AnalysisManager->FillNtupleDColumn(14, momentum.mag());
	
	AnalysisManager->FillNtupleDColumn(15, -log(tan(aTrack->GetMomentumDirection().theta()/2.)));
	AnalysisManager->FillNtupleDColumn(16, cos(aTrack->GetMomentumDirection().theta()));

	AnalysisManager->FillNtupleDColumn(17, costheta);

	AnalysisManager->AddNtupleRow();
}