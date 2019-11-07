
// Test3Dlg.cpp : ʵ���ļ�
//
#include "stdafx.h"			//һ��Ҫ����ͷ

#include "Zaza.h"

#include "Test3.h"
#include "Test3Dlg.h"
#include "DrawDlg.h"
#include "DataDlg.h"
#include "afxdialogex.h"
#include "BaocunDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace rp::standalone::rplidar;
		
RPlidarDriver * drv = RPlidarDriver::CreateDriver(RPlidarDriver::DRIVER_TYPE_SERIALPORT);		//������drv

CString Text_str = _T("NOTHING");

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};


CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTest3Dlg �Ի���

CTest3Dlg::CTest3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTest3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CTest3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_COMBO1, m_Cb);
	DDX_Control(pDX, IDC_EDIT_TIME, m_Time);
}


BEGIN_MESSAGE_MAP(CTest3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTest3Dlg::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON2, &CTest3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CTest3Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDCANCEL, &CTest3Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CTest3Dlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CTest3Dlg ��Ϣ�������

BOOL CTest3Dlg::OnInitDialog()									//*****/��ʼ������
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	GetDlgItem(IDC_COMBO1)->SetWindowText(_T(" "));
	m_Cb.InsertString( 0, _T(" "));
	m_Cb.InsertString( 1, _T("COM1"));
	m_Cb.InsertString( 2, _T("COM2"));
	m_Cb.InsertString( 3, _T("COM3"));
	m_Cb.InsertString( 4, _T("COM4"));
	m_Cb.InsertString( 5, _T("COM5"));
	m_Cb.InsertString( 6, _T("COM6"));
	m_Cb.InsertString( 7, _T("COM7"));
	m_Cb.InsertString( 8, _T("COM8"));
	m_Cb.InsertString( 9, _T("COM9"));
	m_Cb.InsertString( 10, _T("COM10"));
	m_Cb.InsertString( 11, _T("COM11"));
	m_Cb.InsertString( 12, _T("COM12"));
	m_Cb.InsertString( 13, _T("COM13"));
	m_Cb.InsertString( 14, _T("COM14"));
	m_Cb.InsertString( 15, _T("COM15"));

	m_Time.SetWindowTextW(_T("10"));							//ѭ��ɨ�����

	count = _countof(nodes);									//����Ƕ����鳤�ȣ����ڼ���
	opt_com_path = "\\\\.\\com3";								//���ô��ڣ�Ĭ��ֵ
	opt_com_baudrate = 115200;									//���ò����� _u32=4���ֽ� UINT��
	op_result = drv->getHealth(healthinfo);						//��ȡ�������

	Angle=0;													//
	Distance=0;													//��ʼ��������Ϣ
	Quality=0;													//

	break_flag = 0;
	// ���ǽ��������õ��ؼ������򷵻� TRUE
	return TRUE;  
}


void CTest3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTest3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect m_Rect;
		GetClientRect(&m_Rect);
		int x = (m_Rect.Width() - cxIcon + 1) / 2;
		int y = (m_Rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTest3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTest3Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	CDataDlg *p_Dlg = new CDataDlg;
	p_Dlg->Create(IDD_DATADLG);			//��������
	p_Dlg->ShowWindow(SW_SHOW);			//�����
	*/
}


int CTest3Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	return 0;
}


void CTest3Dlg::OnBnClickedButton2()					//******/����ɨ�躯��/
{
	int nLength;
	break_flag = 0;
	CString Time;
	int i = 10;

	int nIndex = m_Cb.GetCurSel();
	switch(nIndex)
	{
	case 0: 
	{
		m_Edit2.SetWindowTextW(_T("Please set up the port."));
		goto on_finished;
	}
	case 1:	opt_com_path = "\\\\.\\com1"; break;
	case 2:	opt_com_path = "\\\\.\\com2"; break;
	case 3:	opt_com_path = "\\\\.\\com3"; break;
	case 4:	opt_com_path = "\\\\.\\com4"; break;
	case 5:	opt_com_path = "\\\\.\\com5"; break;
	case 6:	opt_com_path = "\\\\.\\com6"; break;
	case 7:	opt_com_path = "\\\\.\\com7"; break;
	case 8:	opt_com_path = "\\\\.\\com8"; break;
	case 9:	opt_com_path = "\\\\.\\com9"; break;
	case 10: opt_com_path = "\\\\.\\com10"; break;
	case 11: opt_com_path = "\\\\.\\com11"; break;
	case 12: opt_com_path = "\\\\.\\com12"; break;
	case 13: opt_com_path = "\\\\.\\com13"; break;
	case 14: opt_com_path = "\\\\.\\com14"; break;
	case 15: opt_com_path = "\\\\.\\com15"; break;
	default: opt_com_path = "\\\\.\\com3"; break;
	}

	if (!drv)																	////******/��⴮�ڣ���������/
	{
		m_Edit2.SetWindowTextW(_T("insufficent memory, exit."));
        exit(-2);		//exit���� ͷ�ļ�<stdlib.h>��
    }

    if (IS_FAIL(drv->connect(opt_com_path, opt_com_baudrate)))					//��������	//IS_FAIL�����궨�庯��
	{
		m_Edit2.SetWindowTextW(_T("Error, cannot bind to the specified serial port."));
		goto on_finished;														//����ʧ�ܣ���ǰ������on_finished��ʶ
	}

    rplidar_response_device_info_t devinfo;										//����devinfo����ȡ������Ϣ

    if (IS_FAIL(drv->getDeviceInfo(devinfo)))									//ʧ�ܵĺ궨�庯��
	{
		m_Edit2.SetWindowTextW(_T("Error, cannot get device info."));
		goto on_finished;
    }

    // check health...
    if (!checkRPLIDARHealth(drv))												//����豸�����ȣ����Ϸ�����
	{
		m_Edit2.SetWindowTextW(_T("Error."));
		goto on_finished;
	}
	
	CDrawDlg *p_Draw = new CDrawDlg;			//����Draw����
	p_Draw->Create(IDD_DIALOG_DRAW);			//��������
	p_Draw->ShowWindow(SW_SHOW);				//�����

    drv->startMotor();							//�������
    drv->startScan();							//����ɨ��
    signal(SIGINT, ctrlc);

	m_Time.GetWindowTextW(Time);				//��ȡɨ�����
	i = _ttoi(Time);						//CStringתint

	while(i--)														///******/����ѭ����ѭ��ɨ��/
	{
        op_result = drv->grabScanData(nodes, count);				//�ڵ�����
		
        if (IS_OK(op_result))										//IS_OK()���жϽ���Ƿ���ȷ
		{
            drv->ascendScanData(nodes, count);						//�ӿ�ɨ��

			m_Edit2.SetWindowTextW(_T("  Angle   Distance   Quality\r\n"));				//��������¿�ʼ

			for(pos = 0; pos<(int)count; ++pos)											//******��ʾ����+����/
			{
				Angle = (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f;			//
				Distance = nodes[pos].distance_q2/4.0f;															//��ʾ���ݸ�ֵ
				Quality = nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT;					//

				p_Draw->DrawPoint(pos, Angle, Distance);								//�ڵ�ͼ�ϻ���

				m_Str.Format(_T("%0.3lf%12.3lf%5d\r\n"), Angle, Distance, Quality);		//�ϳ���ʾ���ݵ�CString

				nLength = m_Edit2.GetWindowTextLength();							//
				m_Edit2.SetSel(nLength, nLength);									//ʹ�ı����Զ������
				m_Edit2.ReplaceSel(m_Str);											//�����ݲ���Data�Ի���

				if(KEY_DOWN(VK_RBUTTON))
					break_flag = 1;
			}
		}
		
		p_Draw->Renew();				//�Զ�����OnPaint()
	//	p_Draw->OnPaint();

		if(break_flag==1)
		{
			goto on_finished;
		}
   }

on_finished:													///********�쳣��ת

	m_Edit2.ReplaceSel(_T("\r\nOvered!\r\n"));					//Data������ʾ�������

	drv->stop();
	drv->stopMotor();

	if(break_flag==1)
		MessageBoxW(_T("����ǰ����ɨ��"), _T("BREAK"), MB_ICONEXCLAMATION | MB_OK);
	else if(i<=0)
		MessageBoxW(_T("�����ɨ��"), _T("BREAK"),  MB_ICONEXCLAMATION | MB_OK);								//������־��Ϣ��
	else
		MessageBoxW(_T("�쳣����"), _T("BREAK"),  MB_ICONEXCLAMATION | MB_OK);

}

void CTest3Dlg::OnBnClickedButton4()							//��ͣ��ť����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	drv->stop();												//���ֹͣ
	drv->stopMotor();											//ɨ��ֹͣ
	
	MessageBoxW(_T("��ֹͣɨ�裡"), _T("STOP"), MB_ICONEXCLAMATION | MB_OK);			//������ͣ��Ϣ��

}


void CTest3Dlg::OnBnClickedCancel()								//ȡ����ť�������رճ���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	drv->stop();
	drv->stopMotor();
	RPlidarDriver::DisposeDriver(drv);

	CDialogEx::OnCancel();
}


void CTest3Dlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CBaocunDlg * p_Bao = new CBaocunDlg;
	p_Bao->Create(IDD_DIALOG2_BAOCUN);
	p_Bao->ShowWindow(SW_SHOW);

	p_Bao->m_BaocunDlg.SetWindowTextW(_T("E:\\Test.txt"));
	
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(Text_str);							//���༭���е���ʾ���ݱ���������Text_str����

}


void CTest3Dlg::SavetoFile(char * f_name)
{
	FILE * pf;
	if( (pf = fopen(f_name, "w++")) == NULL)
	{
		MessageBoxW(_T("�޷��򿪸��ļ�"), _T("SAVE"), MB_OK);
	}

	fwrite(Text_str, 1, Text_str.GetLength(), pf);

	fflush(pf);
	fclose(pf);

	MessageBoxW(_T("����ɹ�"), _T("SAVE"), MB_OK);
}
