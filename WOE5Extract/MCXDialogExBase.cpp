// MCXDiablogBase.cpp
//

#include "stdafx.h"

// #include "afxdialogex.h"

#include "MCXDialogExBase.h"
#include "MCXWinAppBase.h"

#include "resource.h"

#include "MCXColors.h"




// Dialog Box CMCXDialogExBase

IMPLEMENT_DYNAMIC(CMCXDialogExBase, CDialogEx)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXDialogExBase::CMCXDialogExBase(UINT nIDTemplate, CWnd* pParent /*=NULL*/) : CDialogEx(nIDTemplate, pParent)
{
    m_pNormalFont       = NULL;
    m_pItalicFont       = NULL;
    m_pBoldFont         = NULL;
    m_pFixedFont        = NULL;
    m_pFixedBoldFont    = NULL;

    m_bInitDone         = false;
    m_bToolTip          = FALSE;

    m_hIcon             = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    
    m_pMenu             = NULL;

    m_bValid            = FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXDialogExBase::~CMCXDialogExBase()
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
void CMCXDialogExBase::SetContextMenu ( CMCXMenuBase *pMenu )
{
    m_pMenu = pMenu;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CToolTipCtrl *CMCXDialogExBase::GetToolTipCtrl()
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
void CMCXDialogExBase::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMCXDialogExBase, CDialogEx)
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
END_MESSAGE_MAP()


//
/////////////////////////////////////////////////////////////////////////////
// Message handling of CMCXDialogExBase
//
/////////////////////////////////////////////////////////////////////////////


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXDialogExBase::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //
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
    //
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION : Pages with OCX should return FALSE
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXDialogExBase::PreTranslateMessage(MSG* pMsg)
{
    //
    if ( m_bToolTip )
    {
        m_ToolTip.RelayEvent(pMsg);
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXDialogExBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXDialogExBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this) )
    {
        return TRUE;
    }
    return CDialogEx::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
INT_PTR CMCXDialogExBase::DoModal()
{
    //

    INT_PTR ptr = CDialogEx::DoModal();

    m_bValid = FALSE;

    return ptr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXDialogExBase::OnNcActivate(BOOL bActive)
{
    //
    BOOL bTreated = m_NC.Activate(this, NULL, bActive);
    if ( bTreated )
    {
        return TRUE;
    }

    return CDialogEx::OnNcActivate(bActive);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXDialogExBase::OnNcPaint()
{
    //
    BOOL bTreated = m_NC.PaintWindow(this, TRUE);
    if ( bTreated )
    {
        return;
    }

    //
    CDialogEx::OnNcPaint();
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXDialogExBase::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CDialogEx::OnNcLButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXDialogExBase::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonUp ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CDialogEx::OnNcLButtonUp(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXDialogExBase::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
    BOOL bTreated = m_NC.OnNcRButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }
    CDialogEx::OnNcRButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXDialogExBase::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

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
void CMCXDialogExBase::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
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
    CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXDialogExBase::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
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

    CDialogEx::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXDialogExBase::OnMouseMove(UINT nFlags, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnMouseMove ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CDialogEx::OnMouseMove(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXDialogExBase::OnNcMouseMove(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcMouseMove ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CDialogEx::OnNcMouseMove(nHitTest, point);
}


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXDialogExBase::OnNcMouseHover(UINT nFlags, CPoint point)
{
    /// Requires Windows 2000 or later
    // WIN32_WINNT  WINVER must be over  0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseHover ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CDialogEx::OnNcMouseHover(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXDialogExBase::OnNcMouseLeave()
{
    /// Requires Windows 2000 or later
    // WIN32_WINNT  WINVER must be over  0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseLeave (this);
    if ( bTreated )
    {
        return;
    }

    CDialogEx::OnNcMouseLeave();
}

