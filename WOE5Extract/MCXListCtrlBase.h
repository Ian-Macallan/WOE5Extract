#pragma once
#include "afxwin.h"
#include "MCXCHeaderCtrlBase.h"
#include "MCXScrollBarBase.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXListCtrlBase : public CListCtrl
{
    DECLARE_DYNAMIC(CMCXListCtrlBase)

    public:
        CMCXListCtrlBase(void);
        virtual ~CMCXListCtrlBase(void);

        DECLARE_MESSAGE_MAP()

    public:
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
        afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);

    public :    
        CFont                   *m_pNormalFont;
        CFont                   *m_pBoldFont;
        CFont                   *m_pItalicFont;
        CFont                   *m_pFixedFont;
        CFont                   *m_pFixedBoldFont;

        BOOL                    m_bFontsDone;

    //
    protected :
        BOOL                    m_bDefaultColor;
        COLORREF                m_DefaultBkColor;
        COLORREF                m_DefaultTextColor;

        CMCXCHeaderCtrlBase     m_HeaderCtrl;
        bool                    m_bHeaderControlSubclassed;
};

//
#define ITEM_NORMAL             0 
#define ITEM_ITALIC             1