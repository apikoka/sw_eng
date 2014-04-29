// MedianFilter.cpp : implementation file
//

#include "stdafx.h"
#include "DIP_Programming.h"
#include "MedianFilter.h"
#include "afxdialogex.h"


// CMedianFilter dialog

IMPLEMENT_DYNAMIC(CMedianFilter, CDialogEx)

CMedianFilter::CMedianFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMedianFilter::IDD, pParent)
	, MaskSize(0)
{

}

CMedianFilter::~CMedianFilter()
{
}

void CMedianFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, MaskSize);
}


BEGIN_MESSAGE_MAP(CMedianFilter, CDialogEx)
END_MESSAGE_MAP()


// CMedianFilter message handlers
