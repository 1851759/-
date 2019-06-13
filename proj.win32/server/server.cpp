#include"server.h"

vector<Client> client(2);

int ret;
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
		ret = recv(*ClientSocket, message, SIZE, 0);
		if (SOCKET_ERROR == ret)
		{
			cout << "recv failed!" << endl; 
			closesocket(*ClientSocket);   //关闭套接字       
			WSACleanup();                 //释放套接字资源;  
			return -1;
		}

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
		if (num > 0 && n == 2)                     //将数据发送给另一个客户端
			send(client[2 - num].sock, message, SIZE, 0);
	}
	return 0;
}
Server::Server()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		cout << "WSAStartup错误" << endl;
		return;
	}
	ServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == ServerSock)
	{
		cout << "socket错误" << endl;
		WSACleanup();                     //释放套接字资源;  
		return;
	}
	                                      //服务器地址
	ServerSock_Addr.sin_family = AF_INET;
	ServerSock_Addr.sin_port = htons(PORT);
	ServerSock_Addr.sin_addr.s_addr = INADDR_ANY;
	                                      //绑定套接字
	ret = bind(ServerSock, (SOCKADDR *)&ServerSock_Addr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == ret)
	{
		cout << "bind错误" << endl;
		closesocket(ServerSock);          //关闭套接字  
		WSACleanup();                     //释放套接字资源;  
		return;
	}
	                                      //监听
	ret = listen(ServerSock, 2);
	if (SOCKET_ERROR == ret)
	{
		cout << "listen错误" << endl;
		closesocket(ServerSock);          //关闭套接字  
		WSACleanup();                     //释放套接字资源;  
		return;
	}
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
			//send(client[1].sock, "1HH", 8, 0);        //告知客户端双方已经连接
			//send(client[1].sock, "hello", 8, 0);
			//cout << "hello" << endl;
			if (Hero[2] != '\0')
			{
				cout << Hero << endl;
				send(client[1].sock, Hero, SIZE, 0);
			}
		}
	}
	closesocket(client[0].sock);
	closesocket(client[1].sock);
}
