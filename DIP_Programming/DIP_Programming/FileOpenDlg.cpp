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
{

}

CFileOpenDlg::~CFileOpenDlg()
{
}

void CFileOpenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFileOpenDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileOpenDlg message handlers
