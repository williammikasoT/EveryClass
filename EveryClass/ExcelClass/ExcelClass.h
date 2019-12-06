
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
#include<map>
//using namespace std;

class ExcelClass
{
public:
	ExcelClass();
	~ExcelClass();
	//定义接口类变量 
	CApplication m_app;
	CWorkbook m_book;
	CWorkbooks m_books;
	CWorksheet m_sheet;
	CWorksheets m_sheets;
	CRange m_range;
	CFont0 m_font;
	CRange m_cols;
	LPDISPATCH m_lpDisp;





	BOOL InitExcel(CString strFilePath);
	BOOL WriteExcel(std::vector<CString> vtrData,CString strFileName,BOOL bLogExcelTimeLastCol);
	bool ReadExcel (std::map<CString, CString> &mString);
	void CloseExcel();
	CString GetCurTiem();
};

//excel的temcode，pcode
/*ExcelClass excel;
CString strPath = L"D:\\BeeMagicMould\\Library_dir\\历史物料和图号对应表.xls";
excel.InitExcel(strPath);
std::map<CString, CString> mString;
if (!excel.ReadExcel(mString)) return ;*///模板编码（temcode）物料编号（pcode）
//std::map<CString, CString>::iterator iter; //excel
//std::map<CString, CString>::iterator iter;
//CString strTemp;
//for (iter = mString.begin(); iter != mString.end(); iter++)
//{
//	CString str = iter->first + L" " + iter->second +  L",";
//	strTemp += str;
//}
//sdProUIHelper::DisplayErrorMessageBox(strTemp);


//int count = m_strNameArr.GetCount();
//CString strTemp1;
//for (int i = 0; i<count; i++) {
//	CString str = m_strNameArr[i] + L",";
//	strTemp1 += str;
//}
//sdProUIHelper::DisplayErrorMessageBox(strTemp1);
