#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
: WorldLogicalVolume(), BakeliteLogicalVolume(), GraphiteLogicalVolume(),
PolyethyleneLogicalVolume(), C2H2F4LogicalVolume(), AluminiumLogicalVolume(),
WorldPhysicalVolume(), BakelitePhysicalVolume(), GraphitePhysicalVolume(),
PolyethylenePhysicalVolume(), C2H2F4PhysicalVolume(), AluminiumPhysicalVolume(), fEmFieldSetup()
{
	fDetectorMessenger = new DetectorMessenger(this);
	fEmFieldSetup = new ElectricFieldSetup() ;
}

DetectorConstruction::~DetectorConstruction()
{
	delete fDetectorMessenger;
	delete fEmFieldSetup;
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
	// ----------------
	// Materials
	// ----------------

	// C2H2F4 Gas

	G4Element* H = new G4Element("Hydrogen", "H", 1, 1.01*g/mole);
	G4Element* C = new G4Element("Carbon" ,  "C", 6, 12.01*g/mole);
	G4Element* F = new G4Element("Fluor",    "F", 9, 19.00*g/mole);

	G4Material* C2H2F4Material = new G4Material("RpcGas", 4089.26*g/m3, 3, kStateGas, 300.*kelvin, 1.*bar);
	C2H2F4Material->AddElement(C, 2); C2H2F4Material->AddElement(H, 2);
	C2H2F4Material->AddElement(F, 4);


	// Aluminium Plate

	G4Material* AluminiumMaterial = new G4Material("Aluminum", 13, 26.98*g/mole, 2.7*g/cm3);


	// Vacuum, Bakelite, Graphyte, Polyethylene

	G4NistManager* nist = G4NistManager::Instance();
	G4Material* VacuumMaterial = nist->FindOrBuildMaterial("G4_Galactic");
	G4Material* BakeliteMaterial = nist->FindOrBuildMaterial("G4_BAKELITE");
	G4Material* GraphiteMaterial = nist->FindOrBuildMaterial("G4_GRAPHITE");
	G4Material* PolyethyleneMaterial = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

	// ----------------
	// Setup
	// ----------------

	// World

	auto WorldSolidVolume = new G4Box("WorldSolidVolume", 15.5*cm, 15.5*cm, 2.*cm);
	WorldLogicalVolume = new G4LogicalVolume(WorldSolidVolume, VacuumMaterial, "WorldLogicalVolume", 0, 0, 0);
	{
		auto attr = new G4VisAttributes(G4Colour(1.,1.,1.));
		attr->SetForceWireframe();
		WorldLogicalVolume->SetVisAttributes(attr);
	}
	WorldPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(), WorldLogicalVolume, "WorldPhysicalVolume", 0, false, 0);


	// Bakelites

	auto BakeliteSolidVolume = new G4Box("BakeliteSolidVolume", 15.0*cm, 15.0*cm, 1.*mm);
	BakeliteLogicalVolume = new G4LogicalVolume(BakeliteSolidVolume, BakeliteMaterial, "BakeliteLogicalVolume", 0, 0, 0);
	{
		auto attr = new G4VisAttributes(G4Colour(1.,1.,1.));
		attr->SetForceSolid();
		BakeliteLogicalVolume->SetVisAttributes(attr);
	}
	BakelitePhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., -2.*mm), BakeliteLogicalVolume,
		"BakelitePhysicalVolume", WorldLogicalVolume, false, 0);
	BakelitePhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., 2.*mm), BakeliteLogicalVolume,
		"BakelitePhysicalVolume", WorldLogicalVolume, false, 1);


	// Graphite

	auto GraphiteSolidVolume = new G4Box("GraphiteSolidVolume", 15.0*cm, 15.0*cm, .1*mm);
	GraphiteLogicalVolume = new G4LogicalVolume(GraphiteSolidVolume, GraphiteMaterial, "GraphiteLogicalVolume", 0, 0, 0);
	{
		auto attr = new G4VisAttributes(G4Colour(.5,.5,.5));
		attr->SetForceSolid();
		GraphiteLogicalVolume->SetVisAttributes(attr);
	}
	GraphitePhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., -3.1*mm), GraphiteLogicalVolume,
		"GraphitePhysicalVolume", WorldLogicalVolume, false, 0);
	GraphitePhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., 3.1*mm), GraphiteLogicalVolume,
		"GraphitePhysicalVolume", WorldLogicalVolume, false, 1);


	// Polyethylene

	auto PolyethyleneSolidVolume = new G4Box("PolyethyleneSolidVolume", 15.0*cm, 15.0*cm, .1*mm);
	PolyethyleneLogicalVolume = new G4LogicalVolume(PolyethyleneSolidVolume, PolyethyleneMaterial, "PolyethyleneLogicalVolume", 0, 0, 0);
	{
		auto attr = new G4VisAttributes(G4Colour(1.,1.,0.));
		attr->SetForceSolid();
		PolyethyleneLogicalVolume->SetVisAttributes(attr);
	}
	PolyethylenePhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., -3.3*mm), PolyethyleneLogicalVolume,
		"PolyethylenePhysicalVolume", WorldLogicalVolume, false, 0);
	PolyethylenePhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., 3.3*mm), PolyethyleneLogicalVolume,
		"PolyethylenePhysicalVolume", WorldLogicalVolume, false, 1);


	// C2H2F4

	auto C2H2F4SolidVolume = new G4Box("C2H2F4SolidVolume", 15.0*cm, 15.0*cm, 1.*mm);
	C2H2F4LogicalVolume = new G4LogicalVolume(C2H2F4SolidVolume, C2H2F4Material, "C2H2F4LogicalVolume", 0, 0, 0);
	{
		auto attr = new G4VisAttributes(G4Colour(0.,1.,1.));
		attr->SetForceWireframe();
		C2H2F4LogicalVolume->SetVisAttributes(attr);
	}
	C2H2F4PhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), C2H2F4LogicalVolume,
		"C2H2F4PhysicalVolume", WorldLogicalVolume, false, 0);

	G4Region* C2H2F4Region = new G4Region("C2H2F4LogicalVolume");
	C2H2F4LogicalVolume->SetRegion(C2H2F4Region);
	C2H2F4Region->AddRootLogicalVolume(C2H2F4LogicalVolume);


	// Aluminium Plate

	auto AluminiumSolidVolume = new G4Box("AluminiumSolidVolume", 15.0*cm, 15.0*cm, 0.02*mm);
	AluminiumLogicalVolume = new G4LogicalVolume(AluminiumSolidVolume, AluminiumMaterial, "AluminiumLogicalVolume", 0, 0, 0);
	{
		auto attr = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
		attr->SetForceSolid();
		AluminiumLogicalVolume->SetVisAttributes(attr);
	}
	AluminiumPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., -3.42*mm), AluminiumLogicalVolume,
		"AluminiumPhysicalVolume", WorldLogicalVolume, false, 0);

	return WorldPhysicalVolume;
}