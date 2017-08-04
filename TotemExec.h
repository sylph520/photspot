#pragma once

#include "stdafx.h"

class TotemExec
{
public:
	TotemExec(void);
	~TotemExec(void);

	// 涉及多个表的查询时，需要通过UNION ALL操作符将它们连接起来
	CString  str_query;// 查询语句
	PGconn *conn;
	PGresult *res;

	int   BuildQueryStr(QueryContent content);
	bool  DBConnect(const char * connStr);
	void  DBExecQuery(const char * connStr);
	int   DBNtuples();
	char* DBGetvalue(PGresult *res, int row, int line);
};

