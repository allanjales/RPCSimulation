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

RunAction::RunAction(DetectorConstruction* det, 
	PrimaryGeneratorAction* prim, HistoManager* histo)
: detector(det), primary(prim), ProcCounter(0), histoManager(histo)
{
	totalEventCount = 0;
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
	G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

	if (ProcCounter) delete ProcCounter;
	ProcCounter = new ProcessesCount;
	totalEventCount = 0;
	photonStats.Clear();
	electronStats.Clear();
	positronStats.Clear();

	std::stringstream strRunID;
	strRunID << aRun->GetRunID();
	histoManager->Book("output_" + strRunID.str());
}

void RunAction::FillData(const G4String & particleName, 
	G4double kinEnergy, G4double costheta, G4double phi, 
	G4double longitudinalPolarization)
{
	if (particleName == "gamma")
		photonStats.FillData(kinEnergy, costheta, longitudinalPolarization);
	else if (particleName == "e-")
		electronStats.FillData(kinEnergy, costheta, longitudinalPolarization);
	else if (particleName == "e+")
		positronStats.FillData(kinEnergy, costheta, longitudinalPolarization);
}

void RunAction::CountProcesses(G4String procName)
{
	size_t nbProc = ProcCounter->size();
	size_t i = 0;
	while ((i<nbProc)&&((*ProcCounter)[i]->GetName()!=procName)) i++;
	if (i == nbProc) ProcCounter->push_back( new OneProcessCount(procName));
	(*ProcCounter)[i]->Count();
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
	G4int NbOfEvents = aRun->GetNumberOfEvent();
	if (NbOfEvents == 0) return;
	
	G4int prec = G4cout.precision(5);
	
	G4ParticleDefinition* particle = primary->GetParticleGun()->GetParticleDefinition();
	G4String Particle = particle->GetParticleName();
	G4double energy = primary->GetParticleGun()->GetParticleEnergy();
	G4cout << "\n The run consists of " << NbOfEvents << " "<< Particle << " of " 
		<< G4BestUnit(energy,"Energy") << " through " << G4endl;

	G4cout << "\n Process calls frequency --->\n";
	for (size_t i = 0; i < ProcCounter->size(); i++)
	{
		G4String procName = (*ProcCounter)[i]->GetName();
		G4int    count    = (*ProcCounter)[i]->GetCounter();
		G4cout << "\t" << procName << " = " << count<<"\n";
	}

	if (totalEventCount == 0) return;

	G4cout << " Gamma: \n";
	photonStats.PrintResults(totalEventCount);
	G4cout << " Electron: \n";
	electronStats.PrintResults(totalEventCount);
	G4cout << " Positron: \n";
	positronStats.PrintResults(totalEventCount);

	G4cout.precision(prec);

	histoManager->Save();

	CLHEP::HepRandom::showEngineStatus();
}

void RunAction::EventFinished()
{
	++totalEventCount;
	photonStats.EventFinished();
	electronStats.EventFinished();
	positronStats.EventFinished();
}

RunAction::ParticleStatistics::ParticleStatistics()
	: currentNumber(0), totalNumber(0), totalNumber2(0),
	sumEnergy(0), sumEnergy2(0), sumPolarization(0),
	sumPolarization2(0), sumCosTheta(0), sumCosTheta2(0)
{}

RunAction::ParticleStatistics::~ParticleStatistics()
{}

void RunAction::ParticleStatistics::EventFinished()
{
	totalNumber += currentNumber;
	totalNumber2 += currentNumber*currentNumber;
	currentNumber = 0;
}

void RunAction::ParticleStatistics::FillData(G4double kinEnergy, 
	G4double costheta, G4double longitudinalPolarization)
{
	++currentNumber;
	sumEnergy+=kinEnergy;
	sumEnergy2+=kinEnergy*kinEnergy;
	sumPolarization+=longitudinalPolarization;
	sumPolarization2+=longitudinalPolarization*longitudinalPolarization;
	sumCosTheta+=costheta;
	sumCosTheta2+=costheta*costheta;
}

void RunAction::ParticleStatistics::PrintResults(G4int totalNumberOfEvents)
{
	G4cout << "Mean Number per Event :" << 
		G4double(totalNumber)/G4double(totalNumberOfEvents)<<"\n";
	
	if (totalNumber==0) totalNumber=1;
	G4double energyMean=sumEnergy/totalNumber;
	G4double energyRms=std::sqrt(sumEnergy2/totalNumber-energyMean*energyMean);
	G4cout << "Mean Energy :" << G4BestUnit(energyMean,"Energy")
		<< " +- " << G4BestUnit(energyRms,"Energy") << "\n";
	G4double polarizationMean = sumPolarization/totalNumber;
	G4double polarizationRms =
		std::sqrt(sumPolarization2/totalNumber-polarizationMean*polarizationMean);
	G4cout << "Mean Polarization :" << polarizationMean
		<< " +- " << polarizationRms << "\n";
}

void RunAction::ParticleStatistics::Clear()
{
	currentNumber=0;
	totalNumber=totalNumber2=0;
	sumEnergy=sumEnergy2=0;
	sumPolarization=sumPolarization2=0;
	sumCosTheta=sumCosTheta2=0;
}