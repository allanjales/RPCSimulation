#include "TrackerDigi.hh"

TrackerDigi::TrackerDigi()
{}

TrackerDigi::~TrackerDigi()
{}

void TrackerDigi::Print()
{
	G4cout
		<< " Edep: " << std::setw(7) << G4BestUnit(trackerDigiEdep, "Energy")
		<< " Time: " << std::setw(7) << G4BestUnit(trackerDigiTime, "Time")
		<< "\n Position: (" << std::setw(7) << G4BestUnit(trackerDigiPosition.x(), "Length") << ","
		<< std::setw(7) << G4BestUnit(trackerDigiPosition.y(), "Length") << ","
		<< std::setw(7) << G4BestUnit(trackerDigiPosition.z(), "Length") << ")"
		<< G4endl;
}

void TrackerDigi::Draw()
{}