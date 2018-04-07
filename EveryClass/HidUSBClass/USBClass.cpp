//要设置为多字符编译，设置为UNICO编译收索不了数据

#include "stdafx.h"
#include "USBClass.h"




USBClass::USBClass()
{
}


USBClass::~USBClass()
{
}

/*
	parameter@ 需要一个矢量缓存BUF
	rever@ 成功返回真，失败返回假
*/
 BOOL USBClass::SearchUSB(std::vector<CString> &vStr)
{
	//std::vector<CString> vStr;
	struct _GUID GUID;
	SP_INTERFACE_DEVICE_DATA DeviceInterfaceData;
	struct {
		DWORD cbSize;
		char DevicePath[256];
	} FunctionClassDeviceData;
	HIDD_ATTRIBUTES HIDAttributes;
	//	SECURITY_ATTRIBUTES SecurityAttributes;
	int Device;
	ULONG BytesReturned;
	bool Success, ManufacturerName, ProductName;
	WCHAR ManufacturerBuffer[256], ProductBuffer[256];
	const WCHAR NotSupplied[] = L"NULL";

	// Initialize the GUID array and setup the security attributes for Win2000
	HidD_GetHidGuid(&GUID);
	SecurityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	SecurityAttributes.lpSecurityDescriptor = NULL;
	SecurityAttributes.bInheritHandle = false;

	// Get a handle for the Plug and Play node and request currently active devices
	PnPHandle = SetupDiGetClassDevs(&GUID, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if (int(PnPHandle) == -1) {
		printf("Could not attach to PnP node");
		int iRetErr = GetLastError();
		return FALSE;
	}

	// Lets look for a maximum of 20 Devices
	for (Device = 0; (Device < 20); Device++) {
		// Initialize our data
		DeviceInterfaceData.cbSize = sizeof(DeviceInterfaceData);
		// Is there a device at this table entry
		Success = SetupDiEnumDeviceInterfaces(PnPHandle, NULL, &GUID, Device, &DeviceInterfaceData);
		if (Success) {

			// There is a device here, get it's name
			FunctionClassDeviceData.cbSize = 5;
			Success = SetupDiGetDeviceInterfaceDetail(PnPHandle, &DeviceInterfaceData,
				(PSP_INTERFACE_DEVICE_DETAIL_DATA)&FunctionClassDeviceData, 256, &BytesReturned, NULL);
			if (!Success) {
				printf("Could not find the system name for this device\n");
				int iRetErr = GetLastError();
				return FALSE;
			}
			CString str;
			str = FunctionClassDeviceData.DevicePath;
			vStr.push_back(str);
		}
	}
	return TRUE;
}

 /*
	parameter@ 打开设备的地址
	revert@ 错误返回错误号，正常返回1
 */
 int USBClass::ConnectUSB(CString strPath)
 {
	 HIDHandle = CreateFile(strPath, GENERIC_READ | GENERIC_WRITE,
	 FILE_SHARE_READ | FILE_SHARE_WRITE, &SecurityAttributes, OPEN_EXISTING, 0, NULL);


	 if (HIDHandle == INVALID_HANDLE_VALUE) 
	 {
		 //str.Format("Errorcode = %d\n", GetLastError());
		 //MessageBox(str);
		 return GetLastError();
	 }
	 else{
#if	0
		 // Get the information about this HID
		 Success = HidD_GetAttributes(HIDHandle, &HIDAttributes);
		 if (!Success) {
			 printf("Could not get HID attributes\n");
			 return; //GetLastError(); 
		 }
		 ManufacturerName = HidD_GetManufacturerString(HIDHandle, ManufacturerBuffer, 256);
		 ProductName = HidD_GetProductString(HIDHandle, ProductBuffer, 256);

		 // And display it!
		 printf("VID = %4.4x, Name = ", HIDAttributes.VendorID);
		 printf("%ws, ", ManufacturerName ? ManufacturerBuffer : NotSupplied);
		 printf("PID = %4.4x, Name = ", HIDAttributes.ProductID);
		 printf("%ws\n", ProductName ? ProductBuffer : NotSupplied);
#endif
		 bool Success = HidD_GetPreparsedData(HIDHandle, &PreparsedData);
		 HidP_GetCaps(PreparsedData, &Capabilities);
	 }
	 return 1;
 }

 /*
	revert@ 写入成功返回真，写入失败返回假
 */
 BOOL USBClass::WriteUSB(CHAR	OutputReport[])
 {
	 DWORD	bWritten;
	 return WriteFile(HIDHandle, OutputReport, Capabilities.OutputReportByteLength, &bWritten, NULL);
 }

 /*
	parameter@ 需要一个cstring BUF缓存
	revert@ 成功返回真失败假
 */
 BOOL USBClass::ReadUSB(CString& stmp)
 {
	 stmp = "";
	 ULONG	Result;
	 int InputReportLength = Capabilities.InputReportByteLength;
	 BYTE	InputReport[300];
	 DWORD	bRead;

	 if (!ReadFile(HIDHandle, InputReport, Capabilities.InputReportByteLength, &bRead, NULL))
	 {
		 return FALSE;
	 }
	 CString str;
	 int iEndflag = 0;
	 for (int i = 0; i<Capabilities.InputReportByteLength-2; i++)
	 {
		 if ('\0' == InputReport[i])  // 去掉帧头帧尾'\0' 
		 {
			 if (2 == iEndflag++) 
			 {
				 return TRUE;
			 }
		 }
		 str.Format("%c", InputReport[i]); //%02X, 
		 stmp += str;					   //+=
	 }

	 return TRUE;
 }


 BOOL USBClass::CloseUSB()
 {
	 if (!CloseHandle(HIDHandle))
	 {
		 return FALSE;
	 }
	 if (!SetupDiDestroyDeviceInfoList(PnPHandle))
	 {
		 return FALSE;
	 }
	 return TRUE;

 }
