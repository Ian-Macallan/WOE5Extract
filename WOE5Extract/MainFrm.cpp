// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "WOE5Extract.h"
#include "WOE5ExtractDoc.h"
#include "WOE5ExtractView.h"
#include "PreferencesDialog.h"
#include <direct.h>

#include "MainFrm.h"

#include "../OE5Extract/OE5ExtractDefinitions.h"
#include "../OE5Extract/OEAddressRoutines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
///////////////////////////////////////////////////////////////////////////////
// CMainFrame
//
///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_COMMAND(ID_PREFERENCES, OnPreferences)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_LANGUAGE_ENGLISH, &CMainFrame::OnLanguageEnglish)
	ON_COMMAND(ID_LANGUAGE_FRENCH, &CMainFrame::OnLanguageFrench)
END_MESSAGE_MAP()

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

//
///////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
//
///////////////////////////////////////////////////////////////////////////////
CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	strDefaultDirectory = 
		theApp.GetProfileString ( "Settings", "Default Directory", NULL );
	if ( strDefaultDirectory == "" )
	{
		GetDirectoryOfIdentity ( );
		if ( *szDirectoryOfIdentity != 0 )
		{
			strDefaultDirectory = szDirectoryOfIdentity;
			if ( strDefaultDirectory != "" )
			{
				_chdir ( szDirectoryOfIdentity );
				theApp.WriteProfileString ( 
					"Settings", "Default Directory", strDefaultDirectory );
			}
		}
	}
	else
	{
		strcpy_s ( szDirectoryOfIdentity, 
				sizeof ( szDirectoryOfIdentity ), strDefaultDirectory );	
		_chdir ( szDirectoryOfIdentity );
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
CMainFrame::~CMainFrame()
{
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	int iPosition_x	= theApp.GetProfileInt ( "Settings", "Position x", -1 );
	int iPosition_y	= theApp.GetProfileInt ( "Settings", "Position y", -1 );
	int iSize_cx	= theApp.GetProfileInt ( "Settings", "Size cx", -1 );
	int iSize_cy	= theApp.GetProfileInt ( "Settings", "Size cy", -1 );

	if ( iPosition_x != -1 )
	{
		if ( ( iPosition_x < GetSystemMetrics ( SM_CXSCREEN ) ) && 
			 ( iPosition_y < GetSystemMetrics ( SM_CYSCREEN ) ) &&
			 ( iPosition_x > 0                                ) && 
			 ( iPosition_y > 0                                ) &&
			 ( iSize_cx    > 0                                ) && 
			 ( iSize_cy    > 0                                )    )
		{
			MoveWindow ( iPosition_x, iPosition_y, iSize_cx, iSize_cy, TRUE );
		}
	}

	theApp.SetMsgFilenameFormat ( );

	return 0;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

//
///////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics
//
///////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

//
///////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable ( FALSE );	
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable ( FALSE );	
	
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable ( FALSE );	
	
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable ( FALSE );	
	
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	if ( theApp.m_LoadingThread != NULL )
	{
		theApp.m_LoadingDialog.EndDialog ( 0 );
	}

	if ( theApp.m_ExtractingThread != NULL )
	{
		theApp.m_ExtractingDialog.EndDialog ( 0 );
	}

	if ( theApp.m_ProgressThread != NULL )
	{
		theApp.m_ProgressDialog.EndDialog ( 0 );
	}
	
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::GetDirectoryOfIdentity()
{

	// TODO: Add your specialized code here
	memset ( szDirectoryOfIdentity, 0, sizeof ( szDirectoryOfIdentity ) );

	RecurseRegistry ( HKEY_CURRENT_USER, "Identities" );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool CMainFrame::RecurseRegistry(HKEY hPreviousKey, char *pTemp)
{

	HKEY			hKey;
	DWORD			dwIndex;
	DWORD			dwLength;
	unsigned long	iLength;
	LONG			iLong; 
	char			szTemp [ LEN_LINE ];
	FILETIME		pLastWriteTime;

	//	Open Registry
	iLong = RegOpenKeyEx ( hPreviousKey, pTemp, NULL, KEY_READ, &hKey );
	if ( iLong != ERROR_SUCCESS )
	{
		return false;
	}

	iLength = sizeof ( szDirectoryOfIdentity ) - 1;
	iLong = RegQueryValueEx ( hKey, "Store Root", NULL, NULL, 
		( unsigned char * ) szDirectoryOfIdentity, &iLength );
	if ( iLong == ERROR_SUCCESS )
	{
		RegCloseKey ( hKey );
		return true;
	}

	memset ( szTemp, 0, sizeof ( szTemp ) );

	dwIndex = 0;
	do
	{
		dwLength = sizeof ( szTemp ) - 1;
		iLong = 
			RegEnumKeyEx (
				hKey, dwIndex, szTemp, &dwLength, NULL, NULL, NULL, &pLastWriteTime );
		if ( iLong != ERROR_SUCCESS )
		{
			RegCloseKey ( hKey );
			return false;
		}

		if ( RecurseRegistry ( hKey, szTemp ) )
		{
			RegCloseKey ( hKey );
			return true;
		}

		dwIndex++;

	}
	while ( iLong == ERROR_SUCCESS );

	RegCloseKey ( hKey );

	return false;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnClose() 
{
	SetAddressRoutinesCancel ( true );

	// TODO: Add your message handler code here and/or call default
	RECT	rectWindow;

	//		If iconic do not save geometry
	if ( IsIconic ( ) )
	{
		theApp.WriteProfileInt ( "Settings", "Iconic", 1 );
		theApp.WriteProfileInt ( "Settings", "Zoomed", 0 );
	}

	if ( IsZoomed () )
	{
		theApp.WriteProfileInt ( "Settings", "Iconic", 0 );
		theApp.WriteProfileInt ( "Settings", "Zoomed", 1 );
	}

	//	Reset thos flags
	if ( ! IsIconic ( ) && ! IsZoomed () )
	{
		theApp.WriteProfileInt ( "Settings", "Iconic", 0 );
		theApp.WriteProfileInt ( "Settings", "Zoomed", 0 );
	}

	//		Get the window
	GetWindowRect ( &rectWindow );
	if ( ( rectWindow.left < GetSystemMetrics ( SM_CXSCREEN ) ) && 
		 ( rectWindow.top  < GetSystemMetrics ( SM_CYSCREEN ) ) &&
		 ( rectWindow.left > 0                                ) &&
		 ( rectWindow.top  > 0                                ) &&
		 ( rectWindow.right - rectWindow.left > 0             ) &&
		 ( rectWindow.bottom - rectWindow.top > 0             )    )
	{
		theApp.WriteProfileInt ( "Settings", "Position x", rectWindow.left	);
		theApp.WriteProfileInt ( "Settings", "Position y", rectWindow.top );
		theApp.WriteProfileInt ( "Settings", "Size cx", rectWindow.right - rectWindow.left );
		theApp.WriteProfileInt ( "Settings", "Size cy", rectWindow.bottom - rectWindow.top );
	}

	CWOE5ExtractView* pView = ( CWOE5ExtractView * ) GetActiveView( );
	if ( pView != NULL )
	{
		pView->SaveColumnsPosition ( );
	}

	CFrameWnd::OnClose();

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnPreferences() 
{
	// TODO: Add your command handler code here
	CPreferencesDialog	dlgPref;
	
	if ( dlgPref.DoModal ( ) == IDOK )
	{
		theApp.SetMsgFilenameFormat ( );
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable ( theApp.m_ProgressThread == NULL );
	
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable ( theApp.m_ProgressThread == NULL );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnLanguageEnglish()
{
    //
	WORD wLanguageID = MAKELANGID(
		LANG_ENGLISH,		//	USHORT usPrimaryLanguage,  // primary language identifier
		SUBLANG_ENGLISH_US	//	USHORT usSubLanguage       // sublanguage identifier
	);

	//
	DWORD	dwLCID = MAKELCID(
	  wLanguageID,			//	WORD wLanguageID,  // language identifier
	  SORT_DEFAULT			//	WORD wSortID       // sorting identifier
	);

	//
	BOOL bSetted = SetThreadLocale ( 
		dwLCID		//	LCID Locale   // locale identifier
	);

    //
    LANGID oldLang =  SetThreadUILanguage( wLanguageID );

	//
	if ( m_Menu.m_hMenu != NULL )
	{
		m_Menu.DestroyMenu ( );
	}
	m_Menu.LoadMenu ( IDR_MAINFRAME );

   // Add the new menu
   SetMenu(&m_Menu);

   // Assign default menu
   m_hMenuDefault = m_Menu.GetSafeHmenu();  // or m_NewMenu.m_hMenu;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnLanguageFrench()
{
    //
	WORD wLanguageID = MAKELANGID(
		LANG_FRENCH,		//	USHORT usPrimaryLanguage,  // primary language identifier
		SUBLANG_FRENCH		//	USHORT usSubLanguage       // sublanguage identifier
	);

	//
	DWORD	dwLCID = MAKELCID(
	  wLanguageID,			//	WORD wLanguageID,  // language identifier
	  SORT_DEFAULT			//	WORD wSortID       // sorting identifier
	);

	//
	BOOL bSetted = SetThreadLocale (
		dwLCID		//	LCID Locale   // locale identifier
	);


    //
    LANGID oldLang =  SetThreadUILanguage( wLanguageID );

	//
	if ( m_Menu.m_hMenu != NULL )
	{
		m_Menu.DestroyMenu ( );
	}
	m_Menu.LoadMenu ( IDR_MAINFRAME );

	// Add the new menu
   SetMenu(&m_Menu);

   // Assign default menu
   m_hMenuDefault = m_Menu.GetSafeHmenu();  // or m_NewMenu.m_hMenu;

}
