#pragma once
#include "afxwin.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXCComboBoxBase : public CComboBox
{
    DECLARE_DYNAMIC(CMCXCComboBoxBase)

    public:
        CMCXCComboBoxBase(void);
        virtual ~CMCXCComboBoxBase(void);

        DECLARE_MESSAGE_MAP()

        //
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

