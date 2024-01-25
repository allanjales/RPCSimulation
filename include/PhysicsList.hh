#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4SystemOfUnits.hh"

class PhysicsList : public G4VModularPhysicsList
{
public:
	PhysicsList();
	~PhysicsList();

protected:
	void ConstructParticle();
	void ConstructProcess();
	void SetCuts();

	void ConstructBosons();
	void ConstructLeptons();
	void ConstructMesons();
	void ConstructBaryons();

	void ConstructGeneral();
	void ConstructEM();
};

#endif