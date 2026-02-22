// MCXDiablogBase.cpp : fichier d'implémentation
//

#include "stdafx.h"

// #include "afxdialogex.h"

#include "MCXListViewBase.h"

#include "resource.h"

#include "MCXColors.h"

#include "MCXWinAppBase.h"


// Boîte de dialogue CMCXListViewBase

IMPLEMENT_DYNAMIC(CMCXListViewBase, CListView)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXListViewBase::CMCXListViewBase() : CListView()
{
    m_pNormalFont               = NULL;
    m_pItalicFont               = NULL;
    m_pBoldFont                 = NULL;
    m_pFixedFont                = NULL;
    m_pFixedBoldFont            = NULL;

    m_bInitDone                 = false;
    m_bFirstTime                = true;
    m_bToolTip                  = FALSE;

    m_hIcon                     = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    
    m_pMenu                     = NULL;

    m_bFontsDone                = FALSE;

    m_bHeaderControlSubclassed  = false;

    m_bValid                    = FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXListViewBase::~CMCXListViewBase()
{
#define DELETE_OBJECT(o) if ( o != NULL ) { delete o; o = NULL; }

    //
    DELETE_OBJECT(m_pNormalFont)
    DELETE_OBJECT(m_pItalicFont)
    DELETE_OBJECT(m_pBoldFont)
    DELETE_OBJECT(m_pFixedFont)
    DELETE_OBJECT(m_pFixedBoldFont)

    m_bValid = FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::SetContextMenu ( CMCXMenuBase *pMenu )
{
    m_pMenu = pMenu;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CToolTipCtrl *CMCXListViewBase::GetToolTipCtrl()
{
    if ( m_bToolTip )
    {
        return &m_ToolTip;
    }

    return NULL;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::DoDataExchange(CDataExchange* pDX)
{
    CListView::DoDataExchange(pDX);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMCXListViewBase, CListView)
    ON_WM_CTLCOLOR()
    ON_WM_ERASEBKGND()
    ON_WM_NCACTIVATE()
    ON_WM_NCPAINT()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_NCLBUTTONUP()
    ON_WM_INITMENUPOPUP()
    ON_WM_DRAWITEM()
    ON_WM_MEASUREITEM()
    ON_WM_NCRBUTTONUP()
    ON_WM_NCRBUTTONDOWN()
    ON_WM_NCRBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_NCMOUSEMOVE()
    ON_WM_NCMOUSEHOVER()
    ON_WM_NCMOUSELEAVE()
    ON_WM_SHOWWINDOW()
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMCXListViewBase::OnNMCustomdraw)
END_MESSAGE_MAP()


//
/////////////////////////////////////////////////////////////////////////////
// Gestionnaires de messages de CMCXListViewBase
//
/////////////////////////////////////////////////////////////////////////////


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXListViewBase::PreCreateWindow(CREATESTRUCT& cs)
{
    CListView::PreCreateWindow(cs);

    //
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXListViewBase::PreTranslateMessage(MSG* pMsg)
{
    //
    if ( m_bToolTip )
    {
        m_ToolTip.RelayEvent(pMsg);
    }

    return CListView::PreTranslateMessage(pMsg);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXListViewBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CListView::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXListViewBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this) )
    {
        return TRUE;
    }
    return CListView::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXListViewBase::OnNcActivate(BOOL bActive)
{
    //
    BOOL bTreated = m_NC.Activate(this, NULL, bActive);
    if ( bTreated )
    {
        return TRUE;
    }

    return CListView::OnNcActivate(bActive);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnNcPaint()
{
    CListView::OnNcPaint();

    //
    BOOL bTreated = m_NC.PaintWindow(this);
    if ( bTreated )
    {
        return;
    }

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CListView::OnNcLButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonUp ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CListView::OnNcLButtonUp(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
    BOOL bTreated = m_NC.OnNcRButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }
    CListView::OnNcRButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    CListView::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

    if ( CMCXColors::m_iDarkTheme == 0 )
    {
        CMCXMenuBase::SetOwnDraw ( pPopupMenu, false, ID_POP_MENU );
    }

    if ( CMCXColors::m_iDarkTheme != 0 )
    {
        static CMCXMenuBase     sysMenu;
        m_pMenu = sysMenu.SetSystemMenu ( this, pPopupMenu );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    //
    //  Menu
    if ( lpDrawItemStruct != NULL )
    {
        if ( lpDrawItemStruct->CtlType == ODT_MENU )
        {
            if ( m_pMenu != NULL )
            {
                m_pMenu->DrawItem(lpDrawItemStruct);
                return;
            }
        }
    }
    
    //
    CListView::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    //
    if ( lpMeasureItemStruct != NULL )
    {
        if ( lpMeasureItemStruct->CtlType == ODT_MENU )
        {
            if ( m_pMenu != NULL )
            {
                m_pMenu->MeasureItem(lpMeasureItemStruct);
                return;
            }
        }
    }

    CListView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnMouseMove(UINT nFlags, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnMouseMove ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CListView::OnMouseMove(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnNcMouseMove(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcMouseMove ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CListView::OnNcMouseMove(nHitTest, point);
}


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnNcMouseHover(UINT nFlags, CPoint point)
{
    // Cette fonctionnalité requiert Windows 2000 ou une version ultérieure.
    // Les symboles _WIN32_WINNT et WINVER doivent être >= 0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseHover ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CListView::OnNcMouseHover(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnNcMouseLeave()
{
    // Cette fonctionnalité requiert Windows 2000 ou une version ultérieure.
    // Les symboles _WIN32_WINNT et WINVER doivent être >= 0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseLeave (this);
    if ( bTreated )
    {
        return;
    }

    CListView::OnNcMouseLeave();
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnInitialUpdate()
{
    CListView::OnInitialUpdate();

    // TODO: ajoutez ici votre code spécialisé et/ou l'appel de la classe de base
    //
    if ( m_bFirstTime )
    {
        m_bFirstTime        = false;

        m_bFontsDone        = TRUE;

        m_pNormalFont       = CMCXWinAppBase::CreateNormalFont ( this );
        m_pBoldFont         = CMCXWinAppBase::CreateBoldFont ( this, m_pNormalFont );
        m_pItalicFont       = CMCXWinAppBase::CreateItalicFont ( this, m_pNormalFont );
        m_pFixedFont        = CMCXWinAppBase::CreateFixedFont ( this, m_pNormalFont );
        m_pFixedBoldFont    = CMCXWinAppBase::CreateFixedBoldFont ( this, m_pNormalFont );


        //
        if( ! m_ToolTip.Create(this))
        {
           TRACE0("Unable to create the ToolTip!");
        }
        else
        {
            m_bToolTip  = TRUE;
            m_ToolTip.SetMaxTipWidth ( 392 );
            m_ToolTip.SetFont ( m_pFixedBoldFont );
            m_ToolTip.SetColors ( );
        }

        //  Activate Context Menu
        GetSystemMenu(FALSE);

        //
        m_NC.HandleSquareCorners ( this );

        m_bValid    = TRUE;
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CListView::OnShowWindow(bShow, nStatus);

    // TODO: ajoutez ici le code de votre gestionnaire de messages
    GetSystemMenu(FALSE);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXListViewBase::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
    if ( CMCXColors::m_iDarkTheme == 0 )
    {
        *pResult = CDRF_DODEFAULT;
        return;
    }

    //
    CListCtrl &list = GetListCtrl();
    if ( list.m_hWnd != NULL )
    {
        if ( list.GetHeaderCtrl ( ) && list.GetHeaderCtrl()->m_hWnd != NULL && m_bHeaderControlSubclassed == false )
        {
            m_HeaderCtrl.SubclassWindow(list.GetHeaderCtrl()->m_hWnd);
            m_bHeaderControlSubclassed = true;
            m_HeaderCtrl.RedrawWindow ( );
        }
    }
    else
    {
        *pResult = CDRF_DODEFAULT;
        return;
    }

    //  for this notification, the structure is actually a
    //  NMLVCUSTOMDRAW that tells you what's going on with the custom
    //  draw action. So, we'll need to cast the generic pNMHDR pointer.
    LPNMLVCUSTOMDRAW    pLVCD   = (LPNMLVCUSTOMDRAW)pNMHDR;

    if ( pLVCD )
    {
        switch ( pLVCD->nmcd.dwDrawStage )
        {
            case CDDS_PREPAINT :
            {
                *pResult = CDRF_NOTIFYITEMDRAW;
                break;
            }

            case CDDS_ITEMPREPAINT :
            {
                int iRow        = (int) pLVCD->nmcd.dwItemSpec; 

                BOOL selected   = list.GetItemState(iRow, LVIS_SELECTED) & LVIS_SELECTED;
                if (selected)
                {
                    pLVCD->clrText      = CMCXColors::GetFGSelectedCR(CMCXColors::m_iDarkTheme != 0);
                    pLVCD->clrTextBk    = CMCXColors::GetBKSelectedCR(CMCXColors::m_iDarkTheme != 0);
                }
                else
                {
                    if ( iRow % 2 == 0)
                    {
                        pLVCD->clrText      = CMCXColors::GetFGNormalCR(CMCXColors::m_iDarkTheme != 0);
                        pLVCD->clrTextBk    = CMCXColors::GetBKNormalCR(CMCXColors::m_iDarkTheme != 0);
                    }
                    else
                    {
                        pLVCD->clrText      = CMCXColors::GetFGNormalCR(CMCXColors::m_iDarkTheme != 0);
                        pLVCD->clrTextBk    = CMCXColors::GetBKNormalCR(CMCXColors::m_iDarkTheme != 0);
                    }
                }

                *pResult    = CDRF_DODEFAULT;
                break;
            }

            default:
            {
                *pResult = CDRF_DODEFAULT;
                break;
            }
        }
    }

    return;
}
