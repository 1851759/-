#include"client.h"
#include "SimpleAudioEngine.h"
#include"RoomScene.h"
#include"GameScene.h"
#include"cocos2d.h"
USING_NS_CC;
int ret, ID = 1, n = 0, IfStart = 0, IfAI = 0;            //IfStart判断是否开始，IfAI判断是否是人机对战
char EnemyHero = '\0', EnemyEquip, AQWE;
Vec2 Position = { 0,0 }, AQWE_Direction;
Vec2 CharToVec2(char Message[SIZE])                //将传递的char数组转化为float数组
{
	Vec2 position;
	char X[SIZE] = { 0 }, Y[SIZE] = { 0 };
	int i, j;
	for (i = 2, j = 0;; i++, j++)
	{
		if (Message[i] == '/')
			break;
		X[j] = Message[i];
	}
	for (i++, j = 0;; i++, j++)
	{
		if (Message[i] == '/')
			break;
		Y[j] = Message[i];
	}
	position.x = strtod(X, NULL);
	position.y = strtod(Y, NULL);
	//float *pos = new float[3];
	//pos = position;
	////log("%f", pos[0]);
	////log("%f", pos[1]);
	return position;
}

char *FloatToChar(float x, float y)                        //将float转化为char数组                //Message[0]还没动，
{
	int i, j;
	char message[SIZE] = { 0 }, X[SIZE] = { 0 }, Y[SIZE] = { 0 };
	sprintf(X, "%f", x);
	sprintf(Y, "%f", y);
	message[0] = 'P';
	for (i = 0, j = 1;; i++, j++)
	{
		if (X[i] == '\0')
			break;
		message[j] = X[i];
	}
	message[j] = '/';
	for (i = 0, j++;; i++, j++)
	{
		if (Y[i] == '\0')
			break;
		message[j] = Y[i];
	}
	message[j] = '/';
	char * Message = new char[strlen(message) + 1];
	strcpy(Message, message);
	return Message;
}

DWORD WINAPI ClientThread(LPVOID lpParameter)                              //线程
{
	SOCKET *ClientSocket = (SOCKET*)lpParameter;
	char message[SIZE];
	for (;IfAI==0;)
	{
		memset(message, '/0', SIZE);
		ret = recv(*ClientSocket, message, SIZE, 0);                       //接受信息：对方ID+信息（例：1a100/200）
		log("%s", message);
		if (SOCKET_ERROR == ret)
		{
			cout << "recv失败" << endl;
			closesocket(*ClientSocket);                                    //关闭套接字       
			WSACleanup();                                                  //释放套接字资源;  
			return -1;
		}
		if (message[0] == 'I')                                             //己方ID
			ID = message[2] - '0';
		if (message[0] == 'C')                                             //Connect
		{

		}
		if (message[0] == 'S')                                             //Start
		{
			IfStart = 1;
		}
		if (message[1] == 'H')                                             //地方英雄
		{
			
			EnemyHero = message[2];
		}

		if (message[1] == 'P')                                             //敌方位置
		{
			Position = CharToVec2(message);
			log("%f", Position.x);
			log("%f", Position.y);
		}
		if (message[1] == 'A')                                           //攻击
		{
			AQWE = 'A';
			AQWE_Direction = CharToVec2(message);
			n++;
		}
		if (message[1] == 'Q')                                           //Q技能
		{
			AQWE = 'Q';
			AQWE_Direction = CharToVec2(message);
			n++;
		}
		if (message[1] == 'W')                                           //W技能
		{
			AQWE = 'W';
			AQWE_Direction = CharToVec2(message);
			n++;
		}
		if (message[1] == 'E')                                           //R技能
		{
			AQWE = 'E';
			AQWE_Direction = CharToVec2(message);
			n++;
		}
		if (message[1] == 'B')                                           //买装备
		{
			EnemyEquip = message[2];
		}
		if (message[0] == 'o')                                             //over                          
			break;
		//一大堆if...
	}
	closesocket(*ClientSocket);
	return 0;
}
Client::Client()
{
	log("aaaaaaaaa");
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		cout << "WSAStartup失败" << endl;
		log("wrong");
		return;
	}
	ClientSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == ClientSock)
	{
		cout << "socket失败" << endl;
		WSACleanup();                                           //释放套接字资源;  
		return;
	}
	ClientSock_Addr.sin_family = AF_INET;
	ClientSock_Addr.sin_port = htons(PORT);
	ClientSock_Addr.sin_addr.s_addr = inet_addr(IP);
	ret = connect(ClientSock, (LPSOCKADDR)&ClientSock_Addr, sizeof(ClientSock_Addr));
	if (SOCKET_ERROR == ret)
	{
		cout << "connect失败" << endl;
		closesocket(ClientSock);                                //关闭套接字  
		WSACleanup();                                           //释放套接字资源  
		return;
	}
	CreateThread(NULL, 0, &ClientThread, &ClientSock, 0, NULL);  //建立子线程
}

Client::~Client()
{
	closesocket(ClientSock);
	WSACleanup();
	return;
}

int Client::MessageSending(char Message[SIZE])                       //发送数据
{
	char message[SIZE] = { 0 };
	message[0] = ID + '0';                                         //message[0]为己方ID
	for (int i = 1; Message[i - 1] != '\0' && i < SIZE; i++)
	{
		message[i] = Message[i - 1];
	}
	send(ClientSock, message, SIZE, 0);
	return 0;
}


