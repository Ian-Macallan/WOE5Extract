#pragma once
#include "afxwin.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXButtonBase : public CButton
{
    DECLARE_DYNAMIC(CMCXButtonBase)

    public:
        CMCXButtonBase(void);
        virtual ~CMCXButtonBase(void);
        DECLARE_MESSAGE_MAP()

        UINT m_IconResource;

    public :
        void SetIconResource ( UINT resource );

        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
        afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
        virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};

