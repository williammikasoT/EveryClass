
//�ο���https://www.cnblogs.com/tianya2543/p/4165997.html

#pragma once
#include "stdafx.h"
//excel ��Ҫ�õ���ͷ�ļ�
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
	//����ӿ������ 
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

//excel��temcode��pcode
/*ExcelClass excel;
CString strPath = L"D:\\BeeMagicMould\\Library_dir\\��ʷ���Ϻ�ͼ�Ŷ�Ӧ��.xls";
excel.InitExcel(strPath);
std::map<CString, CString> mString;
if (!excel.ReadExcel(mString)) return ;*///ģ����루temcode�����ϱ�ţ�pcode��
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
