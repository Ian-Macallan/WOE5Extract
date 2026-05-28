#pragma once

//
///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////
class CMCXWinAppBase : public CWinApp
{
    DECLARE_DYNAMIC(CMCXWinAppBase)

    //
    protected :
        TCHAR           ModuleFileName [ MAX_PATH ];
        TCHAR           InitFileName [ MAX_PATH ];

	public :
		static WORD		        OSVersion [ 4 ];
        //  Ex 0x00060001   for Windows 7
        static DWORD            OSHVersion;
        //  Release Details
        static DWORD            OSLVersion;


    public:
        CMCXWinAppBase(void);
        ~CMCXWinAppBase(void);

        virtual BOOL InitInstance();

        void GetModule ();
        bool SearchInitFile ( const TCHAR *pInitFileName, size_t iInitFileName );

        BOOL WriteProfileIniFile ( const TCHAR *section,  const TCHAR *keyName, const TCHAR *pValue );
        BOOL ReadProfileIniFile ( const TCHAR *section,  const TCHAR *keyName, TCHAR *pValue, size_t iValue, const TCHAR *pDefault );

        UINT GetProfileInt ( const TCHAR *section,  const TCHAR *keyName, int defaultValue );
        UINT GetProfileInt ( const TCHAR *section,  const TCHAR *keyName, int novalue, int defaultValue );
        ULONG GetProfileLong ( const TCHAR *section,  const TCHAR *keyName, int defaultValue );
        double GetProfileDouble ( const TCHAR *section,  const TCHAR *keyName, double defaultValue );
        CString GetProfileString ( const TCHAR *section,  const TCHAR *keyName, const TCHAR *pDefaultValue = _T(""),
                                    TCHAR *pTarget = NULL, size_t iTarget = 0 );

        BOOL WriteProfileLong ( const TCHAR *section,  const TCHAR *keyName, long value, bool bHexa = false );
        BOOL WriteProfileInt ( const TCHAR *section,  const TCHAR *keyName, int value, bool bHexa = false );
        BOOL WriteProfileDouble ( const TCHAR *section,  const TCHAR *keyName, double value );
        BOOL WriteProfileString ( const TCHAR *section,  const TCHAR *keyName, const TCHAR *pValue );

        static const TCHAR *FindFileName ( const TCHAR *pText );
        static TCHAR *RemoveFileType ( TCHAR *pText );
        static BOOL EndsWithI ( const TCHAR *pText, const TCHAR *pEnd );

        //  Strictly Lower
        static bool OSVersionLowerThan ( WORD major, WORD minor );

        //  Greater Or Equal
        static bool OSVersionGreaterThan ( WORD major, WORD minor );

        //
        static CFont *CreateNormalFont( CWnd *pWnd );
        static CFont *CreateBoldFont( CWnd *pWnd, CFont *pNormalFont );
        static CFont *CreateItalicFont( CWnd *pWnd, CFont *pNormalFont );
        static CFont *CreateFixedFont( CWnd *pWnd, CFont *pNormalFont );
        static CFont *CreateFixedBoldFont( CWnd *pWnd, CFont *pNormalFont );

        static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);

};

