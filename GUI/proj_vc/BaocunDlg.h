#pragma once
#include "afxwin.h"


// CBaocunDlg �Ի���

class CBaocunDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBaocunDlg)

public:
	CBaocunDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaocunDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2_BAOCUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_BaocunDlg;
	afx_msg void OnBnClickedOk();
};
