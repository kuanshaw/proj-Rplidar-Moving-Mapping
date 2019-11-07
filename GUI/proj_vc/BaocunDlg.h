#pragma once
#include "afxwin.h"


// CBaocunDlg 对话框

class CBaocunDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBaocunDlg)

public:
	CBaocunDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBaocunDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2_BAOCUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_BaocunDlg;
	afx_msg void OnBnClickedOk();
};
