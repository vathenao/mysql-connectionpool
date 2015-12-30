#ifndef __MYSQL_RESULTSET_H__
#define __MYSQL_RESULTSET_H__

#include "x_resultset.h"
#include <vector>

#define VTH_MAX_FEILD 200
#define VTH_MAX_CHAR_SIZE 513

class MysqlResultSet: public xResultSet
{
public:
	MysqlResultSet(MYSQL_STMT* stmt);
	~MysqlResultSet();
	
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
	void BindResultSet(vector<MYSQL_BIND> &vecBind);
	
private:
	MYSQL_STMT* m_pStmt;
	MYSQL_RES *m_pResMeta;
	vector<MYSQL_BIND> m_vecBind;
	
	my_bool is_null[VTH_MAX_FEILD];
	my_bool error[VTH_MAX_FEILD];
	unsigned long length[VTH_MAX_FEILD];
	
};

#endif