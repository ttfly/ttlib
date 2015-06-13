#ifndef __COMMONTHREAD_H__
#define __COMMONTHREAD_H__
#include "TTGlobal.h"

enum 
{
	enmThreadNameLen = 256,
	enmThreadLogLen = 256
};


class CThread
{
public:
	CThread();
	virtual ~CThread();
public:
	int32_t Start();
	virtual int32_t Terminate();
	virtual void	Execute();
	bool	GetTerminated();
	void	SetTerminated(bool bTerminate);

	const char* GetName();
	void SetName(const char* sName);

	const char* GetLogName();
	void SetLogName(const char* sLogName);

	static bool IsSetPrivateKeyLog();
	static void SetPrivateKeyLog();

	static int32_t InitPrivateKeyLog();
	static CThread* GetLogCtxByPrivateKey();
private:
	pthread_t  m_Thread;
	pthread_mutex_t m_Mutex;
	bool	m_bTerminated;
	char m_szName[enmThreadNameLen];
	char m_szLogName[enmThreadLogLen];
	static bool ms_bIsSetPrivateKeyLog;
	static pthread_key_t m_PrivateKeyLog;

};


#endif