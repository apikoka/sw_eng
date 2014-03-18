
// DIP_ProgrammingDoc.h : interface of the CDIP_ProgrammingDoc class
//


#pragma once
#include "DIP_ProgrammingMyClass.h"

class CDIP_ProgrammingDoc : public CDocument
{
protected: // create from serialization only
	CDIP_ProgrammingDoc();
	DECLARE_DYNCREATE(CDIP_ProgrammingDoc)

// Attributes
public:

// Operations
public:
	CDIP_ProgrammingMyClass Image;

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CDIP_ProgrammingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileOpen();
};
