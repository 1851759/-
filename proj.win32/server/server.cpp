#include"server.h"

vector<Client> client(2);

int ret;
int n = 0;                                        //������Ϸ������
char Hero[SIZE] = "1H";                          //Ӣ������
int IfStart[2] = { 0,0 };
DWORD WINAPI ServerThread(LPVOID lpParameter) //�߳�
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
			closesocket(*ClientSocket);   //�ر��׽���       
			WSACleanup();                 //�ͷ��׽�����Դ;  
			return -1;
		}

		if (message[1] == 'o')           //���յ�����over
			break;
		num = message[0] - '0';
		if (message[1] == 'S')               //�ӵ�����Start
		{
			IfStart[num - 1] = 1;           //��ʾ�ͻ���num�Ѿ�����Start
			if (IfStart[2 - num] == 0)
				continue;
			else
			{
				send(client[0].sock, "Start", 6, 0);
				send(client[1].sock, "Start", 6, 0);
				continue;
			}
		}
		if (message[1] == 'H')           //�յ�����Hero
		{
			Hero[2] = message[2];
			if (n < 2)
				continue;
		}
		cout << "�ͻ��˷��͵�����: " << message << endl;
		if (num > 0 && n == 2)                     //�����ݷ��͸���һ���ͻ���
			send(client[2 - num].sock, message, SIZE, 0);
	}
	return 0;
}
Server::Server()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		cout << "WSAStartup����" << endl;
		return;
	}
	ServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == ServerSock)
	{
		cout << "socket����" << endl;
		WSACleanup();                     //�ͷ��׽�����Դ;  
		return;
	}
	                                      //��������ַ
	ServerSock_Addr.sin_family = AF_INET;
	ServerSock_Addr.sin_port = htons(PORT);
	ServerSock_Addr.sin_addr.s_addr = INADDR_ANY;
	                                      //���׽���
	ret = bind(ServerSock, (SOCKADDR *)&ServerSock_Addr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == ret)
	{
		cout << "bind����" << endl;
		closesocket(ServerSock);          //�ر��׽���  
		WSACleanup();                     //�ͷ��׽�����Դ;  
		return;
	}
	                                      //����
	ret = listen(ServerSock, 2);
	if (SOCKET_ERROR == ret)
	{
		cout << "listen����" << endl;
		closesocket(ServerSock);          //�ر��׽���  
		WSACleanup();                     //�ͷ��׽�����Դ;  
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
		cout << n+1 << "�ſͻ����Ѿ�����" << endl;
		send(client[n].sock, message, SIZE, 0);         //��֪�Է�����
		CreateThread(NULL, 0, &ServerThread, &client[n].sock, 0, NULL);//�������߳�
		n++;
		message[2]++;
		if (n == 2)                                    //������
		{
			send(client[0].sock, "Connect", 8, 0);
			//send(client[1].sock, "1HH", 8, 0);        //��֪�ͻ���˫���Ѿ�����
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
