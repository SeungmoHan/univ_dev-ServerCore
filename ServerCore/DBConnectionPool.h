#pragma once
#include "DBConnection.h"

/*---------------------
	DBConnectionPool
---------------------*/
class DBConnectionPool
{
public:
	~DBConnectionPool();
	DBConnectionPool();

	bool			Connect(int32 connectionCounts, const wchar_t* connectionString);
	void			Clear();

	DBConnection*	Pop();
	void			Push(DBConnection* connection);

private:
	USE_LOCK;
	SQLHENV					m_Environment = SQL_NULL_HANDLE;
	Vector<DBConnection*>	m_Connections;
};
