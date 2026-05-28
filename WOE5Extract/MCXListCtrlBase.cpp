#include "stdafx.h"
#include "MCXListCtrlBase.h"


#include "MCXColors.h"
#include "MCXGDI.h"

#include "MCXWinAppBase.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMCXListCtrlBase, CListCtrl)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXListCtrlBase::CMCXListCtrlBase(void)
{
    m_bDefaultColor             = FALSE;
    m_bHeaderControlSubclassed  = false;

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
CMCXListCtrlBase::~CMCXListCtrlBase(void)
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
BEGIN_MESSAGE_MAP(CMCXListCtrlBase, CListCtrl)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR()
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMCXListCtrlBase::OnNMCustomdraw)
END_MESSAGE_MAP()

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXListCtrlBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //

    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CListCtrl::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXListCtrlBase::OnEraseBkgnd(CDC* pDC)
{
    //

    if ( CMCXColors::OnEraseBkgnd(pDC, this ) )
    {
        return TRUE;
    }

    return CListCtrl::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListCtrlBase::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
    //
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

    if ( CMCXColors::m_iDarkTheme == 0 )
    {
        *pResult = CDRF_DODEFAULT;
        return;
    }

    //
    //  CWnd::UnsubclassWindow
    if( GetHeaderCtrl ( ) && GetHeaderCtrl()->m_hWnd != NULL && m_bHeaderControlSubclassed == false )
    {
        m_HeaderCtrl.SubclassWindow(GetHeaderCtrl()->m_hWnd);
        m_bHeaderControlSubclassed = true;
        m_HeaderCtrl.RedrawWindow ( );
    }

    //  for this notification, the structure is actually a
    //  NMLVCUSTOMDRAW that tells you what's going on with the custom
    //  draw action. So, we'll need to cast the generic pNMHDR pointer.
    LPNMLVCUSTOMDRAW    pLVCD   = (LPNMLVCUSTOMDRAW)pNMHDR;

    if ( pNMCD )
    {
        switch ( pNMCD->dwDrawStage )
        {
            case CDDS_PREPAINT :
            {
                *pResult = CDRF_NOTIFYITEMDRAW;
                break;
            }

            case CDDS_ITEMPREPAINT :
            {
                *pResult = CDRF_NOTIFYSUBITEMDRAW;
                break;
            }
    
            case CDDS_ITEMPREPAINT | CDDS_SUBITEM :
            {
                //
                if ( ! m_bFontsDone )
                {
                    m_bFontsDone    = TRUE;

                    //
                    m_pNormalFont       = CMCXWinAppBase::CreateNormalFont ( this );
                    m_pBoldFont         = CMCXWinAppBase::CreateBoldFont ( this, m_pNormalFont );
                    m_pItalicFont       = CMCXWinAppBase::CreateItalicFont ( this, m_pNormalFont );
                    m_pFixedFont        = CMCXWinAppBase::CreateFixedFont ( this, m_pNormalFont );
                    m_pFixedBoldFont    = CMCXWinAppBase::CreateFixedBoldFont ( this, m_pNormalFont );

                }

                CRect rectLabel;

                int iCol            = pLVCD->iSubItem;
                int iRow            = ( int ) pNMCD->dwItemSpec;
                CString strItem     = GetItemText ( iRow, iCol );
                BOOL bResult        = GetSubItemRect ( iRow, iCol, LVIR_LABEL, rectLabel );
                BOOL bSelected      = GetItemState ( iRow, LVIS_SELECTED ) & LVIS_SELECTED;
                DWORD_PTR dwData    = GetItemData ( iRow );

                //
                HDITEM  tagHeaderInfo;
                memset ( &tagHeaderInfo, 0, sizeof ( tagHeaderInfo ) );

                tagHeaderInfo.mask          =  HDI_FORMAT;
                GetHeaderCtrl()->GetItem ( iCol, &tagHeaderInfo );

                // get the device context.
                CDC *pDC = CDC::FromHandle ( pNMCD->hdc );

                //  Test If line is selected
                if ( bSelected )
                {
                    pDC->FillRect ( &rectLabel, CMCXColors::GetBKSelectedCBrush(true) );
                    pDC->SetTextColor ( CMCXColors::GetFGSelectedCR(true)  );
                }
                else
                {
                    if ( iCol % 1 == 0 )
                    {
                        pDC->FillRect ( &rectLabel, CMCXColors::GetBKNormalCBrush(true) );
                        pDC->SetTextColor ( CMCXColors::GetFGNormalCR(true) );
                    }
                    else
                    {
                        pDC->FillRect ( &rectLabel, CMCXColors::GetBKNormalCBrush(true) );
                        pDC->SetTextColor ( CMCXColors::GetFGNormalCR(true) );
                    }
                }

                //
                //  Paint The Text
                rectLabel.left  += 2;
                rectLabel.right -= 2;
                UINT nFormat = DT_SINGLELINE|DT_VCENTER;
                if ( tagHeaderInfo.fmt  & HDF_LEFT )
                {
                    nFormat |= DT_LEFT;
                }
                else if ( tagHeaderInfo.fmt  & HDF_RIGHT  )
                {
                    nFormat |= DT_RIGHT;
                }
                else if ( tagHeaderInfo.fmt  & HDF_CENTER )
                {
                    nFormat |= DT_CENTER;
                }

                CFont *oldFont = NULL;
                if ( dwData == (DWORD_PTR) ITEM_ITALIC )
                {
                    pDC->SelectObject(m_pItalicFont);
                }

                pDC->DrawText(strItem , rectLabel, nFormat );

                if ( oldFont != NULL )
                {
                    pDC->SelectObject(oldFont);
                }

                *pResult= CDRF_SKIPDEFAULT;

                break;
            }

            default:
            {
                *pResult = CDRF_DODEFAULT;
                break;
            }
        }
    }
}

