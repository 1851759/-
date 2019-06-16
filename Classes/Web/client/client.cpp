#include"client.h"
#include "SimpleAudioEngine.h"
#include"RoomScene.h"
#include"GameScene.h"
#include"cocos2d.h"
USING_NS_CC;
int ID = 1, n = 0, IfStart = 0, IfAI = 0, IfEquipUpdate = 0, P1Level = 1, P2Level = 1, P1Blood = 200, P2Blood = 200;         //IfStart�ж��Ƿ�ʼ��IfAI�ж��Ƿ����˻���ս
char EnemyHero = '\0', AQWE, EnemyEquip;
Vec2 Position = { 0,0 }, AQWE_Direction;
Vec2 CharToVec2(char Message[SIZE])                //�����ݵ�char����ת��Ϊfloat����
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
	return position;
}

char *FloatToChar(float x, float y)                        //��floatת��Ϊchar����                //Message[0]��û����
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

DWORD WINAPI ClientThread(LPVOID lpParameter)                              //�߳�
{
	SOCKET *ClientSocket = (SOCKET*)lpParameter;
	char message[SIZE];
	for (;IfAI==0;)
	{
		memset(message, '/0', SIZE);
		recv(*ClientSocket, message, SIZE, 0);                       //������Ϣ���Է�ID+��Ϣ������1a100/200��
		log("%s", message);
		
		if (message[0] == 'I')                                             //����ID
			ID = message[2] - '0';
		if (message[0] == 'C')                                             //Connect
		{

		}
		if (message[0] == 'S')                                             //Start
		{
			IfStart = 1;
		}
		if (message[1] == 'H')                                             //�ط�Ӣ��
		{
			
			EnemyHero = message[2];
		}

		if (message[1] == 'P')                                             //�з�λ��
		{
			Position = CharToVec2(message);
			log("%f", Position.x);
			log("%f", Position.y);
		}
		if (message[1] == 'A')                                           //����
		{
			AQWE = 'A';
			AQWE_Direction = CharToVec2(message);
			n++;
		}
		if (message[1] == 'Q')                                           //Q����
		{
			AQWE = 'Q';
			AQWE_Direction = CharToVec2(message);
			n++;
		}
		if (message[1] == 'W')                                           //W����
		{
			AQWE = 'W';
			AQWE_Direction = CharToVec2(message);
			n++;
		}
		if (message[1] == 'E')                                           //R����
		{
			AQWE = 'E';
			AQWE_Direction = CharToVec2(message);
			n++;
		}
		if (message[1] == 'B')                                           //��װ��
		{
			EnemyEquip = message[2];
			IfEquipUpdate = 1;
		}
		if (message[1] == 'Z')
		{
			if (message[2] == 'R')
			{
				n_RedDeath = message[3];
			}
			else
			{
				n_BlueDeath = message[3];
			}
		}
		if (message[1] == 'L')
		{
			P1Level = message[2];
			P2Level = message[3];
		}
		if (message[1] == 'X')
		{
			P1Blood = message[2] * 10;
			P2Blood = message[3] * 10;
		}
		if (message[0] == 'o')                                             //over                          
			break;
		//һ���if...
	}
	closesocket(*ClientSocket);
	return 0;
}
Client::Client()
{
	log("aaaaaaaaa");                                          //��Ҳ��֪��Ϊʲô��log���֮����log�ᱨ��
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	//�����׽���
	ClientSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//���ӷ�������ַ
	ClientSock_Addr.sin_family = AF_INET;
	ClientSock_Addr.sin_port = htons(PORT);
	ClientSock_Addr.sin_addr.s_addr = inet_addr(IP);
	//���ӷ�����
	connect(ClientSock, (LPSOCKADDR)&ClientSock_Addr, sizeof(ClientSock_Addr));
	//�������߳�
	CreateThread(NULL, 0, &ClientThread, &ClientSock, 0, NULL);  
	//�ٽ���һ�����̣߳�Ӧ�û��������Ч��
	CreateThread(NULL, 0, &ClientThread, &ClientSock, 0, NULL);  
}

Client::~Client()
{
	closesocket(ClientSock);
	WSACleanup();
	return;
}

int Client::MessageSending(char Message[SIZE])                       //��������
{
	char message[SIZE] = { 0 };
	message[0] = ID + '0';                                         //message[0]Ϊ����ID
	for (int i = 1; Message[i - 1] != '\0' && i < SIZE; i++)
	{
		message[i] = Message[i - 1];
	}
	send(ClientSock, message, SIZE, 0);
	return 0;
}



