#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include <G4VUserDetectorConstruction.hh>
#include <globals.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4ElectricField.hh>
#include "DetectorConstructionMessenger.hh"
#include "SensitiveDetector.hh"

#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4VisAttributes.hh>
#include <G4PVPlacement.hh>
#include <G4UniformElectricField.hh>
#include <G4TransportationManager.hh>
#include <G4EqMagElectricField.hh>
#include <G4ClassicalRK4.hh>
#include <G4ChordFinder.hh>

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction();

	G4VPhysicalVolume* Construct();
	
	void ConstructSDandField();

	//const G4VPhysicalVolume* GetWorld() {return WorldPhysicalVolume;};
	//const G4VPhysicalVolume* GetGasRPC() {return GasPhysicalVolume;};
	void SetGasMaterial(G4Material* material);

	G4Material* C2H2F4Material;
	G4Material* SF6Material;
	G4Material* CO2Material;

	G4UserLimits* WorldUserLimits;
	G4UserLimits* BakeliteUserLimits;
	G4UserLimits* GraphiteUserLimits;
	G4UserLimits* PolyethyleneUserLimits;
	G4UserLimits* GasUserLimits;
	G4UserLimits* AluminiumUserLimits;

	DataHandler* dataHandler;
private:
	G4LogicalVolume*   WorldLogicalVolume;
	G4VPhysicalVolume* WorldPhysicalVolume;

	G4LogicalVolume*   BakeliteLogicalVolume;
	G4VPhysicalVolume* BakelitePhysicalVolume;

	G4LogicalVolume*   GraphiteLogicalVolume;
	G4VPhysicalVolume* GraphitePhysicalVolume;

	G4LogicalVolume*   PolyethyleneLogicalVolume;
	G4VPhysicalVolume* PolyethylenePhysicalVolume;

	G4LogicalVolume*   GasLogicalVolume;
	G4VPhysicalVolume* GasPhysicalVolume;
	
	G4LogicalVolume*   AluminiumLogicalVolume;
	G4VPhysicalVolume* AluminiumPhysicalVolume;
	
	DetectorConstructionMessenger* detectorConstructionMessenger;

	SensitiveDetector* sensitiveDetector;

	void ConstructElectricField();
	void CreateChordFinder(G4FieldManager*, G4ElectricField*);
	void ConstructSensitiveDetector();
};

#endif