#include "stdafx.h"
#include "MCXCToolTipCtrlBase.h"


#include "MCXColors.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMCXCToolTipCtrlBase, CToolTipCtrl)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXCToolTipCtrlBase::CMCXCToolTipCtrlBase(void)
{
    m_bDefaultColor = FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXCToolTipCtrlBase::~CMCXCToolTipCtrlBase(void)
{
}
BEGIN_MESSAGE_MAP(CMCXCToolTipCtrlBase, CToolTipCtrl)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXCToolTipCtrlBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CToolTipCtrl::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXCToolTipCtrlBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this ) )
    {
        return TRUE;
    }

    return CToolTipCtrl::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCToolTipCtrlBase::SetColors ( )
{
    if ( CMCXColors::m_iDarkTheme == 0 )
    {
        if ( m_bDefaultColor )
        {
            SetTipBkColor ( m_DefaultBkColor );
            SetTipTextColor ( m_DefaultTextColor );
        }

        return;
    }

    //
    if ( ! m_bDefaultColor )
    {
        m_DefaultTextColor  = GetTipTextColor();
        m_DefaultBkColor    = GetTipBkColor();
        m_bDefaultColor     = TRUE;
    }

    SetTipTextColor ( CMCXColors::GetFGTipColor(CMCXColors::m_iDarkTheme != 0) );
    SetTipBkColor ( CMCXColors::GetBKTipColor(CMCXColors::m_iDarkTheme != 0) );
}

