
#pragma once
#include "TextProcessing.h"


class DataVisualize
{
public:
	DataVisualize(CString src_querystr);
	~DataVisualize(void);

	CStdioFile fileapp;
private:
	double tec_degree;								// 技术短语筛选的粒度
	double filed_degree;
	std::map<CString, CString>  map_ipctreeinfo;

	// 根据PHP传递过来的参数进行解析
	void FindContentByTag(CString sInclueTag, QueryContent& content);		// 根据字符串中的标签判断该该字符串属于查询中哪个字段
	void QueryLineToContent(CString sline, QueryContent& content);			// 将查询字符串中的各个字段解析出来

	void SetDegree(CString degree);											// 设置粒度值的大小
	bool CreateMultipleDirectory(const CString& szPath);					// 创建多级目录

	float GenerateRandom(float min, float max);					// 生成特定范围内的随机数
	CString  GetMd5(CString src);								// 根据一个字符串得到其MD5值
	CString  GetRealnameByBpc(const char * ipc);				// 根据IPC得到该技术的中文名称info
	CString  FormatTecname(const CString tecname);				// 去除专利技术名称中的词性
	unsigned int  GetYearFromDistri(unsigned int ipc[]);		// 根据历史分布情况得到其起始年份

	unsigned int  GetPeriodFomDistri(unsigned int ipc[]);		// 根据历史分布情况得到其生命周期阶段
	CString  GetPeriodFomDistri(int period);					// 将整型的周期值转化为对应的字符串类型的生命周期



public:
	QueryContent  query_content;
	unsigned int doc_num;
	CString  dir_datav;		// 存储可视化信息的目录

	
	int  CheckHistory(void);												// 检查历史记录
	void TranslateToVisualData(std::map<CString, TermInfo>&  clusterInfo, std::map<CString, TermInfo>  map_keyinfo);	// 对clusterInfo中的技术领域和技术短语进行筛选，构造可视化类型的信息 
	int  SaveDataToFile(std::map<CString, TermInfo>  info);					// 将得到的热点信息写入指定的目录下
};

