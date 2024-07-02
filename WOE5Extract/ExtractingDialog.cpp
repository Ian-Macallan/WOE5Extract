// ExtractingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WOE5Extract.h"
#include "WOE5ExtractDoc.h"
#include "WOE5ExtractView.h"
#include "ExtractingDialog.h"

#include "../OE5Extract/DecodeRoutines.h"
#include "../OE5Extract/OEMessagesRoutines.h"
#include "../OE5Extract/OEAddressRoutines.h"
#include "../OE5Extract/OEAddressDefinitions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
///////////////////////////////////////////////////////////////////////////////
// CExtractingDialog dialog
//
///////////////////////////////////////////////////////////////////////////////

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
CExtractingDialog::CExtractingDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CExtractingDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CExtractingDialog)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CExtractingDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CExtractingDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CExtractingDialog, CDialog)
    //{{AFX_MSG_MAP(CExtractingDialog)
    ON_WM_TIMER()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
///////////////////////////////////////////////////////////////////////////////
// CExtractingDialog message handlers
//
///////////////////////////////////////////////////////////////////////////////
BOOL CExtractingDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    
    SetTimer ( EXTRACTING_THREAD_TIMER, 100, NULL );

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CExtractingDialog::OnTimer(UINT nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    ShowWindow ( SW_HIDE );

    KillTimer ( EXTRACTING_THREAD_TIMER );

    //      get document
    CWOE5ExtractView *pView = ( CWOE5ExtractView * ) ( theApp.m_View );
    if ( pView == NULL )
    {
        theApp.m_ProgressDialog.EndDialog ( 0 );
        EndDialog ( 0 );
        return;
    }

    CWOE5ExtractDoc *pDoc = pView->GetDocument ();
    if ( pDoc == NULL )
    {
        theApp.m_ProgressDialog.EndDialog ( 0 );
        EndDialog ( 0 );
        return;
    }

    CListCtrl& theCtrl = pView->GetListCtrl();

    CString strPathname = pDoc->GetPathName ( );
    char        szPathname [ LEN_PATHNAME ];
    strcpy_s ( szPathname, sizeof ( szPathname ), strPathname );

    if ( strPathname != "" )
    {
        SetAddressRoutinesCancel ( false );

        ProcessFileStep2 ( szPathname, NULL, NULL );
    }

    CDialog::OnTimer(nIDEvent);

    theApp.m_ProgressDialog.EndDialog ( 0 );

    EndDialog ( 0 );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CExtractingDialog::OnDestroy()
{
    theApp.m_pMainWnd->BringWindowToTop( );
//  theApp.m_pMainWnd->SetFocus ( );

    CDialog::OnDestroy();
    
    // TODO: Add your message handler code here
    theApp.m_ExtractingThread = NULL;   
}
