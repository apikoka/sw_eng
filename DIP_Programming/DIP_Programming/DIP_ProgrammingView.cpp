
// DIP_ProgrammingView.cpp : implementation of the CDIP_ProgrammingView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DIP_Programming.h"
#endif

#include "DIP_ProgrammingDoc.h"
#include "DIP_ProgrammingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDIP_ProgrammingView

IMPLEMENT_DYNCREATE(CDIP_ProgrammingView, CView)

BEGIN_MESSAGE_MAP(CDIP_ProgrammingView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDIP_ProgrammingView construction/destruction

CDIP_ProgrammingView::CDIP_ProgrammingView()
{
	// TODO: add construction code here

}

CDIP_ProgrammingView::~CDIP_ProgrammingView()
{
}

BOOL CDIP_ProgrammingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDIP_ProgrammingView drawing

void CDIP_ProgrammingView::OnDraw(CDC* /*pDC*/)
{
	CDIP_ProgrammingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CDIP_ProgrammingView printing

BOOL CDIP_ProgrammingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDIP_ProgrammingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDIP_ProgrammingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CDIP_ProgrammingView diagnostics

#ifdef _DEBUG
void CDIP_ProgrammingView::AssertValid() const
{
	CView::AssertValid();
}

void CDIP_ProgrammingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDIP_ProgrammingDoc* CDIP_ProgrammingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDIP_ProgrammingDoc)));
	return (CDIP_ProgrammingDoc*)m_pDocument;
}
#endif //_DEBUG


// CDIP_ProgrammingView message handlers
