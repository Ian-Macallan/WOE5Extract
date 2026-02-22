#include "stdafx.h"
#include "MCXColors.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
static DWORD rgbBlack           = RGB(0x00,0x00,0x00);
static DWORD rgbWhite           = RGB(0xFF,0xFF,0xFF);
static DWORD rgbGrey            = RGB(0x80,0x80,0x80);
static DWORD rgbGreyC0          = RGB(0xC0,0xC0,0xC0);

static DWORD rgbRed             = RGB(0xFF,0x00,0x00);
static DWORD rgbGreen           = RGB(0x00,0xFF,0x00);
static DWORD rgbBlue            = RGB(0x00,0x00,0xFF);

static DWORD rgbCyan            = RGB(0x00,0xFF,0xFF);
static DWORD rgbMagenta         = RGB(0xFF,0x00,0xFF);
static DWORD rgbYellow          = RGB(0xFF,0xFF,0x00);

static DWORD rgbBlack10         = RGB(0x10,0x10,0x10);
static DWORD rgbBlack20         = RGB(0x20,0x20,0x20);
static DWORD rgbBlack30         = RGB(0x30,0x30,0x30);
static DWORD rgbBlack40         = RGB(0x40,0x40,0x40);
static DWORD rgbWhiteCF         = RGB(0xCF,0xCF,0xCF);
static DWORD rgbWhiteDF         = RGB(0xDF,0xDF,0xDF);
static DWORD rgbWhiteEF         = RGB(0xEF,0xEF,0xEF);

static COLORREF crBlack         = COLORREF(rgbBlack);
static COLORREF crWhite         = COLORREF(rgbWhite);
static COLORREF crGrey          = COLORREF(rgbGrey);
static COLORREF crGreyC0        = COLORREF(rgbGreyC0);

static COLORREF crRed           = COLORREF(rgbRed);
static COLORREF crGreen         = COLORREF(rgbGreen);
static COLORREF crBlue          = COLORREF(rgbBlue);

static COLORREF crCyan          = COLORREF(rgbCyan);
static COLORREF crMagenta       = COLORREF(rgbMagenta);
static COLORREF crYellow        = COLORREF(rgbYellow);

static COLORREF crBlack10       = COLORREF(rgbBlack10);
static COLORREF crBlack20       = COLORREF(rgbBlack20);
static COLORREF crBlack30       = COLORREF(rgbBlack30);
static COLORREF crBlack40       = COLORREF(rgbBlack40);
static COLORREF crWhiteCF       = COLORREF(rgbWhiteCF);
static COLORREF crWhiteDF       = COLORREF(rgbWhiteDF);
static COLORREF crWhiteEF       = COLORREF(rgbWhiteEF);


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CBrush CMCXColors::BlackBrush;
CBrush CMCXColors::WhiteBrush;
CBrush CMCXColors::GreyBrush;

CBrush CMCXColors::RedBrush;
CBrush CMCXColors::GreenBrush;
CBrush CMCXColors::BlueBrush;

CBrush CMCXColors::CyanBrush;
CBrush CMCXColors::MagentaBrush;
CBrush CMCXColors::YellowBrush;

CBrush CMCXColors::Grey192Brush;

CBrush CMCXColors::Black10Brush;
CBrush CMCXColors::Black20Brush;
CBrush CMCXColors::Black30Brush;
CBrush CMCXColors::Black40Brush;
CBrush CMCXColors::WhiteCFBrush;
CBrush CMCXColors::WhiteDFBrush;
CBrush CMCXColors::WhiteEFBrush;

//
/////////////////////////////////////////////////////////////////////////////
//  0 Default Color
//  1 Dark Client Area
//  2 Dark Client Area and Caption
int             CMCXColors::m_iDarkTheme        = 0;
int             CMCXColors::m_iSquareCorner     = 0;

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXColors::CMCXColors(void)
{
}


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXColors::~CMCXColors(void)
{
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXColors::Instanciate()
{
    BOOL bBrush;

    //
    bBrush = BlackBrush.CreateSolidBrush ( crBlack );
    if ( bBrush )
    {
        BlackBrush.UnrealizeObject ( );
    }

    //
    bBrush = WhiteBrush.CreateSolidBrush ( crWhite );
    if ( bBrush )
    {
        WhiteBrush.UnrealizeObject ( );
    }

    //
    bBrush = GreyBrush.CreateSolidBrush ( crGrey );
    if ( bBrush )
    {
        GreyBrush.UnrealizeObject ( );
    }

    //
    bBrush = RedBrush.CreateSolidBrush ( crRed );
    if ( bBrush )
    {
        RedBrush.UnrealizeObject ( );
    }

    //
    //
    bBrush = GreenBrush.CreateSolidBrush ( crGreen );
    if ( bBrush )
    {
        GreenBrush.UnrealizeObject ( );
    }

    //
    //
    bBrush = BlueBrush.CreateSolidBrush ( crBlue );
    if ( bBrush )
    {
        BlueBrush.UnrealizeObject ( );
    }

    //
    bBrush = CyanBrush.CreateSolidBrush ( crCyan );
    if ( bBrush )
    {
        CyanBrush.UnrealizeObject ( );
    }

    //
    //
    bBrush = MagentaBrush.CreateSolidBrush ( crMagenta );
    if ( bBrush )
    {
        MagentaBrush.UnrealizeObject ( );
    }

    //
    //
    bBrush = YellowBrush.CreateSolidBrush ( crYellow );
    if ( bBrush )
    {
        YellowBrush.UnrealizeObject ( );
    }

    //
    bBrush = Grey192Brush.CreateSolidBrush ( crGreyC0 );
    if ( bBrush )
    {
        Grey192Brush.UnrealizeObject ( );
    }

    //
    bBrush = Black10Brush.CreateSolidBrush ( crBlack10 );
    if ( bBrush )
    {
        Black10Brush.UnrealizeObject ( );
    }

    //
    bBrush = Black20Brush.CreateSolidBrush ( crBlack20 );
    if ( bBrush )
    {
        Black20Brush.UnrealizeObject ( );
    }

    //
    bBrush = Black30Brush.CreateSolidBrush ( crBlack30 );
    if ( bBrush )
    {
        Black30Brush.UnrealizeObject ( );
    }

    //
    bBrush = Black40Brush.CreateSolidBrush ( crBlack40 );
    if ( bBrush )
    {
        Black40Brush.UnrealizeObject ( );
    }

    //
    bBrush = WhiteCFBrush.CreateSolidBrush ( crWhiteCF );
    if ( bBrush )
    {
        WhiteCFBrush.UnrealizeObject ( );
    }

    //
    bBrush = WhiteDFBrush.CreateSolidBrush ( crWhiteDF );
    if ( bBrush )
    {
        WhiteDFBrush.UnrealizeObject ( );
    }

    //
    bBrush = WhiteEFBrush.CreateSolidBrush ( crWhiteEF );
    if ( bBrush )
    {
        WhiteEFBrush.UnrealizeObject ( );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXColors::GetBlackBrush()
{
    return ( HBRUSH ) BlackBrush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetWhiteBrush()
{
    return ( HBRUSH ) WhiteBrush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetGreyBrush()
{
    return ( HBRUSH ) GreyBrush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetRedBrush()
{
    return ( HBRUSH ) RedBrush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetGreenBrush()
{
    return ( HBRUSH ) GreenBrush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetBlueBrush()
{
    return ( HBRUSH ) BlueBrush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetCyanBrush()
{
    return ( HBRUSH ) CyanBrush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetMagentaBrush()
{
    return ( HBRUSH ) MagentaBrush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetYellowBrush()
{
    return ( HBRUSH ) YellowBrush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetGreyC0Brush()
{
    return ( HBRUSH ) Grey192Brush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetBlack10Brush()
{
    return ( HBRUSH ) Black10Brush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetBlack20Brush()
{
    return ( HBRUSH ) Black20Brush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetBlack30Brush()
{
    return ( HBRUSH ) Black30Brush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetBlack40Brush()
{
    return ( HBRUSH ) Black40Brush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetWhiteCFBrush()
{
    return ( HBRUSH ) WhiteCFBrush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetWhiteDFBrush()
{
    return ( HBRUSH ) WhiteDFBrush.GetSafeHandle ( );
}

HBRUSH CMCXColors::GetWhiteEFBrush()
{
    return ( HBRUSH ) WhiteEFBrush.GetSafeHandle ( );
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CBrush *CMCXColors::GetBlackCBrush()
{
    return &BlackBrush;
}

CBrush *CMCXColors::GetWhiteCBrush()
{
    return &WhiteBrush;
}

CBrush *CMCXColors::GetGreyCBrush()
{
    return &GreyBrush;
}

CBrush *CMCXColors::GetRedCBrush()
{
    return &RedBrush;
}

CBrush *CMCXColors::GetGreenCBrush()
{
    return &GreenBrush;
}

CBrush *CMCXColors::GetBlueCBrush()
{
    return &BlueBrush;
}

CBrush *CMCXColors::GetCyanCBrush()
{
    return &CyanBrush;
}

CBrush *CMCXColors::GetMagentaCBrush()
{
    return &MagentaBrush;
}

CBrush *CMCXColors::GetYellowCBrush()
{
    return &YellowBrush;
}

CBrush *CMCXColors::GetGreyC0CBrush()
{
    return &Grey192Brush;
}

CBrush *CMCXColors::GetBlack10CBrush()
{
    return &Black10Brush;
}

CBrush *CMCXColors::GetBlack20CBrush()
{
    return &Black20Brush;
}

CBrush *CMCXColors::GetBlack30CBrush()
{
    return &Black30Brush;
}

CBrush *CMCXColors::GetBlack40CBrush()
{
    return &Black40Brush;
}

CBrush *CMCXColors::GetWhiteCFCBrush()
{
    return &WhiteCFBrush;
}

CBrush *CMCXColors::GetWhiteDFCBrush()
{
    return &WhiteDFBrush;
}

CBrush *CMCXColors::GetWhiteEFCBrush()
{
    return &WhiteEFBrush;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
COLORREF CMCXColors::GetBlackCR()
{
    return crBlack;
}

COLORREF CMCXColors::GetWhiteCR()
{
    return crWhite;
}

COLORREF CMCXColors::GetGreyCR()
{
    return crGrey;
}

COLORREF CMCXColors::GetRedCR()
{
    return crRed;
}

COLORREF CMCXColors::GetGreenCR()
{
    return crGreen;
}

COLORREF CMCXColors::GetBlueCR()
{
    return crBlue;
}

COLORREF CMCXColors::GetCyanCR()
{
    return crCyan;
}

COLORREF CMCXColors::GetMagentaCR()
{
    return crMagenta;
}

COLORREF CMCXColors::GetYellowCR()
{
    return crYellow;
}

COLORREF CMCXColors::GetGreyC0CR()
{
    return crGreyC0;
}

COLORREF CMCXColors::GetBlack10CR()
{
    return crBlack10;
}

COLORREF CMCXColors::GetBlack20CR()
{
    return crBlack20;
}

COLORREF CMCXColors::GetBlack30CR()
{
    return crBlack30;
}

COLORREF CMCXColors::GetBlack40CR()
{
    return crBlack40;
}

COLORREF CMCXColors::GetWhiteCFCR()
{
    return crWhiteCF;
}

COLORREF CMCXColors::GetWhiteDFCR()
{
    return crWhiteDF;
}

COLORREF CMCXColors::GetWhiteEFCR()
{
    return crWhiteEF;
}


//
/////////////////////////////////////////////////////////////////////////////
//
//  BUTTON, CLOCK, COMBOBOX, COMMUNICATIONS, CONTROLPANEL, DATEPICKER, DRAGDROP,
//  EDIT, EXPLORERBAR, FLYOUT, GLOBALS, HEADER, LISTBOX, LISTVIEW, MENU, MENUBAND,
//  NAVIGATION, PAGE, PROGRESS, REBAR, SCROLLBAR, SEARCHEDITBOX, SPIN, STARTPANEL,
//  STATUS, TAB, TASKBAND, TASKBAR, TASKDIALOG, TEXTSTYLE, TOOLBAR, TOOLTIP,
//  TRACKBAR, TRAYNOTIFY, TREEVIEW, WINDOW
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXColors::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = NULL;

    if ( CMCXColors::m_iDarkTheme == 0 )
    {
        return hBrush;
    }

    if ( pDC == NULL )
    {
        return hBrush;
    }

    //
    switch(nCtlColor)
    {
        case CTLCOLOR_MSGBOX :
        {
            pDC->SetTextColor(CMCXColors::GetWhiteCR());
            pDC->SetBkColor(CMCXColors::GetBlack30CR());
            pDC->SetBkMode ( TRANSPARENT );
            hBrush = CMCXColors::GetBlack30Brush();
            break;
        }

        case CTLCOLOR_EDIT:
        {
            pDC->SetTextColor(CMCXColors::GetWhiteCR());
            pDC->SetBkColor(CMCXColors::GetBlack10CR());
            pDC->SetBkMode ( TRANSPARENT );
            hBrush = CMCXColors::GetBlack10Brush();
            break;
        }

        case CTLCOLOR_LISTBOX:
        {
            pDC->SetTextColor(CMCXColors::GetWhiteCR());
            pDC->SetBkColor(CMCXColors::GetBlack30CR());
            pDC->SetBkMode ( TRANSPARENT );
            hBrush = CMCXColors::GetBlack20Brush();
            break;
        }

        case CTLCOLOR_BTN:
        {
            pDC->SetTextColor(CMCXColors::GetWhiteCR());
            pDC->SetBkColor(CMCXColors::GetBlack30CR());
            pDC->SetBkMode ( TRANSPARENT );
            hBrush = CMCXColors::GetBlack30Brush();
            break;
        }

        case CTLCOLOR_DLG:
        {
            pDC->SetTextColor(CMCXColors::GetWhiteCR());
            pDC->SetBkColor(CMCXColors::GetBlack30CR());
            pDC->SetBkMode ( TRANSPARENT );
            hBrush = CMCXColors::GetBlack30Brush();
            break;
        }

        case CTLCOLOR_SCROLLBAR:
        {
            pDC->SetTextColor(CMCXColors::GetWhiteCR());
            pDC->SetBkColor(CMCXColors::GetBlack30CR());
            pDC->SetBkMode ( TRANSPARENT );
            hBrush = CMCXColors::GetBlack30Brush();
            break;
        }

        //  Static And Read Only Edit
        case CTLCOLOR_STATIC:
        {
            pDC->SetTextColor(CMCXColors::GetWhiteCR());
            pDC->SetBkColor(CMCXColors::GetBlack30CR());
            //  Transparent makes scroll garbage
            // pDC->SetBkMode ( TRANSPARENT );
            hBrush = CMCXColors::GetBlack30Brush();
            break;
        }

        default :
        {
            pDC->SetTextColor(CMCXColors::GetWhiteCR());
            pDC->SetBkColor(CMCXColors::GetBlack30CR());
            pDC->SetBkMode ( TRANSPARENT );
            hBrush = CMCXColors::GetBlack30Brush();
            break;
        }
    }

    //
    return hBrush;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXColors::OnEraseBkgnd(CDC* pDC, CWnd* pWnd)
{
    if ( CMCXColors::m_iDarkTheme == 0 )
    {
        return FALSE;
    }

    if ( pDC == NULL )
    {
        return FALSE;
    }

    //
    RECT rectFrame;
    pWnd->GetClientRect ( &rectFrame );

    //
    pDC->FillRect ( &rectFrame, CMCXColors::GetBlack30CBrush() );

    //
    return TRUE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXColors::SetWindowTheme ( CWnd *pWnd )
{
    if ( CMCXColors::m_iSquareCorner == 1 )
    {
        if ( CMCXColors::m_iDarkTheme == 2 )
        {
            ::SetWindowTheme ( pWnd->GetSafeHwnd(), WINDOWS_THEME_SQUARE  );
        }
        else
        {
            ::SetWindowTheme ( pWnd->GetSafeHwnd(), WINDOWS_THEME_NULL  );
        }
    }
    else
    {
        ::SetWindowTheme ( pWnd->GetSafeHwnd(), WINDOWS_THEME_NULL  );
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//  Public
/////////////////////////////////////////////////////////////////////////////
//
//  Foreground COLORREF
COLORREF CMCXColors::GetFGNormalCR ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteDFCR();
    }
    else
    {
        return GetBlack20CR();
    }
}

COLORREF CMCXColors::GetFGSelectedCR ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteCR();
    }
    else
    {
        return GetBlackCR();
    }
}


COLORREF CMCXColors::GetFGDisabledCR ( bool bDark )
{
    if ( bDark )
    {
        return GetGreyCR();
    }
    else
    {
        return GetGreyCR();
    }
}

COLORREF CMCXColors::GetFGMenuCR ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteDFCR();
    }
    else
    {
        return GetBlack20CR();
    }
}

COLORREF CMCXColors::GetFGMenuSelectedCR ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteCR();
    }
    else
    {
        return GetBlackCR();
    }
}

COLORREF CMCXColors::GetFGHeaderCR ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteEFCR();
    }
    else
    {
        return GetBlack10CR();
    }
}

//
//  Background COLORREF
COLORREF CMCXColors::GetBKNormalCR ( bool bDark )
{
    return GetFGNormalCR ( ! bDark );
}

COLORREF CMCXColors::GetBKSelectedCR ( bool bDark )
{
    return GetFGSelectedCR ( ! bDark );
}

COLORREF CMCXColors::GetBKDisabledCR ( bool bDark )
{
    return GetFGDisabledCR ( ! bDark );
}

COLORREF CMCXColors::GetBKMenuCR ( bool bDark )
{
    return GetFGMenuCR ( ! bDark );
}

COLORREF CMCXColors::GetBKMenuSelectedCR ( bool bDark )
{
    return GetFGMenuSelectedCR ( ! bDark );
}

COLORREF CMCXColors::GetBKHeaderCR ( bool bDark )
{
    return GetFGHeaderCR ( ! bDark );
}

//  Foreground CBrush
CBrush * CMCXColors::GetFGNormalCBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteDFCBrush();
    }
    else
    {
        return GetBlack20CBrush();
    }
}

CBrush * CMCXColors::GetFGSelectedCBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteCBrush();
    }
    else
    {
        return GetBlackCBrush();
    }
}

CBrush * CMCXColors::GetFGDisabledCBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetGreyCBrush();
    }
    else
    {
        return GetGreyCBrush();
    }
}

CBrush * CMCXColors::GetFGMenuCBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteDFCBrush();
    }
    else
    {
        return GetBlack20CBrush();
    }
}

CBrush * CMCXColors::GetFGMenuSelectedCBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteCBrush();
    }
    else
    {
        return GetBlackCBrush();
    }
}

CBrush * CMCXColors::GetFGHeaderCBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteEFCBrush();
    }
    else
    {
        return GetBlack10CBrush();
    }
}

//
CBrush * CMCXColors::GetBKNormalCBrush ( bool bDark )
{
    return GetFGNormalCBrush ( ! bDark );
}

CBrush * CMCXColors::GetBKSelectedCBrush( bool bDark )
{
    return GetFGSelectedCBrush ( ! bDark );
}

CBrush * CMCXColors::GetBKDisabledCBrush ( bool bDark )
{
    return GetFGDisabledCBrush ( ! bDark );
}

CBrush * CMCXColors::GetBKMenuCBrush( bool bDark )
{
    return GetFGMenuCBrush ( ! bDark );
}

CBrush * CMCXColors::GetBKMenuSelectedCBrush( bool bDark )
{
    return GetFGMenuSelectedCBrush ( ! bDark );
}

CBrush * CMCXColors::GetBKHeaderCBrush( bool bDark )
{
    return GetFGHeaderCBrush ( ! bDark );
}

//  Foreground HBRUSH
HBRUSH CMCXColors::GetFGNormalBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteDFBrush();
    }
    else
    {
        return GetBlack20Brush();
    }
}

HBRUSH CMCXColors::GetFGSelectedBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteBrush();
    }
    else
    {
        return GetBlackBrush();
    }
}

HBRUSH CMCXColors::GetFGDisabledBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetGreyBrush();
    }
    else
    {
        return GetGreyBrush();
    }
}

HBRUSH CMCXColors::GetFGMenuBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteDFBrush();
    }
    else
    {
        return GetBlack20Brush();
    }
}

HBRUSH CMCXColors::GetFGMenuSelectedBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteBrush();
    }
    else
    {
        return GetBlackBrush();
    }
}

HBRUSH CMCXColors::GetFGHeaderBrush ( bool bDark )
{
    if ( bDark )
    {
        return GetWhiteEFBrush();
    }
    else
    {
        return GetBlack10Brush();
    }
}

//
HBRUSH CMCXColors::GetBKNormalBrush ( bool bDark )
{
    return GetFGNormalBrush ( ! bDark );
}

HBRUSH CMCXColors::GetBKSelectedBrush( bool bDark )
{
    return GetFGSelectedBrush ( ! bDark );
}

HBRUSH CMCXColors::GetBKDisabledBrush ( bool bDark )
{
    return GetFGDisabledBrush ( ! bDark );
}

HBRUSH CMCXColors::GetBKMenuBrush( bool bDark )
{
    return GetFGMenuBrush ( ! bDark );
}

HBRUSH CMCXColors::GetBKMenuSelectedBrush( bool bDark )
{
    return GetFGMenuSelectedBrush ( ! bDark );
}

HBRUSH CMCXColors::GetBKHeaderBrush( bool bDark )
{
    return GetFGHeaderBrush ( ! bDark );
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
COLORREF CMCXColors::GetFGTipColor(bool bDark)
{
    if ( bDark )
    {
        return CMCXColors::GetWhiteCR();
    }
    else
    {
        return NULL;
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
COLORREF CMCXColors::GetBKTipColor(bool bDark)
{
    if ( bDark )
    {
        return CMCXColors::GetBlackCR();
    }
    else
    {
        return NULL;
    }
}


