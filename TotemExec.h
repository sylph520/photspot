#pragma once

#include "stdafx.h"

class TotemExec
{
public:
	TotemExec(void);
	~TotemExec(void);

	// �漰�����Ĳ�ѯʱ����Ҫͨ��UNION ALL��������������������
	CString  str_query;// ��ѯ���
	PGconn *conn;
	PGresult *res;

	int   BuildQueryStr(QueryContent content);
	bool  DBConnect(const char * connStr);
	void  DBExecQuery(const char * connStr);
	int   DBNtuples();
	char* DBGetvalue(PGresult *res, int row, int line);
};

