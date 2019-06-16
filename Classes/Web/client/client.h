#pragma once
#include <iostream>
#include <cstdio>
#include <Winsock2.h>
#include <cstring>
#include<vector>
#include<string>
#include"cocos2d.h"
USING_NS_CC;
using namespace std;

#pragma comment(lib, "ws2_32.lib")  

#define PORT 8000                    //端口
#define IP "192.168.1.103"           //IP地址                            
#define SIZE 30                      //缓存区大小

extern int ID, n, IfStart, IfAI, IfEquipUpdate, P1Level, P2Level, P1Blood, P2Blood;
extern char EnemyHero, EnemyEquip, AQWE;
extern Vec2 Position, AQWE_Direction;
class Client                         //客户端
{
public:
	Client();
	~Client();
	int MessageSending(char Message[SIZE]);//传递信息函数
private:
	SOCKET ClientSock;                //客户端套接字
	SOCKADDR_IN ClientSock_Addr;      //客户端地址
};

char *FloatToChar(float x, float y);

extern Client Cli;


