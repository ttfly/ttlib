#include "TTGlobal.h"
#include "TTCommonThread.h"

class CTestThread : public CThread
{
public:
	CTestThread()
	{
		m_nCount = 0;
	}
	virtual ~CTestThread()
	{

	}
public:
	virtual void Execute();
private:
	int32_t m_nCount;
};

void CTestThread::Execute()
{
	while (!GetTerminated())
	{
		printf("%s, count%d\n", GetName(), m_nCount++);
		usleep(1000000);
	}
	pthread_exit(NULL);
}

int main()
{
	int32_t nThreadCount = 5;
	CTestThread testThreads[nThreadCount];
	for (int32_t i = 0; i < nThreadCount; ++i)
	{
		char threadName[64];
		sprintf(threadName, "thread%d", i + 1);
		testThreads[i].SetName(threadName);
		testThreads[i].Start();
	}
	while (true)
	{
		char in = getchar();
		if ('t' == in)
		{
			for (int32_t i = 0; i < nThreadCount; ++i)
			{
				testThreads[i].Terminate();
			}
		}
		else if ('s'==in)
		{
			break;
		}
		if ('b' == in)
		{
			for (int32_t i = 0; i < nThreadCount; ++i)
			{
				testThreads[i].Start();
			}
		}
		usleep(1000);
	}
}