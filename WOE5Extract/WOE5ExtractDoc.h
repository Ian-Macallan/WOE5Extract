// WOE5ExtractDoc.h : interface of the CWOE5ExtractDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WOE5EXTRACTDOC_H__0784886B_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_WOE5EXTRACTDOC_H__0784886B_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWOE5ExtractDoc : public CDocument
{
protected: // create from serialization only
    CWOE5ExtractDoc();
    DECLARE_DYNCREATE(CWOE5ExtractDoc)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWOE5ExtractDoc)
    public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
    virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CWOE5ExtractDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CWOE5ExtractDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WOE5EXTRACTDOC_H__0784886B_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_)
