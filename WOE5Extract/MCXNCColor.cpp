#include "stdafx.h"
#include <afxtoolbar.h>

#include "resource.h"

#include "MCXNCColor.h"
#include "MCXColors.h"

#include "MCXMenuBase.h"
#include "MCXGDI.h"

#include "MCXCWndBase.h"
#include "MCXViewBase.h"
#include "MCXDialogBase.h"
#include "MCXDialogExBase.h"
#include "MCXFrameWndBase.h"
#include "MCXMDIFrameWndBase.h"
#include "MCXMDIChildWndBase.h"

#include "MCXPropertySheetBase.h"
#include "MCXPropertyPageBase.h"

#include "MCXWinAppBase.h"
#include "MCXIcons.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CRect CMCXNCColor::GetFrameFullRect ( const CRect &windowRECT )
{
    CRect frameFullRECT;
    frameFullRECT.left      = 0;
    frameFullRECT.top       = 0;
    frameFullRECT.right     = windowRECT.Width();
    frameFullRECT.bottom    = windowRECT.Height();
    return frameFullRECT;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CRect CMCXNCColor::GetCaptionFullRect ( const CRect &windowRECT )
{
    //  EG : 1
    int yBorder         = GetSystemMetrics(SM_CYBORDER);

    //  EG : 3
    int yFrame          = GetSystemMetrics ( SM_CYDLGFRAME );

    int yCaption        = GetSystemMetrics(SM_CYCAPTION);

    CRect captionFullRECT;

    captionFullRECT.left    = 1;
    captionFullRECT.top     = 1;
    captionFullRECT.right   = windowRECT.Width() - 1;
    captionFullRECT.bottom  = yCaption + 2 * yBorder + yFrame;

    return captionFullRECT;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CRect CMCXNCColor::GetCaptionInsideRect ( const CRect &windowRECT )
{
    //  EG : 1
    int xBorder         = GetSystemMetrics(SM_CXBORDER);
    int yBorder         = GetSystemMetrics(SM_CYBORDER);

    //  EG : 3
    int xFrame          = GetSystemMetrics ( SM_CXDLGFRAME );
    int yFrame          = GetSystemMetrics ( SM_CYDLGFRAME );

    int yCaption        = GetSystemMetrics(SM_CYCAPTION);

    int xLeft           = xBorder + xFrame;
    int yTop            = yBorder + yFrame;

    int x               = xLeft;
    int y               = yTop;
    int cx              = windowRECT.Width() - 2 * xFrame - xBorder;
    int cy              = yCaption + yBorder + yFrame;

    CRect   captionInsideRECT;
    captionInsideRECT.left      = x; 
    captionInsideRECT.top       = y;
    captionInsideRECT.right     = captionInsideRECT.left + cx;
    captionInsideRECT.bottom    = captionInsideRECT.top + cy;
    return captionInsideRECT;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CRect CMCXNCColor::GetMenuBarRect ( HWND hWnd, const CRect &windowRECT )
{
    CRect menuBarRECT;

    //
    //  Menu Bar
    MENUBARINFO mbi;
    ZeroMemory ( &mbi, sizeof(mbi) );
    mbi.cbSize  = sizeof(mbi) ;

    ::GetMenuBarInfo ( hWnd, OBJID_MENU, 0, &mbi );

    menuBarRECT.left    = mbi.rcBar.left - windowRECT.left;
    menuBarRECT.top     = mbi.rcBar.top - windowRECT.top;
    menuBarRECT.right   = menuBarRECT.left + mbi.rcBar.right - mbi.rcBar.left;
    menuBarRECT.bottom  = menuBarRECT.top + mbi.rcBar.bottom - mbi.rcBar.top;

    return menuBarRECT;
}

//
/////////////////////////////////////////////////////////////////////////////
//  Only left and top are correct
//  Bottom and right are same as left and top
/////////////////////////////////////////////////////////////////////////////
CRect CMCXNCColor::GetToolBarRect ( CToolBar *pToolBar, const CRect &windowRECT )
{
    //
    CRect toolBarRect;

    RECT rect;
    pToolBar->GetWindowRect ( &rect );

    toolBarRect.left    = rect.left - windowRECT.left;
    toolBarRect.top     = rect.top - windowRECT.top;
    toolBarRect.right   = toolBarRect.left + rect.right - rect.left;
    toolBarRect.bottom  = toolBarRect.top + rect.bottom - rect.top;

    return toolBarRect;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CRect CMCXNCColor::GetClientFullRect ( const CRect &windowRECT )
{
    //  EG : 1
    int xBorder         = GetSystemMetrics(SM_CXBORDER);
    int yBorder         = GetSystemMetrics(SM_CYBORDER);

    //  EG : 3
    int xFrame          = GetSystemMetrics ( SM_CXDLGFRAME );
    int yFrame          = GetSystemMetrics ( SM_CYDLGFRAME );

    int xIcon           = GetSystemMetrics(SM_CXICON);
    int yIcon           = GetSystemMetrics(SM_CYICON);

    int xIconSmall      = GetSystemMetrics(SM_CXSMICON);
    int yIconSmall      = GetSystemMetrics(SM_CYSMICON);

    int yCaption        = GetSystemMetrics(SM_CYCAPTION);

    CRect clientFullRECT;

    clientFullRECT.top        = yBorder + yFrame + yCaption + yBorder;
    clientFullRECT.left       = 0;
    clientFullRECT.bottom     = windowRECT.Height();
    clientFullRECT.right      = windowRECT.Width();

    return clientFullRECT;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
int CMCXNCColor::GetIconWidth ( )
{
    int xIcon           = GetSystemMetrics(SM_CXICON);
    return xIcon * 3 / 2 - 1;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
int CMCXNCColor::GetIconHeight ( )
{
    int yCaption        = GetSystemMetrics(SM_CYCAPTION);
    return yCaption - 1;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CRect CMCXNCColor::GetIconFullRECT ( const CRect &windowRECT, int left )
{
    int yBorder         = GetSystemMetrics(SM_CYBORDER);
    int yFrame          = GetSystemMetrics ( SM_CYDLGFRAME );

    CRect captionFullRECT   = GetCaptionFullRect ( windowRECT );

    CRect iconFullRECT;

    iconFullRECT.left       = left;
    iconFullRECT.top        = captionFullRECT.top; // yBorder + yFrame;
    iconFullRECT.right      = iconFullRECT.left + GetIconWidth ( );
    iconFullRECT.bottom     = iconFullRECT.top + GetIconHeight ( ) + yFrame - 1; // iconFullRECT.top + yCaption - 1;

    return iconFullRECT;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXNCColor::CMCXNCColor(void)
{
    m_pContextMenu          = NULL;

    m_iHover                = ICON_NOT_SET;

    m_bLeftPressed          = FALSE;
    m_windowRECT.top        = -1;
    m_windowRECT.left       = -1;
    m_LeftPressedPoint.x    = -1;
    m_LeftPressedPoint.y    = -1;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXNCColor::~CMCXNCColor(void)
{
}

//
/////////////////////////////////////////////////////////////////////////////
//  Not Used DrawIconEx is better
/////////////////////////////////////////////////////////////////////////////
void CMCXNCColor::DrawResizedIcon ( CDC *pDC, HICON hIcon, const RECT *pRect )
{
    ICONINFO info;
    ZeroMemory ( &info, sizeof(info) );

    //
    BITMAP bmp;
    ZeroMemory(&bmp, sizeof(bmp));

    int xIcon   = 0;
    int yIcon  = 0;
    int pixels      = 0;

    //
    BOOL bRes = GetIconInfo(hIcon, &info);

    //
    if ( info.hbmColor )
    {
        const int nWrittenBytes = GetObject(info.hbmColor, sizeof(bmp), &bmp);
        if ( nWrittenBytes > 0 )
        {
            xIcon       = bmp.bmWidth;
            yIcon       = bmp.bmHeight;
            pixels      = bmp.bmBitsPixel;
        }
    }
    else if ( info.hbmMask )
    {
        // Icon has no color plane, image data stored in mask
        const int nWrittenBytes = GetObject(info.hbmMask, sizeof(bmp), &bmp);
        if(nWrittenBytes > 0)
        {
            xIcon   = bmp.bmWidth;
            yIcon  = bmp.bmHeight / 2;
            pixels      = 1;
        }
    }

    //
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);

    //
    CMCXBitmap bitmap;
    bitmap.CreateBitmapIndirect ( &bmp );
    CBitmap* pOldBitmap = memDC.SelectObject ( &bitmap );
    memDC.DrawIcon ( 0, 0, hIcon );

    if ( true )
    {
        bRes = pDC->StretchBlt (
            pRect->left,        // x upper left
            pRect->top,         // y upper left
            // The next two lines specify the width and height.
            pRect->right - pRect->left,
            pRect->bottom - pRect->top,
            //  Source
            &memDC,             // source device context
            0, 0,               // x and y upper left
            xIcon,          // source bitmap width
            yIcon,         // source bitmap height
            SRCCOPY );          // raster operation
    }
    else
    {
        bRes = pDC->BitBlt (
            pRect->left,        // x upper left
            pRect->top,         // y upper left
            // The next two lines specify the width and height.
            pRect->right - pRect->left,
            pRect->bottom - pRect->top,
            //  Source
            &memDC,             // source device context
            0, 0,               // x and y upper left
            SRCCOPY );          // raster operation
    }

    //
    if ( info.hbmColor)
    {
        DeleteObject(info.hbmColor);
    }

    if ( info.hbmMask )
    {
        DeleteObject(info.hbmMask);
    }

    memDC.SelectObject ( pOldBitmap );

    //
    DeleteDC(memDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::ScreenPointOverRect ( CWnd *pWnd, CPoint pt, CRect cRect )
{
    CRect windowRECT;
    pWnd->GetWindowRect(&windowRECT);

    cRect.left      += windowRECT.left;
    cRect.top       += windowRECT.top;

    cRect.right     += windowRECT.left;
    cRect.bottom    += windowRECT.top;

    return cRect.PtInRect( pt );
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXNCColor::DrawIconFrame ( CDC *pDC, const CRect crect, bool bFillRect, CBrush *pbr )
{
    if ( pDC == NULL )
    {
        return;
    }

    if ( bFillRect )
    {
        RECT rect = crect;
        if ( pbr != NULL )
        {
            pDC->FillRect ( &rect, pbr );
        }
        else
        {
            pDC->FillRect ( &rect, CMCXColors::GetBKNormalCBrush( true ) );
        }
    }

}

//
/////////////////////////////////////////////////////////////////////////////
//  To draw Background only set icon to zero
/////////////////////////////////////////////////////////////////////////////
void CMCXNCColor::DrawIcon ( CDC *pDC, UINT icon, const CRect crect, bool bFillRect, CBrush *pbr )
{
    if ( pDC == NULL )
    {
        return;
    }

    //
    DrawIconFrame ( pDC, crect, bFillRect, pbr );

    //
    if ( icon != 0 )
    {
        int xIconSmall  = GetSystemMetrics(SM_CXSMICON);
        int yIconSmall  = GetSystemMetrics(SM_CYSMICON);

        int xMargin = ( crect.Width() - xIconSmall ) / 2;
        int yMargin = ( crect.Height() - yIconSmall ) / 2;

        HICON hIcon = AfxGetApp()->LoadIcon(icon);
        DrawIconEx(pDC->m_hDC, crect.left + xMargin, crect.top + yMargin, hIcon, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL);
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//  To draw Background only set icon to zero
/////////////////////////////////////////////////////////////////////////////
void CMCXNCColor::DrawIcon ( CDC *pDC, HICON hIcon, const CRect crect, bool bFillRect, CBrush *pbr )
{
    if ( pDC == NULL )
    {
        return;
    }

    //
    DrawIconFrame ( pDC, crect, bFillRect, pbr );

    //
    if ( hIcon != NULL )
    {
        int xIconSmall  = GetSystemMetrics(SM_CXSMICON);
        int yIconSmall  = GetSystemMetrics(SM_CYSMICON);

        int xMargin = ( crect.Width() - xIconSmall ) / 2;
        int yMargin = ( crect.Height() - yIconSmall ) / 2;

        DrawIconEx(pDC->m_hDC, crect.left + xMargin, crect.top + yMargin, hIcon, xIconSmall, yIconSmall, 0, NULL, DI_NORMAL);
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CDC *CMCXNCColor::GetDeviceContext ( CWnd *pWnd )
{
    return  pWnd->GetWindowDC();
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::InvalidateCaption ( CWnd *pWnd, int darkIndicator )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    if ( CMCXColors::m_iDarkTheme != 2 && CMCXColors::m_iDarkTheme != darkIndicator )
    {
        return FALSE;
    }

    //
    CRect windowRECT;
    pWnd->GetWindowRect(&windowRECT);

    //  The The Caption Rect
    CRect captionFullRECT   = GetCaptionFullRect ( windowRECT );

    //
    pWnd->InvalidateRect ( captionFullRECT, TRUE );

    //
    return TRUE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::PaintCaption( CWnd *pWnd, BOOL bActive, int darkIndicator )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    if ( CMCXColors::m_iDarkTheme != 2 && CMCXColors::m_iDarkTheme != darkIndicator )
    {
        return FALSE;
    }

    //  EG : 1
    int xBorder         = GetSystemMetrics(SM_CXBORDER);
    int yBorder         = GetSystemMetrics(SM_CYBORDER);

    //  EG : 3
    int xFrame          = GetSystemMetrics ( SM_CXDLGFRAME );
    int yFrame          = GetSystemMetrics ( SM_CYDLGFRAME );

    // int xIcon           = GetSystemMetrics(SM_CXICON);
    // int yIcon           = GetSystemMetrics(SM_CYICON);

    // int xIconSmall      = GetSystemMetrics(SM_CXSMICON);
    // int yIconSmall      = GetSystemMetrics(SM_CYSMICON);

    // int yCaption        = GetSystemMetrics(SM_CYCAPTION);

    int xLeft           = xBorder + xFrame;
    int yTop            = yBorder + yFrame;

    int iconWidth       = GetIconWidth();
    int iconHeight      = GetIconHeight();

    //
    CDC* pDC = GetDeviceContext ( pWnd );

    //
    CRect windowRECT;
    pWnd->GetWindowRect(&windowRECT);

    //
    COLORREF foregroundColor = CMCXColors::GetFGNormalCR(CMCXColors::m_iDarkTheme != 0);

    //  First Draw Frmae Rect Around the window
    CRect frameFullRECT     = GetFrameFullRect ( windowRECT );
    pDC->FrameRect ( &frameFullRECT, CMCXColors::GetCyanCBrush() );

    //  The The Caption Rect
    CRect captionFullRECT   = GetCaptionFullRect ( windowRECT );

    //
    if ( bActive )
    {
        pDC->FillSolidRect(&captionFullRECT, CMCXColors::GetBKSelectedCR(CMCXColors::m_iDarkTheme != 0));
    }
    else
    {
        pDC->FillSolidRect(&captionFullRECT, CMCXColors::GetBKNormalCR(CMCXColors::m_iDarkTheme != 0));
    }

    //
    //  Caption Rect
    CRect captionInsideRECT = GetCaptionInsideRect ( windowRECT );

    // Draw Old FRame (Window XP)
    UINT captionOption  = DFCS_CAPTIONMIN | DFCS_CAPTIONMAX | DFCS_CAPTIONCLOSE | DFCS_CAPTIONRESTORE | DFCS_CAPTIONHELP;
    captionOption       |= DFCS_FLAT;
    // pDC->DrawFrameControl ( captionInsideRECT, DFC_CAPTION, captionOption );

    TCHAR szTitle [ MAX_PATH ];
    pWnd->GetWindowText ( szTitle, _wsizeof(szTitle));
    CRect textRECT  = captionInsideRECT;
    textRECT.left   = textRECT.left + iconWidth + xBorder;

    pDC->SetBkMode (TRANSPARENT);
    pDC->SetTextColor (foregroundColor);
    pDC->DrawText ( szTitle, &textRECT, DT_LEFT | DT_VCENTER );

    //
    DWORD dwStyle = pWnd->GetStyle();
    WINDOWPLACEMENT wp;
    pWnd->GetWindowPlacement( &wp );

    //  ICONS
    //////////////////////////////

    //  LEFT
    m_IconRect = GetIconFullRECT ( windowRECT, 1 /* xLeft */ );
    if ( CMCXColors::m_iSquareCorner == 1 )
    {
        DrawIcon ( pDC, IDR_MAINFRAME, m_IconRect );
    }
    else
    {
        if ( ( dwStyle & WS_SYSMENU ) && ( dwStyle & WS_CAPTION ) )
        {
            DrawIcon ( pDC, IDR_MAINFRAME, m_IconRect );
        }
    }

    //  RIGHT
    // Close
    m_CloseRect = GetIconFullRECT ( windowRECT, /* captionInsideRECT.right */ captionFullRECT.right - iconWidth );
    if ( IDI_CLOSE != VAL_CLOSE )
    {
        DrawIcon ( pDC, IDI_CLOSE, m_CloseRect );

    }
    else if ( hIcon_close_ico != NULL )
    {
        DrawIcon ( pDC, hIcon_close_ico, m_CloseRect );
    }

    //  Maximize
    m_MaximizeRect = GetIconFullRECT ( windowRECT, m_CloseRect.left - iconWidth );
    if ( dwStyle & WS_MAXIMIZEBOX )
    {
        if ( wp.showCmd == SW_NORMAL )
        {
            if ( IDI_MAXIMIZE != VAL_MAXIMIZE )
            {
                DrawIcon ( pDC, IDI_MAXIMIZE, m_MaximizeRect );
            }
            else if ( hIcon_maximize_ico != NULL )
            {
                DrawIcon ( pDC, hIcon_maximize_ico, m_MaximizeRect );
            }
        }
        else
        {
            if ( IDI_WINDOWED != VAL_WINDOWED )
            {
                DrawIcon ( pDC, IDI_WINDOWED, m_MaximizeRect );
            }
            else if ( hIcon_windowed_ico != NULL )
            {
                DrawIcon ( pDC, hIcon_windowed_ico, m_MaximizeRect );
            }
        }
    }

    //  Minilmize
    m_MinimizeRect = GetIconFullRECT ( windowRECT, m_MaximizeRect.left - iconWidth );
    if ( dwStyle & WS_MINIMIZEBOX )
    {
        if ( IDI_MINIMIZE != VAL_MINIMIZE )
        {
            DrawIcon ( pDC, IDI_MINIMIZE, m_MinimizeRect );
        }
        else if ( hIcon_minimize_ico != NULL )
        {
            DrawIcon ( pDC, hIcon_minimize_ico, m_MinimizeRect );
        }
    }

    //
    pWnd->ReleaseDC ( pDC );

    return TRUE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::PaintWindow ( CWnd *pWnd, BOOL bFill, CToolBar *pToolBar, BOOL bActive, int darkIndicator )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    if ( CMCXColors::m_iDarkTheme != 2 && CMCXColors::m_iDarkTheme != darkIndicator )
    {
        return FALSE;
    }


    //
    CDC*    pDC     = GetDeviceContext ( pWnd );
    HWND    hWnd    = pWnd->m_hWnd;

    //
    //  Fill Background
    CRect windowRECT;
    pWnd->GetWindowRect(&windowRECT);

    //  First Draw Frmae Rect Around the window
    CRect frameFullRECT = GetFrameFullRect ( windowRECT );
    pDC->FrameRect ( &frameFullRECT, CMCXColors::GetCyanCBrush() );

    //
    //  Menu Bar
    // MENUBARINFO mbi;
    // ZeroMemory ( &mbi, sizeof(mbi) );
    // mbi.cbSize  = sizeof(mbi) ;

    //
    CRect   usedMenuBar;
    usedMenuBar.left    = 0xffff;
    usedMenuBar.top     = 0xffff;
    usedMenuBar.right   = 0;
    usedMenuBar.bottom  = 0;

    //
    CRect   usedToolBar;
    usedToolBar.left    = 0xffff;
    usedToolBar.top     = 0xffff;
    usedToolBar.right   = 0;
    usedToolBar.bottom  = 0;

    //
    if ( hWnd )
    {
        //  0 means full menu
        //  Rect In Screen Coord
        CRect menuBarRect = GetMenuBarRect ( hWnd, windowRECT );
        // ::GetMenuBarInfo ( hWnd, OBJID_MENU, 0, &mbi );

        //
        HMENU hMenu = ::GetMenu(hWnd);
        if ( hMenu != NULL )
        {
            int count = ::GetMenuItemCount(hMenu);
            RECT rectItem;

            for (int i = 0; i < count; i++ )
            {
                //  Retrieve Rect in Screen coordinates
                if (::GetMenuItemRect(hWnd, hMenu, i, &rectItem))
                {
                    if ( rectItem.left < usedMenuBar.left )
                    {
                        usedMenuBar.left = rectItem.left;
                    }
                    if ( rectItem.right > usedMenuBar.right )
                    {
                        usedMenuBar.right = rectItem.right;
                    }
                    if ( rectItem.top < usedMenuBar.top )
                    {
                        usedMenuBar.top = rectItem.top;
                    }
                    if ( rectItem.bottom > usedMenuBar.bottom )
                    {
                        usedMenuBar.bottom = rectItem.bottom;
                    }
                }
            }

            CRect fillRect = menuBarRect;
            fillRect.left = fillRect.left + usedMenuBar.right - usedMenuBar.left;
            pDC->FillRect ( &fillRect, CMCXColors::GetBKNormalCBrush(CMCXColors::m_iDarkTheme != 0) );
            
            // pDC->FillRect ( &fillRect, CMCXColors::GetBlueCBrush () );
        }

        //
        //  Tool Bar
        if ( pToolBar != NULL && pToolBar->m_hWnd != NULL )
        {
            CRect toolBarRect = GetToolBarRect (pToolBar, windowRECT );

            int nbButtons = pToolBar->GetCount();

            //
            for ( int i = 0; i < nbButtons; i++ )
            {
                RECT rectButton;
                pToolBar->GetItemRect ( i, &rectButton );
                if ( rectButton.left < usedToolBar.left )
                {
                    usedToolBar.left = rectButton.left;
                }
                if ( rectButton.right > usedToolBar.right )
                {
                    usedToolBar.right = rectButton.right;
                }
                if ( rectButton.top < usedToolBar.top )
                {
                    usedToolBar.top = rectButton.top;
                }
                if ( rectButton.bottom > usedToolBar.bottom )
                {
                    usedToolBar.bottom = rectButton.bottom;
                }
            }

            CRect fillRect  = toolBarRect;
            fillRect.left   = fillRect.left + usedToolBar.right - usedToolBar.left;
            fillRect.bottom = fillRect.bottom + usedToolBar.bottom - usedToolBar.top;
            fillRect.right  = windowRECT.Width();
            fillRect.bottom = windowRECT.Height();
            // pDC->FillRect ( &fillRect, CMCXColors::GetBKNormalCBrush(CMCXColors::m_iDarkTheme != 0) );
        }
    }

    //
    //  So We will rework this part
    //  Avoiding the menu and the icon bar

    //  The Following line mess the menu
    RECT clientFullRect = GetClientFullRect ( windowRECT );
    if ( bFill )
    {
        //
        pDC->FillRect ( &clientFullRect, CMCXColors::GetBKNormalCBrush(CMCXColors::m_iDarkTheme != 0) );
    }

    //
    pWnd->ReleaseDC ( pDC );

    //
    PaintCaption ( pWnd, bActive, darkIndicator );

    //
    {
        RECT clientRect;
        pWnd->GetClientRect( &clientRect );
        pWnd->InvalidateRect ( &clientRect );
    }
    return TRUE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::Activate( CWnd *pWnd, BOOL bActive, int darkIndicator )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    if ( CMCXColors::m_iDarkTheme != 2 && CMCXColors::m_iDarkTheme != darkIndicator )
    {
        return FALSE;
    }

    return PaintCaption ( pWnd, bActive, darkIndicator );
}


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::OnNcLButtonDown(CWnd *pWnd, UINT nHitTest, CPoint point, int darkIndicator )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    //
    if ( CMCXColors::m_iDarkTheme == 2 || CMCXColors::m_iDarkTheme == darkIndicator )
    {
        if ( ScreenPointOverRect( pWnd, point, m_IconRect ) )
        {
            //  Default Treatment
            if ( CMCXColors::m_iSquareCorner == 1 )
            {
                RECT clientRect;
                pWnd->GetClientRect ( &clientRect );
                pWnd->ClientToScreen ( &clientRect );
                CPoint pt;
                pt.x = clientRect.left;
                pt.y = clientRect.top;

                BOOL bTreated = PopupSystemMenu ( pWnd, nHitTest, pt, darkIndicator );
                return bTreated;
            }
            else
            {
                return FALSE;
            }
        }

        //
        else if ( ScreenPointOverRect( pWnd, point, m_CloseRect ) )
        {
            return TRUE;
        }

        else if ( ScreenPointOverRect( pWnd, point, m_MinimizeRect ) )
        {
            return TRUE;
        }

        else if ( ScreenPointOverRect( pWnd, point, m_MaximizeRect ) )
        {
            return TRUE;
        }

        //  Icons At RIght
        int xIcon   = GetSystemMetrics(SM_CXICON);

        //
        CRect iconsRect;
        iconsRect.top       = m_CloseRect.top;
        iconsRect.bottom    = m_CloseRect.bottom;
        iconsRect.left      = min(min(m_CloseRect.left, m_MinimizeRect.left), m_MaximizeRect.left);
        iconsRect.right     = max(max(m_CloseRect.right, m_MinimizeRect.right), m_MaximizeRect.right);
        iconsRect.left      = iconsRect.left - xIcon;
        if ( ScreenPointOverRect( pWnd, point, iconsRect ) )
        {
            return TRUE;
        }

        //  We Could handle move here
        CRect windowRECT;
        pWnd->GetWindowRect(&windowRECT);
        CRect captionRect = GetCaptionFullRect ( windowRECT );
        if ( ScreenPointOverRect( pWnd, point, captionRect ) )
        {
            m_bLeftPressed      = FALSE;
            m_windowRECT        = windowRECT;
            m_LeftPressedPoint  = point;
            return m_bLeftPressed;
        }
    }

    return FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::OnNcLButtonUp(CWnd *pWnd, UINT nHitTest, CPoint point, int darkIndicator)
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    //
    m_bLeftPressed  = FALSE;

	//
    //
    if ( CMCXColors::m_iDarkTheme == 2 || CMCXColors::m_iDarkTheme == darkIndicator )
    {
        if ( ScreenPointOverRect( pWnd, point, m_IconRect ) )
        {
            //  Default Treatment
            return FALSE;
        }

        else if ( ScreenPointOverRect( pWnd, point, m_CloseRect ) )
        {
            ::SendMessage ( pWnd->m_hWnd, WM_SYSCOMMAND, SC_CLOSE, NULL );
            return TRUE;
        }

        else if ( ScreenPointOverRect( pWnd, point, m_MinimizeRect ) )
        {
            //
            DWORD dwStyle = pWnd->GetStyle();
            WINDOWPLACEMENT wp;
            pWnd->GetWindowPlacement( &wp );
            if ( dwStyle & WS_MINIMIZEBOX )
            {
                ::SendMessage ( pWnd->m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL );
            }
            return TRUE;
        }

        else if ( ScreenPointOverRect( pWnd, point, m_MaximizeRect ) )
        {
            //
            DWORD dwStyle = pWnd->GetStyle();
            WINDOWPLACEMENT wp;
            pWnd->GetWindowPlacement( &wp );
            if ( dwStyle & WS_MAXIMIZEBOX )
            {
                if ( wp.showCmd == SW_NORMAL )
                {
                    ::SendMessage ( pWnd->m_hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, NULL );
                }
                else
                {
                    ::SendMessage ( pWnd->m_hWnd, WM_SYSCOMMAND, SC_RESTORE, NULL );
                }
            }
            return TRUE;
        }

        //  Icons At RIght
        int xIcon   = GetSystemMetrics(SM_CXICON);

        CRect iconsRect;
        iconsRect.top       = m_CloseRect.top;
        iconsRect.bottom    = m_CloseRect.bottom;
        iconsRect.left      = min(min(m_CloseRect.left, m_MinimizeRect.left), m_MaximizeRect.left);
        iconsRect.right     = max(max(m_CloseRect.right, m_MinimizeRect.right), m_MaximizeRect.right);
        iconsRect.left      = iconsRect.left - xIcon;
        if ( ScreenPointOverRect( pWnd, point, iconsRect ) )
        {
            return TRUE;
        }

    }

    return FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::SetThemeChanged ( CWnd *pWnd )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    //
    CMenu *pMenu = GetSystemMenu(pWnd, FALSE);

    if ( pMenu != NULL )
    {
        //  Square Corners
        if ( CMCXColors::m_iSquareCorner == 1 )
        {
            //  Dark Theme Full
            if ( CMCXColors::m_iDarkTheme == 2 )
            {
                CMCXColors::SetWindowTheme ( pWnd );
                //  Remove System Menu
                pWnd->ModifyStyle ( WS_SYSMENU, NULL, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER );
                CMCXMenuBase::SetOwnDraw ( pMenu->GetSubMenu(0), true, ID_SYS_MENU );
            }
            //  Dark Theme and Normal Theme
            else
            {
                CMCXColors::SetWindowTheme ( pWnd );
                //  Add System Menu
                pWnd->ModifyStyle ( NULL, WS_SYSMENU | WS_MINIMIZEBOX, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER );
                if ( false )
                {
                    DWORD dwStyle = GetWindowLong( pWnd->GetSafeHwnd(), GWL_STYLE );
                    dwStyle |= WS_SYSMENU | WS_MINIMIZEBOX;
                    SetWindowLong( pWnd->GetSafeHwnd(), GWL_STYLE, dwStyle );
                }
                CMCXMenuBase::SetOwnDraw ( pMenu->GetSubMenu(0), false, ID_SYS_MENU );

                pWnd->SetWindowPos ( NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER );
            }
	    }
        //  No Square Corners
        else
        {
            CMCXColors::SetWindowTheme ( pWnd );

            //  Add System Menu
            pWnd->ModifyStyle ( NULL, WS_SYSMENU | WS_MINIMIZEBOX, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER );
            if ( false )
            {
                DWORD dwStyle = GetWindowLong( pWnd->GetSafeHwnd(), GWL_STYLE );
                dwStyle |= WS_SYSMENU | WS_MINIMIZEBOX;
                SetWindowLong( pWnd->GetSafeHwnd(), GWL_STYLE, dwStyle );
            }

            if ( CMCXColors::m_iDarkTheme == 2 || CMCXColors::m_iDarkTheme == 1 )
            {
                if ( pMenu )
                {
                    CMCXMenuBase::SetOwnDraw ( pMenu->GetSubMenu(0), true, ID_SYS_MENU );
                }
            }
            else
            {
                if ( pMenu )
                {
                    CMCXMenuBase::SetOwnDraw ( pMenu->GetSubMenu(0), false, ID_SYS_MENU );
                }
            }

            pWnd->SetWindowPos ( NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER );

        }

        //
        if ( CMCXColors::m_iDarkTheme == 0 )
        {
            //
            {
                CMCXPropertySheetBase *pSheet = dynamic_cast<CMCXPropertySheetBase *>(pWnd);
                if ( pSheet != NULL )
                {
                    pSheet->SetContextMenu ( NULL );
                    return FALSE;
                }
            }

            //
            {
                CMCXPropertyPageBase *pPage = dynamic_cast<CMCXPropertyPageBase *>(pWnd);
                if ( pPage != NULL )
                {
                    pPage->SetContextMenu ( NULL );
                    return FALSE;
                }
            }

            //
            {
                CMCXDialogExBase *pDialogEx = dynamic_cast<CMCXDialogExBase *>(pWnd);
                if ( pDialogEx != NULL )
                {
                    pDialogEx->SetContextMenu ( NULL );
                    return FALSE;
                }
            }

            //
            {
                CMCXDialogBase *pDialog = dynamic_cast<CMCXDialogBase *>(pWnd);
                if ( pDialog != NULL )
                {
                    pDialog->SetContextMenu ( NULL );
                    return FALSE;
                }
            }

            //
            {
                CMCXFrameWndBase *pFrame = dynamic_cast<CMCXFrameWndBase *>(pWnd);
                if ( pFrame != NULL )
                {
                    pFrame->SetContextMenu ( NULL );
                    return FALSE;
                }
            }

            //
            {
                CMCXMDIFrameWndBase *pMdiFrame = dynamic_cast<CMCXMDIFrameWndBase *>(pWnd);
                if ( pMdiFrame != NULL )
                {
                    pMdiFrame->SetContextMenu ( NULL );
                    return FALSE;
                }
            }

            //
            {
                CMCXMDIChildWndBase *pMdiChild = dynamic_cast<CMCXMDIChildWndBase *>(pWnd);
                if ( pMdiChild != NULL )
                {
                    pMdiChild->SetContextMenu ( NULL );
                    return FALSE;
                }
            }

            //
            {
                CMCXViewBase *pView = dynamic_cast<CMCXViewBase *>(pWnd);
                if ( pView != NULL )
                {
                    pView->SetContextMenu ( NULL );
                    return FALSE;
                }
            }

            //
            {
                CMCXCWndBase *pWndBase = dynamic_cast<CMCXCWndBase *>(pWnd);
                if ( pWndBase != NULL )
                {
                    pWndBase->SetContextMenu ( NULL );
                    return FALSE;
                }
            }


        }
    }

    //
    return FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::HandleSquareCorners ( CWnd *pWnd, BOOL bWithStyle )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    //
    if ( CMCXColors::m_iSquareCorner == 1 )
    {
        if ( CMCXColors::m_iDarkTheme == 2 )
        {
            CMCXColors::SetWindowTheme ( pWnd );

            //  Remove System Menu
            if ( bWithStyle )
            {
                pWnd->ModifyStyle ( WS_SYSMENU, NULL, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER );
            }
            return TRUE;
        }
    }

    return FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::PopupSystemMenu ( CWnd *pWnd, UINT nHitTest, CPoint point, int darkIndicator )
{
    CMenu *pMenu = pWnd->GetSystemMenu(FALSE);
    if ( pMenu )
    {
        //
        {
            CMCXPropertySheetBase *pSheet = dynamic_cast<CMCXPropertySheetBase *>(pWnd);
            if ( pSheet != NULL )
            {
                CMCXMenuBase        menu;
                menu.Attach ( pMenu->m_hMenu );
                m_pContextMenu = menu.GetSubMenu ( 0 );
                pSheet->SetContextMenu ( m_pContextMenu );
                //  Use System Menu as Popup Menu
                LPARAM lParam = m_pContextMenu->TrackPopupMenu ( 
                    TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON /* | TPM_NONOTIFY */ | TPM_RETURNCMD, 
                    point.x, point.y, pWnd );
                if ( lParam ) 
                {
                    PostMessage(pWnd->GetSafeHwnd(), WM_SYSCOMMAND, lParam, 0);
                }
                menu.Detach ( );
                return TRUE;
            }
        }

        //
        {
            CMCXPropertyPageBase *pPage = dynamic_cast<CMCXPropertyPageBase *>(pWnd);
            if ( pPage != NULL )
            {
                CMCXMenuBase        menu;
                menu.Attach ( pMenu->m_hMenu );
                m_pContextMenu = menu.GetSubMenu ( 0 );
                pPage->SetContextMenu ( m_pContextMenu );
                //  Use System Menu as Popup Menu
                LPARAM lParam = m_pContextMenu->TrackPopupMenu ( 
                    TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON /* | TPM_NONOTIFY */ | TPM_RETURNCMD, 
                    point.x, point.y, pWnd );
                if ( lParam ) 
                {
                    PostMessage(pWnd->GetSafeHwnd(), WM_SYSCOMMAND, lParam, 0);
                }
                menu.Detach ( );
                return TRUE;
            }
        }

        //
        {
            CMCXDialogExBase *pDialogEx = dynamic_cast<CMCXDialogExBase *>(pWnd);
            if ( pDialogEx != NULL )
            {
                CMCXMenuBase        menu;
                menu.Attach ( pMenu->m_hMenu );
                m_pContextMenu = menu.GetSubMenu ( 0 );
                pDialogEx->SetContextMenu ( m_pContextMenu );
                //  Use System Menu as Popup Menu
                LPARAM lParam = m_pContextMenu->TrackPopupMenu ( 
                    TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON /* | TPM_NONOTIFY */ | TPM_RETURNCMD, 
                    point.x, point.y, pWnd );
                if ( lParam ) 
                {
                    PostMessage(pWnd->GetSafeHwnd(), WM_SYSCOMMAND, lParam, 0);
                }
                menu.Detach ( );
                return TRUE;
            }
        }

        {
            CMCXDialogBase *pDialog = dynamic_cast<CMCXDialogBase *>(pWnd);
            if ( pDialog != NULL )
            {
                CMCXMenuBase        menu;
                menu.Attach ( pMenu->m_hMenu );
                m_pContextMenu = menu.GetSubMenu ( 0 );
                pDialog->SetContextMenu ( m_pContextMenu );
                //  Use System Menu as Popup Menu
                LPARAM lParam = m_pContextMenu->TrackPopupMenu ( 
                    TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON /* | TPM_NONOTIFY */ | TPM_RETURNCMD, 
                    point.x, point.y, pWnd );
                if ( lParam ) 
                {
                    PostMessage(pWnd->GetSafeHwnd(), WM_SYSCOMMAND, lParam, 0);
                }
                menu.Detach ( );
                return TRUE;
            }
        }

        {
            CMCXFrameWndBase *pFrame = dynamic_cast<CMCXFrameWndBase *>(pWnd);
            if ( pFrame != NULL )
            {
                CMCXMenuBase        menu;
                menu.Attach ( pMenu->m_hMenu );
                m_pContextMenu = menu.GetSubMenu ( 0 );
                pFrame->SetContextMenu ( m_pContextMenu );
                //  Use System Menu as Popup Menu
                LPARAM lParam = m_pContextMenu->TrackPopupMenu ( 
                    TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON /* | TPM_NONOTIFY */ | TPM_RETURNCMD, 
                    point.x, point.y, pWnd );
                if ( lParam ) 
                {
                    PostMessage(pWnd->GetSafeHwnd(), WM_SYSCOMMAND, lParam, 0);
                }
                menu.Detach ( );
                return TRUE;
            }
        }

        {
            CMCXMDIFrameWndBase *pMdiFrame = dynamic_cast<CMCXMDIFrameWndBase *>(pWnd);
            if ( pMdiFrame != NULL )
            {
                CMCXMenuBase        menu;
                menu.Attach ( pMenu->m_hMenu );
                m_pContextMenu = menu.GetSubMenu ( 0 );
                pMdiFrame->SetContextMenu ( m_pContextMenu );
                //  Use System Menu as Popup Menu
                LPARAM lParam = m_pContextMenu->TrackPopupMenu ( 
                    TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON /* | TPM_NONOTIFY */ | TPM_RETURNCMD, 
                    point.x, point.y, pWnd );
                if ( lParam ) 
                {
                    PostMessage(pWnd->GetSafeHwnd(), WM_SYSCOMMAND, lParam, 0);
                }
                menu.Detach ( );
                return TRUE;
            }
        }

        {
            CMCXMDIChildWndBase *pMdiChild = dynamic_cast<CMCXMDIChildWndBase *>(pWnd);
            if ( pMdiChild != NULL )
            {
                CMCXMenuBase        menu;
                menu.Attach ( pMenu->m_hMenu );
                m_pContextMenu = menu.GetSubMenu ( 0 );
                pMdiChild->SetContextMenu ( m_pContextMenu );
                //  Use System Menu as Popup Menu
                LPARAM lParam = m_pContextMenu->TrackPopupMenu ( 
                    TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON /* | TPM_NONOTIFY */ | TPM_RETURNCMD, 
                    point.x, point.y, pWnd );
                if ( lParam ) 
                {
                    PostMessage(pWnd->GetSafeHwnd(), WM_SYSCOMMAND, lParam, 0);
                }
                menu.Detach ( );
                return TRUE;
            }
        }

        {
            CMCXCWndBase *pWndBase = dynamic_cast<CMCXCWndBase *>(pWnd);
            if ( pWndBase != NULL )
            {
                CMCXMenuBase        menu;
                menu.Attach ( pMenu->m_hMenu );
                m_pContextMenu = menu.GetSubMenu ( 0 );
                pWndBase->SetContextMenu ( m_pContextMenu );
                //  Use System Menu as Popup Menu
                LPARAM lParam = m_pContextMenu->TrackPopupMenu ( 
                    TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON /* | TPM_NONOTIFY */ | TPM_RETURNCMD, 
                    point.x, point.y, pWnd );
                if ( lParam ) 
                {
                    PostMessage(pWnd->GetSafeHwnd(), WM_SYSCOMMAND, lParam, 0);
                }
                menu.Detach ( );
                return TRUE;
            }
        }

        {
            CMCXViewBase *pView = dynamic_cast<CMCXViewBase *>(pWnd);
            if ( pView != NULL )
            {
                CMCXMenuBase        menu;
                menu.Attach ( pMenu->m_hMenu );
                m_pContextMenu = menu.GetSubMenu ( 0 );
                pView->SetContextMenu ( m_pContextMenu );
                //  Use System Menu as Popup Menu
                LPARAM lParam = m_pContextMenu->TrackPopupMenu ( 
                    TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON /* | TPM_NONOTIFY */ | TPM_RETURNCMD, 
                    point.x, point.y, pWnd );
                if ( lParam ) 
                {
                    PostMessage(pWnd->GetSafeHwnd(), WM_SYSCOMMAND, lParam, 0);
                }
                menu.Detach ( );
                return TRUE;
            }
        }

    }

    return FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::OnNcRButtonDown( CWnd *pWnd, UINT nHitTest, CPoint point, int darkIndicator )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    if ( CMCXColors::m_iDarkTheme == 2 || CMCXColors::m_iDarkTheme == darkIndicator )
    {
        BOOL bTreated = PopupSystemMenu ( pWnd, nHitTest, point, darkIndicator );
        return bTreated;
    }

#if 0
    //  Default Behaviour : popup system menu in the caption
    return FALSE;
#endif

    //
    //  This make the menu appear when caption RButton Down
    {
        CMCXPropertySheetBase *pSheet = dynamic_cast<CMCXPropertySheetBase *>(pWnd);
        if ( pSheet != NULL )
        {
            BOOL bTreated = PopupSystemMenu ( pWnd, nHitTest, point, darkIndicator );
            return bTreated;
        }
    }

    {
        CMCXPropertyPageBase *pPage = dynamic_cast<CMCXPropertyPageBase *>(pWnd);
        if ( pPage != NULL )
        {
            BOOL bTreated = PopupSystemMenu ( pWnd, nHitTest, point, darkIndicator );
            return bTreated;
        }
    }

    {
        CMCXDialogExBase *pDialog = dynamic_cast<CMCXDialogExBase *>(pWnd);
        if ( pDialog != NULL )
        {
            BOOL bTreated = PopupSystemMenu ( pWnd, nHitTest, point, darkIndicator );
            return bTreated;
        }
    }

    {
        CMCXDialogBase *pDialog = dynamic_cast<CMCXDialogBase *>(pWnd);
        if ( pDialog != NULL )
        {
            BOOL bTreated = PopupSystemMenu ( pWnd, nHitTest, point, darkIndicator );
            return bTreated;
        }
    }

    {
        CMCXFrameWndBase *pFrame = dynamic_cast<CMCXFrameWndBase *>(pWnd);
        if ( pFrame != NULL )
        {
            BOOL bTreated = PopupSystemMenu ( pWnd, nHitTest, point, darkIndicator );
            return bTreated;
        }
    }

    {
        CMCXFrameWndBase *pFrame = dynamic_cast<CMCXFrameWndBase *>(pWnd);
        if ( pFrame != NULL )
        {
            BOOL bTreated = PopupSystemMenu ( pWnd, nHitTest, point, darkIndicator );
            return bTreated;
        }
    }

    {
        CMCXMDIFrameWndBase *pFrame = dynamic_cast<CMCXMDIFrameWndBase *>(pWnd);
        if ( pFrame != NULL )
        {
            BOOL bTreated = PopupSystemMenu ( pWnd, nHitTest, point, darkIndicator );
            return bTreated;
        }
    }

    {
        CMCXMDIChildWndBase *pChild = dynamic_cast<CMCXMDIChildWndBase *>(pWnd);
        if ( pChild != NULL )
        {
            BOOL bTreated = PopupSystemMenu ( pWnd, nHitTest, point, darkIndicator );
            return bTreated;
        }
    }

    return FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::OnLButtonUp(CWnd *pWnd, UINT nFlags, CPoint point, int darkIndicator)
{
    m_bLeftPressed  = FALSE;
    return FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::OnNcMouseMove(CWnd *pWnd, UINT nHitTest, CPoint point, int darkIndicator )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    //
    if ( CMCXColors::m_iDarkTheme == 2 || CMCXColors::m_iDarkTheme == darkIndicator )
    {
        TRACKMOUSEEVENT tme;
        ZeroMemory ( &tme, sizeof(tme) );
        tme.cbSize      = sizeof(tme);
        tme.hwndTrack   = pWnd->m_hWnd;
        tme.dwFlags     = TME_NONCLIENT  | TME_HOVER | TME_LEAVE;
        tme.dwHoverTime = 100; // HOVER_DEFAULT;
        TrackMouseEvent ( &tme );

        if ( m_bLeftPressed )
        {
            pWnd->SetWindowPos ( NULL, 
                m_windowRECT.left + point.x - m_LeftPressedPoint.x,
                m_windowRECT.top + point.y - m_LeftPressedPoint.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
        }

    }

    //  Always returns FALSE to continue the process
    return FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::OnMouseMove(CWnd *pWnd, UINT nFlags, CPoint point, int darkIndicator )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    //
    if ( CMCXColors::m_iDarkTheme == 2 || CMCXColors::m_iDarkTheme == darkIndicator )
    {
        //  Track Event
        TRACKMOUSEEVENT tme;
        ZeroMemory ( &tme, sizeof(tme) );
        tme.cbSize      = sizeof(tme);
        tme.hwndTrack   = pWnd->m_hWnd;
        tme.dwFlags     = TME_NONCLIENT  | TME_HOVER | TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        TrackMouseEvent ( &tme );

        m_bLeftPressed  = FALSE;
    }

    //  Always returns FALSE to continue the process
    return FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXNCColor::DrawAllIcons (  CWnd *pWnd, UINT iconOnly, int darkIndicator )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return;
	}

    if ( iconOnly == ICON_NOT_SET )
    {
        return;
    }

    //
    if ( CMCXColors::m_iDarkTheme != 2 && CMCXColors::m_iDarkTheme != darkIndicator )
    {
        return;
	}

    //
    DWORD dwStyle = pWnd->GetStyle();
    WINDOWPLACEMENT wp;
    pWnd->GetWindowPlacement( &wp );

    //
    CDC* pDC = GetDeviceContext ( pWnd );

    if ( iconOnly == 0 || iconOnly == IDI_CLOSE )
    {
        if ( IDI_CLOSE != VAL_CLOSE )
        {
            DrawIcon ( pDC, IDI_CLOSE, m_CloseRect );
        }
        else if ( hIcon_close_ico != NULL )
        {
            DrawIcon ( pDC, hIcon_close_ico, m_CloseRect );
        }
    }

    if ( iconOnly == 0 || iconOnly == IDI_MAXIMIZE || iconOnly == IDI_WINDOWED )
    {
        if ( dwStyle & WS_MAXIMIZEBOX )
        {
            if ( wp.showCmd == SW_NORMAL )
            {
                if ( IDI_MAXIMIZE != VAL_MAXIMIZE )
                {
                    DrawIcon ( pDC, IDI_MAXIMIZE, m_MaximizeRect );
                }
                else if ( hIcon_maximize_ico != NULL )
                {
                    DrawIcon ( pDC, hIcon_maximize_ico, m_MaximizeRect );
                }
            }
            else
            {
                if ( IDI_WINDOWED != VAL_WINDOWED )
                {
                    DrawIcon ( pDC, IDI_WINDOWED, m_MaximizeRect );
                }
                else if ( hIcon_windowed_ico != NULL )
                {
                    DrawIcon ( pDC, hIcon_windowed_ico, m_MaximizeRect );
                }
            }
        }
        else
        {
            DrawIconFrame ( pDC, m_MaximizeRect );
        }
    }

    if ( iconOnly == 0 || iconOnly == IDI_MINIMIZE )
    {
        if ( dwStyle & WS_MINIMIZEBOX )
        {
            if ( IDI_MINIMIZE != VAL_MINIMIZE )
            {
                DrawIcon ( pDC, IDI_MINIMIZE, m_MinimizeRect );
            }
            else if ( hIcon_minimize_ico != NULL )
            {
                DrawIcon ( pDC, hIcon_minimize_ico, m_MinimizeRect );
            }
        }
        else
        {
            DrawIconFrame ( pDC, m_MinimizeRect );
        }
    }

    pWnd->ReleaseDC ( pDC );

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::OnNcMouseHover(CWnd *pWnd, UINT nFlags, CPoint point, int darkIndicator)
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    //
    if ( CMCXColors::m_iDarkTheme != 2 && CMCXColors::m_iDarkTheme != darkIndicator )
    {
        return FALSE;
	}

    //  Always returns FALSE to continue the process
    if ( ScreenPointOverRect( pWnd, point, m_CloseRect ) )
    {
        if ( m_iHover != IDI_CLOSE )
        {
            DrawAllIcons ( pWnd, m_iHover );

            CDC* pDC = pWnd->GetWindowDC();
            if ( IDI_CLOSE != VAL_CLOSE )
            {
                DrawIcon ( pDC, IDI_CLOSE, m_CloseRect, true, CMCXColors::GetRedCBrush() );
            }
            else if ( hIcon_close_ico != NULL )
            {
                DrawIcon ( pDC, hIcon_close_ico, m_CloseRect, true, CMCXColors::GetRedCBrush() );
            }
            pWnd->ReleaseDC ( pDC );
            m_iHover    = IDI_CLOSE;
        }
        return FALSE;
    }
    else if ( ScreenPointOverRect( pWnd, point, m_MaximizeRect ) )
    {
        //
        DWORD dwStyle = pWnd->GetStyle();
        WINDOWPLACEMENT wp;
        pWnd->GetWindowPlacement( &wp );

        if ( m_iHover != IDI_MAXIMIZE )
        {
            DrawAllIcons ( pWnd, m_iHover );

            CDC* pDC = pWnd->GetWindowDC();
            if ( dwStyle & WS_MAXIMIZEBOX )
            {
                if ( wp.showCmd == SW_NORMAL )
                {
                    if ( IDI_MAXIMIZE != VAL_MAXIMIZE )
                    {
                        DrawIcon ( pDC, IDI_MAXIMIZE, m_MaximizeRect, true, CMCXColors::GetCyanCBrush() );
                    }
                    else if ( hIcon_maximize_ico != NULL )
                    {
                        DrawIcon ( pDC, hIcon_maximize_ico, m_MaximizeRect, true, CMCXColors::GetCyanCBrush() );
                    }
                }
                else
                {
                    if ( IDI_WINDOWED != VAL_WINDOWED )
                    {
                        DrawIcon ( pDC, IDI_WINDOWED, m_MaximizeRect, true, CMCXColors::GetCyanCBrush() );
                    }
                    else if ( hIcon_windowed_ico != NULL )
                    {
                        DrawIcon ( pDC, hIcon_windowed_ico, m_MaximizeRect, true, CMCXColors::GetCyanCBrush() );
                    }
                }
            }
            else
            {
                DrawIconFrame ( pDC, m_MaximizeRect, true, CMCXColors::GetBKNormalCBrush(CMCXColors::m_iDarkTheme != 0) );
            }
            pWnd->ReleaseDC ( pDC );
            m_iHover    = IDI_MAXIMIZE;
        }
        return FALSE;
    }
    else if ( ScreenPointOverRect( pWnd, point, m_MinimizeRect ) )
    {
        //
        DWORD dwStyle = pWnd->GetStyle();
        WINDOWPLACEMENT wp;
        pWnd->GetWindowPlacement( &wp );

        if ( m_iHover != IDI_MINIMIZE )
        {
            DrawAllIcons ( pWnd, m_iHover );

            CDC* pDC = pWnd->GetWindowDC();
            if ( dwStyle & WS_MINIMIZEBOX )
            {
                if ( IDI_MINIMIZE != VAL_MINIMIZE )
                {
                    DrawIcon ( pDC, IDI_MINIMIZE, m_MinimizeRect, true, CMCXColors::GetCyanCBrush() );
                }
                else if ( hIcon_minimize_ico ) 
                {
                    DrawIcon ( pDC, hIcon_minimize_ico, m_MinimizeRect, true, CMCXColors::GetCyanCBrush() );
                }
            }
            else
            {
                DrawIconFrame ( pDC, m_MinimizeRect, true, CMCXColors::GetBKNormalCBrush(CMCXColors::m_iDarkTheme != 0) );
            }
            pWnd->ReleaseDC ( pDC );
            m_iHover    = IDI_MINIMIZE;
        }
        return FALSE;
    }

    DrawAllIcons ( pWnd, m_iHover );
    m_iHover = ICON_NOT_SET;

    return FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::OnNcMouseLeave(CWnd *pWnd, int darkIndicator )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
		return FALSE;
	}

    //
    if ( CMCXColors::m_iDarkTheme != 2 && CMCXColors::m_iDarkTheme != darkIndicator )
    {
        return FALSE;
	}

    //  Always returns FALSE to continue the process
    DrawAllIcons ( pWnd, m_iHover );
    m_iHover        = ICON_NOT_SET;
    m_bLeftPressed  = FALSE;
    return FALSE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMenu *CMCXNCColor::GetSystemMenu(CWnd *pWnd, BOOL bRevert )
{
	if ( CMCXWinAppBase::OSVersionLowerThan ( 6, 1 ) )
	{
        CMenu *pMenu  = pWnd->GetSystemMenu ( bRevert );
        return pMenu;
	}

    //
    if ( CMCXColors::m_iDarkTheme != 2 )
    {
        //
        CMenu *pMenu  = pWnd->GetSystemMenu ( bRevert );
        return pMenu;
    }

    //
    CMenu *pMenu  = pWnd->GetSystemMenu ( bRevert );
    return pMenu;

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::InsertSystemMenu ( CWnd *pWnd, BOOL bRevert, UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem, LPCTSTR lpszNewItem )
{
    BOOL bInserted = FALSE;

    CMenu *pMenu  = GetSystemMenu ( pWnd, bRevert );
    if ( pMenu != NULL )
    {
        bInserted = pMenu->InsertMenu ( nPosition, nFlags, nIDNewItem, lpszNewItem );
    }

    return bInserted;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXNCColor::AppendSystemMenu ( CWnd *pWnd, BOOL bRevert, UINT nFlags, UINT_PTR nIDNewItem, LPCTSTR lpszNewItem )
{
    BOOL bAppended = FALSE;

    CMenu *pMenu  = GetSystemMenu ( pWnd, bRevert );
    if ( pMenu != NULL )
    {
        bAppended = pMenu->AppendMenu ( nFlags, nIDNewItem, lpszNewItem );
    }

    return bAppended;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
UINT CMCXNCColor::CheckSystemMenuItem ( CWnd *pWnd, BOOL bRevert, UINT nIDCheckItem, UINT nCheck )
{
    UINT result = 0;
    CMenu *pMenu  = GetSystemMenu ( pWnd, bRevert );
    if ( pMenu != NULL )
    {
        result = pMenu->CheckMenuItem ( nIDCheckItem, nCheck );
    }
    return result;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
UINT CMCXNCColor::GetSystemMenuState ( CWnd *pWnd, BOOL bRevert, UINT nID, UINT nFlags )
{
    UINT result = 0;
    CMenu *pMenu  = GetSystemMenu ( pWnd, bRevert );
    if ( pMenu != NULL )
    {
        result = pMenu->GetMenuState ( nID, nFlags );
    }

    return result;
}
