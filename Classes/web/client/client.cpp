#include"client.h"

int ret;
int ID;
DWORD WINAPI ServerThread(LPVOID lpParameter) 
{
	SOCKET *ClientSocket = (SOCKET*)lpParameter;
	char message[SIZE];
	while (true)
	{
		memset(message, '/0', SIZE);
		ret = recv(*ClientSocket, message, SIZE, 0);                       //接受信息：对方ID+信息（例：1a100/200）
		if (SOCKET_ERROR == ret)
		{
			cout << "recv失败" << endl; 
			closesocket(*ClientSocket);                                    //关闭套接字       
			WSACleanup();                                                  //释放套接字资源;  
			return -1;
		}
		if (message[0] == 'I')
			ID = message[2] - '0';
		if (message[0] == 'o')
			break;
		//一大堆if...
	}
	closesocket(*ClientSocket);
	return 0;
}
Client::Client()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		cout << "WSAStartup失败" << endl;
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
	CreateThread(NULL, 0, &ServerThread, &ClientSock, 0, NULL);  //建立子线程
}

Client::~Client()
{
	closesocket(ClientSock);
	WSACleanup();
	return;
}

int Client::SendMessage(char Message[SIZE])                       //发送数据
{
	char message[SIZE] = { 0 };
	message[0] = ID + '0';                                         //message[0]为己方ID
	for (int i = 1;Message[i-1]!='\0' && i<SIZE;i++)
	{
		message[i] = Message[i - 1];
	}
	send(ClientSock, message, SIZE, 0);
	return 0;
}
