#include <iostream>
#include <Windows.h>
#include<string>
#include<thread>  
//仅适用Windows


using namespace std;

HANDLE initCom(char *szStr) {

	//LPCSTR* wszClassName;
	////内存分配
	//memset(wszClassName, 0, sizeof(wszClassName));
	//windows特有函数
	//LPCSTR wszClassName = MultiByteToWideChar(CP_ACP, 0, szStr, strlen(szStr) + 1, NULL,0);
	HANDLE hCom1 = CreateFile(szStr,
		GENERIC_READ | GENERIC_WRITE, //允许读和写
		0, //独占方式
		NULL,
		OPEN_EXISTING, //打开而不是创建
		0, //同步方式
		NULL);

	//if (hCom1 == (HANDLE)-1)
	if (hCom1 == INVALID_HANDLE_VALUE)
	{
		cout << "打开COM失败!"<<endl;
		exit(0);
	}
	else
	{
		cout << "打开COM成功!" << endl;
	}

	SetupComm(hCom1, 1024, 1024); //输入缓冲区和输出缓冲区的大小都是1024
	COMMTIMEOUTS TimeOuts;
	//设定读超时
	TimeOuts.ReadIntervalTimeout = 100;
	TimeOuts.ReadTotalTimeoutMultiplier = 5000;
	TimeOuts.ReadTotalTimeoutConstant = 5000;
	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom1, &TimeOuts); //设置超时
	DCB dcb;
	GetCommState(hCom1, &dcb);
	dcb.BaudRate = 9600; //波特率为9600
	dcb.ByteSize = 8; //每个字节有8位
	dcb.Parity = NOPARITY; //无奇偶校验位
	dcb.StopBits = ONESTOPBIT; //1个停止位
	SetCommState(hCom1, &dcb);
	return hCom1;
}


int main() {
	/*发送模块
	string result="233";
	WriteFile(hCom1, result.data(), result.size(), NULL, NULL);
	*/
	char comName[] = "COM1";
	HANDLE hCom5 = initCom(comName);

	char buffer[1000];
	DWORD readsize;
	int n = 100;
	while (n--) {
		ReadFile(hCom5, buffer, 13, &readsize, NULL);
		cout << "getport ：" << buffer<<endl;
	}
	system("pause");
}

