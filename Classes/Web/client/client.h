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

#define PORT 8000                    //�˿�
#define IP "192.168.1.103"           //IP��ַ                            
#define SIZE 30                      //��������С

extern int ID, n, IfStart, IfAI, IfEquipUpdate, P1Level, P2Level, P1Blood, P2Blood;
extern char EnemyHero, EnemyEquip, AQWE;
extern Vec2 Position, AQWE_Direction;
class Client                         //�ͻ���
{
public:
	Client();
	~Client();
	int MessageSending(char Message[SIZE]);//������Ϣ����
private:
	SOCKET ClientSock;                //�ͻ����׽���
	SOCKADDR_IN ClientSock_Addr;      //�ͻ��˵�ַ
};

char *FloatToChar(float x, float y);

extern Client Cli;


