#pragma once
class TrendAnalyse
{
public:
	TrendAnalyse(void);
	~TrendAnalyse(void);

	double level_1;
	double level_2;
	double level_3;
	double level_4;
	double level_5;
	int ComputePeriod(unsigned int appdistri[]);
};

