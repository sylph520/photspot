// PatentHotspots.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "PatentHotspots.h"
#include "TextProcessing.h"
#include "DataVisualize.h"
#include "TotemExec.h"


//std::map<CString, unsigned int > map_ipc;   // 保存分词后的所有词


int _tmain(int argc, _TCHAR* argv[])
{
	//if (argc<2)
	//{
	////	cout<<"参数传递失败!"<<endl;
	//	return 1;
	//}

//	cout<<"处理中....."<<endl;

	clock_t t_begin,t_end;
	t_begin = clock();

	/* ----------根据argv[1]构造检索表达式------*/
	
	CString  qLine = argv[1];


	//CString qLine = "@sqltable:cn_20130524124357___sep___@appyear:2001to2012___sep___@absti:计算机___sep___@ipc:___sep___@pa:华为___sep___@degree:大";
	//CString qLine = "@sqltable:cn_20130526074030,cn_20140526143546,cn_20140607171633___sep___@appyear:to___sep___@absti:计算机___sep___@ipc:___sep___@pa:___sep___@degree:大";
	
    //CString qLine = "@sqltable:cn_20150918195342,cn_20150918195854,cn_20150918200216,cn_20150918200432,cn_20150918203527,cn_20150918203543,cn_20150918210412,cn_2k___sep___@appyear:to___sep___@absti:___sep___@ipc:___sep___@pa:华为技术有限公司___sep___@degree:大";

	DataVisualize  datav(qLine);
	if (!datav.CheckHistory()) //存在本次检索的历史记录
	{
		// 如果历史记录里面存在本次检索的记录，直接从历史记录中读取
		return 0;
	}

	//cout<<datav.query_content.query_absti<<endl<<datav.query_content.query_degree<<endl<<datav.query_content.query_pa<<endl;


	TotemExec  dbexec;
	dbexec.BuildQueryStr(datav.query_content);// 根据查询content构建查询语句
	

	TextProcessing  textprocessing;
	
	if ( !dbexec.DBConnect("host='127.0.0.1'  port='5678'  dbname='patent'  user='totem'  password='totem'") )  // 括号里面的为数据库连接参数
	{
	   
		return 1;
	}
	else
	{
		// 使用NLPIR进行分词
		if(!NLPIR_Init()) 
		{
			
			printf("Init fails\n");
			
			return -1;
		}

		// 对满足查询条件的专利文本进行分词、聚类、热点发现等操作，将结果写入文件result.txt中
		PQsetClientEncoding(dbexec.conn, "GBK");		/* 设置编码使支持中文 */

		t_begin = clock();

		dbexec.DBExecQuery(dbexec.str_query);

		t_end = clock();
	//	printf("\DBExecQuery ntime cost is %f seconds!\n\n",  (double)(t_end-t_begin)/CLOCKS_PER_SEC);
	//	cout<<dbexec.str_query<<endl;


		int nRes = dbexec.DBNtuples();
		if ( nRes<=0 )
		{  
			//cout<<"未找到满足条件的数据，请重新检索！"<<endl;
			return 1;
		}

		t_begin = clock();


		for (int i(0); i< nRes; ++i)//数据库表名若出现重复，则重命名；
		{
			PatentInfo  pInfo;
			pInfo.ti = textprocessing.SentenceParse(dbexec.DBGetvalue(dbexec.res, i, 0));				/* res的i行0列元素，专利标题 ，对其进行分词*/
			pInfo.abs = textprocessing.SentenceParse(dbexec.DBGetvalue(dbexec.res, i, 1));				/* res的i行1列元素，专利摘要 ，对其进行分词*/
			textprocessing.GetaSubipcOfIPC(pInfo.ipc, dbexec.DBGetvalue(dbexec.res, i, 2));				/* res的i行2列元素，专利分类号 ，取其小类*/
			textprocessing.GetYearFromDate(pInfo.appyear, dbexec.DBGetvalue(dbexec.res, i, 3));			/* res的i行3列元素，专利申请日 ，取其年份*/

			textprocessing.WordsToMap(pInfo);// 统计每个词的信息
		}


		t_end = clock();
	//	printf("\nWordsToMap time cost is %f seconds!\n\n",  (double)(t_end-t_begin)/CLOCKS_PER_SEC);

		t_begin = clock();

		textprocessing.PatentClustering();		// 专利聚类

		t_end = clock();
	//	printf("\nPatentClustering time cost is %f seconds!\n\n",  (double)(t_end-t_begin)/CLOCKS_PER_SEC);


	//	cout<<datav.GetMd5("")<<endl<<datav.GetMd5("Hello World")<<endl<<datav.GetMd5("计算机--华为")<<endl<<datav.GetMd5("----@________")<<endl;

		t_begin = clock();
		datav.doc_num = nRes;
		datav.TranslateToVisualData(textprocessing.clusterInfo, textprocessing.map_keyinfo);
		t_end = clock();
	//	printf("\nTranslateToVisualData time cost is %f seconds!\n\n",  (double)(t_end-t_begin)/CLOCKS_PER_SEC);

		t_begin = clock();
		datav.SaveDataToFile(textprocessing.clusterInfo);

		t_end = clock();
	//	printf("\SaveDataToFile time cost is %f seconds!\n\n",  (double)(t_end-t_begin)/CLOCKS_PER_SEC);

		NLPIR_Exit();
	}


	t_end = clock();
//	printf("\ntime cost is %f seconds!\n\n",  (double)(t_end-t_begin)/CLOCKS_PER_SEC);
	

	return 0;



	int mode;
BEGIN:
	printf("1: 生成用户词典;\n\
2: 导入用户词典;\n\
3: 专利聚类;\n\
0: 退出;\n\
Input:");
	scanf("%d", &mode);
	
	t_begin = clock();
	switch(mode)
	{
	case 1:
		{
			textprocessing.BuildTechDic("outlook.txt",  "userdict.txt");   // 生成用户词典
			break;
		}
	case 2:
		{
			textprocessing.ImportUserDict("userdict.txt"); // 导入用户词典
			break;
		}

	case 3:
		{
			textprocessing.PatentClustering();   // 专利聚类
			break;
		}
	case 0:
		{
			return 0;
		}
	default:
		{
			break;
		}
	}

	t_end = clock();
	printf("\ntime cost is %f seconds!\n\n",  (double)(t_end-t_begin)/CLOCKS_PER_SEC);

	goto BEGIN;
}


