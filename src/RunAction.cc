#include "RunAction.hh"

RunAction::RunAction(DetectorConstruction* detector, PrimaryGeneratorAction* primary)
: detector(detector), primary(primary)
{
	// Get the main data handler
	dataHandler = detector->dataHandler;

	// Random seed
	// G4Random::setTheSeed(time(0));
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
	dataHandler->Book("output_" + strRunID.str());
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

	dataHandler->Save();

	G4Random::showEngineStatus();
}