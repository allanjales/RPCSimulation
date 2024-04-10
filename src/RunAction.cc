#include "RunAction.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4EmCalculator.hh"

#include "Randomize.hh"
#include <iomanip>

#include "G4UnitsTable.hh"

RunAction::RunAction(DetectorConstruction* det, 
	PrimaryGeneratorAction* prim, HistoManager* histo)
: detector(det), primary(prim), histoManager(histo)
{
	//G4Random::setTheSeed(time(0));
	G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
	G4cout << "\n--------------\n";
	G4cout << "Run " << aRun->GetRunID() << " start\n";
	G4cout << "Seed: " << G4Random::getTheSeed() << "\n\n";

	std::stringstream strRunID;
	strRunID << aRun->GetRunID();
	histoManager->Book("output_" + strRunID.str());
	runStartedTime = time(0);
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{	
	G4cout.precision(5);
	G4ParticleDefinition* particle = primary->GetParticleGun()->GetParticleDefinition();
	G4double energy = primary->GetParticleGun()->GetParticleEnergy();
	G4cout << "\nThe run consists of " << aRun->GetNumberOfEvent() << " "
		<< particle->GetParticleName() << " of " << G4BestUnit(energy,"Energy") << " through\n";
	
	double elapsedtime = (time(0) - runStartedTime) * s;
	G4cout << "\nRun " << aRun->GetRunID() << " ended within " << G4BestUnit(elapsedtime, "Time") << "\n";
	G4cout << "--------------\n";

	//if has not been any event, do not save histograms
	if (aRun->GetNumberOfEvent() == 0)
		return;

	histoManager->Save();

	G4Random::showEngineStatus();
}