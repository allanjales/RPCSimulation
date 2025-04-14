#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name)
: G4VSensitiveDetector(name)
{
	collectionName.insert("TrackerHitsCollection");
	collectionName.insert("ElectronFirstHitsCollection");
}

SensitiveDetector::~SensitiveDetector()
{}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
	G4Track* aTrack = aStep->GetTrack();
	if (aTrack->GetTotalEnergy() > 0)
		InsertAtTrackerHC(aStep);

	G4int trackID = aTrack->GetTrackID();
	if (ShouldIgnoreTrackID(trackID))
	 	return true;

	G4int parentID = aTrack->GetParentID();
	if (ShouldIgnoreTrackID(parentID))
	{
		IgnoreTrackID(trackID);
		return true;
	}

	if (aTrack->GetDefinition() != G4Electron::ElectronDefinition())
		return true;

	InsertAtElectronFirstHC(aStep);
	IgnoreTrackID(trackID);

	return true;
}

void SensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
	trackerHitsCollection = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]);
	G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	hce->AddHitsCollection(hcID, trackerHitsCollection);

	electronFirstHitsCollection = new ElectronFirstHitsCollection(SensitiveDetectorName, collectionName[1]);
	hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[1]);
	hce->AddHitsCollection(hcID, electronFirstHitsCollection);

	ignoredTrackIDs.clear();
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
	FillTrackerHitNtuple();
	FillElectronFirstHitNtuple();
}

void SensitiveDetector::InsertAtTrackerHC(const G4Step* aStep)
{
	G4Track* aTrack = aStep->GetTrack();
	TrackerHit* aHit = new TrackerHit();

	aHit->SetTrackerHitParticleID(aTrack->GetDefinition()->GetPDGEncoding());
	aHit->SetTrackerHitEdep(aStep->GetTotalEnergyDeposit());
	aHit->SetTrackerHitPosition(aTrack->GetPosition());
	aHit->SetTrackerHitMomentum(aTrack->GetMomentum());
	aHit->SetTrackerHitKineticEnergy(aTrack->GetKineticEnergy());
	aHit->SetTrackerHitTime(aTrack->GetGlobalTime());

	trackerHitsCollection->insert(aHit);
}

void SensitiveDetector::InsertAtElectronFirstHC(const G4Step* aStep)
{
	G4Track* aTrack = aStep->GetTrack();
	ElectronFirstHit* aHit = new ElectronFirstHit();
	
	aHit->SetElectronFirstHitPosition(aTrack->GetPosition());
	aHit->SetElectronFirstHitMomentum(aTrack->GetMomentum());
	aHit->SetElectronFirstHitKineticEnergy(aTrack->GetKineticEnergy());
	aHit->SetElectronFirstHitTime(aTrack->GetGlobalTime());

	electronFirstHitsCollection->insert(aHit);
}

void SensitiveDetector::FillTrackerHitNtuple()
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	size_t trackerHCEntries = trackerHitsCollection->entries();

	if (trackerHCEntries == 0)
		return;
	
	TrackerHit* aHit;
	int i = 0;
	for (size_t j = 0; j < trackerHCEntries; j++)
	{
		aHit = (*trackerHitsCollection)[j];
		i = 0;

		analysisManager->FillNtupleIColumn(0, i++, aHit->GetTrackerHitParticleID());
		analysisManager->FillNtupleDColumn(0, i++, aHit->GetTrackerHitEdep());
		analysisManager->FillNtupleDColumn(0, i++, aHit->GetTrackerHitPosition().x());
		analysisManager->FillNtupleDColumn(0, i++, aHit->GetTrackerHitPosition().y());
		analysisManager->FillNtupleDColumn(0, i++, aHit->GetTrackerHitPosition().z());
		analysisManager->FillNtupleDColumn(0, i++, aHit->GetTrackerHitTime());
		analysisManager->FillNtupleDColumn(0, i++, aHit->GetTrackerHitMomentum().x());
		analysisManager->FillNtupleDColumn(0, i++, aHit->GetTrackerHitMomentum().y());
		analysisManager->FillNtupleDColumn(0, i++, aHit->GetTrackerHitMomentum().z());
		analysisManager->FillNtupleDColumn(0, i++, aHit->GetTrackerHitKineticEnergy());

		analysisManager->AddNtupleRow(0);
	}
}

void SensitiveDetector::FillElectronFirstHitNtuple()
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	size_t ElectronFirstHitHCEntries = electronFirstHitsCollection->entries();

	if (ElectronFirstHitHCEntries == 0)
		return;
	
	ElectronFirstHit* aHit;
	int i = 0;
	for (size_t j = 0; j < ElectronFirstHitHCEntries; j++)
	{
		aHit = (*electronFirstHitsCollection)[j];
		i = 0;

		analysisManager->FillNtupleDColumn(2, i++, aHit->GetElectronFirstHitPosition().x());
		analysisManager->FillNtupleDColumn(2, i++, aHit->GetElectronFirstHitPosition().y());
		analysisManager->FillNtupleDColumn(2, i++, aHit->GetElectronFirstHitPosition().z());
		analysisManager->FillNtupleDColumn(2, i++, aHit->GetElectronFirstHitTime());
		analysisManager->FillNtupleDColumn(2, i++, aHit->GetElectronFirstHitMomentum().x());
		analysisManager->FillNtupleDColumn(2, i++, aHit->GetElectronFirstHitMomentum().y());
		analysisManager->FillNtupleDColumn(2, i++, aHit->GetElectronFirstHitMomentum().z());
		analysisManager->FillNtupleDColumn(2, i++, aHit->GetElectronFirstHitKineticEnergy());

		analysisManager->AddNtupleRow(2);
	}
}