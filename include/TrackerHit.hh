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
	void SetTrackerHitEdep(G4double edep) { trackerHitEdep = edep; }
	void SetTrackerHitPosition(G4ThreeVector pos) { trackerHitPosition = pos; }
	void SetTrackerHitTime(G4double time) { trackerHitTime = time; }
	void SetTrackerHitMomentum(G4ThreeVector momentum) { trackerHitMomentum = momentum; }
	void SetTrackerHitKineticEnergy(G4double kinEnergy) { trackerHitKineticEnergy = kinEnergy; }

	G4int         GetTrackerHitParticleID() const { return trackerHitparticleID; }
	G4double      GetTrackerHitEdep() const { return trackerHitEdep; }
	G4ThreeVector GetTrackerHitPosition() const { return trackerHitPosition; }
	G4double      GetTrackerHitTime() const { return trackerHitTime; }
	G4ThreeVector GetTrackerHitMomentum() const { return trackerHitMomentum; }
	G4double      GetTrackerHitKineticEnergy() const { return trackerHitKineticEnergy; }

private:
	G4int         trackerHitparticleID    {0};
	G4double      trackerHitEdep          {0.};
	G4ThreeVector trackerHitPosition      {G4ThreeVector(0., 0., 0.)};
	G4double      trackerHitTime          {0.};
	G4ThreeVector trackerHitMomentum      {G4ThreeVector(0., 0., 0.)};
	G4double      trackerHitKineticEnergy {0.};
};

#include "G4THitsCollection.hh"
typedef G4THitsCollection<TrackerHit> TrackerHitsCollection;

#endif