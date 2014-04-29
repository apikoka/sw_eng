
// DIP_ProgrammingView.h : interface of the CDIP_ProgrammingView class
//

#pragma once
#include "GaussianFilter.h"
#include "MedianFilter.h"

class CDIP_ProgrammingView : public CView
{
protected: // create from serialization only
	CDIP_ProgrammingView();
	DECLARE_DYNCREATE(CDIP_ProgrammingView)

// Attributes
public:
	CDIP_ProgrammingDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDIP_ProgrammingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTransformationPower();
	afx_msg void OnEnhancementOriginal();
	afx_msg void OnFilterMedian();
	afx_msg void OnFilterGaussian();
};

#ifndef _DEBUG  // debug version in DIP_ProgrammingView.cpp
inline CDIP_ProgrammingDoc* CDIP_ProgrammingView::GetDocument() const
   { return reinterpret_cast<CDIP_ProgrammingDoc*>(m_pDocument); }
#endif

