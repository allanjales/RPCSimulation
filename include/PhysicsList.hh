#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"
#include "G4SystemOfUnits.hh"

class PhysicsList : public G4VUserPhysicsList
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