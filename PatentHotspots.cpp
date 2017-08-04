// PatentHotspots.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "PatentHotspots.h"
#include "TextProcessing.h"
#include "DataVisualize.h"
#include "TotemExec.h"


//std::map<CString, unsigned int > map_ipc;   // ����ִʺ�����д�


int _tmain(int argc, _TCHAR* argv[])
{
	//if (argc<2)
	//{
	////	cout<<"��������ʧ��!"<<endl;
	//	return 1;
	//}

//	cout<<"������....."<<endl;

	clock_t t_begin,t_end;
	t_begin = clock();

	/* ----------����argv[1]����������ʽ------*/
	
	CString  qLine = argv[1];


	//CString qLine = "@sqltable:cn_20130524124357___sep___@appyear:2001to2012___sep___@absti:�����___sep___@ipc:___sep___@pa:��Ϊ___sep___@degree:��";
	//CString qLine = "@sqltable:cn_20130526074030,cn_20140526143546,cn_20140607171633___sep___@appyear:to___sep___@absti:�����___sep___@ipc:___sep___@pa:___sep___@degree:��";
	
    //CString qLine = "@sqltable:cn_20150918195342,cn_20150918195854,cn_20150918200216,cn_20150918200432,cn_20150918203527,cn_20150918203543,cn_20150918210412,cn_2k___sep___@appyear:to___sep___@absti:___sep___@ipc:___sep___@pa:��Ϊ�������޹�˾___sep___@degree:��";

	DataVisualize  datav(qLine);
	if (!datav.CheckHistory()) //���ڱ��μ�������ʷ��¼
	{
		// �����ʷ��¼������ڱ��μ����ļ�¼��ֱ�Ӵ���ʷ��¼�ж�ȡ
		return 0;
	}

	//cout<<datav.query_content.query_absti<<endl<<datav.query_content.query_degree<<endl<<datav.query_content.query_pa<<endl;


	TotemExec  dbexec;
	dbexec.BuildQueryStr(datav.query_content);// ���ݲ�ѯcontent������ѯ���
	

	TextProcessing  textprocessing;
	
	if ( !dbexec.DBConnect("host='127.0.0.1'  port='5678'  dbname='patent'  user='totem'  password='totem'") )  // ���������Ϊ���ݿ����Ӳ���
	{
	   
		return 1;
	}
	else
	{
		// ʹ��NLPIR���зִ�
		if(!NLPIR_Init()) 
		{
			
			printf("Init fails\n");
			
			return -1;
		}

		// �������ѯ������ר���ı����зִʡ����ࡢ�ȵ㷢�ֵȲ����������д���ļ�result.txt��
		PQsetClientEncoding(dbexec.conn, "GBK");		/* ���ñ���ʹ֧������ */

		t_begin = clock();

		dbexec.DBExecQuery(dbexec.str_query);

		t_end = clock();
	//	printf("\DBExecQuery ntime cost is %f seconds!\n\n",  (double)(t_end-t_begin)/CLOCKS_PER_SEC);
	//	cout<<dbexec.str_query<<endl;


		int nRes = dbexec.DBNtuples();
		if ( nRes<=0 )
		{  
			//cout<<"δ�ҵ��������������ݣ������¼�����"<<endl;
			return 1;
		}

		t_begin = clock();


		for (int i(0); i< nRes; ++i)//���ݿ�����������ظ�������������
		{
			PatentInfo  pInfo;
			pInfo.ti = textprocessing.SentenceParse(dbexec.DBGetvalue(dbexec.res, i, 0));				/* res��i��0��Ԫ�أ�ר������ ��������зִ�*/
			pInfo.abs = textprocessing.SentenceParse(dbexec.DBGetvalue(dbexec.res, i, 1));				/* res��i��1��Ԫ�أ�ר��ժҪ ��������зִ�*/
			textprocessing.GetaSubipcOfIPC(pInfo.ipc, dbexec.DBGetvalue(dbexec.res, i, 2));				/* res��i��2��Ԫ�أ�ר������� ��ȡ��С��*/
			textprocessing.GetYearFromDate(pInfo.appyear, dbexec.DBGetvalue(dbexec.res, i, 3));			/* res��i��3��Ԫ�أ�ר�������� ��ȡ�����*/

			textprocessing.WordsToMap(pInfo);// ͳ��ÿ���ʵ���Ϣ
		}


		t_end = clock();
	//	printf("\nWordsToMap time cost is %f seconds!\n\n",  (double)(t_end-t_begin)/CLOCKS_PER_SEC);

		t_begin = clock();

		textprocessing.PatentClustering();		// ר������

		t_end = clock();
	//	printf("\nPatentClustering time cost is %f seconds!\n\n",  (double)(t_end-t_begin)/CLOCKS_PER_SEC);


	//	cout<<datav.GetMd5("")<<endl<<datav.GetMd5("Hello World")<<endl<<datav.GetMd5("�����--��Ϊ")<<endl<<datav.GetMd5("----@________")<<endl;

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
	printf("1: �����û��ʵ�;\n\
2: �����û��ʵ�;\n\
3: ר������;\n\
0: �˳�;\n\
Input:");
	scanf("%d", &mode);
	
	t_begin = clock();
	switch(mode)
	{
	case 1:
		{
			textprocessing.BuildTechDic("outlook.txt",  "userdict.txt");   // �����û��ʵ�
			break;
		}
	case 2:
		{
			textprocessing.ImportUserDict("userdict.txt"); // �����û��ʵ�
			break;
		}

	case 3:
		{
			textprocessing.PatentClustering();   // ר������
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


