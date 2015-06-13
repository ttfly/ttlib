#ifndef __TTCODEQUEUE_H__
#define __TTCODEQUEUE_H__

#include "TTGlobal.h"

template<uint32_t CAPACITY>
class CCodeQueue
{
public:
	enum 
	{
		enmReservedCodeLength = 8,	//Ô¤Áô¿Õ¼ä³¤¶È
	};
	int32_t Initilize()
	{
		m_nHead = 0;
		m_nTail = 0;
		m_nSize = CAPACITY;
		memset(m_arrCodeBuff, 0, sizeof(m_arrCodeBuff));
		return S_OK;
	}

	int32_t Resume()
	{
		return S_OK;
	}

	int32_t Unintilize()
	{
		return S_OK;
	}

	int32_t	Push(const uint8_t* pBuffer, uint32_t nLength)
	{
		if (!pBuffer || 0>=nLength)
		{
			return E_INVALIDARGUMENT;
		}
		uint8_t* pCodeBuff = GetCodeBuff();
		if (!pCodeBuff || 0 >= m_nSize)
		{
			return E_CODEQUEUE_NOT_INITIALIZED;
		}
		if (IsFull())
		{
			return E_CODEQUEUE_FULL;
		}
		uint32_t nHead = m_nHead;
		uint32_t nTail = m_nTail;
		uint32_t nFreeSize = GetFreeSize();
		if (nHead >= m_nSize || nTail >= m_nSize)
		{
			SetBoundary(0, 0);
			return E_CODEQUEUE_WRONG;
		}
		if ((nLength+sizeof(uint32_t))>nFreeSize)
		{
			return E_CODEQUEUE_SPACE_NOT_ENOUGH;
		}
		uint8_t* p = (uint8_t*)&nLength;
		for (size_t i = 0; i < sizeof(uint32_t);++i)
		{
			pCodeBuff[nTail] = p[i];
			nTail = (nTail + 1) % m_nSize;
		}
		if (nTail < nHead)
		{
			memcpy(pCodeBuff+nTail, pBuffer, nLength);
		}
		else
		{
			if (nLength>(m_nSize - nTail))
			{
				memcpy(pCodeBuff + nTail, pBuffer, m_nSize - nTail);
				memcpy(pCodeBuff, pBuffer + (m_nSize - nTail), nLength - (m_nSize - nTail));
			}
			else
			{
				memcpy(pCodeBuff + nTail, pBuffer, nLength);
			}
		}
		nTail = (nTail + nLength) % m_nSize;
		return SetTail(nTail);
	}

	int32_t Front(uint8_t* pBuff, uint32_t nSize, uint32_t& nLength)
	{
		return S_OK;
	}

	int32_t Pop(uint32_t nLen)
	{
		return S_OK;
	}

	int32_t Pop(uint8_t* pBuff, uint32_t nSize, uint32_t& nLength)
	{
		if (!pBuff || 0>=nSize)
		{
			return E_INVALIDARGUMENT;
		}
		uint8_t* pCodeBuff = GetCodeBuff();
		if (0>=m_nSize || !pCodeBuff)
		{
			return E_CODEQUEUE_NOT_INITIALIZED;
		}
		if (IsEmpty())
		{
			return E_CODEQUEUE_EMPTY;
		}
		if (m_nHead > m_nSize || m_nTail > m_nSize)
		{
			SetBoundary(0, 0);
			return E_INVALID_CODEQUEUE_HEAD;
		}
		uint32_t nUsedSize = GetUsedSize();
		uint32_t nHead = m_nHead;
		uint32_t nTail = m_nTail;
		uint32_t nRealSize = 0;
		uint8_t* p = (uint8_t*)&nRealSize;
		for (size_t i = 0; i < sizeof(uint32_t); ++i)
		{
			p[i] = pCodeBuff[nHead];
			nHead = (nHead + 1) % m_nSize;
		}
		if (nRealSize <=0 || (nRealSize+sizeof(uint32_t)) > nUsedSize)
		{
			SetBoundary(0, 0);
			return E_CODEQUEUE_WRONG;
		}
		if (nSize < nRealSize)
		{
			nHead = (nRealSize + nHead) % m_nSize;
			SetHead(nHead);
			return E_INVALIDARGUMENT;
		}
		nLength = nRealSize;
		if (nTail > nHead)
		{
			memcpy(pBuff, pCodeBuff + nHead, nRealSize);
		}
		else
		{
			if (nRealSize <= (m_nSize-nHead))
			{
				memcpy(pBuff, pCodeBuff + nHead, nRealSize);
			}
			else
			{
				memcpy(pBuff, pCodeBuff + nHead, m_nSize - nHead);
				memcpy(pBuff + (m_nSize - nHead), pCodeBuff, nRealSize - (m_nSize - nHead));
			}
		}
		nHead = (nHead + nRealSize) % m_nSize;
		SetHead(nHead);
		return S_OK;
	}

	
	bool IsFull() const
	{
		return (GetFreeSize() <= 0);
	}

	bool IsEmpty() const
	{
		return (GetUsedSize() <= 0);
	}

	uint32_t GetHead() const { return m_nHead; }
	uint32_t GetTail() const { return m_nTail; }
	uint32_t GetCapacity()const { return CAPACITY; }
	void	GetBoundary(int32_t& nHead, int32_t& nTail)const
	{
		if (m_nHead >= m_nSize || m_nTail >= m_nSize)
		{
			return;
		}
		nHead = m_nHead;
		nTail = m_nTail;
	}

	uint32_t GetFreeSize()const
	{
		if (m_nSize <= enmReservedCodeLength)
		{
			return 0;
		}
		uint32_t nFreeSize = (m_nTail == m_nHead) ? m_nSize : (m_nHead + m_nSize - m_nTail) % m_nSize;
		return nFreeSize;
	}

	uint32_t GetUsedSize()const
	{
		if (m_nSize <= enmReservedCodeLength)
		{
			return 0;
		}
		uint32_t nUseSize = (m_nTail + m_nSize - m_nHead) % m_nSize;
		return nUseSize;

	}

	int32_t SetHead(uint32_t nHead)
	{
		if (nHead > m_nSize)
		{
			return E_INVALID_CODEQUEUE_HEAD;
		}
		m_nHead = nHead;
		return S_OK;
	}

	int32_t SetTail(uint32_t nTail)
	{
		if (nTail > m_nSize)
		{
			return E_INVALID_CODEQUEUE_TAIL;
		}
		m_nTail = nTail;
		return S_OK;
	}

	int32_t SetBoundary(int32_t nHead, int32_t nTail)
	{
		if(nHead > m_nSize)
		{
			return E_INVALID_CODEQUEUE_HEAD;
		}
		if (nTail > m_nSize)
		{
			return E_INVALID_CODEQUEUE_TAIL;
		}
		m_nHead = nHead;
		m_nTail = nTail;
		return S_OK;
	}

	uint8_t* GetCodeBuff() const { return (uint8_t*)m_arrCodeBuff; }
protected:
	uint32_t m_nSize;
	uint32_t m_nHead;
	uint32_t m_nTail;
	uint8_t	m_arrCodeBuff[CAPACITY];
};

#endif