#ifndef Digitizer_hh
#define Digitizer_hh

#include <G4VDigitizerModule.hh>
#include <G4DigiManager.hh>
#include <G4TDigiCollection.hh>

#include "TrackerDigi.hh"
#include "TrackerHit.hh"

class Digitizer : public G4VDigitizerModule
{
public:
	Digitizer(G4String);
	~Digitizer();

	void Digitize() override;

private:
    TrackerDigiCollection* fDigiCollection;
};

#endif