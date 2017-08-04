#include "StdAfx.h"
#include "TrendAnalyse.h"


TrendAnalyse::TrendAnalyse(void)
{

}


TrendAnalyse::~TrendAnalyse(void)
{

}



// 返回值
// 1：引入期
// 2：发展期
// 3：成熟期
// 4：衰退期
// 5：复苏期
int TrendAnalyse::ComputePeriod(unsigned int appdistri[])
{
	int sum(0);
	int subsum(0);

	const int totalyears = 27;

	int beginyear = -1;
	for (int i(0); i<totalyears; ++i)
	{
		sum += appdistri[i];
		
		if (appdistri[i]>0)
		{
			if (beginyear == -1)
			{
				beginyear = i+1985;
			}
		}
	}

	subsum += appdistri[totalyears-1];
	subsum += appdistri[totalyears-2];
	subsum += appdistri[totalyears-3];

	if (subsum != 0)
	{
		float result = (float)subsum/(float)sum;
		if ( (1985+totalyears-beginyear)<3)		//近三年的技术是处于引入期的
		{
			return 1;  // 引入期
		}

		if (result>0.35)
		{
			return 2;  // 发展期
		}
		
		if (result>0.12)
		{
			return 3;  // 成熟期
		}
	}
	return 4;
}