#ifndef DETECTORMESSENGER_HH
#define DETECTORMESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

class DetectorMessenger: public G4UImessenger
{
public:
	DetectorMessenger(DetectorConstruction* );
	~DetectorMessenger();

	virtual void SetNewValue(G4UIcommand*, G4String);

private:
	DetectorConstruction*      fDetector;

	G4UIdirectory*             eventDir;

	G4UIcmdWithADoubleAndUnit* worldMaxStepLengthcmd;
	G4UIcmdWithADoubleAndUnit* polyethyleneMaxStepLengthcmd;
	G4UIcmdWithADoubleAndUnit* graphiteMaxStepLengthcmd;
	G4UIcmdWithADoubleAndUnit* bakeliteMaxStepLengthcmd;
	G4UIcmdWithADoubleAndUnit* gasMaxStepLengthcmd;
	G4UIcmdWithADoubleAndUnit* aluminiumMaxStepLengthcmd;
};

#endif