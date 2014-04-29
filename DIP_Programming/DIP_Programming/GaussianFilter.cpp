// GaussianFilter.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DIP_Programming.h"
#include "GaussianFilter.h"
#include "afxdialogex.h"


// CGaussianFilter 대화 상자입니다.

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


// CGaussianFilter 메시지 처리기입니다.
