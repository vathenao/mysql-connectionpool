#ifndef __MYSQL_RESULTSET_H__
#define __MYSQL_RESULTSET_H__

#include "x_resultset.h"

class MysqlResultSet: public xResultSet
{
public:
	MysqlResultSet(MYSQL_STMT* stmt);
	~MysqlResultSet();
	
	bool next() DECL_THROW_EXCEPTION(SQLException);
	char getByte(size_t index);
	short getShort(size_t index);
	int getInt(size_t index);
	LONG_LONG getLong(size_t index);
	float getFloat(size_t index);
	double getDouble(size_t index);
	string getString(size_t index);
	string getBlob(size_t index);
	Date getDate(size_t index);
	Date getTime(size_t index);
	Date getDateTime(size_t index);

private:
	void BindResultSet();
	void ReleaseVecBind();
	void ReleaseVecIsNull();
	
private:
	MYSQL_STMT* m_pStmt;
	MYSQL_RES *m_pResMeta;
	vector<MYSQL_BIND> m_vecBind;
	vector<my_bool> m_vecIsNull;
};

#endif