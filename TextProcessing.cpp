#include "StdAfx.h"
#include "TextProcessing.h"


TextProcessing::TextProcessing(void)
{
	// 读取停用词表
	try
	{
		GetStopWord("Data\\stop_word.txt");
	}
	catch(...)
	{
	}
}


TextProcessing::~TextProcessing(void)
{
}





// 读取停用词表
int TextProcessing::GetStopWord(CString fname)
{
	char sStopword[10000];
	ifstream stopFile;
	stopFile.open(fname, ios::binary | ios::in);
	if (!stopFile.is_open())
	{
		return 1;    // 打开文件失败
	}
	while ( stopFile.getline(sStopword, sizeof(sStopword)) )
	{
		CString  sLine(sStopword);
		int i(0), j(0);

		while ((j=sLine.Find(",", j)) != -1)
		{
			CString word = sLine.Mid(i, j-i);
			word.TrimLeft();
			word.TrimRight();

			j++;
			i = j;
			if (!word.IsEmpty())
			{
				if ( (word.Find("\"", 0)!=-1) )
				{
					word.Replace("\"", "");
				}
			//	cout<<word<<endl;
				set_stopword.insert(word);
			}

			set_stopword.insert("");    // 空字符
			set_stopword.insert(",");    // 特殊符号","
		}
	}

	stopFile.close();
	return 0;
}



// 专利聚类
/* 根据|-----Term-----IPC
*      |         |    IPC
*      |         |    IPC
*      |         |----termFreq
*      |         |----docFreq
*      |         
*      |-----Term-----IPC
*      |         |    IPC
*      |         |    IPC
*      |         |----termFreq
*      |         |----docFreq
*      |……         
* 构造  

*      |------IPC-----Term
*      |         |    Term
*      |         |    Term
*      |         
*      |------IPC-----Term
*      |         |    Term
*      |         |    Term
*      |
*      |……   
*/
int TextProcessing::PatentClustering()
{
	for (std::map<CString, TermInfo>::iterator p_it=map_keyinfo.begin(); p_it!=map_keyinfo.end(); ++p_it)
	{
		/*-----------------------------
         * (*p_it).first    |  Term
		 *-----------------------------
		 * (*p_it).second   |  std::map<CString, unsigned int> ipcInfo
         *                     unsigned int termFreq;    
		 *                     unsigned int docFreq;
		 *-----------------------------*/
		CString term = (*p_it).first;
		TermInfo  ipcInfo = (*p_it).second;
		ipcInfo.docFreq = 0;

		// 判断某个技术属于哪个技术领域
		// 该技术所属的技术领域中，出现次数最大的哪个领域，最为该技术所属领域
		int maxFrq = 0;
		for ( std::map<CString, unsigned int>::iterator it=ipcInfo.ipcInfo.begin(); it!=ipcInfo.ipcInfo.end(); ++it )
		{
			CString ipc = (*it).first;
			int    freq = (*it).second;   // docfreq

			if (freq > maxFrq)
			{
				maxFrq = freq;
				ipcInfo.docFreq = freq;
				ipcInfo.tecfiled = ipc;
			}
		}

		if ( clusterInfo.find(ipcInfo.tecfiled) != clusterInfo.end() )
		{
			clusterInfo[ipcInfo.tecfiled].ipcInfo.insert(std::map<CString, unsigned int>::value_type(term, ipcInfo.docFreq));
		//	clusterInfo[ipcInfo.tecfiled].allTermFrq += ipcInfo.termFreq;
		}
		else
		{
			ipcInfo.ipcInfo.clear();
			ipcInfo.ipcInfo.insert(std::map<CString, unsigned int>::value_type(term, ipcInfo.docFreq));
			
			clusterInfo.insert(std::map<CString, TermInfo>::value_type(ipcInfo.tecfiled, ipcInfo));
		//	clusterInfo[ipcInfo.tecfiled].ipcInfo.insert(std::map<CString, unsigned int>::value_type(term, ipcInfo.termFreq));
		//	clusterInfo[ipcInfo.tecfiled].allTermFrq = ipcInfo.termFreq;
		}
		clusterInfo[ipcInfo.tecfiled].cludocfreq = map_field[ipcInfo.tecfiled].sumDocfrq;
	}

	return 0;
}



/*
* 对字符串进行分词
* 参数说明：
* sentence：待处理的字符串
* 输出：经过分词和词性标注后的字符串，
* 中间以空格分隔
*/       
const char * TextProcessing::SentenceParse(const char * sentence)
{
	return  NLPIR_ParagraphProcess(sentence, 1); // 使用词性标注
}



// 导入用户词典到NLPIR
int TextProcessing::ImportUserDict(CString userdictfname)
{
	if(!NLPIR_Init()) 
	{
	//	printf("Init fails\n");
		return -1;
	}

	try
	{
		CStdioFile  userfile;
	//	CString userdictfname("userdict.txt");
		userfile.Open(userdictfname, CFile::modeRead);
		CString  strline;
		while (userfile.ReadString(strline))
		{
			NLPIR_AddUserWord(strline);
		}
			
		NLPIR_SaveTheUsrDic();    //保存用户词典
		userfile.Close();
		NLPIR_Exit();
		
	}
	catch(...)
	{
		return 1;
	}

	return 0;
}



// 生成技术词典
// 参数说明：
// outlookfname:当前目录下存储外观专利标题的文件名
// userdictfname：当前目录下保存生成的技术词典的文件名
int TextProcessing::BuildTechDic(CString outlookfname , CString  userdictfname)
{
	std::set<CString>  set_keywords;
	CStdioFile  userdict,outlookfile;
	CString strLine;
	CString strKeyword;
	if ( userdict.Open(userdictfname, CFile::modeCreate | CFile::modeReadWrite) && 
		outlookfile.Open(outlookfname, CFile::modeRead ) )
	{
		while (outlookfile.ReadString(strLine))
		{
		//	int pos = strLine.Find("\t", 0);
		//	if (pos != -1)
		//	{
		//		strKeyword = strLine.Right(strLine.GetLength() - pos-1);
		//		……………………
		//	}

			strKeyword = strLine;
			int pos1, pos2;
			if ( (pos1=strKeyword.Find("(", 0)) != -1 )
			{
				pos2 = strKeyword.Find(")", 0);
				strKeyword.Delete(pos1, pos2-pos1+1);
			}
			if ( (pos1=strKeyword.Find("（", 0)) != -1 )
			{
				pos2 = strKeyword.Find("）", 0);
				strKeyword.Delete(pos1, pos2-pos1+2);
			}
			
			strKeyword.TrimLeft();
			strKeyword.TrimRight();
			set_keywords.insert(strKeyword);
		}
		
		// 对词组进行去重
		for (std::set<CString>::iterator it=set_keywords.begin(); it!=set_keywords.end(); ++it)
		{
			if ( (*it).GetLength()>=2
				&& (*it).GetLength()<=10 )
			{
				userdict.WriteString(*it);
				userdict.WriteString("\n");
			}
		}

		userdict.Close();
		outlookfile.Close();
	}
	else
	{
		return 1;
	}

	return 0;
}




/* 
* 功能说明：构造map_keyinfo，即根据停用词表从分词后的段落中提取出短语信息到map容器中（词频、分类信息）
* 参数说明：
*     sResult：待处理的字符串，为专利标题或专利摘要
*         ipc：专利IPC的小类（前4个字符（发明、实用新型）或前5个字符（外观专利））
*
* 构造|-----Term-----IPC
*      |         |    IPC
*      |         |    IPC
*      |         |----termFreq
*      |         |----docFreq
*      |         
*      |-----Term-----IPC
*      |         |    IPC
*      |         |    IPC
*      |         |----termFreq
*      |         |----docFreq
*      |……     
*/
int TextProcessing::WordsToMap(PatentInfo pInfo)
//int TextProcessing::WordsToMap(const char * sResult, CString  ipc)
{
	if (map_field.find(pInfo.ipc)==map_field.end())
	{
		FieldDistri field;
		field.sumDocfrq = 1;

		memset(field.appDistribute, 0, sizeof(unsigned int)*DATEDISTRI_SIZE);

		field.appDistribute[pInfo.appyear-1985] = 1;
		map_field.insert(std::map<CString, FieldDistri>::value_type(pInfo.ipc, field));
	}
	else
	{
		map_field[pInfo.ipc].sumDocfrq ++;
		map_field[pInfo.ipc].appDistribute[pInfo.appyear-1985] ++; 
	}

	int nlines = 2;
	while (nlines > 0)
	{
		CString sLine;
		if ( nlines == 1 )				// 处理分词后的专利标题
		{
			sLine = pInfo.ti;
		}
		else if ( nlines == 2 )
		{
			sLine = pInfo.abs;
		}
		else
		{
			break;
		}

		int i(0), j(0);
		std::map<CString, bool> map_existline;		// 在计算包含某个词的文档数的时候用到，起去重的作用
		map_existline.clear();
		while ((j=sLine.Find(" ", j)) != -1)
		{
			CString word = sLine.Mid(i, j-i);
			word.TrimLeft();
			word.TrimRight();

			j++;
			i = j;

			// 根据词性进行过滤，并过滤一元、二元词
			int wlen = word.GetLength();
			if ( ( word.Find("/x", 0)==-1 && wlen < 8 ) 
				|| ( word.Find("/x", 0)!=-1 && wlen < 5 ) 
				|| (wlen - word.Find("/x", 0)!=2) && (wlen - word.Find("/n", 0)!=2) && 
				(wlen - word.Find("/vn", 0)!=3) && (wlen - word.Find("/b", 0)!=2) &&
				(wlen - word.Find("/nl", 0)!=3) && (wlen - word.Find("/vi", 0)!=3) )
			{
				continue;
			}

			 // 过滤分词后的停用词
			if (word.IsEmpty() || (set_stopword.find(word) != set_stopword.end())) 
			{	
			}
			else
			{
				if (map_existline.find(word)!=map_existline.end())	//该词在该文档中已经出现过
				{
					map_keyinfo[word].termFreq ++;
				}
				else	//该词在该文档中未出现过
				{
					if (map_keyinfo.find(word) == map_keyinfo.end())
					{
						TermInfo newKey;
						newKey.termFreq = 1;
						newKey.docFreq = 1;
						memset(newKey.appDistribute, 0, sizeof(unsigned int)*DATEDISTRI_SIZE);
						newKey.appDistribute[pInfo.appyear-1985] = 1;
						newKey.ipcInfo.insert(std::map<CString, unsigned int>::value_type(pInfo.ipc, 1));

						map_keyinfo.insert(std::map<CString, TermInfo>::value_type(word, newKey));

						map_existline.insert(std::map<CString, bool>::value_type(word, true));
					}
					else
					{
						map_keyinfo[word].termFreq ++;
						map_keyinfo[word].docFreq ++;
						map_keyinfo[word].appDistribute[pInfo.appyear-1985] += 1;
						
						if (map_keyinfo[word].ipcInfo.find(pInfo.ipc) != map_keyinfo[word].ipcInfo.end() )
						{
							map_keyinfo[word].ipcInfo[pInfo.ipc] ++;
						}
						else
						{
							map_keyinfo[word].ipcInfo.insert(std::map<CString, unsigned int>::value_type(pInfo.ipc, 1));
						}
					}
				}
			}
		}

		--nlines;
	}

	return 0;
}



// 从专利IPC中提取出小类
void TextProcessing::GetaSubipcOfIPC(char * dest_ipc, char * src_ipc)
{
	// 将IPC中的小写字母转化为大写
	int nsize = strlen(src_ipc);
	for (int i(0); i<nsize; ++i)
	{
		if (islower(src_ipc[i]))
		{
			src_ipc[i] = toupper(src_ipc[i]);
		}
	}


	// 获取该专利的技术分类-小类
	int count(0);
	if ( 'A' <= src_ipc[0]
	&& src_ipc[0] <= 'Z')     // 格式形如“H04W8/18I”
	{
		count = 4;
	}
	else                               // 格式形如“14-03”,外观专利
	{
		count = 5;
	}

	for (int i(0); i<count; ++i)
	{
		dest_ipc[i] = src_ipc[i];
	}

	dest_ipc[count] = '\0';

	return;
}



// 从专利申请日中提取出申请年份
void TextProcessing::GetYearFromDate(unsigned int& des_year, char * src_date)
{
	int count = 4;
	if (strlen(src_date)<count)
	{
		des_year = 1985;
		return;
	}
	
	des_year = 0;
	for (int i(0); i<count; ++i)
	{
		des_year += (src_date[i]-'0') * _Pow_int(10, count-i-1);
	}
	
	return;
}


