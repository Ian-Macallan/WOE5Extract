#if !defined(AFX_EXTRACTINGTHREAD_H__E4DA00C3_6183_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_EXTRACTINGTHREAD_H__E4DA00C3_6183_11D5_A09F_0000E8C97BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtractingThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CExtractingThread thread

class CExtractingThread : public CWinThread
{
    DECLARE_DYNCREATE(CExtractingThread)
protected:
    CExtractingThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CExtractingThread)
    public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    //}}AFX_VIRTUAL

// Implementation
protected:
    virtual ~CExtractingThread();

    // Generated message map functions
    //{{AFX_MSG(CExtractingThread)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTRACTINGTHREAD_H__E4DA00C3_6183_11D5_A09F_0000E8C97BDE__INCLUDED_)
