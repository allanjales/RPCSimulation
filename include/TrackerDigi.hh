#ifndef TrackerDigi_hh
#define TrackerDigi_hh

#include <G4VDigi.hh>
#include <G4ThreeVector.hh>
#include <G4TDigiCollection.hh>
#include <G4Allocator.hh>

class TrackerDigi : public G4VDigi
{
public:
    TrackerDigi();
    ~TrackerDigi();
    
    void Print() override;
    void Draw() override;

    void SetEdep(G4double edep) { fEdep = edep; }
    G4double GetEdep() const { return fEdep; }

    void SetPosition(G4ThreeVector pos) { fPosition = pos; }
    G4ThreeVector GetPosition() const { return fPosition; }

	void SetTrackerDigiTime(G4double time) { trackerDigiTime = time; }
	G4double TrackerDigiTime() const { return trackerDigiTime; }

private:
    G4double fEdep {0.};
    G4ThreeVector fPosition {G4ThreeVector(0., 0., 0.)};
    G4double trackerDigiTime {0.};
};

typedef G4TDigiCollection<TrackerDigi> TrackerDigiCollection;

#endif