#ifndef TrackerHit_hh
#define TrackerHit_hh

#include <G4VHit.hh>
#include <G4ThreeVector.hh>

class TrackerHit : public G4VHit
{
public:
	TrackerHit();
	~TrackerHit();
	void Print();

	void SetEdep(G4double edep) { fEdep = edep; }
	G4double GetEdep() { return fEdep; }

	void SetPosition(G4ThreeVector pos) { fPosition = pos; }
	G4ThreeVector GetPosition() { return fPosition; }

	void SetParticleID(G4int id) { fParticleID = id; }
	G4int GetParticleID() const { return fParticleID; }

	void SetKineticEnergy(G4double kinEnergy) { fKineticEnergy = kinEnergy; }
	G4double GetKineticEnergy() const { return fKineticEnergy; }
	void SetTotalEnergy(G4double totalEnergy) { fTotalEnergy = totalEnergy; }
	G4double GetTotalEnergy() const { return fTotalEnergy; }

	void SetTheta(G4double theta) { fTheta = theta; }
	G4double GetTheta() const { return fTheta; }
	void SetPhi(G4double phi) { fPhi = phi; }
	G4double GetPhi() const { return fPhi; }
	void SetCosTheta(G4double cosTheta) { fCosTheta = cosTheta; }
	G4double GetCosTheta() const { return fCosTheta; }

	void SetMomentum(G4double momentum) { fMomentum = momentum; }
	G4double GetMomentum() const { return fMomentum; }
	void SetPt(G4double pt) { fPt = pt; }
	G4double GetPt() const { return fPt; }
	void SetEta(G4double eta) { fEta = eta; }
	G4double GetEta() const { return fEta; }

private:
	G4double fEdep {0};
	G4ThreeVector fPosition {G4ThreeVector(0, 0, 0)};
	G4int fParticleID {0}; // ID da partícula
	G4double fKineticEnergy {0};
	G4double fTotalEnergy {0};
	G4double fTheta {0};
	G4double fPhi {0};
	G4double fCosTheta {0};
	G4double fMomentum {0};
	G4double fPt {0};
	G4double fEta {0};
};

#include "G4THitsCollection.hh"
typedef G4THitsCollection<TrackerHit> TrackerHitsCollection; 

#endif