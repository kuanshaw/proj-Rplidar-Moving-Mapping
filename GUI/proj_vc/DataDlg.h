#pragma once

#include "afxwin.h"
#include "afx.h"


// CDataDlg �Ի���

class CDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataDlg)

public:
	CDataDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDataDlg();

// �Ի�������
	enum { IDD = IDD_DATADLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CEdit m_Edit;		//�༭����

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	CButton m_Btn;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnButton2();
};
