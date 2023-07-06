#include "HistoMessenger.hh"

#include <sstream>

#include "HistoManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"

HistoMessenger::HistoMessenger(HistoManager* manager) : histoManager(manager)
{

}

HistoMessenger::~HistoMessenger()
{

}

void HistoMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{
	
}