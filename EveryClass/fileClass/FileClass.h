#pragma once

class FileClass
{
public:
	FileClass();
	~FileClass();
	bool C_WriteData(CString strPath, CString strName);
	bool ReadData(char *name, CString &strBuf);

};

