// MCXDiablogBase.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "resource.h"

// #include "afxdialogex.h"

#include "MCXFrameWndBase.h"
#include "MCXWinAppBase.h"

#include "MCXColors.h"




// Boîte de dialogue CMCXFrameWndBase

IMPLEMENT_DYNAMIC(CMCXFrameWndBase, CFrameWnd)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXFrameWndBase::CMCXFrameWndBase() : CFrameWnd()
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
CMCXFrameWndBase::~CMCXFrameWndBase()
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
void CMCXFrameWndBase::SetContextMenu ( CMCXMenuBase *pMenu )
{
    m_pMenu = pMenu;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CToolTipCtrl *CMCXFrameWndBase::GetToolTipCtrl()
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
void CMCXFrameWndBase::DoDataExchange(CDataExchange* pDX)
{
    CFrameWnd::DoDataExchange(pDX);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMCXFrameWndBase, CFrameWnd)
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

    ON_MESSAGE(WM_USER + 1, &OnMessageUser1)
    ON_WM_NCCREATE()
END_MESSAGE_MAP()


//
/////////////////////////////////////////////////////////////////////////////
// Gestionnaires de messages de CMCXFrameWndBase
//
/////////////////////////////////////////////////////////////////////////////


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXFrameWndBase::PreCreateWindow(CREATESTRUCT& cs)
{
    CFrameWnd::PreCreateWindow(cs);
 
    //
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXFrameWndBase::PreTranslateMessage(MSG* pMsg)
{
    //
    if ( m_bToolTip )
    {
        m_ToolTip.RelayEvent(pMsg);
    }

    return CFrameWnd::PreTranslateMessage(pMsg);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXFrameWndBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CFrameWnd::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXFrameWndBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this) )
    {
        return TRUE;
    }
    return CFrameWnd::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXFrameWndBase::OnNcActivate(BOOL bActive)
{
    //
    BOOL bTreated = m_NC.Activate(this, NULL, bActive);
    if ( bTreated )
    {
        return TRUE;
    }

    return CFrameWnd::OnNcActivate(bActive);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnNcPaint()
{
    //
    CFrameWnd::OnNcPaint();
    BOOL bTreated = m_NC.PaintWindow(this, FALSE, &m_wndToolBar);
    if ( bTreated )
    {
        return;
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CFrameWnd::OnNcLButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcLButtonUp ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CFrameWnd::OnNcLButtonUp(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
    BOOL bTreated = m_NC.OnNcRButtonDown ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }
    CFrameWnd::OnNcRButtonDown(nHitTest, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

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
void CMCXFrameWndBase::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
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
        else if ( m_AppMenu.m_hMenu != NULL )
        {
            m_AppMenu.DrawItem ( lpDrawItemStruct );
            return;
        }
    }
    
    //
#ifdef _DEBUG
    if ( lpDrawItemStruct != NULL )
    {
        static TCHAR szDebugString [ MAX_PATH ];
        _stprintf_s ( szDebugString, _wsizeof(szDebugString), _T("CMCXFrameWndBase::OnDrawItem %d %d\n"),
            nIDCtl, lpDrawItemStruct->CtlType );
        OutputDebugString ( szDebugString );
    }
#endif

    CFrameWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
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
        else if ( m_AppMenu.m_hMenu != NULL )
        {
            m_AppMenu.MeasureItem ( lpMeasureItemStruct );
            return;
        }
    }

#ifdef _DEBUG
    if ( lpMeasureItemStruct != NULL )
    {
        static TCHAR szDebugString [ MAX_PATH ];
        _stprintf_s ( szDebugString, _wsizeof(szDebugString), _T("CMCXFrameWndBase::OnMeasureItem %d %d\n"),
            nIDCtl, lpMeasureItemStruct->CtlType );
        OutputDebugString ( szDebugString );
    }
#endif
    CFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnMouseMove(UINT nFlags, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnMouseMove ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CFrameWnd::OnMouseMove(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnNcMouseMove(UINT nHitTest, CPoint point)
{
    //
    BOOL bTreated = m_NC.OnNcMouseMove ( this, nHitTest, point );
    if ( bTreated )
    {
        return;
    }

    CFrameWnd::OnNcMouseMove(nHitTest, point);
}


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnNcMouseHover(UINT nFlags, CPoint point)
{
    // Cette fonctionnalité requiert Windows 2000 ou une version ultérieure.
    // Les symboles _WIN32_WINNT et WINVER doivent être >= 0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseHover ( this, nFlags, point );
    if ( bTreated )
    {
        return;
    }

    CFrameWnd::OnNcMouseHover(nFlags, point);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnNcMouseLeave()
{
    // Cette fonctionnalité requiert Windows 2000 ou une version ultérieure.
    // Les symboles _WIN32_WINNT et WINVER doivent être >= 0x0500.
    //
    BOOL bTreated = m_NC.OnNcMouseLeave (this);
    if ( bTreated )
    {
        return;
    }

    CFrameWnd::OnNcMouseLeave();
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CFrameWnd::OnShowWindow(bShow, nStatus);

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


    }

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
int CMCXFrameWndBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  Ajoutez ici votre code de création spécialisé
    CMenu *pSysMenu = GetSystemMenu ( FALSE );
    if ( pSysMenu != NULL )
    {
        // pMenu->AppendMenu(MF_SEPARATOR);
    }

    //
    CMenu *pAppMenu = GetMenu();
    m_AppMenu.SetApplicationMenu ( this, pAppMenu );
    SetMenu ( &m_AppMenu );

    //
    return 0;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
afx_msg LRESULT CMCXFrameWndBase::OnMessageUser1(WPARAM, LPARAM)
{
    DrawMenuBar();
    SendMessage(WM_NCPAINT, 0, 0);
    SetWindowPos(NULL, 0,0,0,0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

    return 0;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::HandleStatusBar ( CMCXStatusBarBase *pStatusBar )
{

    //
    UINT added  = SBPS_OWNERDRAW;
    if ( CMCXColors::m_iDarkTheme == 0 )
    {
        added = NULL;
    }
    pStatusBar->ModifyStyle ( NULL, added );

	//		Set size of the ID_INDICATOR_ERROR
	RECT				rectFrame;
	UINT				nID;
	UINT				nStyle;
	int					cxWidth;

	//		Get the Frame Window Client size
	GetClientRect ( &rectFrame );

    //  Change to enable DrawItem
    int paneCount = pStatusBar->GetCount();
    for  ( int i = 0; i < paneCount; i++ )
    {
        pStatusBar->GetPaneInfo ( i, nID, nStyle, cxWidth );
        nStyle |= added;
        pStatusBar->SetPaneInfo ( i, nID, nStyle, cxWidth );
    }

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXFrameWndBase::OnUpdateFrameMenu(HMENU hMenuAlt)
{
    // TODO: ajoutez ici votre code spécialisé et/ou l'appel de la classe de base

    CFrameWnd::OnUpdateFrameMenu(hMenuAlt);
}


