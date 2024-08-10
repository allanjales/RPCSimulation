#include "DataHandler.hh"

DataHandler::DataHandler()
{
	dataHandlerMessenger = new DataHandlerMessenger(this);

	analysisManager = G4AnalysisManager::Instance();

	analysisManager->CreateNtuple("DetectedParticles", "DetectedParticles");
	analysisManager->CreateNtupleIColumn("ParticleID");
	analysisManager->CreateNtupleIColumn("TrackID");
	analysisManager->CreateNtupleIColumn("EventID");
	analysisManager->CreateNtupleIColumn("RegionID");

	// Step
	analysisManager->CreateNtupleDColumn("StepLength");

	// Post Step
	analysisManager->CreateNtupleDColumn("Time");

	analysisManager->CreateNtupleDColumn("PositionX");
	analysisManager->CreateNtupleDColumn("PositionY");
	analysisManager->CreateNtupleDColumn("PositionZ");

	analysisManager->CreateNtupleDColumn("KinectEnergy");
	analysisManager->CreateNtupleDColumn("TotalEnergy");
	analysisManager->CreateNtupleDColumn("Theta");
	analysisManager->CreateNtupleDColumn("Phi");
	analysisManager->CreateNtupleDColumn("Momentum");

	analysisManager->CreateNtupleDColumn("Pt");
	analysisManager->CreateNtupleDColumn("Eta");
	analysisManager->CreateNtupleDColumn("CosTheta");

	analysisManager->FinishNtuple();
}

DataHandler::~DataHandler()
{
	delete dataHandlerMessenger;
}

void DataHandler::Book(G4String fileName)
{
	std::filesystem::create_directories("./results/");
	analysisManager->OpenFile("results/" + fileName + ".root");
}

void DataHandler::Save()
{
	analysisManager->Write();
	analysisManager->CloseFile();
}

void DataHandler::FillData(const G4Step* aStep, G4int regionID)
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

	int i = 0;
	analysisManager->FillNtupleIColumn(i++,  particle->GetPDGEncoding()); // PDG particle ID
	analysisManager->FillNtupleIColumn(i++,  aTrack->GetTrackID()); // Unique ID for each track
	analysisManager->FillNtupleIColumn(i++,  eventID); // Unique ID for each event in this run
	analysisManager->FillNtupleIColumn(i++,  regionID); // Region ID (for multi sensitive detector regions)

	// Step
	analysisManager->FillNtupleDColumn(i++, aStep->GetStepLength()); // mm

	// Track
	analysisManager->FillNtupleDColumn(i++, aTrack->GetGlobalTime()); // Time since event start (ns)

	analysisManager->FillNtupleDColumn(i++, position.x()); // mm
	analysisManager->FillNtupleDColumn(i++, position.y()); // mm
	analysisManager->FillNtupleDColumn(i++, position.z()); // mm

	analysisManager->FillNtupleDColumn(i++, aTrack->GetKineticEnergy()); // MeV
	analysisManager->FillNtupleDColumn(i++, aTrack->GetTotalEnergy()); // MeV
	analysisManager->FillNtupleDColumn(i++, aTrack->GetMomentumDirection().theta()); // rad
	analysisManager->FillNtupleDColumn(i++, aTrack->GetMomentumDirection().phi()); // rad
	analysisManager->FillNtupleDColumn(i++, momentum.mag()); // MeV/c
	
	analysisManager->FillNtupleDColumn(i++, sqrt(momentum.x()*momentum.x() + momentum.y()*momentum.y())); // MeV/c
	analysisManager->FillNtupleDColumn(i++, -log(tan(aTrack->GetMomentumDirection().theta()/2.)));
	analysisManager->FillNtupleDColumn(i++, cos(aTrack->GetMomentumDirection().theta()));

	analysisManager->AddNtupleRow();
}