#include "globals.hh"
#include "PhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4StepLimiter.hh"

PhysicsList::PhysicsList()
{
	defaultCutValue = 0.0001*mm;
	SetVerboseLevel(1);

	RegisterPhysics(new G4StepLimiterPhysics());
}

PhysicsList::~PhysicsList() {}


void PhysicsList::ConstructParticle()
{
	ConstructBosons();
	ConstructLeptons();
	ConstructMesons();
	ConstructBaryons();
}

void PhysicsList::ConstructBosons()
{
	//G4Geantino::GeantinoDefinition();
	//G4ChargedGeantino::ChargedGeantinoDefinition();
	G4Gamma::GammaDefinition();
}

void PhysicsList::ConstructLeptons()
{
	G4Electron::ElectronDefinition();
	G4Positron::PositronDefinition();

	G4MuonPlus::MuonPlusDefinition();
	G4MuonMinus::MuonMinusDefinition();

	G4NeutrinoE::NeutrinoEDefinition();
	G4AntiNeutrinoE::AntiNeutrinoEDefinition();

	G4NeutrinoMu::NeutrinoMuDefinition();
	G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

void PhysicsList::ConstructMesons()
{
	G4PionPlus::PionPlusDefinition();
	G4PionMinus::PionMinusDefinition();
	G4PionZero::PionZeroDefinition();
	G4Eta::EtaDefinition();
	G4EtaPrime::EtaPrimeDefinition();
	G4KaonPlus::KaonPlusDefinition();
	G4KaonMinus::KaonMinusDefinition();
	G4KaonZero::KaonZeroDefinition();
	G4AntiKaonZero::AntiKaonZeroDefinition();
	G4KaonZeroLong::KaonZeroLongDefinition();
	G4KaonZeroShort::KaonZeroShortDefinition();	
}

void PhysicsList::ConstructBaryons()
{
	G4Proton::ProtonDefinition();
	G4AntiProton::AntiProtonDefinition();

	G4Neutron::NeutronDefinition();
	G4AntiNeutron::AntiNeutronDefinition();
}

void PhysicsList::ConstructProcess()
{
	AddTransportation();
	ConstructEM();
	ConstructGeneral();
}

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

void PhysicsList::ConstructEM()
{
	GetParticleIterator()->reset();
	while ((*GetParticleIterator())())
	{
		G4ParticleDefinition* particle = GetParticleIterator()->value();
		G4ProcessManager* pmanager = particle->GetProcessManager();
		G4String particleName = particle->GetParticleName();
		if (particleName == "gamma")
		{
			pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
			pmanager->AddDiscreteProcess(new G4ComptonScattering);
			pmanager->AddDiscreteProcess(new G4GammaConversion);
			pmanager->AddDiscreteProcess(new G4StepLimiter);
		}
		else if (particleName == "e-")
		{
			pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
			pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
			pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);
			pmanager->AddDiscreteProcess(new G4StepLimiter);
		}
		else if (particleName == "e+")
		{
			pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
			pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
			pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);
			pmanager->AddProcess(new G4eplusAnnihilation,    0,-1, 4);
			pmanager->AddDiscreteProcess(new G4StepLimiter);
		}
		else if (particleName == "mu+" || particleName == "mu-")
		{
			pmanager->AddProcess(new G4MuMultipleScattering, -1, 1, 1);
			pmanager->AddProcess(new G4MuIonisation,         -1, 2, 2);
			pmanager->AddProcess(new G4MuBremsstrahlung,     -1, 3, 3);
			pmanager->AddProcess(new G4MuPairProduction,     -1, 4, 4);
			pmanager->AddDiscreteProcess(new G4StepLimiter);
		}
		else if (particle->GetPDGCharge() != 0)
		{
			pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
			pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
			pmanager->AddDiscreteProcess(new G4StepLimiter);
		}
	}
}

#include "G4Decay.hh"

void PhysicsList::ConstructGeneral()
{
	G4Decay* theDecayProcess = new G4Decay();
	GetParticleIterator()->reset();
	while ((*GetParticleIterator())())
	{
		G4ParticleDefinition* particle = GetParticleIterator()->value();
		G4ProcessManager* pmanager = particle->GetProcessManager();
		if (theDecayProcess->IsApplicable(*particle))
		{
			pmanager->AddProcess(theDecayProcess);
			pmanager->SetProcessOrdering(theDecayProcess, idxPostStep);
			pmanager->SetProcessOrdering(theDecayProcess, idxAtRest);
		}
	}
}

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