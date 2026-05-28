#include "stdafx.h"
#include "MCXWinAppBase.h"
#include "MCXIcons.h"
#include "MCXColors.h"

WORD		     CMCXWinAppBase::OSVersion [ 4 ] = { 0, 0, 0, 0 };
//  Ex 0x00060001   for Windows 7
DWORD            CMCXWinAppBase::OSHVersion = 0L;
//  Release Details
DWORD            CMCXWinAppBase::OSLVersion = 0L;

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMCXWinAppBase, CWinApp)

#pragma comment (lib, "version.lib")

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXWinAppBase::CMCXWinAppBase(void)
{
    //
	//	Get OS Version
    OSHVersion  = 0;
    OSLVersion  = 0;
    ZeroMemory ( OSVersion, sizeof(OSVersion) );

    //
	const TCHAR *kernel32Dll = _T("kernel32.dll");
	DWORD dwHandle = NULL;
	DWORD dwLen = GetFileVersionInfoSize( kernel32Dll, &dwHandle);

	BYTE *lpData = (BYTE *) malloc ( dwLen );
	BOOL bInfoFound = GetFileVersionInfo( kernel32Dll, dwHandle, dwLen, lpData);
	VS_FIXEDFILEINFO *lpBuffer = NULL;
	if ( bInfoFound )
	{
		UINT uLen = 0;
		BOOL itemFound = VerQueryValueW ( lpData, L"\\", (LPVOID *)&lpBuffer, &uLen );
	}

	if ( lpBuffer != NULL )
	{
        OSHVersion      = lpBuffer->dwFileVersionMS;
        OSLVersion      = lpBuffer->dwFileVersionLS;

		OSVersion [ 0 ] = HIWORD(OSHVersion);
		OSVersion [ 1 ] = LOWORD(OSHVersion);
		OSVersion [ 2 ] = HIWORD(OSLVersion);
		OSVersion [ 3 ] = LOWORD(OSLVersion);
	}

	free ( lpData );

    //
    //  Create Icon From Memory
    CreateAllUsedIcons();

}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
CMCXWinAppBase::~CMCXWinAppBase(void)
{
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXWinAppBase::InitInstance()
{

    CWinApp::InitInstance();

    //
    GetModule();

    //
#define PROFILE_SETTING             _T("Settings")
#define PROFILE_DARKTHEME           _T("DarkTheme")
#define PROFILE_SQUARECORNER        _T("SquareCorner")

    CMCXColors::m_iDarkTheme            = GetProfileInt( PROFILE_SETTING, PROFILE_DARKTHEME, -1, 0 );
    CMCXColors::m_iSquareCorner         = GetProfileInt( PROFILE_SETTING, PROFILE_SQUARECORNER, -1, 0 );

    //  Instanciate Colors
    CMCXColors::Instanciate();

    return TRUE;
}

//
/////////////////////////////////////////////////////////////////////////////
//  Strictly Lower
/////////////////////////////////////////////////////////////////////////////
bool CMCXWinAppBase::OSVersionLowerThan ( WORD major, WORD minor )
{
    if ( OSVersion [ 0 ] < major )
    {
        return true;
    }

    if ( OSVersion [ 0 ] == major && OSVersion [ 1 ] < minor )
    {
        return true;
    }

    return false;
}

//
/////////////////////////////////////////////////////////////////////////////
//  Greater Or Equal
/////////////////////////////////////////////////////////////////////////////
bool CMCXWinAppBase::OSVersionGreaterThan ( WORD major, WORD minor )
{
    if ( OSVersion [ 0 ] > major )
    {
        return true;
    }

    if ( OSVersion [ 0 ] == major && OSVersion [ 1 ] >= minor )
    {
        return true;
    }

    return false;
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
BOOL CMCXWinAppBase::WriteProfileIniFile ( const TCHAR *section,  const TCHAR *keyName, const TCHAR *pValue )
{
    // 
    // WritePrivateProfileSection  could be used to delete a section;

    BOOL bWritten =
        WritePrivateProfileString (
            section,            //  __in  LPCTSTR lpAppName,
            keyName,            //  __in  LPCTSTR lpKeyName,
            pValue,             //  __in  LPCTSTR lpString,
            InitFileName        //  __in  LPCTSTR lpFileName
        );
    if ( bWritten <= 0 )
    {
        return FALSE;
    }

    return TRUE;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMCXWinAppBase::EndsWithI ( const TCHAR *pText, const TCHAR *pEnd )
{
    if ( _tcslen(pText) >= _tcslen(pEnd) )
    {
        if ( _tcsicmp ( pText + _tcslen(pText) - _tcslen(pEnd), pEnd ) == 0 )
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
TCHAR *CMCXWinAppBase::RemoveFileType ( TCHAR *pText )
{
    for ( int i = (int) _tcslen(pText) - 1; i >= 0 ; i-- )
    {
        if ( pText [ i ] == _T('.') )
        {
            pText [ i ] = _T('\0');
            return pText;
        }

        if ( pText [ i ] == _T('\\') || pText [ i ] == _T('/') || pText [ i ] == _T(':') )
        {
            return pText;
        }
    }

    return pText;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
const TCHAR *CMCXWinAppBase::FindFileName ( const TCHAR *pText )
{
    for ( int i = (int) _tcslen(pText) - 1; i >= 0 ; i-- )
    {
        if ( pText [ i ] == '\\' || pText [ i ] == '/' )
        {
            return pText + i + 1;
        }
        if ( pText [ i ] == ':' )
        {
            return pText + i + 1;
        }
    }

    return pText;
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
BOOL CMCXWinAppBase::WriteProfileInt ( const TCHAR *section,  const TCHAR *keyName, int value, bool bHexa )
{
    TCHAR szText [ 64 ];
    if ( bHexa )
    {
        _stprintf_s ( szText, sizeof(szText) / sizeof(TCHAR), _T("0x%x"), value );
    }
    else
    {
        _stprintf_s ( szText, sizeof(szText) / sizeof(TCHAR), _T("%d"), value );
    }
    return WriteProfileIniFile ( section, keyName, szText );
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
BOOL CMCXWinAppBase::WriteProfileLong ( const TCHAR *section,  const TCHAR *keyName, long value, bool bHexa )
{
    TCHAR szText [ 64 ];
    if ( bHexa )
    {
        _stprintf_s ( szText, sizeof(szText) / sizeof(TCHAR), _T("0x%lx"), value );
    }
    else
    {
        _stprintf_s ( szText, sizeof(szText) / sizeof(TCHAR), _T("%ld"), value );
    }
    return WriteProfileIniFile ( section, keyName, szText );
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
BOOL CMCXWinAppBase::WriteProfileDouble ( const TCHAR *section, const TCHAR *keyName, double value )
{
    TCHAR szText [ 64 ];
    _stprintf_s ( szText, sizeof(szText) / sizeof(TCHAR), _T("%f"), value );
    return WriteProfileIniFile ( section, keyName, szText );
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
BOOL CMCXWinAppBase::WriteProfileString ( const TCHAR *section,  const TCHAR *keyName, const TCHAR *pValue )
{
    return WriteProfileIniFile ( section, keyName, pValue );
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
BOOL CMCXWinAppBase::ReadProfileIniFile (   const TCHAR *section, const TCHAR *keyName, TCHAR *pValue, size_t iValue,
                                            const TCHAR *pDefault )
{
    ZeroMemory ( pValue, iValue * sizeof(char) );

    DWORD dwResult =
        GetPrivateProfileString(
            section,                        //  __in   LPCTSTR lpAppName,
            keyName,                        //  __in   LPCTSTR lpKeyName,
            pDefault,                       //  __in   LPCTSTR lpDefault,
            pValue,                         //  __out  LPTSTR lpReturnedString,
            (DWORD) iValue,                 //  __in   DWORD nSize,
            InitFileName                    //  __in   LPCTSTR lpFileName
        );
    if ( dwResult <= 0 )
    {
        return FALSE;
    }

    return TRUE;
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
UINT CMCXWinAppBase::GetProfileInt ( const TCHAR *section,  const TCHAR *keyName, int defaultValue )
{
    UINT result = 0;
    TCHAR szText [ 64 ];
    TCHAR szDefault [ 64 ];
    _stprintf_s ( szText, sizeof(szText) / sizeof(TCHAR), _T("%d"), defaultValue );
    _tcscpy_s ( szDefault, szText );
    BOOL bRead = ReadProfileIniFile ( section, keyName, szText, sizeof(szText), szDefault );
    if ( ! bRead )
    {
        return defaultValue;
    }
    if ( _tcsnicmp ( szText, _T("0x"), _tcslen(_T("0x")) ) == 0 )
    {
        int iResult    = 0;
        _stscanf_s ( szText + 2, _T("%x"), &iResult );
        result      = (UINT) iResult;
    }
    else if (  _tcsnicmp ( szText, _T("x"), _tcslen(_T("x")) ) == 0 )
    {
        int iResult    = 0;
        _stscanf_s ( szText + 1, _T("%x"), &iResult );
        result      = (UINT) iResult;
    }
    else
    {
        result = (UINT) _tstoi ( szText );
    }
    return result;
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
UINT CMCXWinAppBase::GetProfileInt ( const TCHAR *section,  const TCHAR *keyName, int novalue, int defaultValue )
{
    int value = (int) GetProfileInt ( section, keyName, novalue );
    if ( value == novalue )
    {
        WriteProfileInt ( section, keyName, defaultValue );
        value = defaultValue;
    }
    return (UINT) value;
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
ULONG CMCXWinAppBase::GetProfileLong ( const TCHAR *section,  const TCHAR *keyName, int defaultValue )
{
    ULONG result = 0;
    TCHAR szText [ 64 ];
    TCHAR szDefault [ 64 ];
    _stprintf_s ( szText, sizeof(szText) / sizeof(TCHAR), _T("%d"), defaultValue );
    _tcscpy_s ( szDefault, szText );
    BOOL bRead = ReadProfileIniFile ( section, keyName, szText, sizeof(szText), szDefault );
    if ( ! bRead )
    {
        return defaultValue;
    }
    if ( _tcsnicmp ( szText, _T("0x"), _tcslen(_T("0x")) ) == 0 )
    {
        long lResult    = 0;
        _stscanf_s ( szText + 2, _T("%lx"), &lResult );
        result      = (UINT) lResult;
    }
    else if ( _tcsnicmp ( szText, _T("x"), _tcslen(_T("x")) ) == 0 )
    {
        long lResult    = 0;
        _stscanf_s ( szText + 1, _T("%lx"), &lResult );
        result      = (UINT) lResult;
    }
    else
    {
        result = (ULONG) _tstol ( szText );
    }
    return result;
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
double CMCXWinAppBase::GetProfileDouble ( const TCHAR *section,  const TCHAR *keyName, double defaultValue )
{
    double result = 0;

    TCHAR szText [ 64 ];
    TCHAR szDefault [ 64 ];
    _stprintf_s ( szText, sizeof(szText) / sizeof(TCHAR), _T("%f"), defaultValue );
    _tcscpy_s ( szDefault, szText );
    BOOL bRead = ReadProfileIniFile ( section, keyName, szText, _wsizeof(szText), szDefault );
    if ( ! bRead )
    {
        return defaultValue;
    }
    result = _tstof ( szText );

    return result;
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
CString CMCXWinAppBase::GetProfileString ( const TCHAR *section,  const TCHAR *keyName, const TCHAR *pDefaultValue,
                                            TCHAR *pTarget, size_t iTarget )
{
    if ( pDefaultValue == NULL )
    {
        pDefaultValue = _T("");
    }
    CString result;

    TCHAR szText [ MAX_PATH ];
    _tcscpy_s ( szText, sizeof(szText) / sizeof(TCHAR), pDefaultValue );
    BOOL bRead = ReadProfileIniFile ( section, keyName, szText, sizeof(szText), pDefaultValue );
    if ( ! bRead )
    {
        return pDefaultValue;
    }

    result = szText;

    if ( pTarget != NULL && iTarget > 0 )
    {
        _tcscpy_s ( pTarget, iTarget, result );
    }

    return result;
}


//
////////////////////////////////////////////////////////////////////////
//      Search Init File
////////////////////////////////////////////////////////////////////////
bool CMCXWinAppBase::SearchInitFile ( const TCHAR *pInitFileName, size_t iInitFileName )
{
    static TCHAR initName [ MAX_PATH ];
    static TCHAR initPathName [ MAX_PATH ];
    TCHAR  *pVariable      = NULL;
    size_t  requiredSize    = 0;

    _tcscpy_s ( initName, sizeof(initName) / sizeof(TCHAR), FindFileName ( pInitFileName ) );

    //
    //      First If ini file is here.
    if ( PathFileExists ( pInitFileName ) )
    {
        return true;
    }

    //
    //      Then Search Environnement
    _tgetenv_s ( &requiredSize, NULL, 0, _T("PATH") );
    if ( requiredSize == 0 )
    {
        return false;
    }

    //
    size_t  iVariable   = ( requiredSize + 1 ) * sizeof(TCHAR) + 1;
    pVariable   = ( TCHAR * ) malloc ( iVariable );

    _tgetenv_s ( &requiredSize, pVariable, requiredSize + 1, _T("PATH") );

    //      Treat Token for PATH
    TCHAR   strDelimit[]    = _T(";");
    TCHAR   *strToken       = NULL;
    TCHAR   *context        = NULL;

    //
    //      Treat Tokens
    strToken = _tcstok_s ( pVariable, strDelimit, &context);
    while( strToken != NULL )
    {
        //
        //      Test Filename
        _tcscpy_s ( initPathName, sizeof(initPathName) / sizeof(TCHAR), strToken );
        if ( ( _tcslen(initPathName) > 0 ) && ( initPathName [ _tcslen(initPathName) - 1 ] != _T('\\') ) )
        {
            _tcscat_s ( initPathName, sizeof(initPathName) / sizeof(TCHAR), _T("\\") );
        }
        _tcscat_s ( initPathName, sizeof(initPathName) / sizeof(TCHAR), initName );

        if ( PathFileExists ( initPathName ) )
        {
            _tcscpy_s ( InitFileName, iInitFileName, initPathName );
            free ( pVariable );
            return true;
        }

        //      Get next token:
        strToken = _tcstok_s( NULL, strDelimit, &context);
    }

    free ( pVariable );

    return false;
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
void CMCXWinAppBase::GetModule ()
{
    DWORD dwResult =
        GetModuleFileName ( NULL,                                       //  __in_opt  HMODULE hModule,
                            ModuleFileName,                             //  __out     LPTSTR lpFilename,
                            sizeof(ModuleFileName) / sizeof(TCHAR)      //  __in      DWORD nSize
                            );
    _tcscpy_s ( InitFileName, sizeof(InitFileName) / sizeof(TCHAR), ModuleFileName );

    const TCHAR *Endx64 = _T("x64.exe") ;
    const TCHAR *Endx86 = _T("x86.exe") ;
    const TCHAR *End64  = _T("64.exe") ;
    const TCHAR *End86  = _T("86.exe") ;

    BOOL endsWithX64    = EndsWithI ( InitFileName, Endx64 );
    BOOL endsWithX86    = EndsWithI ( InitFileName, Endx86 );
    BOOL endsWith64     = EndsWithI ( InitFileName, End64 );
    BOOL endsWith86     = EndsWithI ( InitFileName, End86 );
    if ( endsWithX64 )
    {
        InitFileName [ _tcslen(InitFileName) - _tcslen( Endx64 ) ] = _T('\0');
    }
    else if ( endsWithX86 )
    {
        InitFileName [ _tcslen(InitFileName) - _tcslen( Endx86 ) ] = _T('\0');
    }
    else if ( endsWith64 )
    {
        InitFileName [ _tcslen(InitFileName) - _tcslen( End64 ) ] = _T('\0');
    }
    else if ( endsWith86 )
    {
        InitFileName [ _tcslen(InitFileName) - _tcslen( End86 ) ] = _T('\0');
    }
    else
    {
        RemoveFileType ( InitFileName );
    }

    _tcscat_s ( InitFileName, sizeof(InitFileName) / sizeof(TCHAR), _T(".ini") );

    //
    //      Search Init File and in Path
    SearchInitFile ( InitFileName, sizeof(InitFileName) / sizeof(TCHAR) );

    return;

}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
CFont *CMCXWinAppBase::CreateNormalFont(CWnd *pWnd)
{
    //
    //  Create Fonts
    LOGFONT logFont;

    CFont *pNormalFont               = pWnd->GetFont();
    if ( pNormalFont == NULL )
    {
        pNormalFont = new CFont();

        memset ( &logFont, 0, sizeof(logFont) );
        logFont.lfHeight    = -11;
        logFont.lfWeight    = 400;
        // logFont.lfCharSet   = 0x1;
        _tcscpy_s(logFont.lfFaceName, _wsizeof(logFont.lfFaceName), _T("Tahoma") );
        _tcscpy_s(logFont.lfFaceName, _wsizeof(logFont.lfFaceName), _T("Segoe UI") );
        _tcscpy_s(logFont.lfFaceName, _wsizeof(logFont.lfFaceName), _T("Arial") );
        pNormalFont->CreateFontIndirect(&logFont);
        return pNormalFont;
    }

    pNormalFont->GetLogFont(&logFont);
    pNormalFont = new CFont();
    pNormalFont->CreateFontIndirect(&logFont);

    return pNormalFont;

}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
CFont *CMCXWinAppBase::CreateBoldFont(CWnd *pWnd, CFont *pNormalFont)
{
    if ( pNormalFont == NULL )
    {
        return NULL;
    }

    //
    //  Create Fonts
    LOGFONT logDefaultFont;
    LOGFONT logFont;

    pNormalFont->GetLogFont(&logDefaultFont);

    logFont                     = logDefaultFont;
    logFont.lfWeight            = FW_BOLD;
    CFont *pBoldFont            = new CFont();
    pBoldFont->CreateFontIndirect(&logFont);    // Create the font.

    return pBoldFont;
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
CFont *CMCXWinAppBase::CreateItalicFont(CWnd *pWnd, CFont *pNormalFont)
{
    if ( pNormalFont == NULL )
    {
        return NULL;
    }

    //
    //  Create Fonts
    LOGFONT logDefaultFont;
    LOGFONT logFont;

    pNormalFont->GetLogFont(&logDefaultFont);

    logFont                     = logDefaultFont;
    logFont.lfItalic            = TRUE;
    CFont *pItalicFont          = new CFont();
    pItalicFont->CreateFontIndirect(&logFont);    // Create the font.

    return pItalicFont;

}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
CFont *CMCXWinAppBase::CreateFixedFont(CWnd *pWnd, CFont *pNormalFont)
{
    if ( pNormalFont == NULL )
    {
        return NULL;
    }

    //
    TEXTMETRIC textMetrics;
    CDC *pDC = pWnd->GetDC();
    GetTextMetrics ( pDC->m_hDC, &textMetrics );
    pWnd->ReleaseDC ( pDC );

    //  Create Fonts
    LOGFONT logDefaultFont;
    LOGFONT logFont;

    pNormalFont->GetLogFont(&logDefaultFont);

    logFont                     = logDefaultFont;
    CFont *pFixedFont           = new CFont();
    logFont.lfPitchAndFamily    = FIXED_PITCH;
    logFont.lfHeight            = (LONG) ( (float) textMetrics.tmHeight * 1.10 );
    _tcscpy_s(logFont.lfFaceName, _wsizeof(logFont.lfFaceName), _T("Courier New"));
    pFixedFont->CreateFontIndirect(&logFont);    // Create the font.

    return pFixedFont;

}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
CFont *CMCXWinAppBase::CreateFixedBoldFont(CWnd *pWnd, CFont *pNormalFont)
{
    if ( pNormalFont == NULL )
    {
        return NULL;
    }

    //
    TEXTMETRIC textMetrics;
    CDC *pDC = pWnd->GetDC();
    GetTextMetrics ( pDC->m_hDC, &textMetrics );
    pWnd->ReleaseDC ( pDC );

    //  Create Fonts
    LOGFONT logDefaultFont;
    LOGFONT logFont;

    pNormalFont->GetLogFont(&logDefaultFont);

    logFont                     = logDefaultFont;
    CFont *pFixedBoldFont       = new CFont();
    logFont.lfPitchAndFamily    = FIXED_PITCH;
    logFont.lfWeight            = FW_BOLD;
    logFont.lfHeight            = (LONG) ( (float) textMetrics.tmHeight * 1.10 );
    _tcscpy_s(logFont.lfFaceName, _wsizeof(logFont.lfFaceName), _T("Courier New"));
    pFixedBoldFont->CreateFontIndirect(&logFont);    // Create the font.

    return pFixedBoldFont;
}

//
////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
BOOL CALLBACK CMCXWinAppBase::EnumChildProc(HWND hwnd, LPARAM lParam)
{
    TCHAR szClassName[64]   =  _T("");
    TCHAR szText[128]       =  _T("");
    TCHAR szOwnerDraw[32]   =  _T("");

    GetClassName(hwnd, szClassName, _wsizeof(szClassName));
    GetWindowText(hwnd, szText, _wsizeof(szText));

    int id          = GetDlgCtrlID(hwnd);
    LONG oldStyle   = GetWindowLong(hwnd, GWL_STYLE);
    LONG newStyle   = oldStyle;

#ifdef _DEBUG
    // BS_OWNERDRAW = 0x0B
    //  For Buttom Only
    if ( _tcscmp ( szClassName, _T("Button") ) == 0 )
    {
        if ( ( oldStyle & BS_OWNERDRAW ) != 0 )
        {
            _tcscpy_s ( szOwnerDraw, _wsizeof(szOwnerDraw), _T("BS_OWNERDRAW") );
            newStyle    ^= BS_OWNERDRAW;
        }

        if ( false )
        {
            if ( CMCXColors::m_iDarkTheme == 0 )
            {
                SetWindowLong(hwnd, GWL_STYLE, newStyle );
            }
        }
    }

    //
    static TCHAR szDebugString [ MAX_PATH ];
    _stprintf_s ( szDebugString, _wsizeof(szDebugString), _T("EnumChildProc %d '%s' (%s) 0x%lx (%s)\n"), 
        id, szText, szClassName, oldStyle, szOwnerDraw );
    OutputDebugString ( szDebugString );
#endif

    return TRUE; // continue
}
