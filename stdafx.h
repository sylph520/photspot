// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include "include/NLPIR.h"
#include "MyPQ.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <string>
#include <afx.h>
#include <map>
#include <set>

using namespace::std;


#pragma comment(lib, "lib/NLPIR.lib")
#pragma comment(lib, "lib/libpq.lib")




/* ��PHP���ݹ����Ĳ���
*	 query_absti�������ժҪ�а����Ĺؼ���
*		query_pa��ר��Ȩ��
*	query_degree������
*/
typedef struct QueryContent
{
	CString query_table;
	CString query_yearfrom;
	CString query_yearto;
	CString query_ipc;
	CString query_absti;
	CString query_pa;
	CString query_degree;
}QueryContent;


// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
