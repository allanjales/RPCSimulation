#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "ElectricFieldSetup.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4GenericMessenger.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"

/*
#include "G4VUserDetectorConstruction.hh"

//#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"

#include "G4NistManager.hh"

#include "G4FieldManager.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"

#include "G4GeometryManager.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4ios.hh"
*/

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction();

	G4VPhysicalVolume *Construct();

	//void SetMagField(G4double);
	const G4VPhysicalVolume* GetWorld() {return WorldPhysicalVolume;};

private:
	G4LogicalVolume   *WorldLogicalVolume;
	G4VPhysicalVolume *WorldPhysicalVolume;

	G4LogicalVolume   *BakeliteLogicalVolume;
	G4VPhysicalVolume *BakelitePhysicalVolume;

	G4LogicalVolume   *GraphiteLogicalVolume;
	G4VPhysicalVolume *GraphitePhysicalVolume;

	G4LogicalVolume   *PolyethyleneLogicalVolume;
	G4VPhysicalVolume *PolyethylenePhysicalVolume;

	G4LogicalVolume   *C2H2F4LogicalVolume;
	G4VPhysicalVolume *C2H2F4PhysicalVolume;
	
	G4LogicalVolume   *AluminiumLogicalVolume;
	G4VPhysicalVolume *AluminiumPhysicalVolume;

	DetectorMessenger *fDetectorMessenger;

	ElectricFieldSetup *fEmFieldSetup;
	DetectorMessenger  *detectorMessenger;
};

#endif