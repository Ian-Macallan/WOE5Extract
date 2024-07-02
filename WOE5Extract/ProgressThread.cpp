// ProgressThread.cpp : implementation file
//

#include "stdafx.h"
#include "WOE5Extract.h"
#include "ProgressThread.h"
#include "ProgressDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressThread

IMPLEMENT_DYNCREATE(CProgressThread, CWinThread)

CProgressThread::CProgressThread()
{
}

CProgressThread::~CProgressThread()
{
}

BOOL CProgressThread::InitInstance()
{
    // TODO:  perform and per-thread initialization here
    m_pMainWnd = &theApp.m_ProgressDialog;
    
    theApp.m_ProgressDialog.DoModal ( );

    return TRUE;
}

int CProgressThread::ExitInstance()
{
    // TODO:  perform any per-thread cleanup here
    return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CProgressThread, CWinThread)
    //{{AFX_MSG_MAP(CProgressThread)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressThread message handlers
