// DrawDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test3.h"
#include "DrawDlg.h"
#include "Test3Dlg.h"
#include "afxdialogex.h"


#include <math.h>

const float PI = (float)3.14159265;						//
const int CHANGE = (int)6;								//�����������
const int PTSIZE = (int)2;								//��ĳߴ��С

// CDrawDlg �Ի���

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


// CDrawDlg ��Ϣ�������


 void CDrawDlg::DrawPoint(int pos, double Angle, double Distance)				//�Զ��庯�����Ƕȡ����뻭�㺯��
{
	
	if(pos==0)												//*****������ϵ
	{
		CPaintDC dc(this);
		GetClientRect(m_Rect);

		dc.FillSolidRect(m_Rect, RGB(80,80,80));   			//���������Ի��򴰿�Ϊ��ɫ����
		dc.TextOut(0, 0, _T("����Ҽ�ֹͣɨ��"));
		dc.SetViewportOrg(m_Rect.Width()/2, m_Rect.Height()/2);						//����ԭ��λ��450, 325

		dc.SelectObject(m_PenXY);							//װ�ϻ�������Ļ��ʣ���ɫ
		dc.MoveTo(m_Rect.Width()/2,0);									//X��
		dc.LineTo(m_Rect.Width()/(-2),0);  								//
		dc.MoveTo(0,m_Rect.Height()/2);									//Y��
		dc.LineTo(0,m_Rect.Height()/(-2));								//

		dc.Arc(-50,50,50,-50,0,50,0,50);					//�뾶50��Բ
		dc.Arc(-100,100,100,-100,0,100,0,100);				//�뾶100��Բ
		dc.Arc(-200,200,200,-200,0,200,0,200);				//�뾶200��Բ
		dc.Arc(-400,400,400,-400,0,400,0,400);				//�뾶400��Բ

		dc.TextOut(1, 1, _T("0"));
		dc.TextOut(51, 1, _T("200"));
		dc.TextOut(101, 1, _T("400"));
		dc.TextOut(201, 1, _T("800"));
		dc.TextOut(401, 1, _T("1600"));
	}
	
															//****����/
	p_Static_Draw = (CStatic *)GetDlgItem(IDC_STATIC_DRAW);	//ָ��̬�ı����ָ��
	CPaintDC dc1( p_Static_Draw );							//������̬�ı���Ļ���

	dc1.SetViewportOrg(m_Rect.Width()/2, m_Rect.Height()/2);	

	GetClientRect(m_Rect);									//��ȡ��̬�ı���ľ���

	dc1.SelectObject(m_BrushPt);							//����װ�ϻ�ˢ����ɫ

	p_Static_Draw->Invalidate();							//���µ������

	double x = ( Distance*sin( Angle*PI/180 )) / CHANGE;	//����xֵ
	double y = ( Distance*cos( Angle*PI/180 )) / CHANGE;	//����yֵ

	dc1.Ellipse( (int)x-PTSIZE, (int)y-PTSIZE, (int)x+PTSIZE, (int)y+PTSIZE);		//��Բ����

}
 
 
void CDrawDlg::Renew(void)
{
	InvalidateRect(m_Rect, true);					/////***ˢ��	//�����Onpaint��������ѭ��
}


void CDrawDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	GetClientRect(m_Rect);				

	//InvalidateRect(m_Rect, true);					/////***ˢ��	//�����Onpaint��������ѭ��
	
	dc.FillSolidRect(m_Rect, RGB(80,80,80));   			//���������Ի��򴰿�Ϊ��ɫ����
	dc.TextOut(0, 0, _T("����Ҽ�ֹͣɨ��"));

	dc.SetViewportOrg(m_Rect.Width()/2, m_Rect.Height()/2);							//����ԭ��λ��

	dc.SelectObject(m_PenXY);										//װ�ϻ�������Ļ��ʣ���ɫ
	dc.MoveTo(m_Rect.Width()/2,0);									//X��
	dc.LineTo(m_Rect.Width()/(-2),0);  								//
	dc.MoveTo(0,m_Rect.Height()/2);									//Y��
	dc.LineTo(0,m_Rect.Height()/(-2));								//

	dc.Arc(-50,50,50,-50,0,50,0,50);					//�뾶50��Բ
	dc.Arc(-100,100,100,-100,0,100,0,100);				//�뾶100��Բ
	dc.Arc(-200,200,200,-200,0,200,0,200);				//�뾶200��Բ
	dc.Arc(-400,400,400,-400,0,400,0,400);				//�뾶400��Բ

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


void CDrawDlg::OnEnChangeEdit1()						//�༭����
{

	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������	
}


BOOL CDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BrushBk.CreateSolidBrush( RGB(80,80,80) );						//���ñ���ɫ��ˢ ��ɫ
	m_PenXY.CreatePen( PS_SOLID, 1, RGB(255,125,64) );					//�����ửˢ ��ɫ
	m_BrushPt.CreateSolidBrush( RGB(255,255,0) );						//�����ɫ��ˢ ��ɫ

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

