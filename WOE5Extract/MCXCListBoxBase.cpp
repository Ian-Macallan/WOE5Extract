#include "stdafx.h"
#include "MCXCListBoxBase.h"


#include "MCXColors.h"
#include "MCXGDI.h"

#include "MCXWinAppBase.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMCXCListBoxBase, CListBox)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXCListBoxBase::CMCXCListBoxBase(void)
{
    m_bDefaultColor             = FALSE;

    m_bFontsDone                = FALSE;
    m_pBoldFont                 = NULL;
    m_pItalicFont               = NULL;
    m_pNormalFont               = NULL;
    m_pFixedFont                = NULL;
    m_pFixedBoldFont            = NULL;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXCListBoxBase::~CMCXCListBoxBase(void)
{
#define DELETE_OBJECT(o) if ( o != NULL ) { delete o; o = NULL; }

    //
    DELETE_OBJECT(m_pNormalFont)
    DELETE_OBJECT(m_pItalicFont)
    DELETE_OBJECT(m_pBoldFont)
    DELETE_OBJECT(m_pFixedFont)
    DELETE_OBJECT(m_pFixedBoldFont)
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMCXCListBoxBase, CListBox)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR()
    ON_WM_DRAWITEM_REFLECT()
    ON_WM_DRAWITEM()
    ON_WM_DRAWITEM_REFLECT()
END_MESSAGE_MAP()

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXCListBoxBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //

    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CListBox::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXCListBoxBase::OnEraseBkgnd(CDC* pDC)
{
    //

    if ( CMCXColors::OnEraseBkgnd(pDC, this ) )
    {
        return TRUE;
    }

    return CListBox::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCListBoxBase::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct )
{
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

        CString textString;
        GetText ( lpDrawItemStruct->itemID, textString );
        pDC->DrawText ( textString, &lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER /* |DT_CENTER */ );

        pDC->SetBkColor( crOldBKColor);
        pDC->SetTextColor( crOldColor);
    }
    else
    {
        CListBox::DrawItem ( lpDrawItemStruct );
    }
}
