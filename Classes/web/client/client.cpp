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
		ret = recv(*ClientSocket, message, SIZE, 0);                       //������Ϣ���Է�ID+��Ϣ������1a100/200��
		if (SOCKET_ERROR == ret)
		{
			cout << "recvʧ��" << endl; 
			closesocket(*ClientSocket);                                    //�ر��׽���       
			WSACleanup();                                                  //�ͷ��׽�����Դ;  
			return -1;
		}
		if (message[0] == 'I')
			ID = message[2] - '0';
		if (message[0] == 'o')
			break;
		//һ���if...
	}
	closesocket(*ClientSocket);
	return 0;
}
Client::Client()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		cout << "WSAStartupʧ��" << endl;
		return;
	}
	ClientSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == ClientSock)
	{
		cout << "socketʧ��" << endl;
		WSACleanup();                                           //�ͷ��׽�����Դ;  
		return;
	}
	ClientSock_Addr.sin_family = AF_INET;
	ClientSock_Addr.sin_port = htons(PORT);
	ClientSock_Addr.sin_addr.s_addr = inet_addr(IP);
	ret = connect(ClientSock, (LPSOCKADDR)&ClientSock_Addr, sizeof(ClientSock_Addr));
	if (SOCKET_ERROR == ret)
	{
		cout << "connectʧ��" << endl;
		closesocket(ClientSock);                                //�ر��׽���  
		WSACleanup();                                           //�ͷ��׽�����Դ  
		return;
	}
	CreateThread(NULL, 0, &ServerThread, &ClientSock, 0, NULL);  //�������߳�
}

Client::~Client()
{
	closesocket(ClientSock);
	WSACleanup();
	return;
}

int Client::SendMessage(char Message[SIZE])                       //��������
{
	char message[SIZE] = { 0 };
	message[0] = ID + '0';                                         //message[0]Ϊ����ID
	for (int i = 1;Message[i-1]!='\0' && i<SIZE;i++)
	{
		message[i] = Message[i - 1];
	}
	send(ClientSock, message, SIZE, 0);
	return 0;
}
