#pragma once
#include "afxwin.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXStaticBase : public CStatic
{
    DECLARE_DYNAMIC(CMCXStaticBase)

    public:
        CMCXStaticBase(void);
        virtual ~CMCXStaticBase(void);

        DECLARE_MESSAGE_MAP()

    public:
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

