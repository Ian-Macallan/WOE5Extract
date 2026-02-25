// MCXDiablogBase.cpp
//

#include "stdafx.h"
#include "resource.h"

// #include "afxdialogex.h"
#include "MCXWinAppBase.h"

#include "MCXMDIChildWndBase.h"
#include "MCXMDIFrameWndBase.h"


#include "MCXColors.h"




// Dialog Box CMCXMDIChildWndBase

IMPLEMENT_DYNCREATE(CMCXMDIChildWndBase, CMDIChildWnd)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXMDIChildWndBase::CMCXMDIChildWndBase() : CMDIChildWnd()
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
CMCXMDIChildWndBase::~CMCXMDIChildWndBase()
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
void CMCXMDIChildWndBase::SetContextMenu ( CMCXMenuBase *pMenu )
{
    m_pMenu = pMenu;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CToolTipCtrl *CMCXMDIChildWndBase::GetToolTipCtrl()
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
void CMCXMDIChildWndBase::DoDataExchange(CDataExchange* pDX)
{
    CMDIChildWnd::DoDataExchange(pDX);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMCXMDIChildWndBase, CMDIChildWnd)
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
    ON_WM_CREATE()
END_MESSAGE_MAP()


//
/////////////////////////////////////////////////////////////////////////////
// Message handling of CMCXMDIChildWndBase
//
/////////////////////////////////////////////////////////////////////////////


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMDIChildWndBase::PreCreateWindow(CREATESTRUCT& cs)
{
    CMDIChildWnd::PreCreateWindow(cs);

    //
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION : Pages with OCX should return FALSE
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMDIChildWndBase::PreTranslateMessage(MSG* pMsg)
{
    //
    if ( m_bToolTip )
    {
        m_ToolTip.RelayEvent(pMsg);
    }

    return CMDIChildWnd::PreTranslateMessage(pMsg);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXMDIChildWndBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CMDIChildWnd::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMDIChildWndBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this) )
    {
        return TRUE;
    }
    return CMDIChildWnd::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMDIChildWndBase::OnNcActivate(BOOL bActive)
{
    //
    BOOL bTreated = m_NC.Activate(this, NULL, bActive);
    if ( bTreated )
    {
        return TRUE;
    }

    return CMDIChildWnd::OnNcActivate(bActive);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIChildWndBase::OnNcPaint()
{
    //
    CMDIChildWnd::OnNcPaint();

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
void CMCXMDIChildWndBase::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CMDIChildWnd::OnNcLButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIChildWndBase::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonUp ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CMDIChildWnd::OnNcLButtonUp(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIChildWndBase::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
    BOOL bTreated = m_NC.OnNcRButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }
    CMDIChildWnd::OnNcRButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIChildWndBase::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    CMDIChildWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

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
void CMCXMDIChildWndBase::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
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
    CMDIChildWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIChildWndBase::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
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

    CMDIChildWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIChildWndBase::OnMouseMove(UINT nFlags, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnMouseMove ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CMDIChildWnd::OnMouseMove(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIChildWndBase::OnNcMouseMove(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcMouseMove ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CMDIChildWnd::OnNcMouseMove(nHitTest, point);
}


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIChildWndBase::OnNcMouseHover(UINT nFlags, CPoint point)
{
    // Requires Windows 2000 or later
    // WIN32_WINNT  WINVER must be over  0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseHover ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CMDIChildWnd::OnNcMouseHover(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIChildWndBase::OnNcMouseLeave()
{
    // Requires Windows 2000 or later
    // WIN32_WINNT  WINVER must be over  0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseLeave (this);
    if ( bTreated )
    {
        return;
    }

    CMDIChildWnd::OnNcMouseLeave();
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIChildWndBase::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CMDIChildWnd::OnShowWindow(bShow, nStatus);

    // TODO add your code here
    //  Activate Context Menu
    if ( m_bFirstTime )
    {
        m_bFirstTime    = FALSE;

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

        GetSystemMenu(FALSE);

        //  For Menu without Document
#if 0
        CMenu *pAppMenu = GetMenu();
        m_AppMenu.SetApplicationMenu ( this, pAppMenu );
        SetMenu ( &m_AppMenu );
#endif

        m_NC.HandleSquareCorners ( this, TRUE );
    }

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
int CMCXMDIChildWndBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    //
    return 0;
}
