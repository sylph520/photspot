#include "StdAfx.h"
#include "TotemExec.h"


TotemExec::TotemExec(void)
{
}


TotemExec::~TotemExec(void)
{
}


bool TotemExec::DBConnect(const char * connStr)
{
	conn = PQconnectdb(connStr);			/* 连接数据库 */
	if (MyPQ::status(conn)==false)			/* 通过PQstatus函数返回的连接的状态为失败，CONNECTION_BAD */
	{
		return 0;    // 连接数据库失败
	}
	else
	{
		return 1;    // 连接数据库成功
	}
}


void TotemExec::DBExecQuery(const char * connStr)
{
	res = PQexec(conn, connStr);					/* 发送SQL数据库查询命令 */
}

int TotemExec::DBNtuples()
{
	return PQntuples(res);
}


char *  TotemExec::DBGetvalue(PGresult *res, int row, int line)
{
	return PQgetvalue(res, row, line);
}


// 构建查询语句
int TotemExec::BuildQueryStr(QueryContent content)
{
	/*
	*   search_ii_oid的查询字段中包含ab时会导致数据库挂掉
	*/
	/*
	CString  strContent;
	strContent.Empty();
	if (content.query_absti != _T(""))
	{
		strContent.Format("(ti:(%s) or ab:(%s))", content.query_absti, content.query_absti);

		if (content.query_pa != _T(""))
		{
			strContent.Format("%s and (pa:\"%s\" or inn:\"%s\")", strContent, content.query_pa, content.query_pa);
		}
		strContent = _T("(") + strContent + _T(")");
	}
	else
	{
		if (content.query_pa != _T(""))
		{
			strContent.Format("(pa:\"%s\" or inn:\"%s\")", content.query_pa, content.query_pa);
		}
	}

	str_query.Format("select * from search_ii_oid(\'%s\', \'%s\', \'ti,ab,ic1,ad\', \'\', true, 0, 0);", content.query_table, strContent);
	cout<<str_query<<endl;
	*/

	CString  strContent;
	strContent.Empty();

	CString str_absti, str_pa, str_ipc, str_date;
	str_absti.Empty();
	str_pa.Empty();
	str_ipc.Empty();

	if (content.query_absti != _T(""))
	{
		str_absti.Format(" (ti like \'%%%s%%\' or ab like \'%%%s%%\') ", content.query_absti, content.query_absti);

		if (strContent==_T(""))
		{
			strContent.Format("%s", str_absti);
		}
		else
		{
			strContent = strContent + _T(" and ") + str_absti;
		}
	}

	if (content.query_pa != _T(""))
	{
		str_pa.Format(" (pa like \'%%%s%%\' or inn like \'%%%s%%\') ", content.query_pa, content.query_pa);
		if (strContent==_T(""))
		{
			strContent.Format("%s", str_pa);
		}
		else
		{
			strContent = strContent + _T(" and ") + str_pa;
		}
	}

	if (content.query_ipc != _T(""))
	{
		str_ipc.Format(" (ic1 like \'%s%%\') ", content.query_ipc);
		if (strContent==_T(""))
		{
			strContent.Format("%s", str_ipc);
		}
		else
		{
			strContent = strContent + _T(" and ") + str_ipc;
		}
	}

	if (content.query_yearfrom != _T("") && content.query_yearto!=_T(""))
	{
		str_date.Format(" (ad between \'%s-01-01\' and \'%s-12-31\') ", content.query_yearfrom, content.query_yearto);
		if (strContent==_T(""))
		{
			strContent.Format("%s", str_date);
		}
		else
		{
			strContent = strContent + _T(" and ") + str_date;
		}
	}


	// 分析query_table中包含多少个数据表
	// 说明：当有多个表时，中间以‘,’分隔
	str_query.Empty();
	CString  strline;
	CString  tablename;
	int pos1 = 0;
	int pos2 =0; 
	while ((pos2=content.query_table.Find(",", pos1)) != -1)
	{
		tablename = content.query_table.Mid(pos1, pos2-pos1);
		strline.Format("select ti,ab,ic1,ad from %s where %s union all ", tablename, strContent);
		str_query += strline;
		pos1 = pos2+1;
	}

	tablename = content.query_table.Right(content.query_table.GetLength()-pos1);
	strline.Format("select ti,ab,ic1,ad from %s where %s;", tablename, strContent);
	str_query += strline;
//	str_query.Format("select ti,ab,ic1,ad from %s where %s;", content.query_table, strContent);
	return 0;
}