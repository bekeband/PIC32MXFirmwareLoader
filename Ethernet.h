#pragma once
#if defined (__WIN32__)
#include <winsock.h>
#elif defined (__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif
class CEthernet
{
private:
	WSADATA	wsaData;
	SOCKET	SendSocket;
	sockaddr_in RecvAddr;
	

public:
// Constructor
	CEthernet(void)
	{
		SendSocket = INVALID_SOCKET;

	}


// Destructor
	~CEthernet(void)
	{
		// if comport is already opened close it.
		if(SendSocket != INVALID_SOCKET)
		{
			CloseUdpPort();
		}
	}

	
	BOOL OpenUdpPort(USHORT, ULONG);
	void CloseUdpPort(void);
	void SendUdpPort(BYTE*, INT);
	USHORT ReadUdpPort(BYTE*, INT);
	BOOL GetSocketOpenStatus(void);
};
