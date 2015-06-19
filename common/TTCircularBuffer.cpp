#include "TTCircularBuffer.h"

CircularBuffer::CircularBuffer(uint32_t nSize)
{
	m_pBuff = new char(nSize);
	m_nHead = 0;
	m_nTail = 0;
	m_nContentSize = 0;
	m_nCount = 0;
	m_nMaxSize = nSize;
}

CircularBuffer::~CircularBuffer()
{
	if (m_pBuff)
	{
		delete[] m_pBuff;
		m_pBuff = NULL;
	}
}

int32_t CircularBuffer::Read(char* pBuff, uint32_t nLen)
{
	/*if (!pBuff || 0>=nLen)
	{
		return E_INVALIDARGUMENT;
	}*/
	if (m_nHead > m_nMaxSize || m_nMaxSize)
	{
		Reset();
		return E_CIRCULARBUFF_WRONG;
	}
	if (nLen > m_nContentSize)
	{
		return E_CIRCULARBUFF_NOT_ENOUGH_DATA;
	}
	char* pStartBuff = GetStart();
	if (m_nTail > m_nHead)
	{
		if (pBuff)
		{
			memcpy(pBuff, pStartBuff, nLen);
		}
	}
	else
	{
		if (nLen > (m_nMaxSize-m_nHead))
		{
			//·Ö¶Î¿½±´
			if (pBuff)
			{
				memcpy(pBuff, pStartBuff, m_nMaxSize - m_nHead);
				memcpy(pBuff + (m_nMaxSize - m_nHead), m_pBuff, (nLen - (m_nMaxSize - m_nHead)));
			}
		}
		else
		{
			if (pBuff)
			{
				memcpy(pBuff, pStartBuff, nLen);
			}
		}
	}
	m_nContentSize -= nLen;
	m_nHead = (m_nHead + nLen) % m_nMaxSize;
	if (m_nContentSize<=0)
	{
		m_nHead = m_nTail = 0;
	}
	return S_OK;
}

int32_t CircularBuffer::Write(const char* pBuff, uint32_t nLen)
{
	if (m_nHead >= m_nMaxSize || m_nTail >= m_nMaxSize)
	{
		Reset();
		return E_CIRCULARBUFF_WRONG;
	}
	uint32_t nFreeSize = GetSpace();
	if (nFreeSize < nLen)
	{
		return E_CIRCULARBUFF_SPACE_NOT_ENOUGH;
	}
	char* pBuffStart = GetStart();
	if (m_nTail < m_nHead)
	{
		memcpy(pBuffStart, pBuff, nLen);
	}
	else
	{
		if (nLen > (m_nMaxSize - m_nTail))
		{
			memcpy(pBuffStart, pBuff, m_nMaxSize - m_nTail);
			memcpy(m_pBuff, pBuff + (m_nMaxSize - m_nTail), nLen - (m_nMaxSize - m_nTail));
		}
		else
		{
			memcpy(pBuffStart, pBuff, nLen);
		}
	}
	m_nTail = (m_nTail + nLen) % m_nMaxSize;
	m_nContentSize += nLen;
	m_nCount += nLen;
	return S_OK;
}

int32_t CircularBuffer::SoftRead(char* pBuff, uint32_t nLen)
{
	/*if (!pBuff || 0>=nLen)
	{
	return E_INVALIDARGUMENT;
	}*/
	if (nLen > m_nContentSize)
	{
		return E_CIRCULARBUFF_NOT_ENOUGH_DATA;
	}
	char* pStartBuff = GetStart();
	if (m_nTail > m_nHead)
	{
		if (pBuff)
		{
			memcpy(pBuff, pStartBuff, nLen);
		}
	}
	else
	{
		if (nLen > (m_nMaxSize - m_nHead))
		{
			//·Ö¶Î¿½±´
			if (pBuff)
			{
				memcpy(pBuff, pStartBuff, m_nMaxSize - m_nHead);
				memcpy(pBuff + (m_nMaxSize - m_nHead), m_pBuff, (nLen - (m_nMaxSize - m_nHead)));
			}
		}
		else
		{
			if (pBuff)
			{
				memcpy(pBuff, pStartBuff, nLen);
			}
		}
	}
	/*m_nContentSize -= nLen;
	m_nHead = (m_nHead + nLen) % m_nMaxSize;
	if (m_nContentSize <= 0)
	{
		m_nHead = m_nTail = 0;
	}*/
	return S_OK;
}

int32_t CircularBuffer::Remove(uint32_t nLen)
{
	return Read(NULL, nLen);
}

char* CircularBuffer::GetStart()
{
	return (char*)(m_pBuff + m_nHead);
}

uint32_t CircularBuffer::GetSpace()
{
	return (m_nMaxSize - m_nContentSize);
}

void CircularBuffer::Reset()
{
	m_nHead = 0;
	m_nTail = 0;
	m_nContentSize = 0;
	m_nCount = 0;
}