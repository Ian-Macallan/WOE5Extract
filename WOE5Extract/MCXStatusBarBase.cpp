#include "stdafx.h"

#include "MCXStatusBarBase.h"

#include "MCXColors.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMCXStatusBarBase, CStatusBar)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXStatusBarBase::CMCXStatusBarBase(void)
{
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXStatusBarBase::~CMCXStatusBarBase(void)
{
}
BEGIN_MESSAGE_MAP(CMCXStatusBarBase, CStatusBar)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR()
    ON_WM_DRAWITEM()
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXStatusBarBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CStatusBar::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXStatusBarBase::CtlColor(CDC* pDC, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, this, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CStatusBar::OnCtlColor(pDC, this, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXStatusBarBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this ) )
    {
        return TRUE;
    }

    return CStatusBar::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXStatusBarBase::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    //
    // CStatusBar::DrawItem ( lpDrawItemStruct );
    CDC *pDC = CDC::FromHandle ( lpDrawItemStruct->hDC );
    if ( lpDrawItemStruct != NULL && pDC && CMCXColors::m_iDarkTheme != 0 )
    {
        RECT rect       = lpDrawItemStruct->rcItem;
        rect.top        = rect.top;
        rect.left       = rect.left;
        rect.bottom     = rect.bottom;
        rect.right      = rect.right;

        CBrush *brush = CMCXColors::GetBKNormalCBrush( CMCXColors::m_iDarkTheme != 0 );
        pDC->FillRect ( &rect, brush );

        COLORREF crOldColor;
        COLORREF crOldBKColor;
        if ( lpDrawItemStruct->itemState & ODS_DISABLED )
        {
            crOldBKColor    = pDC->SetBkColor ( CMCXColors::GetBKNormalCR(CMCXColors::m_iDarkTheme != 0) );
            crOldColor      = pDC->SetTextColor ( CMCXColors::GetFGDisabledCR(CMCXColors::m_iDarkTheme != 0) );
        }
        else
        {
            crOldBKColor    = pDC->SetBkColor ( CMCXColors::GetBKNormalCR(CMCXColors::m_iDarkTheme != 0) );
            crOldColor      = pDC->SetTextColor ( CMCXColors::GetFGNormalCR(CMCXColors::m_iDarkTheme != 0)  );
        }

        //
        CString paneString = GetPaneText ( lpDrawItemStruct->itemID );
        pDC->DrawText ( paneString, &lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER /* |DT_CENTER */ );

        pDC->SetBkColor( crOldBKColor);
        pDC->SetTextColor( crOldColor);
    }
    else
    {
        CStatusBar::DrawItem ( lpDrawItemStruct );
    }

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXStatusBarBase::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // TODO add your code here

    //
    CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    if ( pDC )
    {
        pDC->SetTextColor ( CMCXColors::GetFGNormalCR(CMCXColors::m_iDarkTheme != 0) );
        pDC->SetBkColor ( CMCXColors::GetBKNormalCR(CMCXColors::m_iDarkTheme != 0) );
    }
    CStatusBar::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
