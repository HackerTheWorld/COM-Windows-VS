#include <iostream>
#include <Windows.h>
#include<string>
#include<thread>  
//������Windows


using namespace std;

HANDLE initCom(char *szStr) {

	//LPCSTR* wszClassName;
	////�ڴ����
	//memset(wszClassName, 0, sizeof(wszClassName));
	//windows���к���
	//LPCSTR wszClassName = MultiByteToWideChar(CP_ACP, 0, szStr, strlen(szStr) + 1, NULL,0);
	HANDLE hCom1 = CreateFile(szStr,
		GENERIC_READ | GENERIC_WRITE, //�������д
		0, //��ռ��ʽ
		NULL,
		OPEN_EXISTING, //�򿪶����Ǵ���
		0, //ͬ����ʽ
		NULL);

	//if (hCom1 == (HANDLE)-1)
	if (hCom1 == INVALID_HANDLE_VALUE)
	{
		cout << "��COMʧ��!"<<endl;
		exit(0);
	}
	else
	{
		cout << "��COM�ɹ�!" << endl;
	}

	SetupComm(hCom1, 1024, 1024); //���뻺����������������Ĵ�С����1024
	COMMTIMEOUTS TimeOuts;
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout = 100;
	TimeOuts.ReadTotalTimeoutMultiplier = 5000;
	TimeOuts.ReadTotalTimeoutConstant = 5000;
	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom1, &TimeOuts); //���ó�ʱ
	DCB dcb;
	GetCommState(hCom1, &dcb);
	dcb.BaudRate = 9600; //������Ϊ9600
	dcb.ByteSize = 8; //ÿ���ֽ���8λ
	dcb.Parity = NOPARITY; //����żУ��λ
	dcb.StopBits = ONESTOPBIT; //1��ֹͣλ
	SetCommState(hCom1, &dcb);
	return hCom1;
}


int main() {
	/*����ģ��
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
		cout << "getport ��" << buffer<<endl;
	}
	system("pause");
}

