#include "xdbcWrapper.h"


xStmtWrapper::xStmtWrapper(xPrepareStatement* pStmt, const string &runSql) DECL_THROW_EXCEPTION(SQLException):m_pStmt(pStmt), m_runSql(runSql)
{
	if( !m_pStmt )
	{
		throw SQLException("construct xStmtWrapper fail, xPrepareStatement is null.");
	}
}

xStmtWrapper::~xStmtWrapper()
{
	if( m_pStmt )
	{
		delete m_pStmt;
	}
}

void xStmtWrapper::ReSet(xPrepareStatement* pStmt, const string &runSql) 
{
	if( m_pStmt )
	{
		delete m_pStmt;
	}
	
	m_pStmt = pStmt;
	m_runSql = runSql;
}

int xStmtWrapper::executeUpdate() DECL_THROW_EXCEPTION(SQLException)
{
	return m_pStmt->executeUpdate(m_runSql);
}

xResultSet * xStmtWrapper::executeQuery() DECL_THROW_EXCEPTION(SQLException)
{
	return m_pStmt->executeQuery(m_runSql);
}

void xStmtWrapper::setInt(int index, const int &value)
{
	m_pStmt->setInt(index, value);
}

void xStmtWrapper::setString(int index, const string &value)
{
	m_pStmt->setString(index, value);
}

void xStmtWrapper::setDate(int index, const Date &value)
{
	m_pStmt->setDate(index, value);
}

void xStmtWrapper::setDateTime(int index, const Date &value)
{
	m_pStmt->setDateTime(index, value);
}


xRsWrapper::xRsWrapper(xResultSet * rs ):m_rs(rs)
{
	
}

xRsWrapper::~xRsWrapper()
{
	if( m_rs )
	{
		delete m_rs;
	}
}

void xRsWrapper::ReSet(xResultSet * rs )
{
	m_rs = rs;
}

bool xRsWrapper::next() DECL_THROW_EXCEPTION(SQLException)
{
	return m_rs->next();
}

char xRsWrapper::getByte(int index)
{
	return m_rs->getByte(index);
}

short xRsWrapper::getShort(int index)
{
	return m_rs->getShort(index);
}

int xRsWrapper::getInt(int index)
{
	return m_rs->getInt(index);
}

LONG_LONG xRsWrapper::getLong(int index)
{
	return m_rs->getLong(index);
}

float xRsWrapper::getFloat(int index)
{
	return m_rs->getFloat(index);
}

double xRsWrapper::getDouble(int index)
{
	return m_rs->getDouble(index);
}

string xRsWrapper::getString(int index)
{
	return m_rs->getString(index);
}

string xRsWrapper::getBlob(int index)
{
	return m_rs->getBlob(index);
}

Date xRsWrapper::getDate(int index)
{
	return m_rs->getDate(index);
}

Date xRsWrapper::getTime(int index)
{
	return m_rs->getTime(index);
}

Date xRsWrapper::getDateTime(int index)
{
	return m_rs->getDateTime(index);
}







