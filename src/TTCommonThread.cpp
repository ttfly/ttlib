#include "TTCommonThread.h"

bool CThread::ms_bIsSetPrivateKeyLog;
pthread_key_t CThread::m_PrivateKeyLog;

void* ThreadProc(void* pParam)
{
	if (!pParam)
	{
		return pParam;
	}
	CThread* pThread = (CThread*)pParam;
	pThread->Execute();
	return NULL;
}

CThread::CThread()
{
	m_Thread = 0;
	m_bTerminated = false;
	m_szName[0] = '\0';
	m_szLogName[0] = '\0';
}

CThread::~CThread()
{
	Terminate();
}

int32_t CThread::Start()
{
	m_bTerminated = false;
	pthread_create(&m_Thread, NULL, ThreadProc, this);
	return S_OK;
}

int32_t CThread::Terminate()
{
	if (m_bTerminated)
	{
		return S_OK;
	}
	m_bTerminated = true;
	if (m_Thread != 0)
	{
		pthread_join(m_Thread, NULL);
	}
	return S_OK;
}

void	CThread::Execute()
{
	uint32_t n = 0;
	while (!m_bTerminated)
	{
		if ((++n) % 1000 == 0)
		{
			printf("%d\n", n);
		}
		usleep(1000);
	}
	pthread_exit(NULL);
}

bool	CThread::GetTerminated()
{
	return m_bTerminated;
}

void	CThread::SetTerminated(bool bTerminate)
{

}

const char* CThread::GetName()
{
	return m_szName;
}
void CThread::SetName(const char* sName)
{
	strncpy(m_szName, sName, sizeof(m_szName));
}

const char* CThread::GetLogName()
{
	return m_szLogName;
}
void CThread::SetLogName(const char* sLogName)
{
	strncpy(m_szLogName, sLogName, sizeof(m_szLogName));
}

bool CThread::IsSetPrivateKeyLog()
{
	return ms_bIsSetPrivateKeyLog;
}

void CThread::SetPrivateKeyLog()
{
	ms_bIsSetPrivateKeyLog = true;
}

int32_t CThread::InitPrivateKeyLog()
{
	return pthread_key_create(&m_PrivateKeyLog, NULL);
}

CThread* CThread::GetLogCtxByPrivateKey()
{
	void *pData = pthread_getspecific(m_PrivateKeyLog);
}
