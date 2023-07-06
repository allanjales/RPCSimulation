#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
	particleGun = new G4ParticleGun(1);
	G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("mu+");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticleEnergy(1.0*GeV);
	particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.0));

	/*
	G4int n_particle = 1;
	particleGun = new G4ParticleGun(n_particle);

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle("proton");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0., -1.));
	particleGun->SetParticleEnergy(1.0*GeV);
	*/
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
	particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,1.5*mm));
	particleGun->GeneratePrimaryVertex(anEvent);
}