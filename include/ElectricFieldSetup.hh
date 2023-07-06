#ifndef ElectricFieldSetup_hh
#define ElectricFieldSetup_hh

#include "G4ElectricField.hh"
#include "G4UniformElectricField.hh"

#include "G4SystemOfUnits.hh"

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

class G4FieldManager;
class G4ChordFinder;
class G4EquationOfMotion;
class G4Mag_EqRhs;
class G4EqMagElectricField;
class G4MagIntegratorStepper;
class G4MagInt_Driver;
class FieldMessenger;
class ElectricFieldSetup
{
public:
	ElectricFieldSetup(G4ThreeVector);
	ElectricFieldSetup();
	// The value of the field
	// A zero field
	~ElectricFieldSetup();
	void SetStepperType (G4int i) { fStepperType = i; }
	void SetStepper();
	void SetMinStep(G4double s) { fMinStep = s; }
	void UpdateField();
	void SetFieldValue(G4ThreeVector fieldVector);
	void SetFieldValue(G4double fieldValue);
	G4ThreeVector GetConstantFieldValue();
protected:
	// Find the global Field Manager
	G4FieldManager* GetGlobalFieldManager() ;
private:
	G4FieldManager         *fFieldManager;
	G4ChordFinder          *fChordFinder ;
	G4EqMagElectricField   *fEquation ;
	G4ElectricField        *fEMfield;
	G4ThreeVector           fElFieldValue ;
	G4MagIntegratorStepper *fStepper;
	G4MagInt_Driver        *fIntgrDriver;
	G4int                   fStepperType;
	G4double                fMinStep;
	FieldMessenger*         fFieldMessenger;
};
#endif