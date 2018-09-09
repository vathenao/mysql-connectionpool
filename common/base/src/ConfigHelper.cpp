#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ConfigHelper.h"
#include "BaseException.h"

__WILLOW_BEGIN_NAMESPACE

VConfigHelper::VConfigHelper():m_fpConfig(NULL)
{
	
}

VConfigHelper::VConfigHelper(const string &fileName)
{
	m_fileName = fileName;
	Initialize();
}

VConfigHelper::~VConfigHelper()
{
	Close();
}

void VConfigHelper::ReLoad(const string &fileName)
{
	Close();
	m_fileName = fileName;
	Initialize();
}

void VConfigHelper::LoadFile(const string &fileName)
{
	if( NULL==( m_fpConfig=fopen(fileName.c_str(),"r") ) )
	{
		m_fpConfig = NULL;
		m_iErrorCode = VCHP_FILE_NOTFOUND;
		m_sErrorMsg = "fail to load config file \"";
		m_sErrorMsg.append( fileName );
		m_sErrorMsg.append("\". ");
		throw CBaseException(m_sErrorMsg);
	}
}

void VConfigHelper::Initialize()
{
	LoadFile(m_fileName);
	
	m_preLine = "";
	m_sCurSection = "";
	m_sCurKey = "";
	m_sCurValue = "";
}

void VConfigHelper::Close()
{
	if( m_fpConfig )
	{
		fclose(m_fpConfig);
		m_fpConfig = NULL;
	}
}

bool VConfigHelper::GetConfigStringValue(const string &sectionName, const string &keyName, OUT string &keyValue)
{
	IntoSection(sectionName);
	
	if( ReadKeyValue(keyName) )
	{
		keyValue = m_sCurValue;
		return true;
	}
	
	return false;
}

bool VConfigHelper::GetConfigLongValue(const string &sectionName, const string &keyName, OUT long &keyValue)
{
	IntoSection(sectionName);
	
	if( ReadKeyValue(keyName) )
	{
		keyValue = StringToLong(m_sCurValue);
		return true;
	}
	
	return false;
}

bool VConfigHelper::GetConfigIntValue(const string &sectionName, const string &keyName, OUT int &keyValue)
{
	IntoSection(sectionName);
	
	if( ReadKeyValue(keyName) )
	{
		keyValue = (int)StringToLong(m_sCurValue);
		return true;
	}
	
	return false;
}

void VConfigHelper::IntoSection(const string &sSectionName)
{
	fseek(m_fpConfig, 0, SEEK_SET);
	char szBuffer[MAX_CHARACTER_OF_LINE];
	char *pStr1,*pStr2;
	
	while( !feof(m_fpConfig) )
    {
        if( NULL==fgets(szBuffer,MAX_CHARACTER_OF_LINE-1,m_fpConfig) )
            break;
        pStr1 = szBuffer;
		m_preLine = szBuffer;
		
        while( (' '==*pStr1) || ('\t'==*pStr1) )
            pStr1++;
        if( '['==*pStr1 )
        {
            pStr1++;
            while( (' '==*pStr1) || ('\t'==*pStr1) )
                pStr1++;
            pStr2 = pStr1;
            while( (']'!=*pStr1) && ('\0'!=*pStr1) )
                pStr1++;
            if( '\0'==*pStr1)
                continue;
            while( ' '==*(pStr1-1) )
                pStr1--;
            *pStr1 = '\0';
			
            if( isEqual(sSectionName, pStr2) )
			{
				m_sCurSection = sSectionName;
				m_iErrorCode = VCHP_SUCCESS;
				return;
			}
		}	
	}
	
	m_iErrorCode = VCHP_SECTION_NOTFOUND;
	m_sErrorMsg = "can not find section \"[";
	m_sErrorMsg.append( sSectionName );
	m_sErrorMsg.append("]\" in config file \"");
	m_sErrorMsg.append( m_fileName );
	m_sErrorMsg.append("\". ");
	//throw CBaseException(m_sErrorMsg);
}

bool VConfigHelper::ReadKeyValue(const string &keyName)
{
	char szBuffer[MAX_CHARACTER_OF_LINE];
	char pOutKeyValue[MAX_CHARACTER_OF_LINE] = "";
    char *pStr1,*pStr2,*pStr3;
    unsigned int uiLen;
	
    memset(szBuffer,0,sizeof(szBuffer));
    while( !feof(m_fpConfig) )
    {
        if( NULL==fgets(szBuffer,MAX_CHARACTER_OF_LINE - 1,m_fpConfig) )
            break;
        pStr1 = szBuffer;
		m_preLine = szBuffer;
        while( (' '==*pStr1) || ('\t'==*pStr1) )
            pStr1++;
        if( '#'==*pStr1 )
            continue;
        if( ('/'==*pStr1)&&('/'==*(pStr1+1)) )
            continue;
        if( ('\0'==*pStr1)||(0x0d==*pStr1)||(0x0a==*pStr1) )
            continue;
        if( '['==*pStr1 )
        {
            pStr2 = pStr1;
            while( (']'!=*pStr1)&&('\0'!=*pStr1) )
                pStr1++;
            if( ']'==*pStr1 )
			{
				//next section is found
                break;
			}
            pStr1 = pStr2;
        }
        pStr2 = pStr1;
        while( ('='!=*pStr1)&&('\0'!=*pStr1) )
            pStr1++;
        if( '\0'==*pStr1 )
            continue;
        pStr3 = pStr1+1;
        if( pStr2==pStr1 )
            continue;
        *pStr1 = '\0';
        pStr1--;
        while( (' '==*pStr1)||('\t'==*pStr1) )
        {
            *pStr1 = '\0';
            pStr1--;
        }
		
		if( isEqual(keyName, pStr2) )
		{
			m_sCurKey = keyName;
			
			pStr1 = pStr3;
            while( (' '==*pStr1)||('\t'==*pStr1) )
                pStr1++;
            pStr3 = pStr1;
            while( ('\0'!=*pStr1)&&(0x0d!=*pStr1)&&(0x0a!=*pStr1) )
            {
                if( ('/'==*pStr1)&&('/'==*(pStr1+1)) )
                    break;
                pStr1++;
            }
            *pStr1 = '\0';
            uiLen = strlen(pStr3);
            memcpy(pOutKeyValue,pStr3,uiLen);
            *(pOutKeyValue+uiLen) = '\0';
			m_sCurValue = pOutKeyValue;
			m_iErrorCode = VCHP_SUCCESS;
			return true;
		}
	}
	
	m_iErrorCode = VCHP_KEY_NOTFOUND;
	m_sErrorMsg = "can not find key \"";
	m_sErrorMsg.append( keyName );
	m_sErrorMsg.append("\" in section \"[");
	m_sErrorMsg.append( m_sCurSection );
	m_sErrorMsg.append("]\". ");
	
	return false;
}

string VConfigHelper::GetLastErrorMsg()
{
	return m_sErrorMsg;
}

VCHPERRCODE VConfigHelper::GetLastErrorCode()
{
	return m_iErrorCode;
}

__WILLOW_END_NAMESPACE
