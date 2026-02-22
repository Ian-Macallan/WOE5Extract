#pragma once
#include "afxwin.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXSpinButtonCtrlBase : public CSpinButtonCtrl
{
    DECLARE_DYNAMIC(CMCXSpinButtonCtrlBase)

    public:
        CMCXSpinButtonCtrlBase(void);
        virtual ~CMCXSpinButtonCtrlBase(void);
        DECLARE_MESSAGE_MAP()
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

