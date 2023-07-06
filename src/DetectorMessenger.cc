#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* Detector)
: fDetector(Detector)
{}

DetectorMessenger::~DetectorMessenger()
{}

void DetectorMessenger::SetNewValue(G4UIcommand*, G4String)
{}