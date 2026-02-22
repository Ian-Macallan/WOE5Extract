#pragma once
#include "afxwin.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXCCheckListBoxBase : public CCheckListBox
{
    DECLARE_DYNAMIC(CMCXCCheckListBoxBase)

    public:
        CMCXCCheckListBoxBase(void);
        virtual ~CMCXCCheckListBoxBase(void);
        DECLARE_MESSAGE_MAP()
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

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

    public:
        afx_msg void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};

//
#define ITEM_NORMAL             0 
#define ITEM_ITALIC             1