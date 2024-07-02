#if !defined(AFX_MSGFMTCOMBOBOX_H__FF5D8FA1_6F31_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_MSGFMTCOMBOBOX_H__FF5D8FA1_6F31_11D5_A09F_0000E8C97BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgFmtComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgFmtComboBox window

class CMsgFmtComboBox : public CComboBox
{
// Construction
public:
    CMsgFmtComboBox();

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMsgFmtComboBox)
    //}}AFX_VIRTUAL

// Implementation
public:
    void Init();
    virtual ~CMsgFmtComboBox();

    // Generated message map functions
protected:
    //{{AFX_MSG(CMsgFmtComboBox)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGFMTCOMBOBOX_H__FF5D8FA1_6F31_11D5_A09F_0000E8C97BDE__INCLUDED_)
