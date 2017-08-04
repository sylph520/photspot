// MyPQ.h: interface for the MyPQ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPQ_H__AAEB9D67_D341_480F_BBD5_E9370BC32A83__INCLUDED_)
#define AFX_MYPQ_H__AAEB9D67_D341_480F_BBD5_E9370BC32A83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "include\libpq-fe.h"

#define checkStaus(conn) \
if(MyPQ::status(conn)==false){ \
	MessageBox("无法连接数据库"); \
	OnCancel(); \
	return; \
}
#define checkExec(res) \
if(PQresultStatus(res) != PGRES_COMMAND_OK) { \
	MessageBox("执行出错\n请检查数据库"); \
	OnCancel(); \
	return; \
}
#define checkSelect(res) \
if(PQresultStatus(res) != PGRES_TUPLES_OK) { \
	MessageBox("查询出错\n请检查数据库"); \
	OnCancel(); \
	return; \
}

class MyPQ
{
public:

	MyPQ();
	virtual ~MyPQ();
	static bool status(PGconn *conn) {
		if(PQstatus(conn)!= CONNECTION_OK) PQreset(conn);
		return PQstatus(conn)== CONNECTION_OK;
	}

	static PGresult* select(PGconn *conn,const char* sqlCmd){
		PGresult* res=PQexec(conn,sqlCmd);
		if(PQresultStatus(res) != PGRES_TUPLES_OK) {
			PQreset(conn);
			PQclear(res);
			return PQexec(conn,sqlCmd);
		}
		return res;
	}

	static PGresult* exec(PGconn *conn,const char* sqlCmd){
		PGresult* res=PQexec(conn,sqlCmd);
		if(PQresultStatus(res) != PGRES_COMMAND_OK) {
			PQreset(conn);
			PQclear(res);
			return PQexec(conn,sqlCmd);
		}
		return res;
	}
};

#endif // !defined(AFX_MYPQ_H__AAEB9D67_D341_480F_BBD5_E9370BC32A83__INCLUDED_)
