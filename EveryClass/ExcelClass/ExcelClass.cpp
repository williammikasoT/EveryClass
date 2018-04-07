#include "stdafx.h"
#include "ExcelClass.h"


ExcelClass::ExcelClass()
{
}


ExcelClass::~ExcelClass()
{
}


BOOL ExcelClass::InitExcel()
{
	if (!AfxOleInit())
	{
		//MessageBox(L"初始出现问题");
		return FALSE;
	}
	return TRUE;
}

BOOL ExcelClass::WriteExcel(std::vector<CString> vtrData, CString strFileName,BOOL bLogExcelTimeLastCol)
{
	std::vector<CString> vStrLetter,vStrData;
	// 暂时最多写ABCDE行
	vStrLetter.push_back(L"A");
	vStrLetter.push_back(L"B");
	vStrLetter.push_back(L"C");
	vStrLetter.push_back(L"D");
	vStrLetter.push_back(L"E");
	vStrLetter.push_back(L"F");

	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		//this->MessageBox(_T("无法创建Excel应用！"));
		return FALSE;
	}

	books = app.get_Workbooks();
	TCHAR szPath[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, szPath);
	CString strPath(szPath);
	strPath += strFileName; // "\\模版.xlsx"
	lpDisp = books.Open(strPath, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);
	book.AttachDispatch(lpDisp);
	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));
	//获得单元格的内容 使数据有追加记录
	range = sheet.get_UsedRange();
	range = range.get_Rows();
	long UsedRows = range.get_Count();
	CString strNum;
	strNum.Format(L"%d", UsedRows + 1);


	if (bLogExcelTimeLastCol) 
	{
		vtrData.push_back(GetCurTiem());
	}

	//A3 A3,B3 B3 C3 C3,D3 D3
	CString strI;
	for (int i = 0; i < vtrData.size(); i++)
	{
		strI = vStrLetter[i] + strNum;
		range = sheet.get_Range(COleVariant(strI), COleVariant(strI));
		CString sss = vtrData[i];
		range.put_Value2(COleVariant(sss));  // 输入数据
	}

	// excel保存文件到当前目录下覆盖,不提示保存
	book.Save();
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.Quit();
	app.ReleaseDispatch();

	return TRUE;

}

CString ExcelClass::GetCurTiem()
{
	CString strTime, str;
	CTime time = CTime::GetCurrentTime();   ///构造CTime对象
	int m_nYear = time.GetYear();      ///年
	int m_nMonth = time.GetMonth();      ///月
	int m_nDay = time.GetDay();      ///日
	int m_nHour = time.GetHour();      ///小时
	int m_nMinute = time.GetMinute();   ///分钟
	int m_nSecond = time.GetSecond();   ///秒
	strTime.Format(L"%d/", m_nYear);
	str = strTime;
	strTime.Format(L"%02d/", m_nMonth);
	str += strTime;
	strTime.Format(L"%02d/", m_nDay);
	str += strTime;
	strTime.Format(L"%02d:", m_nHour);
	str += strTime;
	strTime.Format(L"%02d:", m_nMinute);
	str += strTime;
	strTime.Format(L"%02d", m_nSecond);
	str += strTime;

	return str;
}