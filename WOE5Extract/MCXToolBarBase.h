#pragma once

#include <afxtoolbar.h>

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXToolBarBase : public CToolBar
{
    DECLARE_DYNAMIC(CMCXToolBarBase)

    public:
        CMCXToolBarBase(void);
        virtual ~CMCXToolBarBase(void);

        DECLARE_MESSAGE_MAP()

        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

        afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);

        afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};

