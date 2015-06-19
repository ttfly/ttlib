#ifndef  __TTCOMMON_MUTEX_H__
#define  __TTCOMMON_MUTEX_H__

#include "TTGlobal.h"

class CommonMutex
{
public:
	CommonMutex()
	{
		pthread_mutex_init(&m_Mutex, NULL);
	}
	virtual ~CommonMutex()
	{
		pthread_mutex_destroy(&m_Mutex);
	}
public:
	int32_t Lock()
	{
		return pthread_mutex_lock(&m_Mutex);
	}
	int32_t UnLock()
	{
		return pthread_mutex_unlock(&m_Mutex);
	}
	int32_t TryLock()
	{
		return pthread_mutex_trylock(&m_Mutex);
	}
private:
	pthread_mutex_t m_Mutex;
};

#endif