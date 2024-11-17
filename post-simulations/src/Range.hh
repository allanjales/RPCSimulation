#ifndef Range_hh
#define Range_hh

class Range
{
private:
	double min = 0.;
	double max = 0.;
	bool areMinMaxSet = false;
	
	void SetRangeValues(double min, double max)
	{
		this->min = min;
		this->max = max;
		areMinMaxSet = true;
	}

public:

	void UpdateRangeValues(double value)
	{
		if (!areMinMaxSet)
		{
			SetRangeValues(value, value);
			return;
		}

		if (value < min)
			min = value;
		if (value > max)
			max = value;
	}

	double GetMin() const
	{
		return min;
	}

	double GetMax() const
	{
		return max;
	}
};

#endif