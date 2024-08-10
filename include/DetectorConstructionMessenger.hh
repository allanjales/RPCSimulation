#ifndef DetectorConstructionMessenger_hh
#define DetectorConstructionMessenger_hh

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>

#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>

class DetectorConstruction;
class DetectorConstructionMessenger: public G4UImessenger
{
public:
	DetectorConstructionMessenger(DetectorConstruction*);
	~DetectorConstructionMessenger();

	virtual void SetNewValue(G4UIcommand*, G4String);

private:
	DetectorConstruction* detector;

	G4UIdirectory* eventDir;

	G4UIcmdWithADoubleAndUnit* worldMaxStepLengthcmd;
	G4UIcmdWithADoubleAndUnit* polyethyleneMaxStepLengthcmd;
	G4UIcmdWithADoubleAndUnit* graphiteMaxStepLengthcmd;
	G4UIcmdWithADoubleAndUnit* bakeliteMaxStepLengthcmd;
	G4UIcmdWithADoubleAndUnit* gasMaxStepLengthcmd;
	G4UIcmdWithADoubleAndUnit* aluminiumMaxStepLengthcmd;
};

#endif