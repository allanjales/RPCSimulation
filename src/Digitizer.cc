#include "Digitizer.hh"

Digitizer::Digitizer(G4String name) : G4VDigitizerModule(name)
{
	collectionName.push_back("TrackerDigiCollection");
}

Digitizer::~Digitizer()
{}

void Digitizer::Digitize()
{
	// Create digi collection
	trackerDigiCollection = new TrackerDigiCollection(GetName(), collectionName[0]);

	// Get hits collection 
	G4DigiManager* digiManager = G4DigiManager::GetDMpointer();
	G4int hitCollectionID = digiManager->GetHitsCollectionID("TrackerHitsCollection");
	const TrackerHitsCollection* trackerHitsCollection(static_cast<const TrackerHitsCollection*>(digiManager->GetHitsCollection(hitCollectionID)));

	if (trackerHitsCollection)
	{
		for (size_t i = 0; i < trackerHitsCollection->entries(); i++)
		{
			TrackerHit* aHit = (*trackerHitsCollection)[i];
			TrackerDigi* aDigi = new TrackerDigi();

			aDigi->SetTrackerDigiEdep(aHit->GetTrackerHitEdep());
			aDigi->SetTrackerDigiPosition(aHit->GetTrackerHitPosition());
			aDigi->SetTrackerDigiTime(aHit->GetTrackerHitTime());

			trackerDigiCollection->insert(aDigi);
		}
	}

	StoreDigiCollection(trackerDigiCollection);
}

void Digitizer::FillTrackerDigiNtuple()
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	TrackerDigi* aDigi;
	int i = 0;
	
	for (size_t j = 0; j < trackerDigiCollection->entries(); j++)
	{
		aDigi = (*trackerDigiCollection)[j];
		i = 0;

		analysisManager->FillNtupleDColumn(1, i++, aDigi->GetTrackerDigiEdep());
		analysisManager->FillNtupleDColumn(1, i++, aDigi->GetTrackerDigiPosition().x());
		analysisManager->FillNtupleDColumn(1, i++, aDigi->GetTrackerDigiPosition().y());
		analysisManager->FillNtupleDColumn(1, i++, aDigi->GetTrackerDigiPosition().z());
		analysisManager->FillNtupleDColumn(1, i++, aDigi->GetTrackerDigiTime());

		analysisManager->AddNtupleRow();
	}
}