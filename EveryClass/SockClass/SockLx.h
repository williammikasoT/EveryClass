// SockLx.h : Version 1.1（支持Unicode、支持VS2015和VC6编译环境）
//Author:吕鑫老师封装类 （支持Linux开发）
//吕鑫老师微博：http://t.qq.com/richmain 吕鑫老师微信：richmain
//更多更好的是项目开发视频教程，请登录http://www.baojy.com
//////////////////////////////////////////////////////////////////////

#pragma once
//#define _CRT_SECURE_NO_WARNINGS
//#define _WINSOCK_DEPRECATED_NO_WARNINGS



#include <stdlib.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <process.h>
#ifdef _UNICODE
#include <comdef.h>


//#include <WS2tcpip.h>
#endif
typedef int socklen_t;
typedef void RET_TYPE;
#else
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
typedef unsigned int SOCKET;
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#ifndef _T
#define _T(x) x
#endif
typedef struct in_addr IN_ADDR;
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL            *PBOOL;
typedef BOOL             *LPBOOL;
typedef BYTE            *PBYTE;
typedef BYTE             *LPBYTE;
typedef int             *PINT;
typedef int              *LPINT;
typedef WORD            *PWORD;
typedef WORD             *LPWORD;
typedef long             *LPLONG;
typedef DWORD           *PDWORD;
typedef DWORD            *LPDWORD;
typedef void             *LPVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef const char* LPCTSTR,*LPCSTR;
typedef char* LPTSTR,*LPSTR;
typedef void* RET_TYPE;
inline int GetLastError()
{
	return errno;
}
#define closesocket(x) close(x)


#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif
#endif
//MFC中已有CScoket，不太支持控制台，不支持多线程
class CSockLx
{
protected:
	SOCKET m_hSocket;//核心成员变量
public:
	operator SOCKET() const
	{
		return m_hSocket;
	}
	BOOL Create(UINT nSocketPort = 0, int nSocketType = SOCK_STREAM
		, LPCTSTR lpszSocketAddress = NULL);

	BOOL Accept(CSockLx& rConnectedSocket, LPTSTR szIP = NULL, UINT *nPort = NULL);
	BOOL Connect(LPCTSTR lpszHostAddress, UINT nHostPort);
	BOOL Listen(int nConnectionBacklog = 5)
	{
		return !listen(m_hSocket, nConnectionBacklog);
	}
	int SendTo(const void* lpBuf, int nBufLen, UINT nHostPort, LPCTSTR lpszHostAddress = NULL, int nFlags = 0);

	int ReceiveFrom(void* lpBuf, int nBufLen, LPTSTR rSocketAddress, UINT& rSocketPort, int nFlags = 0);

	int Send(const void* lpBuf, int nBufLen, int nFlags = 0)
	{
		return send(m_hSocket, (LPCSTR)lpBuf, nBufLen, nFlags);
	}
	int Receive(void* lpBuf, int nBufLen, int nFlags = 0)
	{
		return recv(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags);
	}
	BOOL GetPeerName(LPTSTR rSocketAddress, UINT& rSocketPort);
	BOOL GetSockName(LPTSTR rSocketAddress, UINT& rSocketPort);

	void Close()
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}

#ifdef _UNICODE
	inline static void Pton(LPCTSTR sHostAddr, IN_ADDR &in)
	{
			in.s_addr = inet_addr(_bstr_t(sHostAddr));
	}
	inline static void Ntop(IN_ADDR &in, LPTSTR sHostAddr)
	{
		_tcscpy(sHostAddr, _bstr_t(inet_ntoa(in)));
	}

#else
	inline static void Pton(LPCTSTR sHostAddr, IN_ADDR &in)
	{
		in.s_addr = inet_addr(sHostAddr);
	}
	inline static void Ntop(IN_ADDR &in, LPTSTR sHostAddr)
	{
		
		strcpy_s(sHostAddr, strlen(sHostAddr)+1, inet_ntoa(in));
	}
#endif

	CSockLx();
	virtual ~CSockLx();
};