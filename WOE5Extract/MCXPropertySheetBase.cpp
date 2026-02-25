// MCXPropertySheetBase.cpp
//

#include "stdafx.h"
// #include "afxdialogex.h"
#include "MCXColors.h"
#include "MCXPropertySheetBase.h"
#include "MCXWinAppBase.h"

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////


//
/////////////////////////////////////////////////////////////////////////////
// Dialog Box CMCXPropertySheetBase
//
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMCXPropertySheetBase, CPropertySheet)

//
/////////////////////////////////////////////////////////////////////////////
CMCXPropertySheetBase::CMCXPropertySheetBase(UINT code) : CPropertySheet(code)
{
    m_bToolTip          = FALSE;

    m_pNormalFont       = NULL;
    m_pItalicFont       = NULL;
    m_pBoldFont         = NULL;
    m_pFixedFont        = NULL;
    m_pFixedBoldFont    = NULL;

    m_bInitDone         = false;
    m_bToolTip          = FALSE;

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXPropertySheetBase::~CMCXPropertySheetBase()
{
#define DELETE_OBJECT(o) if ( o != NULL ) { delete o; o = NULL; }

    //
    DELETE_OBJECT(m_pNormalFont)
    DELETE_OBJECT(m_pItalicFont)
    DELETE_OBJECT(m_pBoldFont)
    DELETE_OBJECT(m_pFixedFont)
    DELETE_OBJECT(m_pFixedBoldFont)

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXPropertySheetBase::DoDataExchange(CDataExchange* pDX)
{
    CPropertySheet::DoDataExchange(pDX);
}


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMCXPropertySheetBase, CPropertySheet)
    ON_WM_CTLCOLOR()
    ON_WM_ERASEBKGND()
    ON_WM_MEASUREITEM()
    ON_WM_DRAWITEM()
    ON_WM_DROPFILES()
END_MESSAGE_MAP()


//
/////////////////////////////////////////////////////////////////////////////
// Message handling of CMCXPropertySheetBase
//
/////////////////////////////////////////////////////////////////////////////


//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HBRUSH CMCXPropertySheetBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //
    HBRUSH hBrush = CMCXColors::OnCtlColor ( pDC, pWnd, nCtlColor );
    if ( hBrush != NULL )
    {
        return hBrush;
    }

    HBRUSH hbr = CPropertySheet::OnCtlColor(pDC, pWnd, nCtlColor);

    //
    return hbr;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXPropertySheetBase::OnEraseBkgnd(CDC* pDC)
{
    //
    if ( CMCXColors::OnEraseBkgnd(pDC, this) )
    {
        return TRUE;
    }
    return CPropertySheet::OnEraseBkgnd(pDC);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXPropertySheetBase::SetThemeChanged(bool bDarkTheme )
{
    if ( m_bToolTip )
    {
        m_ToolTip.SetColors ( );
    }

    if ( m_bInitDone )
    {
        Invalidate();
    }
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXPropertySheetBase::SetContextMenu ( CMCXMenuBase *pMenu )
{
    m_pContextMenu = pMenu;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXPropertySheetBase::OnInitDialog()
{
    CPropertySheet::OnInitDialog();


    //
    //
    TEXTMETRIC textMetrics;
    CDC *pDC = GetDC();
    GetTextMetrics ( pDC->m_hDC, &textMetrics );
    ReleaseDC ( pDC );

    //
    //  Create Fonts
    LOGFONT logDefaultFont;
    LOGFONT logFont;

    m_pNormalFont               = GetFont();
    m_pNormalFont->GetLogFont(&logDefaultFont);

    logFont                     = logDefaultFont;
    logFont.lfWeight            = FW_BOLD;
    m_pBoldFont                 = new CFont();
    m_pBoldFont->CreateFontIndirect(&logFont);    // Create the font.

    logFont                     = logDefaultFont;
    logFont.lfItalic            = TRUE;
    m_pItalicFont               = new CFont();
    m_pItalicFont->CreateFontIndirect(&logFont);    // Create the font.

    logFont                     = logDefaultFont;
    m_pFixedFont                = new CFont();
    logFont.lfPitchAndFamily    = FIXED_PITCH;
    logFont.lfHeight            = (LONG) ( (float) textMetrics.tmHeight * 1.10 );
    _tcscpy_s(logFont.lfFaceName, _wsizeof(logFont.lfFaceName), _T("Courier New") );
    m_pFixedFont->CreateFontIndirect(&logFont);    // Create the font.

    logFont                     = logDefaultFont;
    m_pFixedBoldFont            = new CFont();
    logFont.lfPitchAndFamily    = FIXED_PITCH;
    logFont.lfWeight            = FW_BOLD;
    logFont.lfHeight            = (LONG) ( (float) textMetrics.tmHeight * 1.10 );
    _tcscpy_s(logFont.lfFaceName, _wsizeof(logFont.lfFaceName), _T("Courier New") );
    m_pFixedBoldFont->CreateFontIndirect(&logFont);    // Create the font.

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

    //
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION : Pages with OCX should return FALSE
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXPropertySheetBase::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    //
    if ( lpMeasureItemStruct != NULL )
    {
        if ( lpMeasureItemStruct->CtlType == ODT_MENU )
        {
            if ( m_pContextMenu != NULL )
            {
                m_pContextMenu->MeasureItem(lpMeasureItemStruct);
                return;
            }
        }
    }

    //
    CPropertySheet::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CMCXPropertySheetBase::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    //
    if ( lpDrawItemStruct != NULL )
    {
        if ( lpDrawItemStruct->CtlType == ODT_MENU )
        {
            if ( m_pContextMenu != NULL )
            {
                m_pContextMenu->DrawItem(lpDrawItemStruct);
                return;
            }
        }
    }

    CPropertySheet::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

