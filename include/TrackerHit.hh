#ifndef TrackerHit_hh
#define TrackerHit_hh

#include <G4VHit.hh>

#include <G4ThreeVector.hh>
#include <G4UnitsTable.hh>

class TrackerHit : public G4VHit
{
public:
	TrackerHit();
	~TrackerHit();
	
	void Print() override;
	void Draw() override;

	void SetTrackerHitParticleID(G4int id) { trackerHitparticleID = id; }
	G4int GetTrackerHitParticleID() const { return trackerHitparticleID; }

	void SetTrackerHitEdep(G4double edep) { trackerHitEdep = edep; }
	G4double GetTrackerHitEdep() { return trackerHitEdep; }

	void SetTrackerHitPosition(G4ThreeVector pos) { trackerHitPosition = pos; }
	G4ThreeVector GetPosition() { return trackerHitPosition; }

	void SetTrackerHitTime(G4double time) { trackerHitTime = time; }
	G4double TrackerHitTime() const { return trackerHitTime; }

	void SetTrackerHitMomentum(G4ThreeVector momentum) { trackerHitMomentum = momentum; }
	G4ThreeVector GetTrackerHitMomentum() const { return trackerHitMomentum; }
	
	void SetTrackerHitKineticEnergy(G4double kinEnergy) { trackerHitKineticEnergy = kinEnergy; }
	G4double GetTrackerHitKineticEnergy() const { return trackerHitKineticEnergy; }

private:
	G4int trackerHitparticleID {0};
	G4double trackerHitEdep {0.};
	G4ThreeVector trackerHitPosition {G4ThreeVector(0., 0., 0.)};
	G4double trackerHitTime {0.};
	G4ThreeVector trackerHitMomentum {G4ThreeVector(0., 0., 0.)};
	G4double trackerHitKineticEnergy {0.};
};

#include "G4THitsCollection.hh"
typedef G4THitsCollection<TrackerHit> TrackerHitsCollection;

#endif