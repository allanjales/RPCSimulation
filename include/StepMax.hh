#ifndef StepMax_hh
#define StepMax_hh

#include "globals.hh"
#include "G4VDiscreteProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"

class StepMaxMessenger;

class StepMax : public G4VDiscreteProcess
{
public:
	StepMax(const G4String& processName ="stepMax");
	~StepMax();
	
	G4bool IsApplicable(const G4ParticleDefinition&);
	void SetMaxStep(G4double);
	G4double GetMaxStep() {return MaxChargedStep;};

	G4double PostStepGetPhysicalInteractionLength( const G4Track& track,
		G4double previousStepSize, G4ForceCondition* condition);
	
	G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);

	G4double GetMeanFreePath(const G4Track&, G4double, G4ForceCondition*)
		{return 0.;};

private:
	G4double MaxChargedStep;
	StepMaxMessenger* pMess;
};

#endif