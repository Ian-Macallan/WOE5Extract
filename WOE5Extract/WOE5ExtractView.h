// WOE5ExtractView.h : interface of the CWOE5ExtractView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WOE5EXTRACTVIEW_H__0784886D_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_WOE5EXTRACTVIEW_H__0784886D_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <afx.h>
#include <afxwin.h>
#include <afxcmn.h>

#include "../OE5Extract/OEAddressDefinitions.h"

#define COL_ATTACHEMENT     0
#define COL_MESSAGE         (COL_ATTACHEMENT+1)
#define COL_DATE            (COL_MESSAGE+1)
#define COL_AUTHOR          (COL_DATE+1)
#define COL_OBJECT          (COL_AUTHOR+1)
#define COL_SIZE            (COL_OBJECT+1)

class CWOE5ExtractView : public CListView
{
protected: // create from serialization only
    CWOE5ExtractView();
    DECLARE_DYNCREATE(CWOE5ExtractView)

// Attributes
public:
    CWOE5ExtractDoc* GetDocument();

// Operations
public:
    int iCountList;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWOE5ExtractView)
    public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void OnInitialUpdate(); // called first time after construct
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    virtual BOOL OnToolTipNotify(UINT id, NMHDR *pNMH, LRESULT *pResult);
    //}}AFX_VIRTUAL

// Implementation
public:
    void PrepareDirectory();
    bool RetrieveSummaryFile();
    void SaveSummaryFile();
    void SetTheSelection();
    void SelectAll();
    int GetFirstSelectedItem();
    void UnSelectAll();
    void ResetSortOrder();
    void SetHeaderBitmap ( int iColumn, bool bAscending );
    void SortByMessage();
    void SortByAttach();
    void SortBySize();
    void SortByObject();
    void SortByDate();
    void SortByAuthor();
    void SortInfosItems ( int iColumn );
    void RestoreColumnsPosition();
    void SaveColumnsPosition();
    void ExtractMsgFile ( int iPos );
    void FreeAllItems();
    void AddListItem ( structInformation *pStruct );
    void DisplayValues();
    void DisplayHeader();
    virtual ~CWOE5ExtractView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    void CreateMailAddressFile ( CString strFile );
    bool Negate ( bool bValue );
    bool bHeaderDone;
    bool bFirstTime;
    CImageList          m_imgAttachement16;
    CImageList          m_imgAttachement32;
    CImageList          m_imgSortOrder16;
    bool                bSortByMessageAsc;
    bool                bSortByAttachAsc;
    bool                bSortBySizeAsc;
    bool                bSortByObjectAsc;
    bool                bSortByDateAsc;
    bool                bSortByAuthorAsc;

    CToolTipCtrl        m_ToolTip;
    CString m_ToolTipText;

#define MAX_LINES       32 * 1024
    structInformation *pInfos [ MAX_LINES ];

    //{{AFX_MSG(CWOE5ExtractView)
    afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnExtractAll();
    afx_msg void OnExtractAttachement();
    afx_msg void OnExtractMessage();
    afx_msg void OnSelectAll();
    afx_msg void OnUnselectAll();
    afx_msg void OnExtractSelAll();
    afx_msg void OnExtractSelAtt();
    afx_msg void OnExtractSelMsg();
    afx_msg void OnUpdateSelectAll(CCmdUI* pCmdUI);
    afx_msg void OnUpdateUnselectAll(CCmdUI* pCmdUI);
    afx_msg void OnUpdateExtractSelAll(CCmdUI* pCmdUI);
    afx_msg void OnUpdateExtractSelAtt(CCmdUI* pCmdUI);
    afx_msg void OnUpdateExtractSelMsg(CCmdUI* pCmdUI);
    afx_msg void OnUpdateExtractAll(CCmdUI* pCmdUI);
    afx_msg void OnUpdateExtractAttachement(CCmdUI* pCmdUI);
    afx_msg void OnUpdateExtractMessage(CCmdUI* pCmdUI);
    afx_msg void OnOdstatechanged(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnExtractEmail();
    afx_msg void OnUpdateExtractEmail(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
};

#ifndef _DEBUG  // debug version in WOE5ExtractView.cpp
inline CWOE5ExtractDoc* CWOE5ExtractView::GetDocument()
   { return (CWOE5ExtractDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WOE5EXTRACTVIEW_H__0784886D_5C21_11D5_A09F_0000E8C97BDE__INCLUDED_)
