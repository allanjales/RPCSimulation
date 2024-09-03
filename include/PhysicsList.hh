#ifndef PhysicsList_hh
#define PhysicsList_hh

#include "G4VUserPhysicsList.hh"
#include "G4SystemOfUnits.hh"

#include "G4ComptonScattering.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4GammaConversion.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4StepLimiter.hh"

#include "G4MuonNuclearProcess.hh"
#include "G4MuonVDNuclearModel.hh"
#include "G4IonConstructor.hh"
#include "G4GenericIon.hh"

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