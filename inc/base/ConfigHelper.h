#ifndef __CONFIG_HELPER_H__
#define __CONFIG_HELPER_H__

#include "libcommon.h"
#include "pubfunc.h"

__WILLOW_BEGIN_NAMESPACE

/*<D> Declare error code  when an error is occured by reading the configuration file*/
/*<Remark> You can Use the GetLastErrorCode function to get the error code*/
typedef enum tagVCHPERRCODE{
	VCHP_SUCCESS,	//success code
	VCHP_FILE_NOTFOUND,	//can not find configuration file
	VCHP_SECTION_NOTFOUND,	//can not find section
	VCHP_KEY_NOTFOUND		//can not find key
}VCHPERRCODE;

#define MAX_CHARACTER_OF_LINE 1025

class VConfigHelper
{
public:
	VConfigHelper();
	VConfigHelper(const string &fileName);
	~VConfigHelper();
	
	/*<D> Get the value is specified by the designated section and key from a configuration file.*/
	/*<P> sectionName: Section name in the configuration file.*/
	/*<P> keyName: Key name in the configuration file. */
	/*<P> keyVlue: The reference of a string variable to receive the value.*/
	/*<R> true if success, false if failure.*/
	/*<Remark> You can use the GetLastErrorMsg to get the error message and use the GetLastErrorCode
	function to get the Last error code, more information of the error code, refer to the VCHPERRCODE.*/
	bool GetConfigStringValue(const string &sectionName, const string &keyName, OUT string &keyValue);
	
	/*<D> Get the value is specified by the designated section and key from a configuration file.*/
	/*<P> sectionName: Section name in the configuration file.*/
	/*<P> keyName: Key name in the configuration file. */
	/*<P> keyVlue: The reference of a long variable to receive the value.*/
	/*<R> true if success, false if failure.*/
	bool GetConfigLongValue(const string &sectionName, const string &keyName, OUT long &keyValue);
	
	/*<D> Get the value is specified by the designated section and key from a configuration file.*/
	/*<P> sectionName: Section name in the configuration file.*/
	/*<P> keyName: Key name in the configuration file. */
	/*<P> keyVlue: The reference of an int variable to receive the value.*/
	/*<R> true if success, false if failure.*/
	bool GetConfigIntValue(const string &sectionName, const string &keyName, OUT int &keyValue);
	
	/*<D> Reloads config file with a given filename. You must load a file with this function 
	when you construe an instance of VConfigHelper with the default constructor*/
	/*<P> fileName: Filename of the config file which will be reload*/
	/*<R> None*/
	/*<E> Same as Load function*/
	void ReLoad(const string &fileName);
	
	//get last error code
	VCHPERRCODE GetLastErrorCode();
	
	//get last error message
	string GetLastErrorMsg();
private:

	void Initialize();
	/*<D> Loads config file with a given filename.*/
	/*<P> Filename of the config file*/
	/*<R> None*/
	/*<E> CBaseException: The exception would occur when the file which it's path given by 
	fileName cann't be load such as fileName does no exist.*/
	void LoadFile(const string &fileName);
	
	void IntoSection(const string &sectionName);
	
	bool ReadKeyValue(const string &keyName);
	
	
	
	void Close();
private:
	FILE *m_fpConfig;	//file descriptor
	string m_preLine;	// character string of the line which directed by the file descriptor previous
	string m_fileName;
	
	string m_sCurSection;
	string m_sCurKey;
	string m_sCurValue;
	
	string m_sErrorMsg;
	VCHPERRCODE m_iErrorCode; 
};

__WILLOW_END_NAMESPACE

#endif