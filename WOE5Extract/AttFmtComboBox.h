#if !defined(AFX_ATTFMTCOMBOBOX_H__F763D1E1_6F3D_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_ATTFMTCOMBOBOX_H__F763D1E1_6F3D_11D5_A09F_0000E8C97BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttFmtComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAttFmtComboBox window

class CAttFmtComboBox : public CComboBox
{
// Construction
public:
	CAttFmtComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttFmtComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Init();
	virtual ~CAttFmtComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAttFmtComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTFMTCOMBOBOX_H__F763D1E1_6F3D_11D5_A09F_0000E8C97BDE__INCLUDED_)
