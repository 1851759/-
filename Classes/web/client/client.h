#pragma once
#include <iostream>
#include <cstdio>
#include <Winsock2.h>
#include <cstring>
#include<vector>
#include<string>
using namespace std;

#pragma comment(lib, "ws2_32.lib")  

#define PORT 8000                    //�˿�
#define IP "192.168.1.102"           //IP��ַ
#define SIZE 30                      //��������С

class Client                         //�ͻ���
{
public:
	Client();
	~Client();
	int SendMessage(char Message[SIZE]);//������Ϣ����
private:
	SOCKET ClientSock;                //�ͻ����׽���
	SOCKADDR_IN ClientSock_Addr;      //�ͻ��˵�ַ
};