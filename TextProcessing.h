#pragma once


// 保存年份数组的长度
const unsigned int DATEDISTRI_SIZE = 32;



// 专利文档的信息
typedef struct PatentInfo
{
	const char * ti;		// 标题
	const char * abs;		// 摘要
	char  ipc[5];			// 分类号的小类
	unsigned int appyear;	// 申请年份
}PatentInfo;



// techfield：技术分类
//		用一个字符串来表示一个技术分类的名称
//		注意：技术分类中不能包含逗号
// techname：专利技术
//		表明该项技术的字符串
// appyear：申请年份
//		一项专利的最早申请年份作为该技术在可视化二维图中的横坐标
// yaxis：纵坐标
//		二维图中的纵坐标值，范围是[0.00,10.00]，由系统随机生成
// vhotspots：热点程度
//		用一个浮点类型的值表示一项技术的热点程度
// lifeperiod:生命周期阶段
//		引入期；发展期；
//		成熟期；饱和期
typedef struct DataVisual
{
	CString techfield;
	CString techname;
	float	appyear;
	float	yaxis;
	float   vhotspots;
	CString	lifeperiod;
}DataVisual;



//// 词频数目和文档数目
//typedef struct DistriInfo
//{
//	unsigned int termFreq;			// 词频总数
//	unsigned int docFreq;			// 包含该词的文档数
//	unsigned int appDistribute[32];	// 专利申请分布情况
//}DistriInfo;


/*
* 存储某个某个技术领域下的热点技术，或者存储某个技术短语被包含的技术领域
* 参数说明：
* isHotField：该技术领域是否是热点领域
*      filed：某项技术所属的技术领域
*    ipcInfo：该技术领域下包含的热点技术，或某个技术短语被包含的技术领域
* vec_datavs：对热点技术构造的可视化信息
*/
typedef struct TermInfo
{
	bool isHotField;
	CString tecfiled;
	std::map<CString, unsigned int> ipcInfo;
	std::vector<DataVisual> vec_datavs;

	unsigned int termFreq;			// 词频总数
	unsigned int docFreq;			// 包含该词的文档数
	unsigned int appDistribute[DATEDISTRI_SIZE];	// 专利申请分布情况

	unsigned int cludocfreq;		// 技术类别下包含的文档数
}TermInfo;



// 专利技术分类下包含的
// sumDocfrq: 总文档数
// appDistribute: 专利申请分布情况
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

	std::set<CString> set_stopword;					// 存放所有的停用词
	std::map<CString, FieldDistri> map_field;		// 格式：<专利IPC分类，该分类下的申请分布情况>
	std::vector<CString> vec_keyword;				// 辅助map容器按照值进行排序

	std::map<CString, TermInfo>  map_keyinfo;		// 经过分词、统计词频操作后，保存技术词的分布情况
	std::map<CString, TermInfo>  clusterInfo;		// 专利聚类后将得到热点领域和热点技术相关信息保存到该容器中


	int BuildTechDic(CString outlookfname, CString userdictfname);		// 生成技术词典
	int ImportUserDict(CString userdictfname);							// 导入用户词典到NLPIR
	int GetStopWord(CString fname);										// 读取停用词表到set容器
	
	int PatentClustering();												// 按照专利IPC对专利技术词进行聚类
	const char * SentenceParse(const char * sentence);					// 对字符串进行分词
	int WordsToMap(PatentInfo pInfo);									// 功能说明：根据停用词表从分词后的段落中提取出短语信息到map容器中

	void GetaSubipcOfIPC(char * dest_ipc, char * src_ipc);				// 从专利IPC中提取出小类
	void GetYearFromDate(unsigned int& des_year, char * src_date);		// 从专利申请日中提取出申请年份
};

