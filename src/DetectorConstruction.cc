#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{
	detectorConstructionMessenger = new DetectorConstructionMessenger(this);

	dataHandler = new DataHandler();
	sensitiveDetector = new SensitiveDetector("SensitiveDetector", dataHandler);

	// Step Limiter for each material
	WorldUserLimits        = new G4UserLimits();
	PolyethyleneUserLimits = new G4UserLimits();
	GraphiteUserLimits     = new G4UserLimits();
	BakeliteUserLimits     = new G4UserLimits();
	GasUserLimits          = new G4UserLimits();
	AluminiumUserLimits    = new G4UserLimits();
}

DetectorConstruction::~DetectorConstruction()
{
	delete WorldUserLimits;
	delete BakeliteUserLimits;
	delete GraphiteUserLimits;
	delete PolyethyleneUserLimits;
	delete GasUserLimits;
	delete AluminiumUserLimits;

	delete detectorConstructionMessenger;

	delete sensitiveDetector;
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
	// ----------------
	// Materials
	// ----------------

	G4NistManager* nist = G4NistManager::Instance();

	G4Element* H = nist->FindOrBuildElement("H");
	G4Element* C = nist->FindOrBuildElement("C");
	G4Element* F = nist->FindOrBuildElement("F");
	G4Element* S = nist->FindOrBuildElement("S");
	G4Element* O = nist->FindOrBuildElement("O");

	// C2H2F4 Gas

	C2H2F4Material = new G4Material("C2H2F4", 4.25*kg/m3, 3, kStateGas, 295.*kelvin, 0.00168*bar);
	C2H2F4Material->AddElement(C, 2);
	C2H2F4Material->AddElement(H, 2);
	C2H2F4Material->AddElement(F, 4);

	// SF6 Gas

	SF6Material = new G4Material("SF6", 6.17*kg/m3, 2, kStateGas, 295.*kelvin, 0.00168*bar);
	SF6Material->AddElement(S, 1);
	SF6Material->AddElement(F, 6);

	// SF6 Gas

	CO2Material = new G4Material("CO2", 1.98*kg/m3, 2, kStateGas, 295.*kelvin, 0.00168*bar);
	CO2Material->AddElement(C, 1);
	CO2Material->AddElement(O, 2);


	// Aluminium Plate

	G4Material* AluminiumMaterial = nist->FindOrBuildMaterial("G4_Al");


	// Vacuum, Bakelite, Graphyte, Polyethylene

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
	WorldLogicalVolume->SetUserLimits(WorldUserLimits);

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
	BakeliteLogicalVolume->SetUserLimits(BakeliteUserLimits);


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
	GraphiteLogicalVolume->SetUserLimits(GraphiteUserLimits);


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
	PolyethyleneLogicalVolume->SetUserLimits(PolyethyleneUserLimits);


	// Gas

	auto GasSolidVolume = new G4Box("GasSolidVolume", 15.0*cm, 15.0*cm, 1.*mm);
	GasLogicalVolume = new G4LogicalVolume(GasSolidVolume, C2H2F4Material, "GasLogicalVolume", 0, 0, 0);
	{
		auto attr = new G4VisAttributes(G4Colour(0.,1.,1.));
		attr->SetForceWireframe();
		GasLogicalVolume->SetVisAttributes(attr);
	}
	GasPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), GasLogicalVolume,
		"GasPhysicalVolume", WorldLogicalVolume, false, 0);
	GasLogicalVolume->SetUserLimits(GasUserLimits);
	GasLogicalVolume->SetMaterial(C2H2F4Material);


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
	AluminiumLogicalVolume->SetUserLimits(AluminiumUserLimits);

	return WorldPhysicalVolume;
}

void DetectorConstruction::ConstructSDandField()
{
	ConstructElectricField();
	ConstructSensitiveDetector();
}

void DetectorConstruction::ConstructElectricField()
{
	// Set global eletric field
	G4UniformElectricField* globalField = new G4UniformElectricField(G4ThreeVector(0., 0., 0.*kilovolt/mm));
	G4FieldManager* globalFieldManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	globalFieldManager->SetDetectorField(globalField);
	CreateChordFinder(globalFieldManager, globalField);

	// Set local eletric field
	G4UniformElectricField* localField = new G4UniformElectricField(G4ThreeVector(0., 0., -4.5*kilovolt/mm));
	G4FieldManager* localFieldManager = new G4FieldManager();
	localFieldManager->SetDetectorField(localField);
	CreateChordFinder(localFieldManager, localField);

	// Set which parts will have eletric field
	GasLogicalVolume->SetFieldManager(localFieldManager, true);
}

void DetectorConstruction::CreateChordFinder(G4FieldManager* fieldManager, G4ElectricField* field)
{
	auto globalFieldEq = new G4EqMagElectricField(field);

	auto stepper = new G4ClassicalRK4(globalFieldEq, 8);
	G4cout << "G4ClassicalRK4 (default) is called" << G4endl;

	float minStep  = 0.02/1000*mm;
	G4cout << "The minimal step in integral is equal to " << G4BestUnit(minStep, "Length") << G4endl;
	//auto intgrDriver = new G4IntegrationDriver<G4ClassicalRK4>(minStep, stepper, stepper->GetNumberOfVariables());
	auto intgrDriver = new G4MagInt_Driver(minStep, stepper, stepper->GetNumberOfVariables());
	auto chordFinder = new G4ChordFinder(intgrDriver);
	chordFinder->SetDeltaChord(minStep);
	fieldManager->SetChordFinder(chordFinder);
}

void DetectorConstruction::ConstructSensitiveDetector()
{
	GasLogicalVolume->SetSensitiveDetector(sensitiveDetector);
}

void DetectorConstruction::SetGasMaterial(G4Material* material)
{
	GasLogicalVolume->SetMaterial(material);
	G4cout << "Gas material set to " + material->GetName() + "\n";
}