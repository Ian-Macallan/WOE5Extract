// LoadingThread.cpp : implementation file
//

#include "stdafx.h"
#include "WOE5Extract.h"
#include "LoadingThread.h"
#include "LoadingDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
///////////////////////////////////////////////////////////////////////////////
// CLoadingThread
//
///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CLoadingThread, CWinThread)

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
CLoadingThread::CLoadingThread()
{
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
CLoadingThread::~CLoadingThread()
{
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BOOL CLoadingThread::InitInstance()
{
    // TODO:  perform and per-thread initialization here
    m_pMainWnd = &theApp.m_LoadingDialog;
    
    theApp.m_LoadingDialog.DoModal ( );

    return TRUE;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int CLoadingThread::ExitInstance()
{
    // TODO:  perform any per-thread cleanup here

    return CWinThread::ExitInstance();
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CLoadingThread, CWinThread)
    //{{AFX_MSG_MAP(CLoadingThread)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadingThread message handlers
