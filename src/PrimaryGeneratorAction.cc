#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
	// Prepare gun to shoot 1 Particle
	particleGun = new G4ParticleGun(1);
	G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("mu+");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticleEnergy(1.0*GeV);
	particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm, 13.4*mm));
	particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
	// Shoot the particle
	particleGun->GeneratePrimaryVertex(anEvent);
}