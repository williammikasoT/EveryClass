#pragma once

#include "objbase.h"
#include "stdio.h"
#include "stdlib.h"
#include "afxwin.h"
#include  <vector>

extern "C" {
	// Declare the C libraries used
#include "setupapi.h"		// Must link in setupapi.lib
#include "hidsdi.h"			// Must link in hid.lib
}

#pragma comment(lib,"setupapi.lib") 
#pragma comment(lib,"hid.lib")

class USBClass
{
public:
	USBClass();
	~USBClass();
	
	SECURITY_ATTRIBUTES SecurityAttributes;
	HANDLE PnPHandle, HIDHandle;
	HIDP_CAPS	Capabilities;
	PHIDP_PREPARSED_DATA	PreparsedData;

	BOOL USBClass::SearchUSB(std::vector<CString>& vStr);
	int USBClass::ConnectUSB(CString strPath);
	BOOL WriteUSB(CHAR	OutputReport[]);
	BOOL ReadUSB(CString& stmp);
	BOOL CloseUSB();
};

