// WOE5ExtractDoc.cpp : implementation of the CWOE5ExtractDoc class
//

#include "stdafx.h"
#include "WOE5Extract.h"
#include <direct.h>

#include "WOE5ExtractDoc.h"
#include "../OE5Extract/FileRoutines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
///////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractDoc
//
///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CWOE5ExtractDoc, CDocument)

BEGIN_MESSAGE_MAP(CWOE5ExtractDoc, CDocument)
    //{{AFX_MSG_MAP(CWOE5ExtractDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
///////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractDoc construction/destruction
//
///////////////////////////////////////////////////////////////////////////////
CWOE5ExtractDoc::CWOE5ExtractDoc()
{
    // TODO: add one-time construction code here

}

CWOE5ExtractDoc::~CWOE5ExtractDoc()
{
}

BOOL CWOE5ExtractDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractDoc serialization

void CWOE5ExtractDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractDoc diagnostics

#ifdef _DEBUG
void CWOE5ExtractDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CWOE5ExtractDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractDoc commands

BOOL CWOE5ExtractDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
    if (!CDocument::OnOpenDocument(lpszPathName))
        return FALSE;

    if ( lpszPathName != NULL )
    {
        theApp.WriteProfileString ( "Settings", "Default Directory", FindDirectory ( lpszPathName ) );
        int iRes1 = _chdrive ( *lpszPathName - 'A' + 1 );
        int iRes2 = _chdir ( FindDirectory ( lpszPathName ) );
    }
    
    // TODO: Add your specialized creation code here
    UpdateAllViews ( NULL );

    return TRUE;
}

BOOL CWOE5ExtractDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
    // TODO: Add your specialized code here and/or call the base class
    
    return CDocument::OnSaveDocument(lpszPathName);
}
