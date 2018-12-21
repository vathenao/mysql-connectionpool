#ifndef __X_CONNECTION_H__
#define __X_CONNECTION_H__

#include "xdbcdefs.h"
#include "sqlException.h"

class xPrepareStatement;
class xConnection
{
public:
	xConnection()
	{
		m_bIsFree = true;
	}
	
	virtual ~xConnection()
	{
		
	}
	
	/*
	**<D>:Prepare the statement is used to query database
	**<P>:Query statement(SQL)
	**<R>:A pointer to an XStatement instance, a handle is used to all subsequent operations whit the statement.
	*/
	virtual xPrepareStatement* prepareStatement(const string &sqlStr) DECL_THROW_EXCEPTION(SQLException)=0;
	
	virtual void TransactionStart()=0;
	virtual void TransactionEnd()=0;
	virtual void RollBack()=0;
	virtual void Commit()=0;
	virtual void ConnectToDB() = 0;
	
	/*
	**<D>:Lock the connection
	**<P>:None
	**<R>:None
	*/
	virtual void Lock()
	{
		m_bIsFree = false;
	}
	
	/*
	**<D>:UnLock the connection
	**<P>:None
	**<R>:None
	*/
	virtual void UnLock()
	{
		m_bIsFree = true;
	}
	
	/*
	**<D>:Check the connection is free or not
	**<P>:None
	**<R>:None
	*/
	virtual bool IsFree()
	{
		return m_bIsFree;
	}
	
	/*
	**<D>:Check the connection is lock or not 
	**<P>:None
	**<R>:None
	*/
	virtual bool IsLock()
	{
		return !m_bIsFree;
	}

	virtual bool IsConnected()
	{
		return false;
	}
	
protected:
	bool m_bIsFree;	//In general,this property will be used to describe a connection that in a connection pool is free or not
};

#endif