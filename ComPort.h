#pragma once

#include <string.h>

class CComPort
{
private:
	char comPortStrng[25][20];
	unsigned int baudTable[5];

#if defined (__WIN32__)
	HANDLE       comPortHandle; 	// Handle COM port 
#elif defined (__linux__)
  int           comPortHandle;  // Handle COM port 
#endif
	unsigned short RxCount;
	

public:
// Constructor
	CComPort(void)
	{
		char tempComPort[25][20] = {"\\\\.\\COM1", "\\\\.\\COM2", "\\\\.\\COM3", "\\\\.\\COM4", "\\\\.\\COM5",
									"\\\\.\\COM6", "\\\\.\\COM7", "\\\\.\\COM8", "\\\\.\\COM9", "\\\\.\\COM10",
									"\\\\.\\COM11","\\\\.\\COM12", "\\\\.\\COM13", "\\\\.\\COM14", "\\\\.\\COM15",
									"\\\\.\\COM16", "\\\\.\\COM17", "\\\\.\\COM18", "\\\\.\\COM19", "\\\\.\\COM20",
									"\\\\.\\COM21", "\\\\.\\COM22", "\\\\.\\COM23", "\\\\.\\COM24", "\\\\.\\COM25"};
		
		unsigned int tempBaudTable[5] = {9600,	19200,	38400,	57600, 115200};

		memcpy(comPortStrng, tempComPort, sizeof(tempComPort));
		memcpy(baudTable, tempBaudTable, sizeof(baudTable));
#if defined (__WIN32__)
		comPortHandle = NULL;
#elif defined (__linux__)
		comPortHandle = -1;
#endif
	}


// Destructor
	~CComPort(void)
	{
		// if comport is already opened close it.
		if(comPortHandle)
		{
			CloseComPort();
		}
	}

	
	void OpenComPort(unsigned int, unsigned int);
	void CloseComPort(void);
	void SendComPort(char*, int );
	bool GetComPortOpenStatus(void);	
	unsigned short ReadComPort(char*, int);


};
