
// Test3Dlg.cpp : 实现文件
//
#include "stdafx.h"			//一定要在最头

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
		
RPlidarDriver * drv = RPlidarDriver::CreateDriver(RPlidarDriver::DRIVER_TYPE_SERIALPORT);		//定义类drv

CString Text_str = _T("NOTHING");

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTest3Dlg 对话框

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


// CTest3Dlg 消息处理程序

BOOL CTest3Dlg::OnInitDialog()									//*****/初始化函数
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

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

	m_Time.SetWindowTextW(_T("10"));							//循环扫描次数

	count = _countof(nodes);									//定义角度数组长度，用于计数
	opt_com_path = "\\\\.\\com3";								//设置串口！默认值
	opt_com_baudrate = 115200;									//设置波特率 _u32=4个字节 UINT型
	op_result = drv->getHealth(healthinfo);						//获取健康序号

	Angle=0;													//
	Distance=0;													//初始化数据信息
	Quality=0;													//

	break_flag = 0;
	// 除非将焦点设置到控件，否则返回 TRUE
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


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTest3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect m_Rect;
		GetClientRect(&m_Rect);
		int x = (m_Rect.Width() - cxIcon + 1) / 2;
		int y = (m_Rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTest3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTest3Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	CDataDlg *p_Dlg = new CDataDlg;
	p_Dlg->Create(IDD_DATADLG);			//创建窗口
	p_Dlg->ShowWindow(SW_SHOW);			//激活窗口
	*/
}


int CTest3Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}


void CTest3Dlg::OnBnClickedButton2()					//******/启动扫描函数/
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

	if (!drv)																	////******/检测串口，建立连接/
	{
		m_Edit2.SetWindowTextW(_T("insufficent memory, exit."));
        exit(-2);		//exit函数 头文件<stdlib.h>中
    }

    if (IS_FAIL(drv->connect(opt_com_path, opt_com_baudrate)))					//建立连接	//IS_FAIL（）宏定义函数
	{
		m_Edit2.SetWindowTextW(_T("Error, cannot bind to the specified serial port."));
		goto on_finished;														//连接失败，提前结束，on_finished标识
	}

    rplidar_response_device_info_t devinfo;										//定义devinfo，获取驱动信息

    if (IS_FAIL(drv->getDeviceInfo(devinfo)))									//失败的宏定义函数
	{
		m_Edit2.SetWindowTextW(_T("Error, cannot get device info."));
		goto on_finished;
    }

    // check health...
    if (!checkRPLIDARHealth(drv))												//检查设备健康度，在上方定义
	{
		m_Edit2.SetWindowTextW(_T("Error."));
		goto on_finished;
	}
	
	CDrawDlg *p_Draw = new CDrawDlg;			//定义Draw窗口
	p_Draw->Create(IDD_DIALOG_DRAW);			//创建窗口
	p_Draw->ShowWindow(SW_SHOW);				//激活窗口

    drv->startMotor();							//启动电机
    drv->startScan();							//开启扫描
    signal(SIGINT, ctrlc);

	m_Time.GetWindowTextW(Time);				//获取扫描次数
	i = _ttoi(Time);						//CString转int

	while(i--)														///******/进入循环，循环扫描/
	{
        op_result = drv->grabScanData(nodes, count);				//节点数据
		
        if (IS_OK(op_result))										//IS_OK()是判断结果是否正确
		{
            drv->ascendScanData(nodes, count);						//加快扫描

			m_Edit2.SetWindowTextW(_T("  Angle   Distance   Quality\r\n"));				//清空再重新开始

			for(pos = 0; pos<(int)count; ++pos)											//******显示数据+画点/
			{
				Angle = (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f;			//
				Distance = nodes[pos].distance_q2/4.0f;															//显示数据赋值
				Quality = nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT;					//

				p_Draw->DrawPoint(pos, Angle, Distance);								//在地图上画点

				m_Str.Format(_T("%0.3lf%12.3lf%5d\r\n"), Angle, Distance, Quality);		//合成显示数据的CString

				nLength = m_Edit2.GetWindowTextLength();							//
				m_Edit2.SetSel(nLength, nLength);									//使文本框自动卷到最后
				m_Edit2.ReplaceSel(m_Str);											//将数据插入Data对话框

				if(KEY_DOWN(VK_RBUTTON))
					break_flag = 1;
			}
		}
		
		p_Draw->Renew();				//自动调用OnPaint()
	//	p_Draw->OnPaint();

		if(break_flag==1)
		{
			goto on_finished;
		}
   }

on_finished:													///********异常跳转

	m_Edit2.ReplaceSel(_T("\r\nOvered!\r\n"));					//Data数据显示窗口清空

	drv->stop();
	drv->stopMotor();

	if(break_flag==1)
		MessageBoxW(_T("已提前结束扫描"), _T("BREAK"), MB_ICONEXCLAMATION | MB_OK);
	else if(i<=0)
		MessageBoxW(_T("已完成扫描"), _T("BREAK"),  MB_ICONEXCLAMATION | MB_OK);								//弹出标志消息框
	else
		MessageBoxW(_T("异常结束"), _T("BREAK"),  MB_ICONEXCLAMATION | MB_OK);

}

void CTest3Dlg::OnBnClickedButton4()							//暂停按钮函数
{
	// TODO: 在此添加控件通知处理程序代码

	drv->stop();												//电机停止
	drv->stopMotor();											//扫描停止
	
	MessageBoxW(_T("已停止扫描！"), _T("STOP"), MB_ICONEXCLAMATION | MB_OK);			//弹出暂停消息框

}


void CTest3Dlg::OnBnClickedCancel()								//取消按钮函数，关闭程序
{
	// TODO: 在此添加控件通知处理程序代码
	drv->stop();
	drv->stopMotor();
	RPlidarDriver::DisposeDriver(drv);

	CDialogEx::OnCancel();
}


void CTest3Dlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	CBaocunDlg * p_Bao = new CBaocunDlg;
	p_Bao->Create(IDD_DIALOG2_BAOCUN);
	p_Bao->ShowWindow(SW_SHOW);

	p_Bao->m_BaocunDlg.SetWindowTextW(_T("E:\\Test.txt"));
	
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(Text_str);							//将编辑框中的显示数据保存下来，Text_str保存

}


void CTest3Dlg::SavetoFile(char * f_name)
{
	FILE * pf;
	if( (pf = fopen(f_name, "w++")) == NULL)
	{
		MessageBoxW(_T("无法打开该文件"), _T("SAVE"), MB_OK);
	}

	fwrite(Text_str, 1, Text_str.GetLength(), pf);

	fflush(pf);
	fclose(pf);

	MessageBoxW(_T("保存成功"), _T("SAVE"), MB_OK);
}
