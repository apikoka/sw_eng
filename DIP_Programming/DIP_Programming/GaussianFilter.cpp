// GaussianFilter.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DIP_Programming.h"
#include "GaussianFilter.h"
#include "afxdialogex.h"


// CGaussianFilter ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGaussianFilter, CDialog)

CGaussianFilter::CGaussianFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CGaussianFilter::IDD, pParent)
	, m_iGaussianMaskSize(0)
{

}

CGaussianFilter::~CGaussianFilter()
{
}

void CGaussianFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_iGaussianMaskSize);
}


BEGIN_MESSAGE_MAP(CGaussianFilter, CDialog)
END_MESSAGE_MAP()


// CGaussianFilter �޽��� ó�����Դϴ�.
