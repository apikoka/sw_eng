#pragma once


// CGaussianFilter ��ȭ �����Դϴ�.

class CGaussianFilter : public CDialog
{
	DECLARE_DYNAMIC(CGaussianFilter)

public:
	CGaussianFilter(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGaussianFilter();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_iGaussianMaskSize;
};
