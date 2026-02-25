#pragma once
#include "afxwin.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXEditBase : public CEdit
{
    DECLARE_DYNAMIC(CMCXEditBase)

    public:
        CMCXEditBase(void);
        virtual ~CMCXEditBase(void);

        DECLARE_MESSAGE_MAP()

    public:
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

