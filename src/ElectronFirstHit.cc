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
	G4VVisManager* visManager = G4VVisManager::GetConcreteInstance();
	if (!visManager)
		return;
	
	G4Circle circle(ElectronFirstHitPosition);
	circle.SetScreenSize(4.);
	circle.SetFillStyle(G4Circle::filled);
	G4Colour colour(.9, .5, .2);
	//G4Colour colour(.4, .7, .3);
	G4VisAttributes attributes(colour);
	circle.SetVisAttributes(attributes);
	visManager->Draw(circle);
}