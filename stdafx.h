// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
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




/* 从PHP传递过来的参数
*	 query_absti：标题或摘要中包含的关键词
*		query_pa：专利权人
*	query_degree：粒度
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


// TODO: 在此处引用程序需要的其他头文件
