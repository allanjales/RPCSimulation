#ifndef HISTOMANAGER_HH
#define HISTOMANAGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class HistoManager;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

class HistoMessenger: public G4UImessenger {
public:
	HistoMessenger(HistoManager* );
	~HistoMessenger();

	void SetNewValue(G4UIcommand* ,G4String );

private:

	HistoManager* histoManager;

	G4UIdirectory*        histoDir;
	G4UIcmdWithAString*   factoryCmd;
	G4UIcmdWithAString*   typeCmd;
	G4UIcmdWithAString*   optionCmd;
	G4UIcommand*          histoCmd;
	G4UIcmdWithAnInteger* rmhistoCmd;
};

#endif