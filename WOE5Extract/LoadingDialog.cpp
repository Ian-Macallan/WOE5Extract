// LoadingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WOE5Extract.h"
#include "WOE5ExtractDoc.h"
#include "WOE5ExtractView.h"
#include "LoadingDialog.h"

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
// CLoadingDialog dialog
//
///////////////////////////////////////////////////////////////////////////////
CLoadingDialog::CLoadingDialog(CWnd* pParent /*=NULL*/) : CDialog(CLoadingDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CLoadingDialog)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CLoadingDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CLoadingDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CLoadingDialog, CDialog)
    //{{AFX_MSG_MAP(CLoadingDialog)
    ON_WM_DESTROY()
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
///////////////////////////////////////////////////////////////////////////////
// CLoadingDialog message handlers
//
///////////////////////////////////////////////////////////////////////////////
void AddListItems ( void *pWnd, void *pStruct )
{
    CWOE5ExtractView    *pView;
    structInformation   *pInfo;

    pView = ( CWOE5ExtractView * )( pWnd );
    pInfo = ( structInformation * ) ( pStruct );

    pView->AddListItem ( pInfo );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CLoadingDialog::OnDestroy()
{
    theApp.m_pMainWnd->BringWindowToTop( );
    //  theApp.m_pMainWnd->SetWindowPos ( (CWnd * ) &wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE );
    //  theApp.m_pMainWnd->SetFocus ( );

    CDialog::OnDestroy();
    
    // TODO: Add your message handler code here
    theApp.m_LoadingThread = NULL;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BOOL CLoadingDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    SetBoolKeep ( false );

    SetTimer ( LOADING_THREAD_TIMER, 100, NULL );

    BringWindowToTop( );

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CLoadingDialog::OnTimer(UINT nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    ShowWindow ( SW_HIDE );

    KillTimer ( LOADING_THREAD_TIMER );

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
        CString strDirectory =
            theApp.GetProfileString ( "Settings", "Working Directory", "" );
        CString strDiskDrive =
            theApp.GetProfileString ( "Settings", "Working Disk Drive", "" );


        //      First processing
        if ( strDirectory == "" )
        {
            SetDirectory ( szPathname );
        }
        else
        {
            SetDirectory ( (LPCTSTR) strDirectory );
        }

        if ( strDiskDrive != "" )
        {
            SetDrive ( (LPCTSTR) strDiskDrive );
        }

        SetAddressRoutinesCancel ( false );

        ProcessFileStep1 ( szPathname, NULL, pView );

        SetBoolOnlyMessages ( true );
        SetAllSelected ( );

        ProcessFileStep2 ( szPathname, AddListItems, pView );

        theCtrl.SetItemCount ( pView->iCountList );
        pView->SaveSummaryFile ( );

    }

    CDialog::OnTimer(nIDEvent);

    theApp.m_ProgressDialog.EndDialog ( 0 );
    EndDialog ( 0 );
}

