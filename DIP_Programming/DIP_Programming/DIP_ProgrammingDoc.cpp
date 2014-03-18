
// DIP_ProgrammingDoc.cpp : implementation of the CDIP_ProgrammingDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DIP_Programming.h"
#endif

#include "DIP_ProgrammingDoc.h"
#include "FileOpenDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDIP_ProgrammingDoc

IMPLEMENT_DYNCREATE(CDIP_ProgrammingDoc, CDocument)

BEGIN_MESSAGE_MAP(CDIP_ProgrammingDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CDIP_ProgrammingDoc::OnFileOpen)
END_MESSAGE_MAP()


// CDIP_ProgrammingDoc construction/destruction

CDIP_ProgrammingDoc::CDIP_ProgrammingDoc()
{
	// TODO: add one-time construction code here

}

CDIP_ProgrammingDoc::~CDIP_ProgrammingDoc()
{
}

BOOL CDIP_ProgrammingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CDIP_ProgrammingDoc serialization

void CDIP_ProgrammingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CDIP_ProgrammingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CDIP_ProgrammingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDIP_ProgrammingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDIP_ProgrammingDoc diagnostics

#ifdef _DEBUG
void CDIP_ProgrammingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDIP_ProgrammingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDIP_ProgrammingDoc commands


void CDIP_ProgrammingDoc::OnFileOpen()
{
	// TODO: Add your command handler code here
	CFileDialog fileopen(true);
	CFileOpenDlg myDlg;

	if( fileopen.DoModal() == IDCANCEL )
		return ;

	CString filename = fileopen.GetPathName();


	if(myDlg.DoModal() == IDCANCEL)
		return ;

	Image.m_BMPHeader.biWidth=Image.m_uiWidth=myDlg.FileOpenDlg_GetCol();
	Image.m_BMPHeader.biHeight=Image.m_uiHeight=myDlg.FileOpenDlg_GetRow();

	Image.MyClass_ReadFile(filename);


	UpdateAllViews(NULL);
}
