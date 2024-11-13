#ifndef TrackerDigi_hh
#define TrackerDigi_hh

#include <G4VDigi.hh>
#include <G4ThreeVector.hh>
#include <G4TDigiCollection.hh>
#include <G4UnitsTable.hh>

class TrackerDigi : public G4VDigi
{
public:
	TrackerDigi();
	~TrackerDigi();
	
	void Print() override;
	void Draw() override;

	void SetTrackerDigiEdep(G4double edep) { trackerDigiEdep = edep; }
	void SetTrackerDigiPosition(G4ThreeVector pos) { trackerDigiPosition = pos; }
	void SetTrackerDigiTime(G4double time) { trackerDigiTime = time; }
	
	G4double      GetTrackerDigiEdep() const { return trackerDigiEdep; }
	G4ThreeVector GetTrackerDigiPosition() const { return trackerDigiPosition; }
	G4double      GetTrackerDigiTime() const { return trackerDigiTime; }

private:
	G4double      trackerDigiEdep     {0.};
	G4ThreeVector trackerDigiPosition {G4ThreeVector(0., 0., 0.)};
	G4double      trackerDigiTime     {0.};
};

typedef G4TDigiCollection<TrackerDigi> TrackerDigiCollection;

#endif