#include "stdafx.h"
#include "MCXToolBarBase.h"

#include "MCXColors.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMCXToolBarBase, CToolBar)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXToolBarBase::CMCXToolBarBase(void)
{
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXToolBarBase::~CMCXToolBarBase(void)
{
}
BEGIN_MESSAGE_MAP(CMCXToolBarBase, CToolBar)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR()
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMCXToolBarBase::OnNMCustomdraw)
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXToolBarBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CToolBar::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXToolBarBase::CtlColor(CDC* pDC, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, this, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CToolBar::OnCtlColor(pDC, this, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXToolBarBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this ) )
    {
        return TRUE;
    }

    return CToolBar::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXToolBarBase::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
    if ( true )
    {
        *pResult = 0;
        // return;
    }

    if ( CMCXColors::m_iDarkTheme == 0 )
    {
        *pResult = CDRF_DODEFAULT;
        return;
    }

    //
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

    switch (pNMCD->dwDrawStage)
    {
        case CDDS_PREPAINT :
        {
            *pResult = CDRF_NOTIFYITEMDRAW;
            return;
        }

        // 
        case CDDS_ITEMPREPAINT :
        {
            RECT rectTool   = pNMCD->rc;
            UINT uState     = pNMCD->uItemState;

            UINT nIndex     = -1;
            UINT nID        = -1;
            UINT nStyle     = 0;
            int iImage      = -1;
            //  pCD->dwItemSpec Seems To be The IDB

            CToolBarCtrl &toolBarCtrl   = GetToolBarCtrl();

            //
            int toIndex = (int) CommandToIndex( (UINT) pNMCD->dwItemSpec);

            //  ANother way to search index
            int count = toolBarCtrl.GetButtonCount( );

            for ( int i = 0; i < count; i++ )
            {
                GetButtonInfo ( i, nID, nStyle, iImage );
                if ( nID == pNMCD->dwItemSpec )
                {
                    nIndex  = i;
                    break;
                }
            }

            //
            if ( nIndex == -1 )
            {
                *pResult = CDRF_DODEFAULT;
                return;
            }

            //
            int cxIcon  = GetSystemMetrics ( SM_CXSMICON );
            int cyIcon  = GetSystemMetrics ( SM_CYSMICON );

            CString buttonText = GetButtonText ( nIndex );

            //
#ifdef _DEBUG
            static TCHAR szDebugString [ MAX_PATH ];
            _stprintf_s ( szDebugString, _wsizeof(szDebugString), _T("OnNMCustomdraw %d rc %d %d '%s'\n"), 
                nIndex,  pNMCD->rc.left, pNMCD->rc.right, buttonText );
            OutputDebugString ( szDebugString );
#endif

            CImageList *pImageList      = toolBarCtrl.GetImageList();
            if ( pImageList != NULL )
            {
                CDC *pDC = CDC::FromHandle ( pNMCD->hdc );

                UINT uStyle     = DFCS_BUTTONPUSH;
                if ( uState & ODS_SELECTED )
                {
                    uStyle |= DFCS_FLAT;
                    pDC->SetBkMode ( TRANSPARENT );
                    pDC->SetBkColor ( CMCXColors::GetBKHeaderCR(CMCXColors::m_iDarkTheme != 0) );
                    pDC->SetTextColor ( CMCXColors::GetFGHeaderCR(CMCXColors::m_iDarkTheme != 0) );
                }
                else if ( uState & ODS_DISABLED || uState & ODS_GRAYED )
                {
                    uStyle |= DFCS_INACTIVE;
                    pDC->SetBkMode ( TRANSPARENT );
                    pDC->SetBkColor ( CMCXColors::GetBKHeaderCR(CMCXColors::m_iDarkTheme != 0) );
                    pDC->SetTextColor (  CMCXColors::GetFGDisabledCR(CMCXColors::m_iDarkTheme != 0) );
                }
                else if ( uState & ODS_HOTLIGHT )
                {
                    uStyle |= DFCS_PUSHED;
                    pDC->SetBkMode ( TRANSPARENT );
                    pDC->SetBkColor ( CMCXColors::GetBKHeaderCR(CMCXColors::m_iDarkTheme != 0) );
                    pDC->SetTextColor ( CMCXColors::GetFGSelectedCR(CMCXColors::m_iDarkTheme != 0) );
                }
                else
                {
                    uStyle |= DFCS_FLAT;
                    pDC->SetBkMode ( TRANSPARENT );
                    pDC->SetBkColor ( CMCXColors::GetBKHeaderCR(CMCXColors::m_iDarkTheme != 0) );
                    pDC->SetTextColor ( CMCXColors::GetFGHeaderCR(CMCXColors::m_iDarkTheme != 0) );
                }

                //
                pDC->DrawFrameControl ( &rectTool, DFC_BUTTON, uStyle );

                //
                int space = 1;
                if (  rectTool.right - rectTool.left > cxIcon )
                {
                    rectTool.left       = rectTool.left + space;
                    rectTool.right      = rectTool.right - space;
                }

                if ( rectTool.bottom - rectTool.top > cyIcon )
                {
                    rectTool.top        = rectTool.top + space;
                    rectTool.bottom     = rectTool.bottom - space;
                }

                //
                FillRect ( pDC->GetSafeHdc(), &rectTool, CMCXColors::GetBKHeaderBrush(CMCXColors::m_iDarkTheme != 0) );

                //
                int width       = rectTool.right - rectTool.left;
                int height      = rectTool.bottom - rectTool.top;

                int xMargin     = ( width - cxIcon ) / 2;
                int yMargin     = ( height - cyIcon ) / ( cyIcon / 2 );
                POINT pt;
                pt.x = rectTool.left;
                pt.y = rectTool.top + yMargin;

                if (  rectTool.right - rectTool.left > cxIcon )
                {
                    pt.x += xMargin;
                }

                if ( rectTool.bottom - rectTool.top > cyIcon )
                {
                    pt.y += yMargin;
                }

                if ( pImageList != NULL && iImage >= 0 )
                {
                    pImageList->Draw ( pDC, iImage, pt, ILD_NORMAL );
                }

                RECT rectText   = rectTool;
                // rectText.top    += cxIcon + 2;

                //
                CFont* pOldFont     = ( CFont * ) pDC->SelectStockObject ( ANSI_VAR_FONT );
                pDC->DrawText ( buttonText, &rectText, DT_SINGLELINE | DT_BOTTOM /* | DT_CENTER */ );
                pDC->SelectObject ( pOldFont );
            }
            else
            {
#ifdef _DEBUG
                OutputDebugString ( _T("ImageList NULL\n") );
#endif
            }

            *pResult = CDRF_SKIPDEFAULT;
            // *pResult = CDRF_DODEFAULT;
            return;
        }

        default :
        {
#ifdef _DEBUG
            OutputDebugString ( _T("case default\n") );
#endif
        }
    }

    *pResult = CDRF_DODEFAULT;
}
