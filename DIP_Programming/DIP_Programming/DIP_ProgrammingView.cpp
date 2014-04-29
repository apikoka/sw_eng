
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
	ON_COMMAND(ID_TRANSFORMATION_POWER, &CDIP_ProgrammingView::OnTransformationPower)
	ON_COMMAND(ID_ENHANCEMENT_ORIGINAL, &CDIP_ProgrammingView::OnEnhancementOriginal)
	ON_COMMAND(ID_FILTER_GAUSSIAN, &CDIP_ProgrammingView::OnFilterGaussian)
	ON_COMMAND(ID_FILTER_MEDIAN, &CDIP_ProgrammingView::OnFilterMedian)
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

void CDIP_ProgrammingView::OnDraw(CDC* pDC)
{
	CDIP_ProgrammingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	if(pDoc->Image.m_ppcBMPToShow)
	{
		StretchDIBits(pDC->GetSafeHdc(),
			0, 0, pDoc->Image.m_uiWidth, pDoc->Image.m_uiHeight,
			0, 0, pDoc->Image.m_BMPHeader.biWidth, pDoc->Image.m_BMPHeader.biHeight,
			pDoc->Image.m_ppcBMPToShow[0], (LPBITMAPINFO)&pDoc->Image.m_BMPHeader, DIB_RGB_COLORS, SRCCOPY);
	}

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


void CDIP_ProgrammingView::OnTransformationPower()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDIP_ProgrammingDoc* pDoc = GetDocument();
	pDoc->Image.m_bLogTransform = TRUE;
	
	pDoc->Image.MyClass_MakeBMP();

	pDoc->UpdateAllViews(NULL);

}


void CDIP_ProgrammingView::OnEnhancementOriginal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDIP_ProgrammingDoc* pDoc = GetDocument();

	pDoc->Image.m_bLogTransform=FALSE;
	pDoc->Image.m_uiFilterSelection=0;

	pDoc->Image.MyClass_MakeBMP();
	
	pDoc->UpdateAllViews(NULL);
	
}

void CDIP_ProgrammingView::OnFilterMedian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDIP_ProgrammingDoc* pDoc = GetDocument();
	CMedianFilter cMedianFilter;

	if(cMedianFilter.DoModal() == IDCANCEL)
	{
		exit(1);
	}

	switch(cMedianFilter.MaskSize)
	{
	case 0:
		pDoc->Image.m_uiMedianFilterMaskSize=3;
		break;
	case 1:
		pDoc->Image.m_uiMedianFilterMaskSize=5;
		break;
	case 2:
		pDoc->Image.m_uiMedianFilterMaskSize=7;
		break;
	default :
		pDoc->Image.m_uiMedianFilterMaskSize=3;
		break;
	}



	pDoc->Image.m_bLogTransform=FALSE;
	pDoc->Image.m_uiFilterSelection=1;

	pDoc->Image.MyClass_MakeBMP();

	pDoc->UpdateAllViews(NULL);
}

void CDIP_ProgrammingView::OnFilterGaussian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	CDIP_ProgrammingDoc* pDoc = GetDocument();
	CGaussianFilter cGaussianFilter;

	
	if(cGaussianFilter.DoModal() == IDCANCEL)
	{
		exit(1);
	}

	switch(cGaussianFilter.m_iGaussianMaskSize)
	{
	case 0:
		pDoc->Image.m_uiGaussianFilterMaskSize=3;
		break;
	case 1:
		pDoc->Image.m_uiGaussianFilterMaskSize=5;
		break;
	case 2:
		pDoc->Image.m_uiGaussianFilterMaskSize=7;
		break;
	default :
		pDoc->Image.m_uiGaussianFilterMaskSize=3;
		break;
	}


	pDoc->Image.m_bLogTransform=FALSE;
	pDoc->Image.m_uiFilterSelection=2;

	pDoc->Image.MyClass_MakeBMP();

	pDoc->UpdateAllViews(NULL);
}