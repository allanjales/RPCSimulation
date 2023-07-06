#include "ElectricFieldSetup.hh"

ElectricFieldSetup::ElectricFieldSetup()
: fChordFinder(), fStepper(), fIntgrDriver()
{
	fEMfield = new G4UniformElectricField(G4ThreeVector(0., 0., -4.5*kilovolt/mm));
	//fFieldMessenger = new FieldMessenger(this) ;
	fEquation = new G4EqMagElectricField(fEMfield);
	fMinStep = 0.01*mm;
	fStepperType = 4; // ClassicalRK4, the default stepper
	fFieldManager = GetGlobalFieldManager();
	UpdateField();
}

ElectricFieldSetup::ElectricFieldSetup(G4ThreeVector pFV)
: fChordFinder(), fStepper(), fIntgrDriver()
{
	fEMfield = new G4UniformElectricField(pFV);
	// GetGlobalFieldManager()->CreateChordFinder(this);
	//fFieldMessenger = new FieldMessenger(this) ;
	fEquation = new G4EqMagElectricField(fEMfield);
	fMinStep = 0.01*mm;
	fStepperType = 4; // ClassicalRK4, the default stepper
	fFieldManager = GetGlobalFieldManager();
	UpdateField();
}

ElectricFieldSetup::~ElectricFieldSetup()
{
	if(fChordFinder)
		delete fChordFinder;
	if(fStepper)
		delete fStepper;
	if(fEquation)
		delete fEquation;
	if(fEMfield)
		delete fEMfield;
}

void ElectricFieldSetup::UpdateField()
{
	SetStepper();
	G4cout << "The minimal step is equal to " << fMinStep/mm << " mm" << G4endl;
	
	fFieldManager->SetDetectorField(fEMfield);
	
	if(fChordFinder)
		delete fChordFinder;
	// fChordFinder = new G4ChordFinder(fEMfield, fMinStep, fStepper);
	
	fIntgrDriver = new G4MagInt_Driver(fMinStep, fStepper, fStepper->GetNumberOfVariables());
	fChordFinder = new G4ChordFinder(fIntgrDriver);

	fFieldManager->SetChordFinder(fChordFinder);
}

void ElectricFieldSetup::SetStepper()
{
	G4int nvar = 8;
	if(fStepper)
		delete fStepper;
	
	switch (fStepperType)
	{
		case 0:
			fStepper = new G4ExplicitEuler(fEquation, nvar);
			G4cout << "G4ExplicitEuler is called" << G4endl;
			break;
		case 1:
			fStepper = new G4ImplicitEuler(fEquation, nvar);
			G4cout << "G4ImplicitEuler is called" << G4endl;
			break;
		case 2:
			fStepper = new G4SimpleRunge(fEquation, nvar);
			G4cout << "G4SimpleRunge is called" << G4endl;
			break;
		case 3:
			fStepper = new G4SimpleHeum(fEquation, nvar);
			G4cout << "G4SimpleHeum is called" << G4endl;
			break;
		case 4:
			fStepper = new G4ClassicalRK4(fEquation, nvar);
			G4cout << "G4ClassicalRK4 (default) is called" << G4endl;
			break;
		case 5:
			fStepper = new G4CashKarpRKF45(fEquation, nvar);
			G4cout << "G4CashKarpRKF45 is called" << G4endl;
			break;
		case 6:
			fStepper = 0;
			//new G4RKG3_Stepper(fEquation, nvar);
			G4cout << "G4RKG3_Stepper is not currently working for Electric Field" << G4endl;
			break;
		case 7:
			fStepper = 0;
			//new G4HelixExplicitEuler(fEquation);
			G4cout << "G4HelixExplicitEuler is not valid for Electric Field" << G4endl;
			break;
		case 8:
			fStepper = 0;
			//new G4HelixImplicitEuler(fEquation);
			G4cout << "G4HelixImplicitEuler is not valid for Electric Field" << G4endl;
			break;
		case 9:
			fStepper = 0;
			//new G4HelixSimpleRunge( fEquation );
			G4cout << "G4HelixSimpleRunge is not valid for Electric Field" << G4endl;
			break;
		default:
			fStepper = 0;
	}
}

void ElectricFieldSetup::SetFieldValue(G4double fieldValue)
{
	G4ThreeVector fieldVector(0., 0., 0.);
	SetFieldValue(fieldVector);
}

void ElectricFieldSetup::SetFieldValue(G4ThreeVector fieldVector)
{
	// Find the Field Manager for the global field
	G4FieldManager* fieldMgr = GetGlobalFieldManager();

	if(fieldVector != G4ThreeVector(0.,0.,0.))
	{
		if(fEMfield)
			delete fEMfield;
		fEMfield = new G4UniformElectricField(fieldVector);
	
		fEquation->SetFieldObj(fEMfield);
		// UpdateField();
		fieldMgr->SetDetectorField(fEMfield);
	}
	else
	{
		// If the new field's value is Zero, then it is best to
		// insure that it is not used for propagation.
		if(fEMfield)
			delete fEMfield;
		fEMfield = 0;
		fEquation->SetFieldObj(fEMfield);
	}
}

G4FieldManager* ElectricFieldSetup::GetGlobalFieldManager()
{
	return G4TransportationManager::GetTransportationManager()->GetFieldManager();
}