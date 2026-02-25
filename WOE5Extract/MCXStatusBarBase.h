#pragma once

#include <afxstatusbar.h>

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXStatusBarBase : public CStatusBar
{
    DECLARE_DYNAMIC(CMCXStatusBarBase)

    public:
        CMCXStatusBarBase(void);
        virtual ~CMCXStatusBarBase(void);

        DECLARE_MESSAGE_MAP()

    public:
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

        afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);

        afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);

        virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};

