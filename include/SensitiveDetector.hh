#ifndef SensitiveDetector_hh
#define SensitiveDetector_hh

#include "G4VSensitiveDetector.hh"
#include "DataHandler.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
public:
	SensitiveDetector(G4String, DataHandler*);
	~SensitiveDetector();
private:
    DataHandler *dataHandler;
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};

#endif