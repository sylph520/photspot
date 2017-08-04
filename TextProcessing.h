#pragma once


// �����������ĳ���
const unsigned int DATEDISTRI_SIZE = 32;



// ר���ĵ�����Ϣ
typedef struct PatentInfo
{
	const char * ti;		// ����
	const char * abs;		// ժҪ
	char  ipc[5];			// ����ŵ�С��
	unsigned int appyear;	// �������
}PatentInfo;



// techfield����������
//		��һ���ַ�������ʾһ���������������
//		ע�⣺���������в��ܰ�������
// techname��ר������
//		������������ַ���
// appyear���������
//		һ��ר�����������������Ϊ�ü����ڿ��ӻ���άͼ�еĺ�����
// yaxis��������
//		��άͼ�е�������ֵ����Χ��[0.00,10.00]����ϵͳ�������
// vhotspots���ȵ�̶�
//		��һ���������͵�ֵ��ʾһ������ȵ�̶�
// lifeperiod:�������ڽ׶�
//		�����ڣ���չ�ڣ�
//		�����ڣ�������
typedef struct DataVisual
{
	CString techfield;
	CString techname;
	float	appyear;
	float	yaxis;
	float   vhotspots;
	CString	lifeperiod;
}DataVisual;



//// ��Ƶ��Ŀ���ĵ���Ŀ
//typedef struct DistriInfo
//{
//	unsigned int termFreq;			// ��Ƶ����
//	unsigned int docFreq;			// �����ôʵ��ĵ���
//	unsigned int appDistribute[32];	// ר������ֲ����
//}DistriInfo;


/*
* �洢ĳ��ĳ�����������µ��ȵ㼼�������ߴ洢ĳ���������ﱻ�����ļ�������
* ����˵����
* isHotField���ü��������Ƿ����ȵ�����
*      filed��ĳ��������ļ�������
*    ipcInfo���ü��������°������ȵ㼼������ĳ���������ﱻ�����ļ�������
* vec_datavs�����ȵ㼼������Ŀ��ӻ���Ϣ
*/
typedef struct TermInfo
{
	bool isHotField;
	CString tecfiled;
	std::map<CString, unsigned int> ipcInfo;
	std::vector<DataVisual> vec_datavs;

	unsigned int termFreq;			// ��Ƶ����
	unsigned int docFreq;			// �����ôʵ��ĵ���
	unsigned int appDistribute[DATEDISTRI_SIZE];	// ר������ֲ����

	unsigned int cludocfreq;		// ��������°������ĵ���
}TermInfo;



// ר�����������°�����
// sumDocfrq: ���ĵ���
// appDistribute: ר������ֲ����
typedef struct FieldDistri
{
	unsigned int sumDocfrq;
	unsigned int appDistribute[DATEDISTRI_SIZE];
}FieldDistri;




class TextProcessing
{
public:
	TextProcessing(void);
	~TextProcessing(void);

	std::set<CString> set_stopword;					// ������е�ͣ�ô�
	std::map<CString, FieldDistri> map_field;		// ��ʽ��<ר��IPC���࣬�÷����µ�����ֲ����>
	std::vector<CString> vec_keyword;				// ����map��������ֵ��������

	std::map<CString, TermInfo>  map_keyinfo;		// �����ִʡ�ͳ�ƴ�Ƶ�����󣬱��漼���ʵķֲ����
	std::map<CString, TermInfo>  clusterInfo;		// ר������󽫵õ��ȵ�������ȵ㼼�������Ϣ���浽��������


	int BuildTechDic(CString outlookfname, CString userdictfname);		// ���ɼ����ʵ�
	int ImportUserDict(CString userdictfname);							// �����û��ʵ䵽NLPIR
	int GetStopWord(CString fname);										// ��ȡͣ�ôʱ�set����
	
	int PatentClustering();												// ����ר��IPC��ר�������ʽ��о���
	const char * SentenceParse(const char * sentence);					// ���ַ������зִ�
	int WordsToMap(PatentInfo pInfo);									// ����˵��������ͣ�ôʱ�ӷִʺ�Ķ�������ȡ��������Ϣ��map������

	void GetaSubipcOfIPC(char * dest_ipc, char * src_ipc);				// ��ר��IPC����ȡ��С��
	void GetYearFromDate(unsigned int& des_year, char * src_date);		// ��ר������������ȡ���������
};

