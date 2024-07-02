#if !defined(AFX_EXTRACTINGDIALOG_H__E4DA00C2_6183_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_EXTRACTINGDIALOG_H__E4DA00C2_6183_11D5_A09F_0000E8C97BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtractingDialog.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CExtractingDialog dialog

class CExtractingDialog : public CDialog
{
// Construction
public:
    CExtractingDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CExtractingDialog)
    enum { IDD = IDD_EXTRACTING };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CExtractingDialog)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CExtractingDialog)
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnDestroy();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTRACTINGDIALOG_H__E4DA00C2_6183_11D5_A09F_0000E8C97BDE__INCLUDED_)
