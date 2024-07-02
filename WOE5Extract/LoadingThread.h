#if !defined(AFX_LOADINGTHREAD_H__2EC053A2_5D2F_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_LOADINGTHREAD_H__2EC053A2_5D2F_11D5_A09F_0000E8C97BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoadingThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CLoadingThread thread

class CLoadingThread : public CWinThread
{
    DECLARE_DYNCREATE(CLoadingThread)
protected:
    CLoadingThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CLoadingThread)
    public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    //}}AFX_VIRTUAL

// Implementation
protected:
    virtual ~CLoadingThread();

    // Generated message map functions
    //{{AFX_MSG(CLoadingThread)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADINGTHREAD_H__2EC053A2_5D2F_11D5_A09F_0000E8C97BDE__INCLUDED_)
