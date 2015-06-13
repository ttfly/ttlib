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
	uint32_t m_nHead;			//buffͷ����־
	uint32_t m_nTail;			//buff��β����־
	uint32_t m_nMaxSize;		//buff��󳤶�
	uint32_t m_nContentSize;	//��ǰ�洢���ݳ���
	uint64_t m_nCount;			//д������ֽڳ���
};

#endif