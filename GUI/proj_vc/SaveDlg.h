#pragma once
#include "afxwin.h"


// CSaveDlg �Ի���

class CSaveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveDlg)

public:
	CSaveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSaveDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_SaveEid;
	afx_msg void OnBnClickedOk();
};
