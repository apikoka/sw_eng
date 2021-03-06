#pragma once


// CFileOpenDlg dialog

class CFileOpenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileOpenDlg)

public:
	CFileOpenDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileOpenDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	UINT m_DlgCol;
	UINT m_DlgRow;

public:
	UINT FileOpenDlg_GetRow()				{return m_DlgRow;}
	UINT FileOpenDlg_GetCol()				{return m_DlgCol;}

};
