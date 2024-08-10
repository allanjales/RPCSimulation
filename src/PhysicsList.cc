#include "PhysicsList.hh"

PhysicsList::PhysicsList()
{
	defaultCutValue = 0.001*mm;
	SetVerboseLevel(1);

	// Most accurate EM models and settings
	RegisterPhysics(new G4EmStandardPhysics_option4());
	RegisterPhysics(new G4IonElasticPhysics());
	RegisterPhysics(new G4DecayPhysics());
	
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