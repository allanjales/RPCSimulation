#ifndef PrimaryGeneratorAction_hh
#define PrimaryGeneratorAction_hh

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

/*
#include "DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
*/

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();
	~PrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event*);
	G4ParticleGun* GetParticleGun() {return particleGun;};

private:
	G4ParticleGun *particleGun;
};

#endif