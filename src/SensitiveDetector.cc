#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name)
: G4VSensitiveDetector(name)
{}

SensitiveDetector::~SensitiveDetector()
{}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	// G4double edep = aStep->GetTotalEnergyDeposit();
	// if(edep == 0.) return false;
	// G4cout << "Energy deposited: " << edep << G4endl;
	
	G4ParticleDefinition* particle = aStep->GetTrack()->GetDefinition();
	if (particle->GetParticleType() != "lepton" && particle->GetParticleType() != "gamma")
	{
		G4cout << "Particle Type: " << particle->GetParticleType() << "\n";
		G4cout << particle->GetParticleName() << " | " << particle->GetPDGEncoding() << "\n";
	}
	
	// Store info
	FillData(aStep);
	return true;
}

void SensitiveDetector::FillData(const G4Step* aStep)
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	//G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	G4StepPoint* prePoint = aStep->GetPreStepPoint();
	G4StepPoint* endPoint = aStep->GetPostStepPoint();

	G4ThreeVector prePosition = prePoint->GetPosition();
	G4ThreeVector endPosition = endPoint->GetPosition();

	G4Track* aTrack = aStep->GetTrack();
	G4ParticleDefinition* particle = aStep->GetTrack()->GetDefinition();
	G4ThreeVector position = aTrack->GetPosition();
	G4ThreeVector momentum = aTrack->GetMomentum();

	int i = 0;
	analysisManager->FillNtupleIColumn(i++,  particle->GetPDGEncoding()); // PDG particle ID
	//analysisManager->FillNtupleIColumn(i++,  aTrack->GetTrackID()); // Unique ID for each track
	//analysisManager->FillNtupleIColumn(i++,  eventID); // Unique ID for each event in this run
	//analysisManager->FillNtupleIColumn(i++,  regionID); // Region ID (for multi sensitive detector regions)

	// Step
	//analysisManager->FillNtupleDColumn(i++, aStep->GetStepLength()); // mm

	// Track
	//analysisManager->FillNtupleDColumn(i++, aTrack->GetGlobalTime()); // Time since event start (ns)

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