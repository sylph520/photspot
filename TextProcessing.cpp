#include "StdAfx.h"
#include "TextProcessing.h"


TextProcessing::TextProcessing(void)
{
	// ��ȡͣ�ôʱ�
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





// ��ȡͣ�ôʱ�
int TextProcessing::GetStopWord(CString fname)
{
	char sStopword[10000];
	ifstream stopFile;
	stopFile.open(fname, ios::binary | ios::in);
	if (!stopFile.is_open())
	{
		return 1;    // ���ļ�ʧ��
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

			set_stopword.insert("");    // ���ַ�
			set_stopword.insert(",");    // �������","
		}
	}

	stopFile.close();
	return 0;
}



// ר������
/* ����|-----Term-----IPC
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
*      |����         
* ����  

*      |------IPC-----Term
*      |         |    Term
*      |         |    Term
*      |         
*      |------IPC-----Term
*      |         |    Term
*      |         |    Term
*      |
*      |����   
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

		// �ж�ĳ�����������ĸ���������
		// �ü��������ļ��������У����ִ��������ĸ�������Ϊ�ü�����������
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
* ���ַ������зִ�
* ����˵����
* sentence����������ַ���
* ����������ִʺʹ��Ա�ע����ַ�����
* �м��Կո�ָ�
*/       
const char * TextProcessing::SentenceParse(const char * sentence)
{
	return  NLPIR_ParagraphProcess(sentence, 1); // ʹ�ô��Ա�ע
}



// �����û��ʵ䵽NLPIR
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
			
		NLPIR_SaveTheUsrDic();    //�����û��ʵ�
		userfile.Close();
		NLPIR_Exit();
		
	}
	catch(...)
	{
		return 1;
	}

	return 0;
}



// ���ɼ����ʵ�
// ����˵����
// outlookfname:��ǰĿ¼�´洢���ר��������ļ���
// userdictfname����ǰĿ¼�±������ɵļ����ʵ���ļ���
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
		//		����������������
		//	}

			strKeyword = strLine;
			int pos1, pos2;
			if ( (pos1=strKeyword.Find("(", 0)) != -1 )
			{
				pos2 = strKeyword.Find(")", 0);
				strKeyword.Delete(pos1, pos2-pos1+1);
			}
			if ( (pos1=strKeyword.Find("��", 0)) != -1 )
			{
				pos2 = strKeyword.Find("��", 0);
				strKeyword.Delete(pos1, pos2-pos1+2);
			}
			
			strKeyword.TrimLeft();
			strKeyword.TrimRight();
			set_keywords.insert(strKeyword);
		}
		
		// �Դ������ȥ��
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
* ����˵��������map_keyinfo��������ͣ�ôʱ�ӷִʺ�Ķ�������ȡ��������Ϣ��map�����У���Ƶ��������Ϣ��
* ����˵����
*     sResult����������ַ�����Ϊר�������ר��ժҪ
*         ipc��ר��IPC��С�ࣨǰ4���ַ���������ʵ�����ͣ���ǰ5���ַ������ר������
*
* ����|-----Term-----IPC
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
*      |����     
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
		if ( nlines == 1 )				// ����ִʺ��ר������
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
		std::map<CString, bool> map_existline;		// �ڼ������ĳ���ʵ��ĵ�����ʱ���õ�����ȥ�ص�����
		map_existline.clear();
		while ((j=sLine.Find(" ", j)) != -1)
		{
			CString word = sLine.Mid(i, j-i);
			word.TrimLeft();
			word.TrimRight();

			j++;
			i = j;

			// ���ݴ��Խ��й��ˣ�������һԪ����Ԫ��
			int wlen = word.GetLength();
			if ( ( word.Find("/x", 0)==-1 && wlen < 8 ) 
				|| ( word.Find("/x", 0)!=-1 && wlen < 5 ) 
				|| (wlen - word.Find("/x", 0)!=2) && (wlen - word.Find("/n", 0)!=2) && 
				(wlen - word.Find("/vn", 0)!=3) && (wlen - word.Find("/b", 0)!=2) &&
				(wlen - word.Find("/nl", 0)!=3) && (wlen - word.Find("/vi", 0)!=3) )
			{
				continue;
			}

			 // ���˷ִʺ��ͣ�ô�
			if (word.IsEmpty() || (set_stopword.find(word) != set_stopword.end())) 
			{	
			}
			else
			{
				if (map_existline.find(word)!=map_existline.end())	//�ô��ڸ��ĵ����Ѿ����ֹ�
				{
					map_keyinfo[word].termFreq ++;
				}
				else	//�ô��ڸ��ĵ���δ���ֹ�
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



// ��ר��IPC����ȡ��С��
void TextProcessing::GetaSubipcOfIPC(char * dest_ipc, char * src_ipc)
{
	// ��IPC�е�Сд��ĸת��Ϊ��д
	int nsize = strlen(src_ipc);
	for (int i(0); i<nsize; ++i)
	{
		if (islower(src_ipc[i]))
		{
			src_ipc[i] = toupper(src_ipc[i]);
		}
	}


	// ��ȡ��ר���ļ�������-С��
	int count(0);
	if ( 'A' <= src_ipc[0]
	&& src_ipc[0] <= 'Z')     // ��ʽ���硰H04W8/18I��
	{
		count = 4;
	}
	else                               // ��ʽ���硰14-03��,���ר��
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



// ��ר������������ȡ���������
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


