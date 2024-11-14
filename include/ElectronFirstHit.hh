#ifndef ElectronFirstHit_hh
#define ElectronFirstHit_hh

#include <G4VHit.hh>
#include <G4ThreeVector.hh>
#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4VisAttributes.hh>

class ElectronFirstHit : public G4VHit
{
public:
	ElectronFirstHit();
	~ElectronFirstHit();
	
	void Print() override;
	void Draw() override;

	void SetElectronFirstHitPosition(G4ThreeVector pos) { ElectronFirstHitPosition = pos; }
	void SetElectronFirstHitTime(G4double time) { ElectronFirstHitTime = time; }
	void SetElectronFirstHitMomentum(G4ThreeVector momentum) { ElectronFirstHitMomentum = momentum; }
	void SetElectronFirstHitKineticEnergy(G4double kinEnergy) { ElectronFirstHitKineticEnergy = kinEnergy; }

	G4ThreeVector GetElectronFirstHitPosition() { return ElectronFirstHitPosition; }
	G4double      GetElectronFirstHitTime() const { return ElectronFirstHitTime; }
	G4ThreeVector GetElectronFirstHitMomentum() const { return ElectronFirstHitMomentum; }
	G4double      GetElectronFirstHitKineticEnergy() const { return ElectronFirstHitKineticEnergy; }

private:
	G4ThreeVector ElectronFirstHitPosition      {G4ThreeVector(0., 0., 0.)};
	G4double      ElectronFirstHitTime          {0.};
	G4ThreeVector ElectronFirstHitMomentum      {G4ThreeVector(0., 0., 0.)};
	G4double      ElectronFirstHitKineticEnergy {0.};
};

#include "G4THitsCollection.hh"
typedef G4THitsCollection<ElectronFirstHit> ElectronFirstHitsCollection;

#endif