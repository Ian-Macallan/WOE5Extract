#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <Windows.h>

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXCHeaderCtrlBase : public CHeaderCtrl
{
    DECLARE_DYNAMIC(CMCXCHeaderCtrlBase)

    public:
        CMCXCHeaderCtrlBase(void);
        virtual ~CMCXCHeaderCtrlBase(void);
        DECLARE_MESSAGE_MAP()
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
        afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};

