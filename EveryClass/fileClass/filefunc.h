#pragma once

#include "stdafx.h"
#include<afx.h>
#include <shlwapi.h>
#include <list>
#include "tlhelp32.h"

class FileUseClass
{
public:
	FileUseClass();
	~FileUseClass();
	int  strsplinum(char *str, const char*del);
	void split_del(char **arr, char *str, const char *del);
	bool ReadData(CString sfile_x, CString sfile_y, CString &sbuff_x, CString &sbuff_y);
	bool WriteData(CString sfilex_name, CString sfiley_name, CString sbuf_x, CString sbuf_y);
	bool WriteData(CString sfilex_name, CString sbuf_x);
	CString stringToCString(std::string str);
	char* CStringToChar(CString s);
	int CStringToNum(CString s);
	int CstringToList(CString s, std::list<CString> &ls);
	DWORD GetProcessIdFromName(LPCTSTR name);
	void split_usb(char *name, int numchar, CString &sbuff, char* cWord, int numTest);
	void del_split(char **arr, char *str, const char *del);
	bool C_WriteData(CString strPath, CString strName);
};