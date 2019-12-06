#include "stdafx.h"
#include "ExcelClass.h"


ExcelClass::ExcelClass()
{
}


ExcelClass::~ExcelClass()
{
	/*CloseExcel();*/
}


BOOL ExcelClass::InitExcel(CString strFilePath)
{
	if (!AfxOleInit())
		return FALSE;

	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	if (!m_app.CreateDispatch(_T("Excel.Application"), NULL))
	{
		AfxMessageBox(_T("无法启动Excel服务器!"));
		return false;
	}

	m_books.AttachDispatch(m_app.get_Workbooks());
	m_lpDisp = m_books.Open(strFilePath, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);


	return TRUE;
}

BOOL ExcelClass::WriteExcel(std::vector<CString> vtrData, CString strFileName,BOOL bLogExcelTimeLastCol)
{

	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	//if (!m_app.CreateDispatch(_T("Excel.Application"))) return FALSE;
	
	//m_lpDisp = m_books.Open(strFileName, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);

	m_book.AttachDispatch(m_lpDisp);
	m_books = m_app.get_Workbooks();
	
	m_sheets = m_book.get_Worksheets();
	m_sheet = m_sheets.get_Item(COleVariant((short)1));
	//获得单元格的内容 使数据有追加记录
	m_range = m_sheet.get_UsedRange();
	m_range = m_range.get_Rows();
	long UsedRows = m_range.get_Count();
	CString strNum;
	strNum.Format(L"%d", UsedRows + 1);


	if (bLogExcelTimeLastCol) 
	{
		vtrData.push_back(GetCurTiem());
	}


	std::vector<CString> vStrLetter, vStrData;
	// 暂时最多写ABCDE行
	vStrLetter.push_back(L"A");
	vStrLetter.push_back(L"B");
	vStrLetter.push_back(L"C");
	vStrLetter.push_back(L"D");
	vStrLetter.push_back(L"E");
	vStrLetter.push_back(L"F");

	//A3 A3,B3 B3 C3 C3,D3 D3
	CString strI;
	for (int i = 0; i < vtrData.size(); i++)
	{
		strI = vStrLetter[i] + strNum;
		m_range = m_sheet.get_Range(COleVariant(strI), COleVariant(strI));
		CString sss = vtrData[i];
		m_range.put_Value2(COleVariant(sss));  // 输入数据
	}

	// excel保存文件到当前目录下覆盖,不提示保存

	CloseExcel();

	return TRUE;

}


bool ExcelClass::ReadExcel(std::map<CString, CString>& mString)
{

	//得到Workbook    
	m_book.AttachDispatch(m_lpDisp);
	//得到Worksheets   
	m_sheets.AttachDispatch(m_book.get_Worksheets());

	//得到当前活跃sheet 
	m_lpDisp = m_book.get_ActiveSheet();
	m_sheet.AttachDispatch(m_lpDisp);

	//获取行，列
	m_range = m_sheet.get_UsedRange();

	m_range = m_range.get_Rows();
	long UsedRows = m_range.get_Count();
	m_range  = m_range.get_Columns();
	long UsedCols = m_range.get_Count();

	//std::map<CString, CString> mString;

	CStringArray strName;
	CStringArray strArr;
	for (int r = 2;r <= UsedRows; r++)
	{ 
		for (int c = 2; c <= 3; c++)
		{
			m_range.AttachDispatch(m_sheet.get_Cells());
			m_range.AttachDispatch(m_range.get_Item(COleVariant((long)r), COleVariant((long)c)).pdispVal);   //第一变量是行，第二个变量是列，即第二行第一列


			COleVariant vResult = m_range.get_Value2();
			if (vResult.vt == VT_BSTR) //字符串  
			{
				if(c == 2)
				strName.Add(vResult.bstrVal);
				else if(c == 3)
				strArr.Add(vResult.bstrVal);
			}
			else if (vResult.vt == VT_R8) //8字节的数字  
			{
				CString str;
				str.Format(_T("%.0f"), vResult.dblVal);
				if (c == 2)
					strName.Add(str);
				else if(c == 3)
					strArr.Add(str);
			}

		}
	}

	for (int i = 0; i < strName.GetCount(); i++)
	{
		if (strName[i].IsEmpty() || strArr.IsEmpty())
			continue;
		mString.insert(std::pair<CString, CString>(strArr[i], strName[i]));
	}
		

		//mString[strName[i]] = strArr[i];

	CloseExcel();

	return true;
}

void ExcelClass::CloseExcel()
{
	m_book.Save();
	m_range.ReleaseDispatch();
	m_sheet.ReleaseDispatch();
	m_sheets.ReleaseDispatch();
	m_book.ReleaseDispatch();
	m_books.ReleaseDispatch();
	m_app.Quit();
	m_app.ReleaseDispatch();
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