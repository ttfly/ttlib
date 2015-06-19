#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include "TTGlobal.h"
#include "TTCircularBuffer.h"

class TCPSocket
{
public:
	TCPSocket();
	virtual TCPSocket();
public:
	SOCKETTYPE GetType() const
	{
		return m_nScoketType;
	}
	SOCKETSTATUS GetStatus() const
	{
		return m_nStatus;
	}
	SOCKETFD GetSocketFD()const
	{
		return m_nSocketFD;
	}

	void Reset()
	{
		m_nStatus = enmSocketStatus_Invalid;
		m_nSocketFD = enmInvalidSocketFD;
	}

	const uint8_t* GetInBuffStart()const
	{
		return (const uint8_t*)(m_ibuf.GetStart());
	}
	const uint8_t* GetOutBuffStart() const
	{
		return (const uint8_t*)(m_obuf.GetStart());
	}

	uint32_t GetInBuffLen()
	{
		return m_ibuf.GetLength();
	}

	uint32_t GetOutBuffLen()
	{
		return m_obuf.GetLength();
	}

	bool RemoveInBuff(uint32_t nSize)
	{
		return	m_ibuf.Remove((size_t)nSize);
	}
	bool ReadFromInBuff(char* pBuff, uint32_t nLen)
	{
		return m_ibuf.Read(pBuff, nLen)
	}

	void ResetInBuff()
	{
		m_ibuf.Reset();
	}

	bool IsConnected()
	{
		return enmSocketStatus_Connected == m_nStatus;
	}

	bool IsConnecting()
	{
		return enmSocketStatus_Connecting == m_nStatus;
	}

	void OnConnectSuccess();

	int32_t CreateSocket();

	void CloseSocket();

	int32_t OpenAsServer(const char* szIP, uint16_t nPort, bool bNonBlock = true);

	int32_t OnAccept();
	
	int32_t Connect(const char* szRemoteIP = NULL, uint16_t nPort = 0, bool bNonBlock = true, int32_t nTimeOut = enmDefaultSocketConnectTimeout);



private:
	


private:
	SOCKETFD		m_nSocketFD;
	SOCKETTYPE		m_nScoketType;
	SOCKETSTATUS	m_nStatus;
	int32_t			m_nThreadIndex;
	CircularBuffer	m_ibuf;
	CircularBuffer	m_obuf;
	uint16_t		m_nPort;
	char			m_sIP[enmMaxIPAddressLength];
	SOCKETADDR	m_stPeerAddr;
};

#endif