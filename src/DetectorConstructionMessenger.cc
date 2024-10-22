#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"

DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* detector)
: detector(detector)
{
	stepDir = new G4UIdirectory("/RPCSim/maxStepLength/");
	stepDir ->SetGuidance("Step control");

	worldMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/world", this);
	worldMaxStepLengthcmd->SetGuidance("Sets the max step length in the world");
	worldMaxStepLengthcmd->SetParameterName("length", false);
	worldMaxStepLengthcmd->SetRange("length>0");
	worldMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	polyethyleneMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/polyethylene", this);
	polyethyleneMaxStepLengthcmd->SetGuidance("Sets the max step length in the polyethylene material");
	polyethyleneMaxStepLengthcmd->SetParameterName("length", false);
	polyethyleneMaxStepLengthcmd->SetRange("length>0");
	polyethyleneMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	graphiteMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/graphite", this);
	graphiteMaxStepLengthcmd->SetGuidance("Sets the max step length in the graphite material");
	graphiteMaxStepLengthcmd->SetParameterName("length", false);
	graphiteMaxStepLengthcmd->SetRange("length>0");
	graphiteMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	bakeliteMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/bakelite", this);
	bakeliteMaxStepLengthcmd->SetGuidance("Sets the max step length in the bakelite material");
	bakeliteMaxStepLengthcmd->SetParameterName("length", false);
	bakeliteMaxStepLengthcmd->SetRange("length>0");
	bakeliteMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	gasMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/gas", this);
	gasMaxStepLengthcmd->SetGuidance("Sets the max step length in the gas material");
	gasMaxStepLengthcmd->SetParameterName("length", false);
	gasMaxStepLengthcmd->SetRange("length>0");
	gasMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	aluminiumMaxStepLengthcmd = new G4UIcmdWithADoubleAndUnit("/RPCSim/maxStepLength/aluminium", this);
	aluminiumMaxStepLengthcmd->SetGuidance("Sets the max step length in the aluminium material");
	aluminiumMaxStepLengthcmd->SetParameterName("length", false);
	aluminiumMaxStepLengthcmd->SetRange("length>0");
	aluminiumMaxStepLengthcmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	gasMaterialcmd = new G4UIcmdWithAString("/RPCSim/gasMaterial", this);
	gasMaterialcmd->SetGuidance("Sets the gas material based on the NIST database or C2H2F4, SF6, CO2");
	gasMaterialcmd->SetParameterName("materialName", false);
	gasMaterialcmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

DetectorConstructionMessenger::~DetectorConstructionMessenger()
{
	delete worldMaxStepLengthcmd;
	delete bakeliteMaxStepLengthcmd;
	delete graphiteMaxStepLengthcmd;
	delete polyethyleneMaxStepLengthcmd;
	delete gasMaxStepLengthcmd;
	delete aluminiumMaxStepLengthcmd;
	
	delete stepDir;
}

void DetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if (command == worldMaxStepLengthcmd)
	{
		G4double maxStepLength = worldMaxStepLengthcmd->GetNewDoubleValue(newValue);
		detector->WorldUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the world        set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
	else if (command == polyethyleneMaxStepLengthcmd)
	{
		G4double maxStepLength = polyethyleneMaxStepLengthcmd->GetNewDoubleValue(newValue);
		detector->PolyethyleneUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the polyethylene set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
	else if (command == graphiteMaxStepLengthcmd)
	{
		G4double maxStepLength = graphiteMaxStepLengthcmd->GetNewDoubleValue(newValue);
		detector->GraphiteUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the graphite     set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
	else if (command == bakeliteMaxStepLengthcmd)
	{
		G4double maxStepLength = bakeliteMaxStepLengthcmd->GetNewDoubleValue(newValue);
		detector->BakeliteUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the bakelite     set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
	else if (command == gasMaxStepLengthcmd)
	{
		G4double maxStepLength = gasMaxStepLengthcmd->GetNewDoubleValue(newValue);
		detector->GasUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the gas          set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
	else if (command == aluminiumMaxStepLengthcmd)
	{
		G4double maxStepLength = aluminiumMaxStepLengthcmd->GetNewDoubleValue(newValue);
		detector->AluminiumUserLimits->SetMaxAllowedStep(maxStepLength);
		G4cout << "Max step length in the aluminium    set to " << G4BestUnit(maxStepLength, "Length") << "\n";
	}
	else if (command == gasMaterialcmd)
	{
		G4String materialName = newValue;
		if (materialName == "C2H2F4")
		{
			detector->SetGasMaterial(detector->C2H2F4Material);
		}
		else if (materialName == "SF6")
		{
			detector->SetGasMaterial(detector->SF6Material);
		}
		else if (materialName == "CO2")
		{
			detector->SetGasMaterial(detector->CO2Material);
		}
		else if (materialName == "iC4H10")
		{
			detector->SetGasMaterial(detector->iC4H10Material);
		}
		else if (materialName == "CMSMixture")
		{
			detector->SetGasMaterial(detector->CMSMixtureMaterial);
		}
		else
		{
			auto newMaterial =  G4NistManager::Instance()->FindOrBuildMaterial(materialName);
			detector->SetGasMaterial(newMaterial);
		}
	}
}