// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__07848869_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_MAINFRM_H__07848869_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
    
protected: // create from serialization only
    CMainFrame();
    DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMainFrame)
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

// Implementation
public:
    bool RecurseRegistry ( HKEY hPreviousKey, char *pTemp );
    void GetDirectoryOfIdentity ( );
    virtual ~CMainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
    CStatusBar      m_wndStatusBar;
    CToolBar        m_wndToolBar;
    CReBar          m_wndReBar;
    CDialogBar      m_wndDlgBar;
    CMenu           m_Menu;

// Generated message map functions
protected:
    char szDirectoryOfIdentity [ 255 ];
    CString strDefaultDirectory;
    //{{AFX_MSG(CMainFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
    afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
    afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
    afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
    afx_msg void OnDestroy();
    afx_msg void OnClose();
    afx_msg void OnPreferences();
    afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
    afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLanguageEnglish();
    afx_msg void OnLanguageFrench();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__07848869_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_)
