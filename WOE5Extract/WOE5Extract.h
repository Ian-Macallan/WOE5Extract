// WOE5Extract.h : main header file for the WOE5EXTRACT application
//

#if !defined(AFX_WOE5EXTRACT_H__07848865_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_WOE5EXTRACT_H__07848865_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ExtractingDialog.h"   // Added by ClassView
#include "LoadingDialog.h"  // Added by ClassView
#include "ProgressDialog.h" // Added by ClassView

#define LOADING_THREAD_TIMER    1
#define EXTRACTING_THREAD_TIMER 2
#define PROGRESS_THREAD_TIMER   3

/////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractApp:
// See WOE5Extract.cpp for the implementation of this class
//

class CWOE5ExtractApp : public CWinApp
{
public:
    void SetMsgFilenameFormat ( );
    CView * m_View;

    CWinThread * m_ExtractingThread;
    CExtractingDialog m_ExtractingDialog;

    CWinThread * m_LoadingThread;
    CLoadingDialog m_LoadingDialog;

    CWinThread * m_ProgressThread;
    CProgressDialog m_ProgressDialog;

    CWOE5ExtractApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWOE5ExtractApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation
    //{{AFX_MSG(CWOE5ExtractApp)
    afx_msg void OnAppAbout();
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

extern  CWOE5ExtractApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WOE5EXTRACT_H__07848865_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_)
