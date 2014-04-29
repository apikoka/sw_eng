#pragma once


// CMedianFilter dialog

class CMedianFilter : public CDialogEx
{
	DECLARE_DYNAMIC(CMedianFilter)

public:
	CMedianFilter(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMedianFilter();

// Dialog Data
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int MaskSize;
};
