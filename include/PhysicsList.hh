#ifndef PhysicsList_hh
#define PhysicsList_hh

#include "G4VModularPhysicsList.hh"

#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>
#include <G4EmStandardPhysics_option4.hh>
#include <G4IonElasticPhysics.hh>
#include <G4DecayPhysics.hh>
#include <G4StepLimiterPhysics.hh>

class PhysicsList : public G4VModularPhysicsList
{
public:
	PhysicsList();
	~PhysicsList();

protected:
	void SetCuts();
};

#endif