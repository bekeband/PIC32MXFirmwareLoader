//#include "stdafx.h"
#include "ComPort.h"
#include "Ethernet.h"
#include "USB_HID.h"
#include "Hex.h"
#include "BootLoader.h"
#include "PIC32UBL.h"
//#include "PIC32UBLDlg.h"
//#include "./PIC32UBLDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





/****************************************************************************
 * Opens com port
 *
 * \param comPort  Com port to be opened.
 * \param baud     Baud rate
 * \param 
 * \return         Opens the com port
 *****************************************************************************/
void CComPort::OpenComPort(unsigned int comPort, unsigned int baud)
{    
	CString buff;
	
    DWORD        bytes_read    = 0;     // Number of bytes read from port    
    DWORD        bytes_written = 0;    // Number of bytes written to the port    
    
    int   bStatus;
    DCB          comSettings;          // Contains various port settings    

	

	COMMTIMEOUTS CommTimeouts;

	

	if(comPortHandle)
	{
		// If com port is already open, close it.
		CloseComPort();
		
	}    
	          
	buff = comPortStrng[comPort];	
    
    // Open COM port    
    if ((comPortHandle =  CreateFile(buff,                // open com5:                    
    	GENERIC_READ | GENERIC_WRITE, // for reading and writing                    
    	0,                            // exclusive access                    
    	NULL,                         // no security attributes                    
    	OPEN_EXISTING,                                  
    	FILE_ATTRIBUTE_NORMAL,                    
    	NULL)) == INVALID_HANDLE_VALUE)    
    {        
    	// error processing code goes here		
		MessageBox(NULL, "Not able to open com port!", NULL, 0);
		comPortHandle = NULL;
			
	}  
	else
	{
		// Set timeouts in milliseconds    
		CommTimeouts.ReadIntervalTimeout         = 0;
		CommTimeouts.ReadTotalTimeoutMultiplier  = 0;
		CommTimeouts.ReadTotalTimeoutConstant    = 5; // Read time out 5ms.
		CommTimeouts.WriteTotalTimeoutMultiplier = 1;
		CommTimeouts.WriteTotalTimeoutConstant   = 500; // Write time out 500ms.


		(void)SetCommTimeouts(comPortHandle,&CommTimeouts);
	    
	    
		
		// Set Port parameters.    
		// Make a call to GetCommState() first in order to fill    
		// the comSettings structure with all the necessary values.    
		// Then change the ones you want and call SetCommState().    
		GetCommState(comPortHandle, &comSettings);

		baud = baudTable[baud];

			
		
		comSettings.BaudRate = baud;
		comSettings.StopBits = ONESTOPBIT;
		comSettings.ByteSize = 8;
		comSettings.Parity   = NOPARITY;   // No Parity
		comSettings.fParity  = FALSE;
		comSettings.fRtsControl = RTS_CONTROL_ENABLE; // Keep the RTS ON, to trigger bootloader enter bootload mode. 
		bStatus = SetCommState(comPortHandle, &comSettings);
	    
		
		if (bStatus == 0)    
		{        
			// error processing code goes here    
			MessageBox(NULL, "Error in setting the COM port!", NULL, 0);
			CloseComPort();
		} 
		
	}
}


/****************************************************************************
 * Close com port
 *
 * \param   
 * \param      
 * \param 
 * \return         
 *****************************************************************************/
void CComPort::CloseComPort(void)
{

	// If already a com port is opened, close it.
#if defined (__WIN32__)
	CloseHandle(comPortHandle);
	comPortHandle= NULL;
#elif defined (__linux__)
	close(comPortHandle);
	comPortHandle= -1;
#endif
}


/****************************************************************************
 * Send com port
 *
 * \param  buffer: Data buffer
 * \param  bufflen: Buffer Length    
 * \param 
 * \return         
 *****************************************************************************/
void CComPort::SendComPort(char *buffer, int bufflen)
{
	unsigned long bytes_written;
	
#if defined (__WIN32__)
	(void)WriteFile(comPortHandle,              // Handle       
    		   &buffer[0],      // Outgoing data       
    		   bufflen,              // Number of bytes to write       
    		   &bytes_written,  // Number of bytes written       
    		   NULL);
#elif defined (__linux__)
#endif
	
}

/****************************************************************************
 * Reads com port
 *
 * \param  buffer: Data buffer
 * \param  MaxLen: Max possible length
 * \param 
 * \return  Number of bytes read.       
 *****************************************************************************/
unsigned short CComPort::ReadComPort(char* buffer, int MaxLen)
{
#if defined (__WIN32__)
	(void)ReadFile(comPortHandle,   // Handle                
        	buffer,            // Incoming data                
        	MaxLen,                  // Number of bytes to read                
        	(unsigned long *)&RxCount,          // Number of bytes read                
        	NULL);
#elif defined (__LINUX__)
#endif
	return RxCount;
	
}

/****************************************************************************
 * Gets com port status
 *
 * \param  
 * \param   
 * \param 
 * \return  true if com port is up and running      
 *****************************************************************************/
bool CComPort::GetComPortOpenStatus(void)
{
#if defined (__WIN32__)
	if(comPortHandle){ return true; } else { return false; }
#elif defined (__linux__)
  if(comPortHandle != -1){ return true; } else { return false; }
#endif
}

/************End of file******************************************************/