#include "ElectronFirstHit.hh"

ElectronFirstHit::ElectronFirstHit()
{}

ElectronFirstHit::~ElectronFirstHit()
{}

void ElectronFirstHit::Print()
{
	G4cout
		<< " Time: " << std::setw(7) << G4BestUnit(ElectronFirstHitTime, "Time")
		<< " Kinetic Energy: " << std::setw(7) << G4BestUnit(ElectronFirstHitKineticEnergy, "Energy")
		<< "\n Position: (" << std::setw(7) << G4BestUnit(ElectronFirstHitPosition.x(), "Length") << ","
		<< std::setw(7) << G4BestUnit(ElectronFirstHitPosition.y(), "Length") << ","
		<< std::setw(7) << G4BestUnit(ElectronFirstHitPosition.z(), "Length") << ")"
		<< "\n Momentum: (" << std::setw(7) << G4BestUnit(ElectronFirstHitMomentum.x(), "Momentum") << ","
		<< std::setw(7) << G4BestUnit(ElectronFirstHitMomentum.y(), "Momentum") << ","
		<< std::setw(7) << G4BestUnit(ElectronFirstHitMomentum.z(), "Momentum") << ")"
		<< G4endl;
}

void ElectronFirstHit::Draw()
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