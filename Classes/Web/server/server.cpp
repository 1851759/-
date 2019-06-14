#include"server.h"

vector<Client> client(2);

int n = 0;                                        //参与游戏的人数
char Hero[SIZE] = "1H";                          //英雄名字
int IfStart[2] = { 0,0 };
DWORD WINAPI ServerThread(LPVOID lpParameter) //线程
{
	SOCKET *ClientSocket = (SOCKET*)lpParameter;
	char message[SIZE];
	int num;
	for(;;)
	{
		memset(message, '/0', SIZE);
		recv(*ClientSocket, message, SIZE, 0);
		if (message[1] == 'o')           //接收到数据over
			break;
		num = message[0] - '0';
		if (message[1] == 'S')               //接到数据Start
		{
			IfStart[num - 1] = 1;           //表示客户端num已经发送Start
			if (IfStart[2 - num] == 0)
				continue;
			else
			{
				send(client[0].sock, "Start", 6, 0);
				send(client[1].sock, "Start", 6, 0);
				continue;
			}
		}
		if (message[1] == 'H')           //收到数据Hero
		{
			Hero[2] = message[2];
			if (n < 2)
				continue;
		}
		cout << "客户端发送的数据: " << message << endl;
		if (num > 0 && n == 2 && &client[2-num]!=NULL)                     //将数据发送给另一个客户端
			send(client[2 - num].sock, message, SIZE, 0);
	}
	return 0;
}
Server::Server()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	//建立套接字
	ServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//服务器地址
	ServerSock_Addr.sin_family = AF_INET;
	ServerSock_Addr.sin_port = htons(PORT);
	ServerSock_Addr.sin_addr.s_addr = INADDR_ANY;
	//绑定套接字
	bind(ServerSock, (SOCKADDR *)&ServerSock_Addr, sizeof(SOCKADDR_IN));
	//监听
	listen(ServerSock, 2);
}

Server::~Server()
{
	closesocket(ServerSock);
	WSACleanup();
	return;
}

int Server::Run()
{
	char message[SIZE] = "ID1";
	for (;;)
	{
		client[n].sock = accept(ServerSock, 0, 0);
		cout << n+1 << "号客户端已经连接" << endl;
		send(client[n].sock, message, SIZE, 0);         //告知对方号码
		CreateThread(NULL, 0, &ServerThread, &client[n].sock, 0, NULL);//建立子线程
		n++;
		message[2]++;
		if (n == 2)                                    //人满了
		{
			send(client[0].sock, "Connect", 8, 0);
			if (Hero[2] != '\0')
			{
				send(client[1].sock, Hero, SIZE, 0);
			}
		}
	}
	closesocket(client[0].sock);
	closesocket(client[1].sock);
}
