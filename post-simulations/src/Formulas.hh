#ifndef Formulas_hh
#define Formulas_hh

#include <cmath>

class Formulas
{
public:
	static double GetTheta(double x, double y, double z)
	{
		return acos(z / sqrt(x*x + y*y + z*z));
	}

	static double GetPhi(double x, double y)
	{
		return atan2(y, x);
	}

	static double GetMomentum(double px, double py, double pz)
	{
		return sqrt(px*px + py*py + pz*pz);
	}

	static double GetPt(double px, double py)
	{
		return sqrt(px*px + py*py);
	}

	static double GetEta(double pz, double p, double theta)
	{
		return 0.5 * log((p + pz) / (p - pz));
	}
};

#endif