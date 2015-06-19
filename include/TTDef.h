#ifndef __TTDEF_H__
#define __TTDEF_H__

typedef int	SOCKETFD;

typedef int SOCKETTYPE;

enum 
{
	enmSocketType_Communication = 1,		//通信Socket
	enmSocketType_Listen		= 2,		//监听Socket
};

typedef int SOCKETSTATUS;

enum 
{
	enmSocketStatus_Invalid		= -1,		//无效状态
	enmSocketStatus_Closed		= 0,		//关闭
	enmSocketStatus_Opened		= 1,		//打开
	enmSocketStatus_Connecting	= 2,		//连接中
	enmSocketStatus_Connected	= 3,		//已连接
	enmSocketStatus_Error		= 4,		//Socket错误
};

typedef struct sockaddr_in SOCKETADDR;
enum 
{
	enmInvalidArgument			= -1,			//无效数值
	enmInvalidSocketFD			= -1,			//无效数值
	enmMaxIPAddressLength		= 20,			//IP地址有效长度
	enmDefaultSocketConnectTimeout = 3000,		//3s

};

#endif