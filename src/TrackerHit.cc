#include "TrackerHit.hh"

TrackerHit::TrackerHit()
{}

TrackerHit::~TrackerHit()
{}

void TrackerHit::Print()
{
	G4cout
		<< " Particle ID: " << trackerHitparticleID
		<< " Edep: " << std::setw(7) << G4BestUnit(trackerHitEdep, "Energy")
		<< " Time: " << std::setw(7) << G4BestUnit(trackerHitTime, "Time")
		<< " Kinetic Energy: " << std::setw(7) << G4BestUnit(trackerHitKineticEnergy, "Energy")
		<< "\n Position: (" << std::setw(7) << G4BestUnit(trackerHitPosition.x(), "Length") << ","
		<< std::setw(7) << G4BestUnit(trackerHitPosition.y(), "Length") << ","
		<< std::setw(7) << G4BestUnit(trackerHitPosition.z(), "Length") << ")"
		<< "\n Momentum: (" << std::setw(7) << G4BestUnit(trackerHitMomentum.x(), "Momentum") << ","
		<< std::setw(7) << G4BestUnit(trackerHitMomentum.y(), "Momentum") << ","
		<< std::setw(7) << G4BestUnit(trackerHitMomentum.z(), "Momentum") << ")"
		<< G4endl;
}

void TrackerHit::Draw()
{
	// G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	// if(pVVisManager)
	// {
	// 	G4Circle circle(fPos);
	// 	circle.SetScreenSize(4.);
	// 	circle.SetFillStyle(G4Circle::filled);
	// 	G4Colour colour(1.,0.,0.);
	// 	G4VisAttributes attribs(colour);
	// 	circle.SetVisAttributes(attribs);
	// 	pVVisManager->Draw(circle);
	// }
}