// ProgressDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WOE5Extract.h"
#include "WOE5ExtractDoc.h"
#include "WOE5ExtractView.h"
#include "ProgressDialog.h"

#include "../OE5Extract/OEAddressRoutines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
///////////////////////////////////////////////////////////////////////////////
// CProgressDialog dialog
//
///////////////////////////////////////////////////////////////////////////////
CProgressDialog::CProgressDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CProgressDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CProgressDialog)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    bFirstTime = true;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CProgressDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CProgressDialog)
    DDX_Control(pDX, IDC_CANCEL, m_Cancel);
    DDX_Control(pDX, IDC_STEP, m_Step);
    DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
    //}}AFX_DATA_MAP
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CProgressDialog, CDialog)
    //{{AFX_MSG_MAP(CProgressDialog)
    ON_WM_DESTROY()
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_CANCEL, OnCancel)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
///////////////////////////////////////////////////////////////////////////////
// CProgressDialog message handlers
//
///////////////////////////////////////////////////////////////////////////////
void CProgressDialog::OnDestroy()
{
    theApp.m_pMainWnd->BringWindowToTop( );
    // theApp.m_pMainWnd->SetWindowPos ( (CWnd * ) &wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE );
    // theApp.m_pMainWnd->SetFocus ( );

    CDialog::OnDestroy();
    
    // TODO: Add your message handler code here
    KillTimer ( PROGRESS_THREAD_TIMER );

    theApp.m_ProgressThread = NULL;
    
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BOOL CProgressDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    bFirstTime = true;

    // TODO: Add extra initialization here
    m_Step.SetWindowText ( "" );
    m_Progress.SetRange32 ( 0, GetFileLength ( ) );
    m_Progress.SetPos ( 0 );

    SetTimer ( PROGRESS_THREAD_TIMER, 100, NULL );
    
    BringWindowToTop( );

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CProgressDialog::OnTimer(UINT nIDEvent)
{
    // TODO: Add your message handler code here and/or call default

    m_Step.SetWindowText ( GetProcessStep ( ) );
    m_Progress.SetRange32 ( 0, GetFileLength ( ) );
    m_Progress.SetPos ( GetFilePosition ( ) );

    CDialog::OnTimer(nIDEvent);

    if ( bFirstTime )
    {
        bFirstTime = false;
        BringWindowToTop( );
    }
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CProgressDialog::OnCancel()
{
    // TODO: Add your control notification handler code here
    SetAddressRoutinesCancel ( true );
    //      get document

    CWOE5ExtractView *pView = ( CWOE5ExtractView * ) ( theApp.m_View );
    if ( pView == NULL )
    {
        return;
    }

    CWOE5ExtractDoc *pDoc = pView->GetDocument ();
    if ( pDoc == NULL )
    {
        return;
    }

    pDoc->OnNewDocument ( );
}
