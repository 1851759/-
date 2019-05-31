#pragma once
#include <iostream>
#include <cstdio>
#include <Winsock2.h>
#include <cstring>
#include<vector>
#include<string>
using namespace std;

#pragma comment(lib, "ws2_32.lib")  

#define PORT 8000                    //端口
#define IP "192.168.1.102"           //IP地址
#define SIZE 30                      //缓存区大小

class Client                         //客户端
{
public:
	Client();
	~Client();
	int SendMessage(char Message[SIZE]);//传递信息函数
private:
	SOCKET ClientSock;                //客户端套接字
	SOCKADDR_IN ClientSock_Addr;      //客户端地址
};