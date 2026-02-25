#pragma once
#include "afxwin.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXScrollBarBase : public CScrollBar
{
    DECLARE_DYNAMIC(CMCXScrollBarBase)

    public:
        CMCXScrollBarBase(void);
        virtual ~CMCXScrollBarBase(void);

        DECLARE_MESSAGE_MAP()

    public:
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

