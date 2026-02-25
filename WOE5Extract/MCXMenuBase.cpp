#include "stdafx.h"
#include "resource.h"

#include "MCXMenuBase.h"
#include "MCXColors.h"
#include "MCXGDI.h"
#include "MCXIcons.h"


static  const int EXTRA_PIXELS_WIDTH    = 8;
static  const int EXTRA_PIXELS_HEIGHT   = 6;
static  const int SEPARATOR_HEIGHT      = 3;

#define MENU_TEXT_SIZE  256

//


//
HICON    CMCXMenuBase::m_hCheckWhiteIcon    = NULL;
HICON    CMCXMenuBase::m_hCheckBlackIcon    = NULL;

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
static void UpperCaseString ( TCHAR *pText )
{
    for ( size_t i = 0; i < _tcslen(pText); i++ )
    {
        pText [ i ] = toupper(pText [ i ] );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CMCXMenuBase, CMenu)

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXMenuBase::CMCXMenuBase(void)
{
    m_pWnd              = NULL;
    m_pMenu             = NULL;

    InitIcons();

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMenuBase::InitIcons()
{
    if ( m_hCheckWhiteIcon == NULL )
    {
        if ( IDI_CHECK_WHITE != VAL_CHECK_WHITE )
        {
            m_hCheckWhiteIcon   = AfxGetApp()->LoadIcon(IDI_CHECK_WHITE);
        }
        else if ( hIcon_check_ico != NULL )
        {
            m_hCheckWhiteIcon   = hIcon_check_ico;
        }
    }
    if ( m_hCheckBlackIcon == NULL )
    {
        if ( IDI_CHECK_BLACK != VAL_CHECK_BLACK )
        {
            m_hCheckBlackIcon   = AfxGetApp()->LoadIcon(IDI_CHECK_BLACK);
        }
        else if ( hIcon_checkblack_ico != NULL )
        {
            m_hCheckBlackIcon   = hIcon_checkblack_ico;
        }
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXMenuBase::~CMCXMenuBase(void)
{
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMenuBase::CreateMenu()
{
    return CMenu::CreateMenu();
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMenuBase::CreatePopupMenu()
{
    return CMenu::CreatePopupMenu();
}

//
/////////////////////////////////////////////////////////////////////////////
//  This is the entry that Initialize Popup Menu
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMenuBase::LoadMenu(LPCTSTR lpszResourceName)
{
    return CMenu::LoadMenu(lpszResourceName);
}

//
/////////////////////////////////////////////////////////////////////////////
//  This is the entry that Initialize Popup Menu
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMenuBase::LoadMenu(UINT nIDResource)
{
    return CMenu::LoadMenu(nIDResource);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXMenuBase *CMCXMenuBase::SetSystemMenu(CWnd* pWnd, CMenu* pSysMenu, int level)
{
    m_pWnd = pWnd;

    //
    if ( pSysMenu != NULL )
    {
        m_pMenu = pSysMenu;
        SetOwnDraw ( m_pMenu->m_hMenu, true, level );
    }

    return this;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXMenuBase *CMCXMenuBase::SetApplicationMenu(CWnd* pWnd, CMenu *pAppMenu, int level )
{
    m_pWnd      = pWnd;

    //
    if ( pAppMenu != NULL )
    {
        //
        if ( m_hMenu != NULL )
        {
            Detach ();
        }

        //
        BOOL bAttached = Attach ( pAppMenu->m_hMenu );
        SetOwnDraw ( m_hMenu, CMCXColors::m_iDarkTheme != 0, level );
        pAppMenu->Detach();
    }

    return this;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMenuBase::UnSetSystemMenu(CMenu* pSysMenu, int level)
{
    //
    if ( pSysMenu != NULL )
    {
        SetOwnDraw ( pSysMenu->m_hMenu, false, level );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMenuBase::UnSetAppMenu(CMenu* pAppMenu, int level )
{
    //
    if ( pAppMenu != NULL )
    {
        SetOwnDraw ( pAppMenu->m_hMenu, false, level );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//  The hMenu must be the handle of the submenu
/////////////////////////////////////////////////////////////////////////////
void CMCXMenuBase::SetOwnDraw ( HMENU hMenu, bool bOwnDrawn, int level )
{
    //  MFT_OWNERDRAW

    //
    //      Retrieve the Menu
    CMenu   *menu = CMenu::FromHandle ( hMenu );

    //
    //      If no handle : return
    if ( menu == NULL )
    {
        return;
    }

    //
    //      If menu is not correct: return
    if ( menu->m_hMenu == NULL )
    {
        return;
    }

    for ( UINT iPos = 0; iPos < (UINT) menu->GetMenuItemCount ( ); iPos++ )
    {
        TCHAR            szText [ MENU_TEXT_SIZE ];
        ZeroMemory ( szText, sizeof(szText) );

        MENUITEMINFO    menuItemInfo;
        ZeroMemory ( &menuItemInfo, sizeof ( menuItemInfo ) );
        menuItemInfo.cbSize     = sizeof ( menuItemInfo );

        menuItemInfo.cch        = _wsizeof ( szText );
        menuItemInfo.dwTypeData = szText;
        menuItemInfo.fMask      =   MIIM_BITMAP | MIIM_CHECKMARKS | MIIM_DATA |
                                    MIIM_FTYPE | MIIM_ID | MIIM_STATE | MIIM_STRING |
                                    MIIM_SUBMENU;
        BOOL bRes = menu->GetMenuItemInfo ( iPos, &menuItemInfo, TRUE );
        if ( bRes )
        {
            //  Only Type and Data
            menuItemInfo.fMask          = MIIM_FTYPE | MIIM_DATA;

            if ( bOwnDrawn )
            {
                menuItemInfo.fType          |= MFT_OWNERDRAW;
            //  Set Index and level in dwItemData
                menuItemInfo.dwItemData     = iPos | ( level << 8 );
            }
            else if ( menuItemInfo.fType & MFT_OWNERDRAW )
            {
                menuItemInfo.fType          ^= MFT_OWNERDRAW;
                menuItemInfo.dwItemData     = 0;
            }
            menuItemInfo.cch            = ( UINT ) _tcslen ( szText );
            bRes = menu->SetMenuItemInfo ( iPos, &menuItemInfo, TRUE );
            if ( ! bRes )
            {
#ifdef _DEBUG
                OutputDebugString ( _T("SetOwnDraw Error SetMenuItemInfo\n") );
#endif
            }

#ifdef _DEBUG
            static TCHAR szDebugString [ MAX_PATH ];
            _stprintf_s ( szDebugString, _wsizeof(szDebugString), _T("SetOwnDraw %0x:'%s' OwnDrawn %d bm %d\n"), 
                level, szText, bOwnDrawn, menuItemInfo.hbmpItem );
            OutputDebugString ( szDebugString );
#endif

            if ( menuItemInfo.hSubMenu )
            {
                SetOwnDraw ( menuItemInfo.hSubMenu, bOwnDrawn, level + 1 );
            }
        }
        else
        {
            OutputDebugString ( _T("SetOwnDraw GetMenuItemInfo Fails\n") );
        }
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMenuBase::SetOwnDraw ( CMenu *pMenu, bool bOwnDrawn, int level )
{
    if ( pMenu )
    {
        SetOwnDraw ( pMenu->GetSafeHmenu(), bOwnDrawn, level );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//  This is the entry that Initialize Popup Menu
/////////////////////////////////////////////////////////////////////////////
CMCXMenuBase *CMCXMenuBase::GetSubMenu ( int nPos )
{
    m_pMenu  = CMenu::GetSubMenu( nPos );
    return this;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMenuBase::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    if ( m_pMenu != NULL )
    {
        DrawMenuItem ( lpDrawItemStruct );
    }
    else if ( m_hMenu != NULL ) 
    {
        DrawMenuItem ( lpDrawItemStruct );
    }
    else
    {
#ifdef _DEBUG
        OutputDebugString ( _T("default CMenu::DrawItem\n") );
#endif
        CMenu::DrawItem ( lpDrawItemStruct );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMenuBase::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct )
{
    if ( m_pMenu != NULL )
    {
        MeasureMenuItem(lpMeasureItemStruct);
    }
    else if ( m_hMenu != NULL ) 
    {
        MeasureMenuItem(lpMeasureItemStruct );
    }
    else
    {
#ifdef _DEBUG
        OutputDebugString ( _T("default CMenu::MeasureItem\n") );
#endif
        CMenu::MeasureItem(lpMeasureItemStruct);
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//  For Submenu
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMenuBase::TrackPopupMenu(UINT nFlags, int x, int y, CWnd* pWnd, LPCRECT lpRect )
{
    m_pWnd = pWnd;

    if ( m_pMenu != NULL )
    {
        if ( CMCXColors::m_iDarkTheme != 0 )
        {
            SetOwnDraw(m_pMenu->m_hMenu, true, ID_POP_MENU );
        }
        else
        {
            SetOwnDraw(m_pMenu->m_hMenu, false, ID_POP_MENU );
        }
        return  m_pMenu->TrackPopupMenu( nFlags,  x,  y, pWnd, lpRect );
    }
    else
    {
        if ( CMCXColors::m_iDarkTheme != 0 )
        {
            SetOwnDraw(m_hMenu, true, ID_POP_MENU);
        }
        else
        {
            SetOwnDraw(m_hMenu, false, ID_POP_MENU);
        }
        return  CMenu::TrackPopupMenu( nFlags,  x,  y, pWnd, lpRect );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
UINT CMCXMenuBase::GetMenuItemCount ( )
{
    if ( m_pMenu )
    {
        return m_pMenu->GetMenuItemCount ( );
    }
    else
    {
        return CMenu::GetMenuItemCount ( );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//  For Submenu
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMenuBase::GetMenuItemInfo ( UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos )
{
    if ( m_pMenu )
    {
        return m_pMenu->GetMenuItemInfo ( uItem, lpMenuItemInfo, fByPos );
    }
    else
    {
        return CMenu::GetMenuItemInfo ( uItem, lpMenuItemInfo, fByPos );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//  For Submenu
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXMenuBase::SetMenuItemInfo ( UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos )
{
    if ( m_pMenu )
    {
        return m_pMenu->SetMenuItemInfo ( uItem, lpMenuItemInfo, fByPos );
    }
    else
    {
        return CMenu::SetMenuItemInfo ( uItem, lpMenuItemInfo, fByPos );
    }

}

//
/////////////////////////////////////////////////////////////////////////////
//  For Submenu
/////////////////////////////////////////////////////////////////////////////
UINT CMCXMenuBase::EnableMenuItem ( UINT nIDEnableItem, UINT nEnable )
{
    if ( m_pMenu )
    {
        return m_pMenu->EnableMenuItem ( nIDEnableItem, nEnable );
    }
    else
    {
        return CMenu::EnableMenuItem ( nIDEnableItem, nEnable );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXMenuBase::MeasureMenuItem ( CDC *pDC, const TCHAR *pText, CSize *pSize )
{
    //
    //      Initial Size
    int xCheckIcon  = GetSystemMetrics(SM_CXMENUCHECK);
    int yCheckIcon  = GetSystemMetrics(SM_CYMENUCHECK);

    pSize->cx = xCheckIcon + EXTRA_PIXELS_WIDTH;

    //
    if ( pText != NULL && _tcslen ( pText ) > 0 )
    {
        pSize->cy = yCheckIcon + EXTRA_PIXELS_HEIGHT;

        CFont* pOldFont     = ( CFont * ) pDC->SelectStockObject( ANSI_VAR_FONT );
        INT tabStop         = ( INT ) _tcslen ( pText );
        CSize sizeText      = pDC->GetOutputTabbedTextExtent ( pText, -1, 1, &tabStop );
        pSize->cx           += sizeText.cx + xCheckIcon;
        if ( sizeText.cy > pSize->cy )
        {
            pSize->cy = sizeText.cy;
        }

        pDC->SelectObject ( pOldFont );
    }
    else
    {
        if ( pSize->cy < SEPARATOR_HEIGHT )
        {
            pSize->cy       = SEPARATOR_HEIGHT;
        }

        pSize->cx           += (EXTRA_PIXELS_WIDTH * 2 );
    }

    return;
}

//
/////////////////////////////////////////////////////////////////////////////
//  For Submenu
/////////////////////////////////////////////////////////////////////////////
void CMCXMenuBase::MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct )
{
    //
    if ( lpMeasureItemStruct == NULL )
    {
        return;
    }

    //
    //      The Size
    CSize               size (0,0);

    //
    //      Get Info
    TCHAR    szText [ MENU_TEXT_SIZE ];
    ZeroMemory ( szText, sizeof(szText) );

    MENUITEMINFO    menuItemInfo;
    ZeroMemory ( &menuItemInfo, sizeof ( menuItemInfo ) );
    menuItemInfo.cbSize  = sizeof (menuItemInfo);

    menuItemInfo.fMask          =   MIIM_BITMAP | MIIM_CHECKMARKS | MIIM_DATA |
                                    MIIM_FTYPE | MIIM_ID | MIIM_STATE | MIIM_STRING |
                                    MIIM_SUBMENU;
    menuItemInfo.cch            = _wsizeof ( szText );
    menuItemInfo.dwTypeData     = szText;
    //  itemData contains the position / index
    UINT iPos   = ( UINT ) lpMeasureItemStruct->itemData & ID_MNU_MASK;
    //  We could search by itemID
    UINT id     = lpMeasureItemStruct->itemID;

    //
    BOOL bRes = GetMenuItemInfo ( id, &menuItemInfo, FALSE );
    if ( bRes )
    {
        if ( m_pWnd )
        {
            CDC *pDC    = m_pWnd->GetDC ( );
            if ( pDC )
            {
                ULONG_PTR itemData = menuItemInfo.dwItemData;

                //  Avoid Top Level
                ULONG_PTR shifted  = itemData >> 8;
                if ( shifted != ID_TOP_MENU && shifted != ID_MDI_MENU )
                {
                    _tcscat_s  ( szText, _wsizeof(szText), _T("ALT+F99") );
                }
                else
                {
                    UpperCaseString ( szText );
                }

                //
                MeasureMenuItem ( pDC, szText, &size );
                if ( _tcslen(szText) > 0 )
                {
                    size.cx     = size.cx + 1;
                    size.cy     = size.cy + 1;
                }
                int iRes    = m_pWnd->ReleaseDC ( pDC );

#ifdef _DEBUG
            static TCHAR szDebugString [ MAX_PATH ];
            _stprintf_s ( szDebugString, _wsizeof(szDebugString), _T("MeasureMenuItem '%s' cx %d\n"), szText, size.cx );
            OutputDebugString ( szDebugString );
#endif
            }
        }
    }
    else
    {
#ifdef _DEBUG
        OutputDebugString ( _T("GetMenuItemInfo failed\n") );
#endif
    }

    lpMeasureItemStruct->itemWidth      = size.cx;
    lpMeasureItemStruct->itemHeight     = size.cy;

}

//
//====================================================================================
//      Draw an Item
//====================================================================================
void CMCXMenuBase::DrawMenuItem (   LPDRAWITEMSTRUCT lpDrawItemStruct, CDC *pDC,
                                    CRect *pRect, const TCHAR *pText, MENUITEMINFO *menuInfo )
{
    InitIcons();

    //
    int xCheckIcon  = GetSystemMetrics(SM_CXMENUCHECK);
    int yCheckIcon  = GetSystemMetrics(SM_CYMENUCHECK);

    int xIconSmall  = GetSystemMetrics(SM_CXSMICON);
    int yIconSmall  = GetSystemMetrics(SM_CYSMICON);



    const   int     TextAttrLeft    =   DT_EXPANDTABS | DT_LEFT | DT_VCENTER | DT_SINGLELINE;
    const   int     TextAttrRight   =   DT_EXPANDTABS | DT_RIGHT | DT_VCENTER | DT_SINGLELINE;

    COLORREF        colorFg         = 0;
    int             bkMode          = 0;

    HBRUSH      hOldBrush       = NULL;
    BOOL        bDone           = FALSE;

    TCHAR    szText [ MENU_TEXT_SIZE ];
    ZeroMemory ( szText, sizeof(szText) );


    //  The entire control needs to be drawn
    //  This is called line by line
    if ( lpDrawItemStruct->itemAction & ODA_DRAWENTIRE )
    {
        bDone = pDC->DrawFrameControl ( &lpDrawItemStruct->rcItem, DFC_POPUPMENU, 0 );
        RECT rect = *pRect;
        rect.top        = rect.top + 1;
        rect.left       = rect.left + 1;
        rect.right      = rect.right  - 1;
        rect.bottom     = rect.bottom  - 1;
        pDC->FillRect ( pRect, CMCXColors::GetBKMenuCBrush(CMCXColors::m_iDarkTheme != 0));
    }

    //
    BOOL bDrawIcon = FALSE;
    if ( lpDrawItemStruct->itemState & ODS_CHECKED )
    {
        // We Will Have to Draw a Bitmap
        hOldBrush       = ( HBRUSH ) pDC->SelectObject ( CMCXColors::GetFGMenuBrush(CMCXColors::m_iDarkTheme != 0) );
        int xIconSmall  = GetSystemMetrics(SM_CXSMICON);
        int yIconSmall  = GetSystemMetrics(SM_CYSMICON);

        if ( CMCXColors::m_iDarkTheme != 0 )
        {
            //
            bDrawIcon = DrawIconEx ( pDC->m_hDC, lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top, 
                m_hCheckWhiteIcon, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL );
        }
        else
        {
            //
            bDrawIcon = DrawIconEx ( pDC->m_hDC, lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top, 
                m_hCheckBlackIcon, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL );
        }
        //
        pDC->SelectObject ( hOldBrush );
    }

    else if ( menuInfo->hbmpItem != NULL )
    {
        hOldBrush       = ( HBRUSH ) pDC->SelectObject ( CMCXColors::GetFGNormalBrush(CMCXColors::m_iDarkTheme != 0) );

        RECT iconRect   = lpDrawItemStruct->rcItem;
        iconRect.top++;
        iconRect.left++;
        iconRect.bottom++;
        iconRect.right++;
        if ( menuInfo->hbmpItem == HBMMENU_POPUP_RESTORE )
        {
            //
            if ( IDI_WINDOWED != VAL_WINDOWED )
            {
                HICON hIcon   = AfxGetApp()->LoadIcon(IDI_WINDOWED);
                DrawIconEx ( pDC->m_hDC, iconRect.left, iconRect.top, hIcon, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL );
            }
            else if ( hIcon_windowed_ico != NULL )
            {
                DrawIconEx ( pDC->m_hDC, iconRect.left, iconRect.top, hIcon_windowed_ico, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL );
            }
        }
        else if ( menuInfo->hbmpItem == HBMMENU_POPUP_MINIMIZE )
        {
            if ( IDI_MINIMIZE != VAL_MINIMIZE )
            {
                HICON hIcon   = AfxGetApp()->LoadIcon(IDI_MINIMIZE);
                DrawIconEx ( pDC->m_hDC, iconRect.left, iconRect.top, hIcon, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL );
            }
            else if ( hIcon_minimize_ico != NULL )
            {
                DrawIconEx ( pDC->m_hDC, iconRect.left, iconRect.top, hIcon_minimize_ico, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL );
            }
        }
        else if ( menuInfo->hbmpItem == HBMMENU_POPUP_MAXIMIZE )
        {
            if ( IDI_MAXIMIZE != VAL_MAXIMIZE )
            {
                HICON hIcon   = AfxGetApp()->LoadIcon(IDI_MAXIMIZE);
                DrawIconEx ( pDC->m_hDC, iconRect.left, iconRect.top, hIcon, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL );
            }
            else if ( hIcon_maximize_ico != NULL )
            {
                DrawIconEx ( pDC->m_hDC, iconRect.left, iconRect.top, hIcon_maximize_ico, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL );
            }
        }
        else if ( menuInfo->hbmpItem == HBMMENU_POPUP_CLOSE )
        {
            if ( IDI_CLOSE != VAL_CLOSE )
            {
                HICON hIcon   = AfxGetApp()->LoadIcon(IDI_CLOSE);
                DrawIconEx ( pDC->m_hDC, iconRect.left, iconRect.top, hIcon, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL );
            }
            else if ( hIcon_close_ico != NULL )
            {
                DrawIconEx ( pDC->m_hDC, iconRect.left, iconRect.top, hIcon_close_ico, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL );
            }
        }
        //
        pDC->SelectObject ( hOldBrush );
    }

    //
    if ( lpDrawItemStruct->itemAction & ( ODA_FOCUS | ODA_SELECT ) )
    {
        hOldBrush = ( HBRUSH ) pDC->SelectObject ( CMCXColors::GetFGMenuSelectedBrush(CMCXColors::m_iDarkTheme != 0) );
    }
    else
    {
        hOldBrush = ( HBRUSH ) pDC->SelectObject ( CMCXColors::GetFGMenuBrush(CMCXColors::m_iDarkTheme != 0) );
    }

    //
    if ( lpDrawItemStruct->itemState & ODS_SELECTED )
    {
        if ( lpDrawItemStruct->itemState & ( ODS_GRAYED | ODS_DISABLED ) )
        {
            colorFg = pDC->SetTextColor ( CMCXColors::GetFGDisabledCR(CMCXColors::m_iDarkTheme != 0) );
        }
        else
        {
            colorFg = pDC->SetTextColor ( CMCXColors::GetFGMenuSelectedCR(CMCXColors::m_iDarkTheme != 0) );
        }
    }
    else
    {
        if ( lpDrawItemStruct->itemState & ( ODS_GRAYED | ODS_DISABLED ) )
        {
            colorFg = pDC->SetTextColor ( CMCXColors::GetFGDisabledCR(CMCXColors::m_iDarkTheme != 0) );
        }
        else
        {
            colorFg = pDC->SetTextColor ( CMCXColors::GetFGMenuCR(CMCXColors::m_iDarkTheme != 0) );
        }
    }

    //
    pRect->left += xCheckIcon;

    //
    if ( pText != NULL && _tcslen ( pText ) > 0 )
    {
        if ( lpDrawItemStruct->itemState & ODS_SELECTED )
        {
            pDC->FillRect ( pRect, CMCXColors::GetBKMenuSelectedCBrush(CMCXColors::m_iDarkTheme != 0) );
        }
        else
        {
            pDC->FillRect ( pRect, CMCXColors::GetBKMenuCBrush(CMCXColors::m_iDarkTheme != 0) );
        }

        bkMode          = pDC->SetBkMode ( TRANSPARENT );
        pRect->left     += EXTRA_PIXELS_WIDTH / 2;

        _tcscpy_s ( szText, _wsizeof(szText), pText );
        TCHAR *pTab = _tcschr( szText, _T('\t') );
        if ( pTab != NULL )
        {
            *pTab = _T('\0');
            pTab++;
        }

        pDC->DrawText ( szText, pRect, TextAttrLeft );
        if ( pTab )
        {
            CRect rect = pRect;
            rect.right = rect.right - EXTRA_PIXELS_WIDTH / 2;
            pDC->DrawText ( pTab, &rect, TextAttrRight );
        }

        pDC->SetBkMode ( bkMode );

#ifdef _DEBUG
        static TCHAR szDebugString [ MAX_PATH ];
        _stprintf_s ( szDebugString, _wsizeof(szDebugString), _T("DrawMenuItem '%s' bm %d\n"), 
                    szText, menuInfo->hbmpItem );
        OutputDebugString ( szDebugString );
#endif

    }
    else
    {
        if ( lpDrawItemStruct->itemState & ODS_SELECTED )
        {
            pDC->FillRect ( pRect, CMCXColors::GetBKMenuSelectedCBrush(CMCXColors::m_iDarkTheme != 0) );
        }
        else
        {
            pDC->FillRect ( pRect, CMCXColors::GetBKMenuCBrush(CMCXColors::m_iDarkTheme != 0) );
        }

        bkMode          = pDC->SetBkMode ( TRANSPARENT );

        int penSize = 1;
        CMCXPen penBlack;
        penBlack.CreatePen(PS_SOLID, penSize, CMCXColors::GetFGMenuCR(CMCXColors::m_iDarkTheme != 0) );
        CPen* pOldPen = pDC->SelectObject(&penBlack);

        pRect->left     += EXTRA_PIXELS_WIDTH / 2;
        int middle = ( pRect->bottom  - pRect->top ) / 2;
        pDC->MoveTo ( pRect->left, pRect->top + middle );
        pDC->LineTo ( pRect->right - EXTRA_PIXELS_WIDTH / 2, pRect->top + middle );

        pDC->SelectObject(pOldPen);
        penBlack.DeleteObject();

    }

    pDC->SetTextColor ( colorFg );

    pDC->SelectObject ( hOldBrush );

}

//
//====================================================================================
//      Main Entry DrawItem
//
//      Must be a little cleaned
//====================================================================================
void CMCXMenuBase::DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    //
    if ( lpDrawItemStruct == NULL )
    {
        return;
    }

    //
    //      Get Menu Informations
    TCHAR    szText [ MENU_TEXT_SIZE ];
    ZeroMemory ( szText, sizeof(szText) );

    //
    MENUITEMINFO    menuItemInfo;
    ZeroMemory ( &menuItemInfo, sizeof ( menuItemInfo ) );
    menuItemInfo.cbSize  = sizeof ( menuItemInfo );

    //
    menuItemInfo.fMask      =   MIIM_BITMAP | MIIM_CHECKMARKS | MIIM_DATA |
                                MIIM_FTYPE | MIIM_ID | MIIM_STATE | MIIM_STRING |
                                MIIM_SUBMENU;
    menuItemInfo.cch        = _wsizeof ( szText ) - 1;
    menuItemInfo.dwTypeData = szText;
    //  itemData contains the position / index
    UINT iPos   = ( UINT ) lpDrawItemStruct->itemData & ID_MNU_MASK;
    //  We could search by itemID
    UINT id     = lpDrawItemStruct->itemID;

    //
    BOOL bRes = GetMenuItemInfo ( id, &menuItemInfo, FALSE );
    if ( bRes )
    {
        //
        //      Menu rectangle
        CRect   rectMenu = lpDrawItemStruct->rcItem;

        CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        if ( pDC )
        {
            //  Only for Top Level
            ULONG_PTR itemData = menuItemInfo.dwItemData;
            ULONG_PTR shifted  = itemData >> 8;
            if ( shifted == ID_TOP_MENU || shifted == ID_MDI_MENU )
            {
                UpperCaseString ( szText );
            }

            DrawMenuItem ( lpDrawItemStruct, pDC, &rectMenu, szText, &menuItemInfo );
        }
    }
    else
    {
#ifdef _DEBUG
        OutputDebugString ( _T("GetMenuItemInfo failed\n") );
#endif
    }
}

//
//====================================================================================
//      Compute the maximum Bitmap size
//====================================================================================
void CMCXMenuBase::ComputeBitmapMaxSize ( HBITMAP hBitmap )
{
    if ( hBitmap )
    {
        //
        //      Bitmap
        CBitmap *pBitmap = CBitmap::FromHandle ( hBitmap );
        if ( pBitmap )
        {
            //
            //      Bitmap Info
            BITMAP              bmInfo;
            ZeroMemory ( &bmInfo, sizeof ( bmInfo ) );

            if ( pBitmap->GetBitmap ( &bmInfo ) )
            {
                if ( m_iBitmapWidth < bmInfo.bmWidth )
                {
                    m_iBitmapWidth = bmInfo.bmWidth;
                }

                if ( m_iBitmapHeight < bmInfo.bmHeight )
                {
                    m_iBitmapHeight = bmInfo.bmHeight;
                }
            }
        }
    }
}

//
//====================================================================================
//      Compute the maximum Bitmap size
//====================================================================================
void CMCXMenuBase::ComputeBitmapMaxSize (  )
{
    m_iBitmapWidth  = 0;
    m_iBitmapHeight = 0;

    for ( UINT iPos = 0; iPos < GetMenuItemCount ( ); iPos++ )
    {
        MENUITEMINFO    menuItemInfo;
        ZeroMemory ( &menuItemInfo, sizeof ( menuItemInfo ) );
        menuItemInfo.cbSize     = sizeof ( menuItemInfo );

        menuItemInfo.fMask      =   MIIM_BITMAP | MIIM_CHECKMARKS;
        BOOL bRes = GetMenuItemInfo ( iPos, &menuItemInfo, TRUE );
        if ( bRes )
        {
            if ( menuItemInfo.hbmpChecked )
            {
                ComputeBitmapMaxSize ( menuItemInfo.hbmpChecked  );
            }

            if ( menuItemInfo.hbmpUnchecked )
            {
                ComputeBitmapMaxSize ( menuItemInfo.hbmpUnchecked );
            }

            if ( menuItemInfo.hbmpItem )
            {
                ComputeBitmapMaxSize ( menuItemInfo.hbmpItem  );
            }

        }
    }

    m_iBitmapWidth  += (EXTRA_PIXELS_WIDTH*2);
    m_iBitmapHeight += (EXTRA_PIXELS_HEIGHT*2);
}

//
//====================================================================================
//      Draw a bitmap
//====================================================================================
void CMCXMenuBase::DrawBitmap(CDC *pDC, CBitmap *pBitmap, CRect *pRect)
{
    //
    //      Memory DC
    CDC     memDC;
    memDC.CreateCompatibleDC ( pDC );           // ...create it

    //
    //      Select the Bitmap
    if ( memDC.m_hDC )
    {
        CBitmap *pOldBitmap = memDC.SelectObject( pBitmap );
        
        *pRect -= CRect ( 1, 1, 2, 2 );             // shrink

        // blast bits to screen
        pDC->BitBlt ( pRect->left, pRect->top,
            pRect->Width(), pRect->Height(), &memDC, 0, 0, SRCCOPY );

        memDC.SelectObject ( pOldBitmap );          // restore DC
    }
}

//
//====================================================================================
//      Draw a Bitmap
//====================================================================================
int CMCXMenuBase::DrawBitmap(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if ( lpDrawItemStruct == NULL )
    {
        return m_iBitmapWidth;
    }

    CRect rectBitmap    = lpDrawItemStruct->rcItem;

    //
    //      Bitmap Info
    BITMAP              bmInfo;
    ZeroMemory ( &bmInfo, sizeof ( bmInfo ) );

    //
    //      Get Menu Informations
    MENUITEMINFO    menuItemInfo;
    ZeroMemory ( &menuItemInfo, sizeof ( menuItemInfo ) );
    menuItemInfo.cbSize  = sizeof ( menuItemInfo );

    menuItemInfo.fMask      = MIIM_BITMAP | MIIM_CHECKMARKS;
    //  itemData contains the position / index
    UINT iPos   = ( UINT ) lpDrawItemStruct->itemData & ID_MNU_MASK;
    //  We could search by itemID
    UINT id     = lpDrawItemStruct->itemID;

    //
    BOOL bRes = GetMenuItemInfo ( id, &menuItemInfo, FALSE );
    if ( bRes )
    {

        CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        if ( pDC )
        {
            // EraseRectWithGrade1 ( &rectBitmap, pDC );

            //
            //      No Bitmap to display
            if ( menuItemInfo.hbmpUnchecked == NULL )
            {
                return m_iBitmapWidth;
            }

            CBitmap *pBitmap;
            pBitmap             = CBitmap::FromHandle ( menuItemInfo.hbmpUnchecked );
            if ( pBitmap == NULL )
            {
                return m_iBitmapWidth;
            }

            pBitmap->GetBitmap ( &bmInfo );
            rectBitmap.top      += EXTRA_PIXELS_HEIGHT;
            rectBitmap.left     += EXTRA_PIXELS_WIDTH;
            rectBitmap.right    = rectBitmap.left + bmInfo.bmWidth + EXTRA_PIXELS_WIDTH;
            rectBitmap.bottom   = rectBitmap.top + bmInfo.bmHeight + EXTRA_PIXELS_HEIGHT;

            //
            if ( lpDrawItemStruct->itemState & ODS_SELECTED )
            {
                pDC->DrawFrameControl( &rectBitmap, DFC_BUTTON, DFCS_BUTTONPUSH );
            }

            //
            //      Draw the Bitmap
            DrawBitmap ( pDC, pBitmap, &rectBitmap );
        }
    }

    return ( m_iBitmapWidth );

}

//
//====================================================================================
//
//====================================================================================
BOOL CMCXMenuBase::SetMenuItemBitmaps ( UINT nPosition, UINT nFlags, const CBitmap *pBmpUnchecked,
                                        const CBitmap *pBmpChecked )
{
    if ( m_pMenu )
    {
        return m_pMenu->SetMenuItemBitmaps ( nPosition, nFlags, pBmpUnchecked, pBmpChecked );
    }

    return FALSE;
}

