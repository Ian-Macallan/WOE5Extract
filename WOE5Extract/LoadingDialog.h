#if !defined(AFX_LOADINGDIALOG_H__2EC053A1_5D2F_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_LOADINGDIALOG_H__2EC053A1_5D2F_11D5_A09F_0000E8C97BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoadingDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoadingDialog dialog

class CLoadingDialog : public CDialog
{
// Construction
public:
    CLoadingDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CLoadingDialog)
    enum { IDD = IDD_LOADING };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CLoadingDialog)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CLoadingDialog)
    afx_msg void OnDestroy();
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT nIDEvent);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADINGDIALOG_H__2EC053A1_5D2F_11D5_A09F_0000E8C97BDE__INCLUDED_)
