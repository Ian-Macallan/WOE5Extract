#include "stdafx.h"
#include "MCXCCheckListBoxBase.h"


#include "MCXColors.h"
#include "MCXGDI.h"

#include "MCXWinAppBase.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMCXCCheckListBoxBase, CCheckListBox)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXCCheckListBoxBase::CMCXCCheckListBoxBase(void)
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
CMCXCCheckListBoxBase::~CMCXCCheckListBoxBase(void)
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
BEGIN_MESSAGE_MAP(CMCXCCheckListBoxBase, CCheckListBox)
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
HBRUSH CMCXCCheckListBoxBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //

    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CCheckListBox::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXCCheckListBoxBase::OnEraseBkgnd(CDC* pDC)
{
    //

    if ( CMCXColors::OnEraseBkgnd(pDC, this ) )
    {
        return TRUE;
    }

    return CCheckListBox::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCCheckListBoxBase::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct )
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

        CString paneString;
        GetText ( lpDrawItemStruct->itemID, paneString );
        pDC->DrawText ( paneString, &lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER /* |DT_CENTER */ );

        pDC->SetBkColor( crOldBKColor);
        pDC->SetTextColor( crOldColor);
    }
    else
    {
        CCheckListBox::DrawItem ( lpDrawItemStruct );
    }
}
