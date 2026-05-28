#include "stdafx.h"
#include "MCXButtonBase.h"

#include "MCXColors.h"

#include "MCXGDI.h"

//
/////////////////////////////////////////////////////////////////////////////
//  BS_OWNERDRAW
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMCXButtonBase, CButton)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXButtonBase::CMCXButtonBase(void)
{
    m_IconResource = 0;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXButtonBase::~CMCXButtonBase(void)
{
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXButtonBase::SetIconResource ( UINT resource )
{
    m_IconResource = resource;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMCXButtonBase, CButton)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR()
    ON_WM_RBUTTONUP()
    ON_WM_CREATE()
END_MESSAGE_MAP()

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXButtonBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CButton::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXButtonBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this ) )
    {
        return TRUE;
    }

    return CButton::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//  For CButton we must implement for OWE DRAW
/////////////////////////////////////////////////////////////////////////////
void CMCXButtonBase::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    UINT uStyle = DFCS_BUTTONPUSH;

    static TCHAR szText [ MAX_PATH ];

    CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    if ( pDC )
    {

        // This code only works with buttons.
        ASSERT ( lpDrawItemStruct->CtlType == ODT_BUTTON );

        // If drawing selected, add the pushed style to DrawFrameControl.
        if ( lpDrawItemStruct->itemState & ODS_SELECTED )
        {
            uStyle |= DFCS_PUSHED;
        }

        // Draw the button frame.
        // pDC->DrawEdge ( &lpDrawItemStruct->rcItem, EDGE_ETCHED, BF_ADJUST );
        pDC->DrawFrameControl ( &lpDrawItemStruct->rcItem, DFC_BUTTON, uStyle );
        if ( CMCXColors::m_iDarkTheme != 0 )
        {
            RECT rect = lpDrawItemStruct->rcItem;
            rect.top        = rect.top + 1;
            rect.left       = rect.left + 1;
            rect.bottom     = rect.bottom - 2;
            rect.right      = rect.right - 2;
            pDC->FillRect ( &rect, CMCXColors::GetBKNormalCBrush( CMCXColors::m_iDarkTheme != 0 ) );
        }

        // Get the button's text.
        GetWindowText ( szText, _wsizeof(szText) );

        // Draw the button text using the text color white.
        COLORREF crOldColor;
        if ( ( lpDrawItemStruct->itemState & ODS_DISABLED ) != 0 )
        {
            crOldColor = pDC->SetTextColor ( CMCXColors::GetFGDisabledCR( CMCXColors::m_iDarkTheme != 0 ) );
        }
        else if ( ( lpDrawItemStruct->itemState & ODS_FOCUS ) != 0 )
        {
            crOldColor = pDC->SetTextColor ( CMCXColors::GetFGSelectedCR( CMCXColors::m_iDarkTheme != 0 ) );
        }
        else
        {
            crOldColor = pDC->SetTextColor ( CMCXColors::GetFGNormalCR( CMCXColors::m_iDarkTheme != 0 ) );
        }

        if ( m_IconResource != 0 && ( lpDrawItemStruct->itemState & ODS_DISABLED ) == 0 )
        {
            int xIconSmall  = GetSystemMetrics(SM_CXSMICON);
            int yIconSmall  = GetSystemMetrics(SM_CYSMICON);

            int xMargin = ( ( lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left ) - xIconSmall ) / 2;
            int yMargin = ( ( lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top ) - yIconSmall ) / 2;
            if ( xMargin < 0 )
            {
                xMargin = 0;
            }
            if ( yMargin < 0 )
            {
                yMargin = 0;
            }
            HICON hIcon = AfxGetApp()->LoadIcon ( m_IconResource );

            DrawIconEx ( pDC->m_hDC, lpDrawItemStruct->rcItem.left + xMargin, lpDrawItemStruct->rcItem.top + yMargin, 
                hIcon, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL );
        }
        else
        {
            pDC->DrawText ( szText, &lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER );
        }

        pDC->SetTextColor( crOldColor);
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXButtonBase::OnRButtonUp(UINT nFlags, CPoint point)
{
    //
    NMHDR hdr;
    hdr.code        = NM_RCLICK;
    hdr.hwndFrom    = this->GetSafeHwnd();
    hdr.idFrom      = GetDlgCtrlID();
    this->GetParent()->SendMessage(WM_NOTIFY, (WPARAM)hdr.idFrom, (LPARAM)&hdr );
}

