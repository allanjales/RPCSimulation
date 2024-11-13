#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name)
: G4VSensitiveDetector(name)
{
	collectionName.insert("TrackerHitsCollection");
}

SensitiveDetector::~SensitiveDetector()
{}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{
	InsertAtTrackerHC(aStep);
	return true;
}

void SensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
	trackerHitsCollection = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]);

	G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	hce->AddHitsCollection(hcID, trackerHitsCollection);
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
	/*
	G4int HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	fHitCollection = static_cast<TrackerHitsCollection*>(HCE->GetHC(HCID));

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	int i = 0;
	for (size_t j = 0; j < fHitCollection->entries(); j++)
	{
		TrackerHit* hit = (*fHitCollection)[j];

		i = 0;
		analysisManager->FillNtupleIColumn(i++, hit->GetParticleID());
		
		analysisManager->FillNtupleDColumn(i++, hit->GetPosition().x());
		analysisManager->FillNtupleDColumn(i++, hit->GetPosition().y());
		analysisManager->FillNtupleDColumn(i++, hit->GetPosition().z());

		analysisManager->FillNtupleDColumn(i++, hit->GetKineticEnergy());
		analysisManager->FillNtupleDColumn(i++, hit->GetTotalEnergy());
		analysisManager->FillNtupleDColumn(i++, hit->GetTheta());
		analysisManager->FillNtupleDColumn(i++, hit->GetPhi());
		analysisManager->FillNtupleDColumn(i++, hit->GetMomentum());

		analysisManager->FillNtupleDColumn(i++, hit->GetPt());
		analysisManager->FillNtupleDColumn(i++, hit->GetEta());
		analysisManager->FillNtupleDColumn(i++, hit->GetCosTheta());

		analysisManager->AddNtupleRow();
	}
	*/
}

void SensitiveDetector::InsertAtTrackerHC(const G4Step* aStep)
{
	TrackerHit* aHit = new TrackerHit();

	G4Track* aTrack = aStep->GetTrack();
	G4ThreeVector momentum = aTrack->GetMomentum();

	aHit->SetTrackerHitParticleID(aTrack->GetDefinition()->GetPDGEncoding());
	aHit->SetTrackerHitEdep(aStep->GetTotalEnergyDeposit());
	aHit->SetTrackerHitPosition(aTrack->GetPosition());
	aHit->SetTrackerHitMomentum(aTrack->GetMomentum());
	aHit->SetTrackerHitKineticEnergy(aTrack->GetKineticEnergy());
	aHit->SetTrackerHitTime(aTrack->GetGlobalTime());

	trackerHitsCollection->insert(aHit);
}