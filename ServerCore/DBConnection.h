#pragma once
#include <sql.h>
#include <sqlext.h>

/*-------------------
	DBConnection
-------------------*/
class DBConnection
{
public:
	bool Connect(SQLHENV hEnv, const wchar_t* connectionString);
	void Clear();

	bool Execute(const wchar_t* query);
	bool Fetch();

	int32 GetRowCount();
	void UnBind();

public:
	bool BindParam(SQLUSMALLINT paramIndex, SQLSMALLINT cType, SQLSMALLINT sqlType, SQLULEN len, SQLPOINTER ptr, SQLLEN* index);
	bool BindColumn(SQLUSMALLINT columnIndex, SQLSMALLINT cType, SQLULEN len, SQLPOINTER value, SQLLEN* index);
	void HandleError(SQLRETURN ret);


private:
	SQLHDBC		m_Connection = SQL_NULL_HANDLE;
	SQLHSTMT	m_Statement = SQL_NULL_HANDLE;
};
