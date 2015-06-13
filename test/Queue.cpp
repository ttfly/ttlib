#include "TTGlobal.h"
#include "TTCodeQueue.h"
#include <string.h>
#include <iostream>

using namespace std;

#define  QUEUE_SIZE		256*1024

typedef CCodeQueue<QUEUE_SIZE> TestQueue;
int32_t main()
{
	TestQueue	testQueue;
	testQueue.Initilize();
	uint32_t nCount = 0;
	while (nCount <= 5)
	{
		string str;
		std::cin >> str;
		testQueue.Push((uint8_t*)str.c_str(), strlen(str.c_str())+1);
		nCount++;
	}
	uint8_t buff[1024];
	uint32_t nLen;
	while (testQueue.Pop(buff, 1024, nLen)==S_OK)
	{
		cout << buff << endl;
	}
	return 0;
}