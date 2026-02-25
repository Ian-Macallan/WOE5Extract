// MCXDiablogBase.cpp
//

#include "stdafx.h"

// #include "afxdialogex.h"
#include "resource.h"

#include "MCXCWndBase.h"


#include "MCXColors.h"


// Dialog Box CMCXCWndBase

IMPLEMENT_DYNCREATE(CMCXCWndBase, CWnd)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXCWndBase::CMCXCWndBase() : CWnd()
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
CMCXCWndBase::~CMCXCWndBase()
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
void CMCXCWndBase::SetContextMenu ( CMCXMenuBase *pMenu )
{
    m_pMenu = pMenu;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CToolTipCtrl *CMCXCWndBase::GetToolTipCtrl()
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
void CMCXCWndBase::DoDataExchange(CDataExchange* pDX)
{
    CWnd::DoDataExchange(pDX);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMCXCWndBase, CWnd)
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
// Message handling of CMCXCWndBase
//
/////////////////////////////////////////////////////////////////////////////


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXCWndBase::PreCreateWindow(CREATESTRUCT& cs)
{
    CWnd::PreCreateWindow(cs);

    //
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION : Pages with OCX should return FALSE
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXCWndBase::PreTranslateMessage(MSG* pMsg)
{
    //
    if ( m_bToolTip )
    {
        m_ToolTip.RelayEvent(pMsg);
    }

    return CWnd::PreTranslateMessage(pMsg);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXCWndBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXCWndBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this) )
    {
        return TRUE;
    }
    return CWnd::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXCWndBase::OnNcActivate(BOOL bActive)
{
    //
    BOOL bTreated = m_NC.Activate(this, NULL, bActive);
    if ( bTreated )
    {
        return TRUE;
    }

    return CWnd::OnNcActivate(bActive);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCWndBase::OnNcPaint()
{

    CWnd::OnNcPaint();

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
void CMCXCWndBase::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CWnd::OnNcLButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCWndBase::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonUp ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CWnd::OnNcLButtonUp(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCWndBase::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
    BOOL bTreated = m_NC.OnNcRButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }
    CWnd::OnNcRButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCWndBase::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    CWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

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
void CMCXCWndBase::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
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
    CWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCWndBase::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
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

    CWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCWndBase::OnMouseMove(UINT nFlags, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnMouseMove ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CWnd::OnMouseMove(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCWndBase::OnNcMouseMove(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcMouseMove ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CWnd::OnNcMouseMove(nHitTest, point);
}


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCWndBase::OnNcMouseHover(UINT nFlags, CPoint point)
{
    /// Requires Windows 2000 or later
    // WIN32_WINNT  WINVER must be over  0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseHover ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CWnd::OnNcMouseHover(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCWndBase::OnNcMouseLeave()
{
    /// Requires Windows 2000 or later
    // WIN32_WINNT  WINVER must be over  0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseLeave (this);
    if ( bTreated )
    {
        return;
    }

    CWnd::OnNcMouseLeave();
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXCWndBase::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CWnd::OnShowWindow(bShow, nStatus);

    // TODO add your code here
        //  Activate Context Menu
    if ( m_bFirstTime )
    {
        m_bFirstTime    = FALSE;

        GetSystemMenu(FALSE);

        //  For Menu without Document
#if 0
        CMenu *pAppMenu = GetMenu();
        m_AppMenu.SetApplicationMenu ( this, pAppMenu );
        SetMenu ( &m_AppMenu );
#endif
    }

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
int CMCXCWndBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    //
    return 0;
}
