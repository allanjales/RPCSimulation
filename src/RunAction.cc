#include "RunAction.hh"

RunAction::RunAction()
{
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

	// std::stringstream strRunID;
	// strRunID << aRun->GetRunID();
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	std::filesystem::create_directories("./results/");
	analysisManager->OpenFile("results/output.root");

	analysisManager->CreateNtuple("TrackerHits", "TrackerHits");
	analysisManager->CreateNtupleIColumn(0, "ParticleID");
	analysisManager->CreateNtupleDColumn(0, "Edep");
	analysisManager->CreateNtupleDColumn(0, "PositionX");
	analysisManager->CreateNtupleDColumn(0, "PositionY");
	analysisManager->CreateNtupleDColumn(0, "PositionZ");
	analysisManager->CreateNtupleDColumn(0, "Time");
	analysisManager->CreateNtupleDColumn(0, "MomentumX");
	analysisManager->CreateNtupleDColumn(0, "MomentumY");
	analysisManager->CreateNtupleDColumn(0, "MomentumZ");
	analysisManager->CreateNtupleDColumn(0, "KinectEnergy");
	analysisManager->FinishNtuple(0);

	analysisManager->CreateNtuple("TrackerDigi", "TrackerDigi");
	analysisManager->CreateNtupleDColumn(1, "Edep");
	analysisManager->CreateNtupleDColumn(1, "PositionX");
	analysisManager->CreateNtupleDColumn(1, "PositionY");
	analysisManager->CreateNtupleDColumn(1, "PositionZ");
	analysisManager->CreateNtupleDColumn(1, "Time");
	analysisManager->FinishNtuple(1);

	analysisManager->CreateNtuple("ElectronFirstHits", "ElectronFirstHits");
	analysisManager->CreateNtupleDColumn(2, "PositionX");
	analysisManager->CreateNtupleDColumn(2, "PositionY");
	analysisManager->CreateNtupleDColumn(2, "PositionZ");
	analysisManager->CreateNtupleDColumn(2, "Time");
	analysisManager->CreateNtupleDColumn(2, "MomentumX");
	analysisManager->CreateNtupleDColumn(2, "MomentumY");
	analysisManager->CreateNtupleDColumn(2, "MomentumZ");
	analysisManager->CreateNtupleDColumn(2, "KinectEnergy");
	analysisManager->FinishNtuple(2);

	runStartedTime = time(0);
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
	/*
	G4cout.precision(5);
	G4ParticleDefinition* particle = primary->GetParticleGun()->GetParticleDefinition();
	G4double energy = primary->GetParticleGun()->GetParticleEnergy();
	G4cout << "\nThe run consists of " << aRun->GetNumberOfEvent() << " "
		<< particle->GetParticleName() << " of " << G4BestUnit(energy,"Energy") << " through\n";
	*/

	double elapsedtime = (time(0) - runStartedTime) * s;
	G4cout << "\nRun " << aRun->GetRunID() << " ended within " << G4BestUnit(elapsedtime, "Time") << "\n";
	G4cout << "--------------\n";

	//if has not been any event, do not save histograms
	if (aRun->GetNumberOfEvent() == 0)
		return;

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();

	G4Random::showEngineStatus();
}