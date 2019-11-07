// DrawDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test3.h"
#include "DrawDlg.h"
#include "Test3Dlg.h"
#include "afxdialogex.h"


#include <math.h>

const float PI = (float)3.14159265;						//
const int CHANGE = (int)6;								//距离放缩比例
const int PTSIZE = (int)2;								//点的尺寸大小

// CDrawDlg 对话框

IMPLEMENT_DYNAMIC(CDrawDlg, CDialogEx)

CDrawDlg::CDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrawDlg::IDD, pParent)
{

}

CDrawDlg::~CDrawDlg()
{
}

/*
void CDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_Draw);
}
*/

BEGIN_MESSAGE_MAP(CDrawDlg, CDialogEx)

//	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_EN_CHANGE(IDC_EDIT1, &CDrawDlg::OnEnChangeEdit1)

	ON_WM_PAINT()
	END_MESSAGE_MAP()


// CDrawDlg 消息处理程序


 void CDrawDlg::DrawPoint(int pos, double Angle, double Distance)				//自定义函数，角度、距离画点函数
{
	
	if(pos==0)												//*****画坐标系
	{
		CPaintDC dc(this);
		GetClientRect(m_Rect);

		dc.FillSolidRect(m_Rect, RGB(80,80,80));   			//设置整个对话框窗口为灰色背景
		dc.TextOut(0, 0, _T("鼠标右键停止扫描"));
		dc.SetViewportOrg(m_Rect.Width()/2, m_Rect.Height()/2);						//设置原点位置450, 325

		dc.SelectObject(m_PenXY);							//装上画坐标轴的画笔，红色
		dc.MoveTo(m_Rect.Width()/2,0);									//X轴
		dc.LineTo(m_Rect.Width()/(-2),0);  								//
		dc.MoveTo(0,m_Rect.Height()/2);									//Y轴
		dc.LineTo(0,m_Rect.Height()/(-2));								//

		dc.Arc(-50,50,50,-50,0,50,0,50);					//半径50的圆
		dc.Arc(-100,100,100,-100,0,100,0,100);				//半径100的圆
		dc.Arc(-200,200,200,-200,0,200,0,200);				//半径200的圆
		dc.Arc(-400,400,400,-400,0,400,0,400);				//半径400的圆

		dc.TextOut(1, 1, _T("0"));
		dc.TextOut(51, 1, _T("200"));
		dc.TextOut(101, 1, _T("400"));
		dc.TextOut(201, 1, _T("800"));
		dc.TextOut(401, 1, _T("1600"));
	}
	
															//****画点/
	p_Static_Draw = (CStatic *)GetDlgItem(IDC_STATIC_DRAW);	//指向静态文本框的指针
	CPaintDC dc1( p_Static_Draw );							//创建静态文本框的画笔

	dc1.SetViewportOrg(m_Rect.Width()/2, m_Rect.Height()/2);	

	GetClientRect(m_Rect);									//获取静态文本框的矩形

	dc1.SelectObject(m_BrushPt);							//画笔装上画刷，黄色

	p_Static_Draw->Invalidate();							//更新点的数据

	double x = ( Distance*sin( Angle*PI/180 )) / CHANGE;	//计算x值
	double y = ( Distance*cos( Angle*PI/180 )) / CHANGE;	//计算y值

	dc1.Ellipse( (int)x-PTSIZE, (int)y-PTSIZE, (int)x+PTSIZE, (int)y+PTSIZE);		//画圆函数

}
 
 
void CDrawDlg::Renew(void)
{
	InvalidateRect(m_Rect, true);					/////***刷新	//会调用Onpaint，陷入死循环
}


void CDrawDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	GetClientRect(m_Rect);				

	//InvalidateRect(m_Rect, true);					/////***刷新	//会调用Onpaint，陷入死循环
	
	dc.FillSolidRect(m_Rect, RGB(80,80,80));   			//设置整个对话框窗口为灰色背景
	dc.TextOut(0, 0, _T("鼠标右键停止扫描"));

	dc.SetViewportOrg(m_Rect.Width()/2, m_Rect.Height()/2);							//设置原点位置

	dc.SelectObject(m_PenXY);										//装上画坐标轴的画笔，红色
	dc.MoveTo(m_Rect.Width()/2,0);									//X轴
	dc.LineTo(m_Rect.Width()/(-2),0);  								//
	dc.MoveTo(0,m_Rect.Height()/2);									//Y轴
	dc.LineTo(0,m_Rect.Height()/(-2));								//

	dc.Arc(-50,50,50,-50,0,50,0,50);					//半径50的圆
	dc.Arc(-100,100,100,-100,0,100,0,100);				//半径100的圆
	dc.Arc(-200,200,200,-200,0,200,0,200);				//半径200的圆
	dc.Arc(-400,400,400,-400,0,400,0,400);				//半径400的圆

	dc.TextOut(1, 1, _T("0"));
	dc.TextOut(51, 1, _T("200"));
	dc.TextOut(101, 1, _T("400"));
	dc.TextOut(201, 1, _T("800"));
	dc.TextOut(401, 1, _T("1600"));

}


int CDrawDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CDrawDlg::OnEnChangeEdit1()						//编辑框函数
{

	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码	
}


BOOL CDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_BrushBk.CreateSolidBrush( RGB(80,80,80) );						//设置背景色画刷 灰色
	m_PenXY.CreatePen( PS_SOLID, 1, RGB(255,125,64) );					//坐标轴画刷 红色
	m_BrushPt.CreateSolidBrush( RGB(255,255,0) );						//点的颜色画刷 黄色

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

