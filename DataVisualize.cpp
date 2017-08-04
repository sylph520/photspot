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

//	cout<<"IPC����������"<<map_ipctreeinfo.size()<<endl;

	CString  folder;
	folder = GetMd5(src_querystr);
	dir_datav.Format("VisualData\\%s", folder);

	filed_degree = 0.03;
	QueryLineToContent(src_querystr, query_content);
	SetDegree(query_content.query_degree);

	srand((unsigned)time(0)); //�������
}


DataVisualize::~DataVisualize(void)
{
}




// �趨�����ʵ�ɸѡ�ٽ�����
void DataVisualize::SetDegree(CString degree)
{
	if (degree.Find("��") != -1)
	{
		tec_degree = 0.09;
	}
	else if(degree.Find("��") != -1)
	{
		tec_degree = 0.10;
	}
	else if(degree.Find("С") != -1)
	{
		tec_degree = 0.15;
	}
	else
	{
		tec_degree = 0.05;
	}
}

/* 
*  ��clusterInfo�еļ�������ͼ����������ɸѡ�������ȵ���ӻ���Ϣ
*  ����std::map<CString, TermInfo>  clusterInfo
*     ����std::vector<DataVisual> vec_datavs
*  ע�⣺clusterInfo�а���vec_datavs
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

		//�Եõ��ļ����������ɸѡ
		if ( (double)clu_totalfrq > (double)doc_num * filed_degree)
		{
			CString tmp;
			tmp.Format("\n\n----------------------------------------------------------------------------------\n%s\t( %d ):\n", (*it).first, clu_totalfrq);
			fileKey.WriteString(tmp);
			
			for ( std::map<CString, unsigned int>::iterator t_it= (*it).second.ipcInfo.begin(); t_it!= (*it).second.ipcInfo.end(); ++t_it )
			{
				if ( (double)(*t_it).second > (tec_degree * clu_totalfrq))
				{
					// ������Ӧ�Ŀ��ӻ�������Ϣ
					DataVisual datavtmp;
					datavtmp.techfield  = GetRealnameByBpc((*it).first);	// ר�����������ļ�����������
					datavtmp.techname = FormatTecname((*t_it).first);		// ר����������
					datavtmp.appyear = GetYearFromDistri(map_keyinfo[(*t_it).first].appDistribute) + GenerateRandom(0.00, 2.00) - 1;
																			// ר��������ݣ���Ϊ������ֵ
																			// Ϊ��ʹ���������Ϸֲ����Ӿ��ȣ�����һ��[-1, 1]֮��������
					datavtmp.yaxis = GenerateRandom(2.00, 10.00);		    // �ڶ�ά�����е�������ֵ
																		
					datavtmp.vhotspots = (*t_it).second;				    // ר���ȵ�̶�
					datavtmp.lifeperiod = GetPeriodFomDistri(trendAnalyse.ComputePeriod(map_keyinfo[(*t_it).first].appDistribute));	// ר�����������ļ�����������

					clusterInfo[(*it).first].vec_datavs.push_back(datavtmp);
					
					tmp.Format("   %s\t\t%d\n", (*t_it).first, (*t_it).second);
					fileKey.WriteString(tmp);

					// �Ըü��������Ƿ����ȵ���б��
					clusterInfo[(*it).first].isHotField = true;
				}
			}
		}
		else
		{
			// �Ըü��������Ƿ����ȵ���б��
			clusterInfo[(*it).first].isHotField = false;
		}
	}

//	cout<<"����������"<<clusterInfo.size()<<endl;
	fileKey.Close();

}



// �����͵�����ֵת��Ϊ��Ӧ���ַ������͵���������
CString  DataVisualize::GetPeriodFomDistri(int period)
{
	CString strPeriod;
	switch(period)
	{
	case 1:
		{
			strPeriod = _T("������");
			break;
		}
	case 2:
		{
			strPeriod = _T("��չ��");
			break;
		}
	case 3:
		{
			strPeriod = _T("������");
			break;
		}
	case 4:
		{
			strPeriod = _T("˥����");
			break;
		}
	
	case 5:
		{
			strPeriod = _T("������");
			break;
		}
	default:
		{
			strPeriod = _T("δ֪");
			break;
		}
	}

	return strPeriod;
}



// ȥ��ר�����������еĴ���
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


// ������ʷ�ֲ�����õ�����ʼ���
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
	//	tmp.Format("��ʼ��ݣ�%d\t%.2f", 1985+k, (float)subsum/(float)sum);
	//	fileapp.WriteString(tmp);
	//	fileapp.WriteString("\n");
	//}
	

	return (1985+i);
}



// ����ѯ�ַ����еĸ����ֶν�������
// ����Ϊ��ѯ�ַ���sline�����ΪQueryContent
/* 
* ���ݹ����Ĳ�ѯ������ʽ
* @sqltable:***___sep___@absti:***___sep___@pa:***___sep___@degree:***
* ��___sep___��Ϊ�ָ���
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




/* ���ݼ�����IPC�ҵ��ü�������������
*  ���������
*		ipc��ר����IPCС��
*		map_ipctreeinfo������IPCС�༰���Ӧ�������Ƶ�map����
*  �����
*		info��IPC��Ӧ����������
*/
CString DataVisualize::GetRealnameByBpc(const char * ipc)
{
	CString info;
	// ���������map_ipctreeinfo���ҵ���IPC��Ӧ���������ƣ������������Ʒ���
	if (map_ipctreeinfo.find(ipc) != map_ipctreeinfo.end())
	{
		info = map_ipctreeinfo[ipc];
	}
	else  // ���򽫸�IPC����Ϊ�ü�������������
	{
		info = ipc;
	}

	return  info;
}




// �����ַ����еı�ǩ�жϸø��ַ������ڲ�ѯ���ĸ��ֶ�
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



// �����ض���Χ�ڵ������
float DataVisualize::GenerateRandom(float min, float max)
{
	return (min + (max-min)*rand()/(RAND_MAX+1.0));
}


// ����һ���ַ����õ���MD5ֵ
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



// �жϸ���ʷ��¼���Ƿ���ڱ��μ����Ŀ��ӻ����
// ���������ֱ�Ӵ���ʷ��¼�ж�ȡ���������򴴽���Ŀ¼
// ����ֵ��   0�����ڣ����ݲ�Ϊ��  1�����ڣ�������Ϊ�գ� 2�������ڣ��Ҵ����ɹ��� 3�������ڣ��Ҵ���ʧ��
int DataVisualize::CheckHistory(void)
{
	WIN32_FIND_DATA  wfd;
	HANDLE hFind = FindFirstFile(dir_datav, &wfd);
	if (hFind != INVALID_HANDLE_VALUE)  // ------Ŀ¼����
	{
		// �жϸ�Ŀ¼���Ƿ����.csv��ʽ������
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

		if (count>=1)//��Ŀ¼�´��������ļ�
		{
			return 0;
		}
		else
		{
			return 1;
		}
		
	}
	else // -------------------Ŀ¼������
	{
		if (CreateMultipleDirectory(dir_datav))	 // ������Ŀ¼
		{
			return 2;		// �����ɹ�
		}
		else
		{
			return 3;		// ����ʧ��
		}
		
	}
	FindClose(hFind);

	return 0;
}




/* ���õ����ȵ���Ϣд��ָ����Ŀ¼��
 *   ���������
 *			info���õ����ȵ㼼����Ϣ��path��ָ����·��
 *   �����
 *			ָ��Ŀ¼�¸���ĳ�ֹ������ɵ�һϵ���ı��ļ�
 *   ����ֵ��
 *			0��ִ�гɹ��� 1������·��ʧ�ܣ� 2��д�ļ�ʱ����
 */
int  DataVisualize::SaveDataToFile(std::map<CString, TermInfo>  info)
{
	WIN32_FIND_DATA  wfd;

	HANDLE hFind = FindFirstFile(dir_datav, &wfd);
	if (hFind != INVALID_HANDLE_VALUE)  // ------Ŀ¼����
	{	
	}
	else // -------------------Ŀ¼������
	{
		if (CreateMultipleDirectory(dir_datav))	 // ������Ŀ¼
		{
		}
		else
		{
			return 1;		// ����ʧ��
		}

	}
	FindClose(hFind);


	for ( std::map<CString, TermInfo>::iterator it=info.begin(); it!=info.end(); ++it )
	{
		if (info[(*it).first].isHotField)	// ���������ȵ�����
		{
			CStdioFile file;
			CString  fpath;
			fpath.Format("%s\\%s.csv",dir_datav, GetRealnameByBpc((*it).first));

			if (file.Open(fpath, CFile::modeCreate | CFile::modeWrite))
			{
				file.WriteString("��������,ר������,���,������,�ȵ�̶�,�������ڽ׶�");
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



// �������Ŀ¼
bool DataVisualize::CreateMultipleDirectory(const CString& szPath)
{
	CString strDir(szPath);//���Ҫ������Ŀ¼�ַ���
    //ȷ����'\'��β�Դ������һ��Ŀ¼
    if (strDir.GetAt(strDir.GetLength()-1)!=_T('\\'))
    {
        strDir.AppendChar(_T('\\'));
    }
    std::vector<CString> vPath;		// ���ÿһ��Ŀ¼�ַ���
    CString strTemp;				// һ����ʱ����,���Ŀ¼�ַ���
    bool bSuccess = false;			// �ɹ���־

    //����Ҫ�������ַ���
    for (int i=0;i<strDir.GetLength();++i)
    {
        if (strDir.GetAt(i) != _T('\\'))	//�����ǰ�ַ�����'\\'
        {
            strTemp.AppendChar(strDir.GetAt(i));
        }
        else								//�����ǰ�ַ���'\\'
        {
            vPath.push_back(strTemp);	//����ǰ����ַ�����ӵ�������
            strTemp.AppendChar(_T('\\'));
        }
    }

    //�������Ŀ¼������,����ÿ��Ŀ¼
    std::vector<CString>::const_iterator vIter;
    for (vIter = vPath.begin(); vIter != vPath.end(); vIter++) 
    {
        //���CreateDirectoryִ�гɹ�,����true,���򷵻�false
        bSuccess = CreateDirectory(*vIter, NULL) ? true : false;    
    }

    return bSuccess;
}
