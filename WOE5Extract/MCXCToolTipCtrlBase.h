#pragma once
#include "afxwin.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXCToolTipCtrlBase : public CToolTipCtrl
{
    DECLARE_DYNAMIC(CMCXCToolTipCtrlBase)

    public:
        CMCXCToolTipCtrlBase(void);
        virtual ~CMCXCToolTipCtrlBase(void);

        DECLARE_MESSAGE_MAP()
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

    public :
        void SetColors ( );

    //
    protected :
        BOOL        m_bDefaultColor;
        COLORREF    m_DefaultBkColor;
        COLORREF    m_DefaultTextColor;

};

