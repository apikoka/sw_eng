// FileOpenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DIP_Programming.h"
#include "FileOpenDlg.h"
#include "afxdialogex.h"


// CFileOpenDlg dialog

IMPLEMENT_DYNAMIC(CFileOpenDlg, CDialogEx)

CFileOpenDlg::CFileOpenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileOpenDlg::IDD, pParent)
	, m_DlgCol(0)
	, m_DlgRow(0)
{

}

CFileOpenDlg::~CFileOpenDlg()
{
}

void CFileOpenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DlgCol);
	DDX_Text(pDX, IDC_EDIT2, m_DlgRow);
}


BEGIN_MESSAGE_MAP(CFileOpenDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileOpenDlg message handlers
