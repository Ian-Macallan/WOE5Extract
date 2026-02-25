// MCXDiablogBase.cpp
//

#include "stdafx.h"
#include "resource.h"

// #include "afxdialogex.h"

#include "MCXMDIFrameWndBase.h"
#include "MCXWinAppBase.h"

#include "MCXColors.h"


// Dialog Box CMCXMDIFrameWndBase

IMPLEMENT_DYNCREATE(CMCXMDIFrameWndBase, CMDIFrameWnd)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXMDIFrameWndBase::CMCXMDIFrameWndBase() : CMDIFrameWnd()
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
CMCXMDIFrameWndBase::~CMCXMDIFrameWndBase()
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
void CMCXMDIFrameWndBase::SetContextMenu ( CMCXMenuBase *pMenu )
{
    m_pMenu = pMenu;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CToolTipCtrl *CMCXMDIFrameWndBase::GetToolTipCtrl()
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
void CMCXMDIFrameWndBase::DoDataExchange(CDataExchange* pDX)
{
    CMDIFrameWnd::DoDataExchange(pDX);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMCXMDIFrameWndBase, CMDIFrameWnd)
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
// Message handling of CMCXMDIFrameWndBase
//
/////////////////////////////////////////////////////////////////////////////


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMDIFrameWndBase::PreCreateWindow(CREATESTRUCT& cs)
{
    CMDIFrameWnd::PreCreateWindow(cs);

    //
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION : Pages with OCX should return FALSE
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMDIFrameWndBase::PreTranslateMessage(MSG* pMsg)
{
    //
    if ( m_bToolTip )
    {
        m_ToolTip.RelayEvent(pMsg);
    }

    return CMDIFrameWnd::PreTranslateMessage(pMsg);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXMDIFrameWndBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CMDIFrameWnd::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMDIFrameWndBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this) )
    {
        return TRUE;
    }
    return CMDIFrameWnd::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMDIFrameWndBase::OnNcActivate(BOOL bActive)
{
    //
    BOOL bTreated = m_NC.Activate(this, NULL, bActive);
    if ( bTreated )
    {
        return TRUE;
    }

    return CMDIFrameWnd::OnNcActivate(bActive);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnNcPaint()
{
    CMDIFrameWnd::OnNcPaint();

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
void CMCXMDIFrameWndBase::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CMDIFrameWnd::OnNcLButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonUp ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CMDIFrameWnd::OnNcLButtonUp(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
    BOOL bTreated = m_NC.OnNcRButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }
    CMDIFrameWnd::OnNcRButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    CMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

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
void CMCXMDIFrameWndBase::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    //
    //  Menu
    if ( lpDrawItemStruct != NULL && lpDrawItemStruct->CtlType == ODT_MENU )
    {
        ULONG_PTR itemData = lpDrawItemStruct->itemData;
        ULONG_PTR shifted  = itemData >> 8;
        if ( shifted == ID_SYS_MENU || shifted == ID_POP_MENU )
        {
            if ( m_pMenu != NULL )
            {
                m_pMenu->DrawItem ( lpDrawItemStruct );
                return;
            }
        }
        else if ( shifted == ID_MDI_MENU )
        {
            m_MdiMenu.DrawItem ( lpDrawItemStruct );
            return;
        }
        else if ( m_AppMenu.m_hMenu != NULL )
        {
            m_AppMenu.DrawItem ( lpDrawItemStruct );
            return;
        }
    }
    
    //
    //
#ifdef _DEBUG
    if ( lpDrawItemStruct != NULL )
    {
        static TCHAR szDebugString [ MAX_PATH ];
        _stprintf_s ( szDebugString, _wsizeof(szDebugString), _T("CMCXMDIFrameWndBase::OnDrawItem %d %d\n"),
            nIDCtl, lpDrawItemStruct->CtlType );
        OutputDebugString ( szDebugString );
    }
#endif
    CMDIFrameWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    //
    if ( lpMeasureItemStruct != NULL && lpMeasureItemStruct->CtlType == ODT_MENU )
    {
        ULONG_PTR itemData = lpMeasureItemStruct->itemData;
        ULONG_PTR shifted  = itemData >> 8;
        if ( shifted == ID_SYS_MENU || shifted == ID_POP_MENU )
        {
            if ( m_pMenu != NULL )
            {
                m_pMenu->MeasureItem ( lpMeasureItemStruct );
                return;
            }
        }
        else if ( shifted == ID_MDI_MENU )
        {
            m_MdiMenu.MeasureItem ( lpMeasureItemStruct );
            return;
        }
        else if ( m_AppMenu.m_hMenu != NULL )
        {
            m_AppMenu.MeasureItem ( lpMeasureItemStruct );
            return;
        }
    }

    //
#ifdef _DEBUG
    if ( lpMeasureItemStruct != NULL )
    {
        static TCHAR szDebugString [ MAX_PATH ];
        _stprintf_s ( szDebugString, _wsizeof(szDebugString), _T("CMCXMDIFrameWndBase::OnMeasureItem %d %d\n"),
            nIDCtl, lpMeasureItemStruct->CtlType );
        OutputDebugString ( szDebugString );
    }
#endif
    CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnMouseMove(UINT nFlags, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnMouseMove ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CMDIFrameWnd::OnMouseMove(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnNcMouseMove(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcMouseMove ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CMDIFrameWnd::OnNcMouseMove(nHitTest, point);
}


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnNcMouseHover(UINT nFlags, CPoint point)
{
    // Requires Windows 2000 or later
    // WIN32_WINNT  WINVER must be over  0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseHover ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CMDIFrameWnd::OnNcMouseHover(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnNcMouseLeave()
{
    // Requires Windows 2000 or later
    // WIN32_WINNT  WINVER must be over  0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseLeave (this);
    if ( bTreated )
    {
        return;
    }

    CMDIFrameWnd::OnNcMouseLeave();
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CMDIFrameWnd::OnShowWindow(bShow, nStatus);

    // TODO add your code here
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

        //  For Menu with Document
        CMenu *pMdiMenu = GetMenu();
        m_MdiMenu.SetApplicationMenu ( this, pMdiMenu, ID_MDI_MENU );
        // SetMenu ( &m_AppMenu );

        //
        m_NC.HandleSquareCorners ( this );
    }

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
int CMCXMDIFrameWndBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    //  For Menu without Document
    CMenu *pAppMenu = GetMenu();
    m_AppMenu.SetApplicationMenu ( this, pAppMenu );
    // SetMenu ( &m_AppMenu );

    //
    return 0;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::HandleStatusBar ( CMCXStatusBarBase *pStatusBar )
{
    if ( pStatusBar != NULL )
    {
        //
        UINT added  = SBPS_OWNERDRAW;
        if ( CMCXColors::m_iDarkTheme == 0 )
        {
            added = NULL;
        }
        pStatusBar->ModifyStyle ( NULL, added );

	    //		Set SBPS_OWNERDRAW
	    UINT				nID;
	    UINT				nStyle;
	    int					cxWidth;

        //  Change to enable DrawItem
        int paneCount = pStatusBar->GetCount();
        for  ( int i = 0; i < paneCount; i++ )
        {
            pStatusBar->GetPaneInfo ( i, nID, nStyle, cxWidth );
            nStyle |= added;
            pStatusBar->SetPaneInfo ( i, nID, nStyle, cxWidth );
        }
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMDIFrameWndBase::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
    // TODO Add specialized code here

    BOOL bCreateClient = CMDIFrameWnd::OnCreateClient(lpcs, pContext);

    return bCreateClient;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMenu* CMCXMDIFrameWndBase::MDISetMenu( CMenu* pFrameMenu, CMenu* pWindowMenu)
{
    CMenu *pMenu = CMDIFrameWnd::MDISetMenu( pFrameMenu, pWindowMenu );
    return pMenu;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnUpdateFrameMenu(HMENU hMenuAlt)
{
    // TODO Add specialized code here

    CMDIFrameWnd::OnUpdateFrameMenu(hMenuAlt);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMDIFrameWndBase::OnUpdateFrameTitle(BOOL bAddToTitle)
{
    // TODO Add specialized code here

    CMDIFrameWnd::OnUpdateFrameTitle(bAddToTitle);
}
