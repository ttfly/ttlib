#ifndef __TTCIRCULAR_BUFFER_H__
#define __TTCIRCULAR_BUFFER_H__
#include "TTGlobal.h"

class CircularBuffer
{
public:
	CircularBuffer(uint32_t nSize=16);
	~CircularBuffer();

	int32_t Read(char* pBuff, uint32_t nLen);

	int32_t Write(const char* pBuff, uint32_t nLen);

	int32_t SoftRead(char* pBuff, uint32_t nLen);

	int32_t Remove(uint32_t nLen);

	char* GetStart();
	uint32_t GetSpace();

	uint32_t GetContentSize(){ return m_nContentSize; }


	uint32_t GetHead(){ return m_nHead; }

	uint32_t GetTail(){ return m_nTail; }

	void Reset();

protected:
	char*	m_pBuff;			//buff
	uint32_t m_nHead;			//buff头部标志
	uint32_t m_nTail;			//buff的尾部标志
	uint32_t m_nMaxSize;		//buff最大长度
	uint32_t m_nContentSize;	//当前存储内容长度
	uint64_t m_nCount;			//写入的总字节长度
};

#endif