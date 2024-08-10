#ifndef DataHandlerMessenger_hh
#define DataHandlerMessenger_hh

#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>

class DataHandler;
class DataHandlerMessenger: public G4UImessenger
{
public:
	DataHandlerMessenger(DataHandler*);
	~DataHandlerMessenger();

	void SetNewValue(G4UIcommand* ,G4String );

private:
	DataHandler* dataHandler;
};

#endif