
#pragma once
#include "TextProcessing.h"


class DataVisualize
{
public:
	DataVisualize(CString src_querystr);
	~DataVisualize(void);

	CStdioFile fileapp;
private:
	double tec_degree;								// ��������ɸѡ������
	double filed_degree;
	std::map<CString, CString>  map_ipctreeinfo;

	// ����PHP���ݹ����Ĳ������н���
	void FindContentByTag(CString sInclueTag, QueryContent& content);		// �����ַ����еı�ǩ�жϸø��ַ������ڲ�ѯ���ĸ��ֶ�
	void QueryLineToContent(CString sline, QueryContent& content);			// ����ѯ�ַ����еĸ����ֶν�������

	void SetDegree(CString degree);											// ��������ֵ�Ĵ�С
	bool CreateMultipleDirectory(const CString& szPath);					// �����༶Ŀ¼

	float GenerateRandom(float min, float max);					// �����ض���Χ�ڵ������
	CString  GetMd5(CString src);								// ����һ���ַ����õ���MD5ֵ
	CString  GetRealnameByBpc(const char * ipc);				// ����IPC�õ��ü�������������info
	CString  FormatTecname(const CString tecname);				// ȥ��ר�����������еĴ���
	unsigned int  GetYearFromDistri(unsigned int ipc[]);		// ������ʷ�ֲ�����õ�����ʼ���

	unsigned int  GetPeriodFomDistri(unsigned int ipc[]);		// ������ʷ�ֲ�����õ����������ڽ׶�
	CString  GetPeriodFomDistri(int period);					// �����͵�����ֵת��Ϊ��Ӧ���ַ������͵���������



public:
	QueryContent  query_content;
	unsigned int doc_num;
	CString  dir_datav;		// �洢���ӻ���Ϣ��Ŀ¼

	
	int  CheckHistory(void);												// �����ʷ��¼
	void TranslateToVisualData(std::map<CString, TermInfo>&  clusterInfo, std::map<CString, TermInfo>  map_keyinfo);	// ��clusterInfo�еļ�������ͼ����������ɸѡ��������ӻ����͵���Ϣ 
	int  SaveDataToFile(std::map<CString, TermInfo>  info);					// ���õ����ȵ���Ϣд��ָ����Ŀ¼��
};

