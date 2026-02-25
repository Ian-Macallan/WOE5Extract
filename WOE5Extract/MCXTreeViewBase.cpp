// MCXDiablogBase.cpp
//

#include "stdafx.h"

// #include "afxdialogex.h"

#include "MCXTreeViewBase.h"

#include "resource.h"

#include "MCXColors.h"

#include "MCXWinAppBase.h"


// Boîte de dialogue CMCXTreeViewBase

IMPLEMENT_DYNAMIC(CMCXTreeViewBase, CTreeView)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXTreeViewBase::CMCXTreeViewBase() : CTreeView()
{
    m_pNormalFont       = NULL;
    m_pItalicFont       = NULL;
    m_pBoldFont         = NULL;
    m_pFixedFont        = NULL;
    m_pFixedBoldFont    = NULL;

    m_bInitDone         = false;
    m_bFirstTime        = true;
    m_bToolTip          = FALSE;

    m_hIcon             = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    
    m_pMenu             = NULL;


    m_bValid            = FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXTreeViewBase::~CMCXTreeViewBase()
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
void CMCXTreeViewBase::SetContextMenu ( CMCXMenuBase *pMenu )
{
    m_pMenu = pMenu;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CToolTipCtrl *CMCXTreeViewBase::GetToolTipCtrl()
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
void CMCXTreeViewBase::DoDataExchange(CDataExchange* pDX)
{
    CTreeView::DoDataExchange(pDX);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMCXTreeViewBase, CTreeView)
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
END_MESSAGE_MAP()


//
/////////////////////////////////////////////////////////////////////////////
// Gestionnaires de messages de CMCXTreeViewBase
//
/////////////////////////////////////////////////////////////////////////////


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXTreeViewBase::PreCreateWindow(CREATESTRUCT& cs)
{
    CTreeView::PreCreateWindow(cs);

    //
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION : OCX Pages
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXTreeViewBase::PreTranslateMessage(MSG* pMsg)
{
    //
    if ( m_bToolTip )
    {
        m_ToolTip.RelayEvent(pMsg);
    }

    return CTreeView::PreTranslateMessage(pMsg);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXTreeViewBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CTreeView::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXTreeViewBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this) )
    {
        return TRUE;
    }
    return CTreeView::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXTreeViewBase::OnNcActivate(BOOL bActive)
{
    //
    BOOL bTreated = m_NC.Activate(this, NULL, bActive);
    if ( bTreated )
    {
        return TRUE;
    }

    return CTreeView::OnNcActivate(bActive);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXTreeViewBase::OnNcPaint()
{
    CTreeView::OnNcPaint();

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
void CMCXTreeViewBase::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CTreeView::OnNcLButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXTreeViewBase::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonUp ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CTreeView::OnNcLButtonUp(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXTreeViewBase::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
    BOOL bTreated = m_NC.OnNcRButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }
    CTreeView::OnNcRButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXTreeViewBase::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    CTreeView::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

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
void CMCXTreeViewBase::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
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
    CTreeView::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXTreeViewBase::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
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

    CTreeView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXTreeViewBase::OnMouseMove(UINT nFlags, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnMouseMove ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CTreeView::OnMouseMove(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXTreeViewBase::OnNcMouseMove(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcMouseMove ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CTreeView::OnNcMouseMove(nHitTest, point);
}


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXTreeViewBase::OnNcMouseHover(UINT nFlags, CPoint point)
{
    // Requires WIN 2000 or later
    // WIN32_WINNT et WINVER >= 0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseHover ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CTreeView::OnNcMouseHover(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXTreeViewBase::OnNcMouseLeave()
{
    // Requires WIN 2000 or later
    // WIN32_WINNT et WINVER >= 0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseLeave (this);
    if ( bTreated )
    {
        return;
    }

    CTreeView::OnNcMouseLeave();
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXTreeViewBase::OnInitialUpdate()
{
    CTreeView::OnInitialUpdate();

    // TODO: Add Code Here
    //
    if ( m_bFirstTime )
    {
        m_bFirstTime        = false;

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

        GetTreeCtrl ( ).SetTextColor ( CMCXColors::GetFGNormalCR(CMCXColors::m_iDarkTheme != 0) );
        GetTreeCtrl ( ).SetBkColor ( CMCXColors::GetBKNormalCR(CMCXColors::m_iDarkTheme != 0) );
        GetTreeCtrl ( ).SetLineColor ( CMCXColors::GetFGNormalCR(CMCXColors::m_iDarkTheme != 0) );

        //
        m_bValid    = TRUE;
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXTreeViewBase::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CTreeView::OnShowWindow(bShow, nStatus);

    // TODO: ajoutez ici le code de votre gestionnaire de messages
    GetSystemMenu(FALSE);
}
