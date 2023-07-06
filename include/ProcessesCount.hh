#ifndef ProcessesCount_HH
#define ProcessesCount_HH

#include "globals.hh"
#include <vector>

class OneProcessCount
{
public:
	OneProcessCount(G4String name) {Name=name; Counter=0;};
	~OneProcessCount() {};
public:
	G4String GetName()    {return Name;};
	G4int    GetCounter() {return Counter;};
	void     Count()      {Counter++;};

private:
	G4String Name;
	G4int    Counter;
};

typedef std::vector<OneProcessCount*> ProcessesCount;

#endif