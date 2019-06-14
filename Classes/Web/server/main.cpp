#include"server.h"

int main()
{
	Server ser;
	ser.Run();
	ser.~Server();
	return 0;
}