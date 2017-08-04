#include "StdAfx.h"
#include "TrendAnalyse.h"


TrendAnalyse::TrendAnalyse(void)
{

}


TrendAnalyse::~TrendAnalyse(void)
{

}



// ����ֵ
// 1��������
// 2����չ��
// 3��������
// 4��˥����
// 5��������
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
		if ( (1985+totalyears-beginyear)<3)		//������ļ����Ǵ��������ڵ�
		{
			return 1;  // ������
		}

		if (result>0.35)
		{
			return 2;  // ��չ��
		}
		
		if (result>0.12)
		{
			return 3;  // ������
		}
	}
	return 4;
}