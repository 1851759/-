#pragma once
#include<iostream>
#include<cstdio>
#include<Winsock2.h>
#include<cstring>
#include<vector>
#include<string>
using namespace std;

#pragma comment(lib, "ws2_32.lib")  

#define PORT 8000                    //端口
#define IP "192.168.1.102"           //IP地址
#define SIZE 30                      //缓存区大小

struct Client                        //客户端
{
	SOCKET sock;
	SOCKADDR_IN addr;
};

class Server                         //服务器
{
public:
	Server();
	~Server();
	int Run();
private:
	SOCKET ServerSock;                //服务器套接字
	SOCKADDR_IN ServerSock_Addr;      //服务器地址
};