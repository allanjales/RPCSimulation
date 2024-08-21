#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name, DataHandler* dataHandler)
: G4VSensitiveDetector(name), dataHandler(dataHandler)
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
	dataHandler->FillData(aStep, 0);

	return true;
}