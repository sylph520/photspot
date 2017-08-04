#include "StdAfx.h"
#include "DataVisualize.h"
#include "TrendAnalyse.h"
#include "md5.h"



DataVisualize::DataVisualize(CString src_querystr)
{
	fileapp.Open("yeardis.txt", CFile::modeCreate | CFile::modeWrite);
	map_ipctreeinfo.clear();
	CStdioFile fileipctree;
	CString ipcfname("Config\\ipcstreeshort.txt");
	try
	{
		fileipctree.Open(ipcfname, CFile::modeRead);
		CString sLine, sIpc, sContent;
		while (fileipctree.ReadString(sLine))
		{
			int nSize = sLine.GetLength();
			int nSep = sLine.Find("\t", 0);
			if (nSep != -1)
			{
				sIpc = sLine.Left(nSep);
				sContent = sLine.Right(nSize - nSep -1);

				map_ipctreeinfo.insert(std::map<CString, CString>::value_type(sIpc, sContent));
			}
			else
			{
				continue;
			}
		}
	}
	catch(...)
	{
	}

//	cout<<"IPC词条总数："<<map_ipctreeinfo.size()<<endl;

	CString  folder;
	folder = GetMd5(src_querystr);
	dir_datav.Format("VisualData\\%s", folder);

	filed_degree = 0.03;
	QueryLineToContent(src_querystr, query_content);
	SetDegree(query_content.query_degree);

	srand((unsigned)time(0)); //随机种子
}


DataVisualize::~DataVisualize(void)
{
}




// 设定技术词的筛选临界粒度
void DataVisualize::SetDegree(CString degree)
{
	if (degree.Find("大") != -1)
	{
		tec_degree = 0.09;
	}
	else if(degree.Find("中") != -1)
	{
		tec_degree = 0.10;
	}
	else if(degree.Find("小") != -1)
	{
		tec_degree = 0.15;
	}
	else
	{
		tec_degree = 0.05;
	}
}

/* 
*  对clusterInfo中的技术领域和技术短语进行筛选，构造热点可视化信息
*  根据std::map<CString, TermInfo>  clusterInfo
*     构造std::vector<DataVisual> vec_datavs
*  注意：clusterInfo中包含vec_datavs
*/

void DataVisualize::TranslateToVisualData(std::map<CString, TermInfo>&  clusterInfo, std::map<CString, TermInfo>  map_keyinfo )
{
	CStdioFile  fileKey;
	fileKey.Open("keyinfo.txt", CFile::modeCreate | CFile::modeReadWrite);
	int times = 0;
	TrendAnalyse trendAnalyse;
	for ( std::map<CString, TermInfo>::iterator it=clusterInfo.begin(); it!=clusterInfo.end(); ++it )
	{
		int clu_totalfrq =    clusterInfo[(*it).first].cludocfreq;

		//对得到的技术领域进行筛选
		if ( (double)clu_totalfrq > (double)doc_num * filed_degree)
		{
			CString tmp;
			tmp.Format("\n\n----------------------------------------------------------------------------------\n%s\t( %d ):\n", (*it).first, clu_totalfrq);
			fileKey.WriteString(tmp);
			
			for ( std::map<CString, unsigned int>::iterator t_it= (*it).second.ipcInfo.begin(); t_it!= (*it).second.ipcInfo.end(); ++t_it )
			{
				if ( (double)(*t_it).second > (tec_degree * clu_totalfrq))
				{
					// 构造相应的可视化数据信息
					DataVisual datavtmp;
					datavtmp.techfield  = GetRealnameByBpc((*it).first);	// 专利技术所属的技术领域名称
					datavtmp.techname = FormatTecname((*t_it).first);		// 专利技术名称
					datavtmp.appyear = GetYearFromDistri(map_keyinfo[(*t_it).first].appDistribute) + GenerateRandom(0.00, 2.00) - 1;
																			// 专利申请年份，作为横坐标值
																			// 为了使其在纵轴上分布更加均匀，加上一个[-1, 1]之间的随机数
					datavtmp.yaxis = GenerateRandom(2.00, 10.00);		    // 在二维坐标中的纵坐标值
																		
					datavtmp.vhotspots = (*t_it).second;				    // 专利热点程度
					datavtmp.lifeperiod = GetPeriodFomDistri(trendAnalyse.ComputePeriod(map_keyinfo[(*t_it).first].appDistribute));	// 专利技术所处的技术生命周期

					clusterInfo[(*it).first].vec_datavs.push_back(datavtmp);
					
					tmp.Format("   %s\t\t%d\n", (*t_it).first, (*t_it).second);
					fileKey.WriteString(tmp);

					// 对该技术领域是否是热点进行标记
					clusterInfo[(*it).first].isHotField = true;
				}
			}
		}
		else
		{
			// 对该技术领域是否是热点进行标记
			clusterInfo[(*it).first].isHotField = false;
		}
	}

//	cout<<"词条总数："<<clusterInfo.size()<<endl;
	fileKey.Close();

}



// 将整型的周期值转化为对应的字符串类型的生命周期
CString  DataVisualize::GetPeriodFomDistri(int period)
{
	CString strPeriod;
	switch(period)
	{
	case 1:
		{
			strPeriod = _T("引入期");
			break;
		}
	case 2:
		{
			strPeriod = _T("发展期");
			break;
		}
	case 3:
		{
			strPeriod = _T("成熟期");
			break;
		}
	case 4:
		{
			strPeriod = _T("衰退期");
			break;
		}
	
	case 5:
		{
			strPeriod = _T("复苏期");
			break;
		}
	default:
		{
			strPeriod = _T("未知");
			break;
		}
	}

	return strPeriod;
}



// 去除专利技术名称中的词性
CString DataVisualize::FormatTecname(const CString tecname)
{
	int pos = tecname.Find("/", 0);
	if (pos != -1)
	{
		return tecname.Left(pos);
	}
	else
	{
		return tecname;
	}
}


// 根据历史分布情况得到其起始年份
unsigned int  DataVisualize::GetYearFromDistri(unsigned int ipc[])
{
//	fileapp.WriteString("\n----------------------------------------------------------------\n");
	int i(0);int k=-1;
	
//	int sum(0);
//	int subsum(0);
	for (; i<DATEDISTRI_SIZE; ++i)
	{
	//	sum += ipc[i];
	//	CString  tmp;
	//	tmp.Format("%d\t%d", 1985+i, ipc[i]);
	//	fileapp.WriteString(tmp);
	//	fileapp.WriteString("\n");
		if (ipc[i]>0)
		{
			break;
		}

	}
//	subsum += ipc[26];
//	subsum += ipc[25];
//	subsum += ipc[24];
	//if (subsum!=0)
	//{
	//	CString tmp;
	//	tmp.Format("起始年份：%d\t%.2f", 1985+k, (float)subsum/(float)sum);
	//	fileapp.WriteString(tmp);
	//	fileapp.WriteString("\n");
	//}
	

	return (1985+i);
}



// 将查询字符串中的各个字段解析出来
// 输入为查询字符串sline，输出为QueryContent
/* 
* 传递过来的查询条件格式
* @sqltable:***___sep___@absti:***___sep___@pa:***___sep___@degree:***
* “___sep___”为分隔符
*/
void DataVisualize::QueryLineToContent(CString sline, QueryContent& content)
{
	const char *  sep_str = "___sep___";
	int pos1 = 0;
	int pos2 = sline.Find(sep_str, pos1);
	while(1)
	{
		CString tmp;
		if (pos2 != -1)
		{
			tmp = sline.Mid(pos1, pos2-pos1);
			FindContentByTag(tmp, content);

			pos1 = pos2 + strlen(sep_str);
			pos2 = sline.Find(sep_str, pos1);
		}
		else
		{
			tmp = sline.Right(sline.GetLength()-pos1);
			FindContentByTag(tmp, content);
			break;
		}	
	}
}




/* 根据技术的IPC找到该技术的中文名称
*  输入参数：
*		ipc：专利的IPC小类
*		map_ipctreeinfo：保存IPC小类及其对应中文名称的map容器
*  输出：
*		info：IPC对应的中文名称
*/
CString DataVisualize::GetRealnameByBpc(const char * ipc)
{
	CString info;
	// 如果在容器map_ipctreeinfo中找到该IPC对应的中文名称，将其中文名称返回
	if (map_ipctreeinfo.find(ipc) != map_ipctreeinfo.end())
	{
		info = map_ipctreeinfo[ipc];
	}
	else  // 否则将该IPC号作为该技术的中文名称
	{
		info = ipc;
	}

	return  info;
}




// 根据字符串中的标签判断该该字符串属于查询中哪个字段
void DataVisualize::FindContentByTag(CString sInclueTag, QueryContent& content)
{
	const char *  tag_appyear = "@appyear:";
	const char *  tag_qtable = "@sqltable:";
	const char *  tag_absti = "@absti:";
	const char *  tag_ipc = "@ipc:";
	const char *  tag_pa = "@pa:";
	const char *  tag_degree = "@degree:";

	const char *  sep_years = "to";
	if (sInclueTag.Find(tag_qtable, 0) != -1)
	{
		content.query_table = sInclueTag.Right(sInclueTag.GetLength()-strlen(tag_qtable));
		return;
	}

	if (sInclueTag.Find(tag_absti, 0) != -1)
	{
		content.query_absti = sInclueTag.Right(sInclueTag.GetLength()-strlen(tag_absti));
		return;
	}

	if (sInclueTag.Find(tag_ipc, 0) != -1)
	{
		content.query_ipc = sInclueTag.Right(sInclueTag.GetLength()-strlen(tag_ipc));
		return;
	}

	if (sInclueTag.Find(tag_pa, 0) != -1)
	{
		content.query_pa = sInclueTag.Right(sInclueTag.GetLength()-strlen(tag_pa));
		return;
	}

	if (sInclueTag.Find(tag_degree, 0) != -1)
	{
		content.query_degree = sInclueTag.Right(sInclueTag.GetLength()-strlen(tag_degree));
		return;
	}

	if (sInclueTag.Find(tag_appyear, 0) != -1)
	{
		CString  year_tmp;
		year_tmp = sInclueTag.Right(sInclueTag.GetLength()-strlen(tag_appyear));
		int pos = year_tmp.Find(sep_years, 0);
		if (pos != -1)
		{
			content.query_yearfrom = year_tmp.Left(pos);
			content.query_yearto = year_tmp.Right(year_tmp.GetLength()-pos-strlen(sep_years));
		}
		return;
	}
}



// 生成特定范围内的随机数
float DataVisualize::GenerateRandom(float min, float max)
{
	return (min + (max-min)*rand()/(RAND_MAX+1.0));
}


// 根据一个字符串得到其MD5值
CString  DataVisualize::GetMd5(CString src)
{
	CString  dest;
	dest.Empty();

	unsigned char decrypt[16];    
	MD5_CTX md5;
	MD5Init(&md5);         		
	MD5Update(&md5, (unsigned char *)src.GetBuffer(src.GetLength()), src.GetLength());
	MD5Final(&md5, decrypt);        

	CString  tmp;
	for (int i=0; i<16; i++)
	{
		tmp.Format("%02x", decrypt[i]);
		dest += tmp;
	}
	
	return dest;
}



// 判断该历史记录中是否存在本次检索的可视化结果
// 如果存在则直接从历史记录中读取，不存在则创建该目录
// 返回值：   0：存在，数据不为空  1：存在，但数据为空， 2：不存在，且创建成功， 3：不存在，且创建失败
int DataVisualize::CheckHistory(void)
{
	WIN32_FIND_DATA  wfd;
	HANDLE hFind = FindFirstFile(dir_datav, &wfd);
	if (hFind != INVALID_HANDLE_VALUE)  // ------目录存在
	{
		// 判断该目录下是否存在.csv格式的数据
		CFileFind finder;

		// build a string with wildcards 
		CString strWildcard(dir_datav); 
		strWildcard += _T("\\*.csv");

		// start working for files 
		BOOL bWorking = finder.FindFile(strWildcard);

		int count(0);
		while (bWorking) 
		{ 
			bWorking = finder.FindNextFile();
			++count;
		}

		if (count>=1)//该目录下存在数据文件
		{
			return 0;
		}
		else
		{
			return 1;
		}
		
	}
	else // -------------------目录不存在
	{
		if (CreateMultipleDirectory(dir_datav))	 // 创建该目录
		{
			return 2;		// 创建成功
		}
		else
		{
			return 3;		// 创建失败
		}
		
	}
	FindClose(hFind);

	return 0;
}




/* 将得到的热点信息写入指定的目录下
 *   输入参数：
 *			info：得到的热点技术信息，path：指定的路径
 *   输出：
 *			指定目录下根据某种规则生成的一系列文本文件
 *   返回值：
 *			0：执行成功， 1：创建路径失败， 2：写文件时出错
 */
int  DataVisualize::SaveDataToFile(std::map<CString, TermInfo>  info)
{
	WIN32_FIND_DATA  wfd;

	HANDLE hFind = FindFirstFile(dir_datav, &wfd);
	if (hFind != INVALID_HANDLE_VALUE)  // ------目录存在
	{	
	}
	else // -------------------目录不存在
	{
		if (CreateMultipleDirectory(dir_datav))	 // 创建该目录
		{
		}
		else
		{
			return 1;		// 创建失败
		}

	}
	FindClose(hFind);


	for ( std::map<CString, TermInfo>::iterator it=info.begin(); it!=info.end(); ++it )
	{
		if (info[(*it).first].isHotField)	// 该领域是热点领域
		{
			CStdioFile file;
			CString  fpath;
			fpath.Format("%s\\%s.csv",dir_datav, GetRealnameByBpc((*it).first));

			if (file.Open(fpath, CFile::modeCreate | CFile::modeWrite))
			{
				file.WriteString("技术分类,专利技术,年份,纵坐标,热点程度,生命周期阶段");
				file.WriteString("\n");

				for (int i = 0; i<(*it).second.vec_datavs.size(); ++i )
				{
					DataVisual datavtmp = (*it).second.vec_datavs.at(i);
					CString tmp;
	
					file.WriteString(datavtmp.techfield);
					file.WriteString(",");
					file.WriteString(datavtmp.techname);
					file.WriteString(",");
					tmp.Format("%.2f", datavtmp.appyear);
					file.WriteString(tmp);
					file.WriteString(",");
					tmp.Format("%.2f", datavtmp.yaxis);
					file.WriteString(tmp);
					file.WriteString(",");
					tmp.Format("%.2f", datavtmp.vhotspots);
					file.WriteString(tmp);
					file.WriteString(",");
					tmp.Format("%s", datavtmp.lifeperiod);
					file.WriteString(tmp);
					file.WriteString("\n");

				}

				file.Close();
			}
			else
			{
				continue;
			}
		}
	}

	return 0;
}



// 创建多层目录
bool DataVisualize::CreateMultipleDirectory(const CString& szPath)
{
	CString strDir(szPath);//存放要创建的目录字符串
    //确保以'\'结尾以创建最后一个目录
    if (strDir.GetAt(strDir.GetLength()-1)!=_T('\\'))
    {
        strDir.AppendChar(_T('\\'));
    }
    std::vector<CString> vPath;		// 存放每一层目录字符串
    CString strTemp;				// 一个临时变量,存放目录字符串
    bool bSuccess = false;			// 成功标志

    //遍历要创建的字符串
    for (int i=0;i<strDir.GetLength();++i)
    {
        if (strDir.GetAt(i) != _T('\\'))	//如果当前字符不是'\\'
        {
            strTemp.AppendChar(strDir.GetAt(i));
        }
        else								//如果当前字符是'\\'
        {
            vPath.push_back(strTemp);	//将当前层的字符串添加到数组中
            strTemp.AppendChar(_T('\\'));
        }
    }

    //遍历存放目录的数组,创建每层目录
    std::vector<CString>::const_iterator vIter;
    for (vIter = vPath.begin(); vIter != vPath.end(); vIter++) 
    {
        //如果CreateDirectory执行成功,返回true,否则返回false
        bSuccess = CreateDirectory(*vIter, NULL) ? true : false;    
    }

    return bSuccess;
}
