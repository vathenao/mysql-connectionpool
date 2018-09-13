#include "stdafx.h"
#include "dbconnect.h"
#include "connpool.h"
#include "x_prepareStatement.h"
#include "x_resultset.h"

#define TIMEOUT 0

DbConnect::DbConnect()
{
	ConnectionPool::GetInstance()->GetConnection(&m_pConn,TIMEOUT);
	m_sRunSql = "";
	iCurrIndex = 0;
	m_pStmt = NULL;
	m_rs = NULL;
}

DbConnect::~DbConnect()
{
	ConnectionPool::GetInstance()->ReleaseConnection(m_pConn);
	
	if( m_pStmt )
	{
		delete m_pStmt;
	}
	
	if( m_rs )
	{
		delete m_rs;
	}
}

void DbConnect::SetSqlText(string sql)
{
	if( m_pStmt )
	{
		delete m_pStmt;
		m_pStmt = NULL;
	}

	m_sRunSql = sql;
	m_pStmt = m_pConn->prepareStatement(m_sRunSql);
}


void DbConnect::setInt(int index, const int &value)
{
	if( index <= iCurrIndex++)
	{
		char errmsg[65];
		snprintf(errmsg, 64, "Invalid Index[%d] for binding param.", index);
		throw SQLException(errmsg);
	}
	
	m_pStmt->setInt(index, value);
}

void DbConnect::setString(int index, const string &value)
{
	if( index <= iCurrIndex++)
	{
		char errmsg[65];
		snprintf(errmsg, 64, "Invalid Index[%d] for binding param.", index);
		throw SQLException(errmsg);
	}
	
	m_pStmt->setString(index, value);
}

void DbConnect::setDate(int index, const Date &value)
{
	if( index <= iCurrIndex++)
	{
		char errmsg[65];
		snprintf(errmsg, 64, "Invalid Index[%d] for binding param.", index);
		throw SQLException(errmsg);
	}
	
	m_pStmt->setDate(index, value);
}

void DbConnect::setDateTime(int index, const Date &value)
{
	if( index <= iCurrIndex++)
	{
		char errmsg[65];
		snprintf(errmsg, 64, "Invalid Index[%d] for binding param.", index);
		throw SQLException(errmsg);
	}
	
	m_pStmt->setDateTime(index, value);
}

int DbConnect::executeUpdate() DECL_THROW_EXCEPTION(SQLException)
{
	return m_pStmt->executeUpdate(m_sRunSql);
}

void DbConnect::executeQuery() DECL_THROW_EXCEPTION(SQLException)
{
	if( m_rs )
	{
		delete m_rs;
		m_rs = NULL;
	}
	
	m_rs = m_pStmt->executeQuery(m_sRunSql);
}

void DbConnect::TransactionStart()
{
	m_pConn->TransactionStart();
}

void DbConnect::TransactionEnd()
{
	m_pConn->TransactionEnd();
}

void DbConnect::RollBack()
{
	m_pConn->RollBack();
}

void DbConnect::Commit()
{
	m_pConn->Commit();
}

bool DbConnect::next() DECL_THROW_EXCEPTION(SQLException)
{
	if( !m_rs )
	{
		return false;
	}
	return m_rs->next();
}

char DbConnect::getByte(int index)
{
	return m_rs->getByte(index);
}

short DbConnect::getShort(int index)
{
	return m_rs->getShort(index);
}

int DbConnect::getInt(int index)
{
	return m_rs->getInt(index);
}

LONG_LONG DbConnect::getLong(int index)
{
	return m_rs->getLong(index);
}

float DbConnect::getFloat(int index)
{
	return m_rs->getFloat(index);
}

double DbConnect::getDouble(int index)
{
	return m_rs->getDouble(index);
}

string DbConnect::getString(int index)
{
	return m_rs->getString(index);
}

string DbConnect::getBlob(int index)
{
	return m_rs->getBlob(index);
}

Date DbConnect::getDate(int index)
{
	return m_rs->getDate(index);
}

Date DbConnect::getTime(int index)
{
	return m_rs->getTime(index);
}

Date DbConnect::getDateTime(int index)
{
	return m_rs->getDateTime(index);
}