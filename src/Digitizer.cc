#include "Digitizer.hh"

Digitizer::Digitizer(G4String name) : G4VDigitizerModule(name)
{
	collectionName.push_back("TrackerDigiCollection");
}

Digitizer::~Digitizer()
{}

void Digitizer::Digitize()
{
	//TrackerDigiCollection* digiCollection = new TrackerDigiCollection(GetName(), collectionName[0]);
	//TrackerDigi* aDigi = new TrackerDigi();
	//digiCollection->insert(aDigi);

	//StoreDigiCollection(digiCollection);

    // Cria uma nova coleção de Digis
    fDigiCollection = new TrackerDigiCollection(GetName(), collectionName[0]);


    // Obtém a coleção de hits
    G4DigiManager* digiManager = G4DigiManager::GetDMpointer();
    G4int hitCollectionID = digiManager->GetHitsCollectionID("TrackerHitCollection");
    const TrackerHitsCollection* hitsCollection(static_cast<const TrackerHitsCollection*>(digiManager->GetHitsCollection(hitCollectionID)));

    if (hitsCollection)
    {
        for (size_t i = 0; i < hitsCollection->entries(); i++)
        {
            TrackerHit* hit = (*hitsCollection)[i];
            
            TrackerDigi* digi = new TrackerDigi();
            digi->SetEdep(hit->GetEdep());
            digi->SetPosition(hit->GetPosition());

            fDigiCollection->insert(digi);
        }
    }
	
    StoreDigiCollection(fDigiCollection);
}