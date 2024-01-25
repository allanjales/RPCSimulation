#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4GenericMessenger.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"

// Field
#include <G4UnitsTable.hh>

// Ainda olhar qual excluir
#include "G4UniformElectricField.hh"
#include "G4UniformMagField.hh"
#include "G4MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4EquationOfMotion.hh"
#include "G4EqMagElectricField.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4ChordFinder.hh"
#include "G4ExplicitEuler.hh"
#include "G4ImplicitEuler.hh"
#include "G4SimpleRunge.hh"
#include "G4SimpleHeum.hh"
#include "G4ClassicalRK4.hh"
#include "G4HelixExplicitEuler.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4HelixSimpleRunge.hh"
#include "G4CashKarpRKF45.hh"
#include "G4RKG3_Stepper.hh"

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
	
	void ConstructSDandField();

	//void SetMagField(G4double);
	const G4VPhysicalVolume* GetWorld() {return WorldPhysicalVolume;};
	const G4VPhysicalVolume* GetGasRPC() {return C2H2F4PhysicalVolume;};

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

	//ElectricFieldSetup *fieldSetup;
	DetectorMessenger  *detectorMessenger;

	void CreateChordFinder(G4FieldManager*, G4ElectricField*);
};

#endif