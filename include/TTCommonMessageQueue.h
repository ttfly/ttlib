#ifndef __TTCOMMON_MESSAGEQUEUE_H__
#define __TTCOMMON_MESSAGEQUEUE_H__

#include "TTGlobal.h"
#include "TTCommonMutex.h"
#include "TTNocopyable.h"

template <class T>
class CMessageQueue : Noncopyable
{
public:
	CMessageQueue(){}
	~CMessageQueue(){}
public:
	void Push(const T& message)
	{
		if (0 == m_Mutex.Lock())
		{
			m_Queue.push_back(message);
			m_Mutex.UnLock();
		}
		else
		{
			assert(0, "Push Fail");
		}
	}

	T Pop()
	{
		if (0!= m_Mutex.TryLock())
		{
			return T();
		}
		if (m_Queue.empty())
		{
			m_Mutex.UnLock();
			return T();
		}
		T message = T();
		if (!m_Queue.empty())
		{
			message = m_Queue.front();
			m_Queue.pop_front();
		}
		m_Mutex.UnLock();
		return message;
	}
	bool Pop(T& t)
	{
		if (m_Queue.empty())
		{
			return false;
		}
		t = Pop();
		return true;
	}
	T Front()
	{
		if (0 != m_Mutex.TryLock())
		{
			return T();
		}
		if (m_Queue.empty())
		{
			m_Mutex.UnLock();
			return T();
		}
		T message = T();
		if (!m_Queue.empty())
		{
			message = m_Queue.front();
		}
		m_Mutex.UnLock();
		return message;
	}
	int32_t Size()
	{
		return deque.size();
	}
private:
	CommonMutex m_Mutex;
	std::deque<T> m_Queue;
};

#endif