#pragma once

#include "afxwin.h"
#include "afx.h"


// CDataDlg 对话框

class CDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataDlg)

public:
	CDataDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataDlg();

// 对话框数据
	enum { IDD = IDD_DATADLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CEdit m_Edit;		//编辑框类

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	CButton m_Btn;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnButton2();
};
