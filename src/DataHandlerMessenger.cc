#include "DataHandlerMessenger.hh"
#include "DataHandler.hh"

DataHandlerMessenger::DataHandlerMessenger(DataHandler* dataHandler)
: dataHandler(dataHandler)
{}

DataHandlerMessenger::~DataHandlerMessenger()
{}

void DataHandlerMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{}