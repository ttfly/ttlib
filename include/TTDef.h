#ifndef __TTDEF_H__
#define __TTDEF_H__

typedef int	SOCKETFD;

typedef int SOCKETTYPE;

enum 
{
	enmSocketType_Communication = 1,		//ͨ��Socket
	enmSocketType_Listen		= 2,		//����Socket
};

typedef int SOCKETSTATUS;

enum 
{
	enmSocketStatus_Invalid		= -1,		//��Ч״̬
	enmSocketStatus_Closed		= 0,		//�ر�
	enmSocketStatus_Opened		= 1,		//��
	enmSocketStatus_Connecting	= 2,		//������
	enmSocketStatus_Connected	= 3,		//������
	enmSocketStatus_Error		= 4,		//Socket����
};

typedef struct sockaddr_in SOCKETADDR;
enum 
{
	enmInvalidArgument			= -1,			//��Ч��ֵ
	enmInvalidSocketFD			= -1,			//��Ч��ֵ
	enmMaxIPAddressLength		= 20,			//IP��ַ��Ч����
	enmDefaultSocketConnectTimeout = 3000,		//3s

};

#endif