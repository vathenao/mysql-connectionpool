#ifndef __DB_CONNECT_H__
#define __DB_CONNECT_H__

#include "global.h"
#include "xdbcWrapper.h"
#include "connpoolException.h"

class xConnection;
class XDBC_EXPORT DbConnect
{
public:
	DbConnect();
	~DbConnect();

	void SetSqlText(string sql);
	void setInt(int index, const int &value);
	void setString(int index, const string &paramValue);
	void setDate(int index, const Date &date);
	void setDateTime(int index, const Date &date);
	
	int executeUpdate() DECL_THROW_EXCEPTION(SQLException);
	void executeQuery() DECL_THROW_EXCEPTION(SQLException);
	static void TransactionStart();
	static void TransactionEnd();
	static void RollBack();
	static void Commit();
	
	bool next() DECL_THROW_EXCEPTION(SQLException);
	char getByte(int index);
	short getShort(int index);
	int getInt(int index);
	LONG_LONG getLong(int index);
	float getFloat(int index);
	double getDouble(int index);
	string getString(int index);
	string getBlob(int index);
	Date getDate(int index);
	Date getTime(int index);
	Date getDateTime(int index);
		
private:
	DbConnect(const DbConnect &dbconn){}
	DbConnect &operator=(const DbConnect &dbconn) { return *this; }
	
	xConnection *m_pConn;
	xPrepareStatement *m_pStmt;
	xResultSet *m_rs;
	string m_sRunSql;
	int iCurrIndex;	
};

#endif