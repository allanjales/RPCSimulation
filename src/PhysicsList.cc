#include "globals.hh"
#include "PhysicsList.hh"
#include <G4UnitsTable.hh>

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4StepLimiter.hh"

#include "G4EmStandardPhysics_option4.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"

PhysicsList::PhysicsList()
{
	defaultCutValue = 0.01*mm;
	SetVerboseLevel(1);

	// Most accurate EM models and settings
	RegisterPhysics(new G4EmStandardPhysics_option4());

	RegisterPhysics(new G4DecayPhysics());

	// High precision hadronic physics
	RegisterPhysics(new G4HadronPhysicsQGSP_BERT_HP());
	
	RegisterPhysics(new G4StepLimiterPhysics());
}

PhysicsList::~PhysicsList() {}

void PhysicsList::SetCuts()
{
	// Set the range cuts for secondary production 
	// low energy limit on particle production
	if (verboseLevel > 0)
	{
		G4cout << "\nPhysicsList::SetCuts:";
		G4cout << "\n> CutLength : " << G4BestUnit(defaultCutValue, "Length") << "\n\n";
	}

	SetCutValue(defaultCutValue, "gamma");
	SetCutValue(defaultCutValue, "e-");
	SetCutValue(defaultCutValue, "e+");
}