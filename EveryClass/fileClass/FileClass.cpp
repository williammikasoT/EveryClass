#include "stdafx.h"
#include "FileClass.h"


FileClass::FileClass()
{
}


FileClass::~FileClass()
{
}

bool FileClass::C_WriteData(CString strPath, CString strName) {
	CFile WriteFile;
	WriteFile.Open(strPath, CFile::modeWrite | CFile::modeRead | CFile::modeCreate);
	USES_CONVERSION;
	char *WriteBuf = T2A(strName.GetBuffer(0));
	WriteFile.Write(WriteBuf, strlen(WriteBuf) + 1);
	WriteBuf = NULL;
	return TRUE;
}

bool FileClass::ReadData(char *name, CString &strBuf)
{
	FILE* pFile = nullptr;        //pFile = fopen(sPath.c_str(), "r+t");  
	fopen_s(&pFile, name, "rb");

	if (!pFile)
	{
		return FALSE;
	}

	fseek(pFile, 0, SEEK_END);
	int nFileLen = ftell(pFile);
	char* buf = new char[nFileLen];

	fseek(pFile, 0, SEEK_SET);
	fread(buf, sizeof(char), nFileLen, pFile);
	fclose(pFile);

	strBuf = buf;
	delete[] buf;

	return TRUE;
}

