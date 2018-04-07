
//参考：https://www.cnblogs.com/tianya2543/p/4165997.html

#pragma once
#include "stdafx.h"
//excel 需要用到的头文件
#include "CApplication.h"
#include "CFont0.h"
#include"CRange.h"
#include"CWorkbook.h"
#include"CWorkbooks.h"
#include"CWorksheet.h"
#include"CWorksheets.h"
#include<vector>
//using namespace std;

class ExcelClass
{
public:
	ExcelClass();
	~ExcelClass();
	//定义接口类变量 
	CApplication app;
	CWorkbook book;
	CWorkbooks books;
	CWorksheet sheet;
	CWorksheets sheets;
	CRange range;
	CFont0 font;
	CRange cols;
	LPDISPATCH lpDisp;

	BOOL InitExcel();
	BOOL WriteExcel(std::vector<CString> vtrData,CString strFileName,BOOL bLogExcelTimeLastCol);
	CString GetCurTiem();
};

