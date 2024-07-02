// WOE5Extract.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <Windows.h>
#include <afx.h>

#include "resource.h"

#include "WOE5Extract.h"

#include "MainFrm.h"
#include "WOE5ExtractDoc.h"
#include "WOE5ExtractView.h"

#include "../OE5Extract/OEMessagesRoutines.h"
#include "../OE5Extract/DecodeRoutines.h"

#include "AutomaticVersionHeader.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
///////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractApp
//
///////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CWOE5ExtractApp, CWinApp)
    //{{AFX_MSG_MAP(CWOE5ExtractApp)
    ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
    // Standard file based document commands
    ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
    // Standard print setup command
    ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

//
/////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractApp construction
//
/////////////////////////////////////////////////////////////////////////////
CWOE5ExtractApp::CWOE5ExtractApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
    m_LoadingThread = NULL;
    m_ExtractingThread = NULL;
    m_ProgressThread = NULL;
}

//
/////////////////////////////////////////////////////////////////////////////
// The one and only CWOE5ExtractApp object
//
/////////////////////////////////////////////////////////////////////////////
CWOE5ExtractApp theApp;

//
/////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractApp initialization
//
/////////////////////////////////////////////////////////////////////////////
BOOL CWOE5ExtractApp::InitInstance()
{
    AfxEnableControlContainer();

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#ifdef _AFXDLL
//  Enable3dControls();         // Call this when using MFC in a shared DLL
#else
//  Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif

    // Change the registry key under which our settings are stored.
    // TODO: You should modify this string to be something appropriate
    // such as the name of your company or organization.
    SetRegistryKey(_T(PROGRAM_REGKEY));

    //
    //  Necessary To open files directly
    HRESULT  hRes = CoInitialize(NULL);

#if 0
    WORD wLanguageID = MAKELANGID(
        LANG_ENGLISH,       //  USHORT usPrimaryLanguage,  // primary language identifier
        SUBLANG_ENGLISH_US  //  USHORT usSubLanguage       // sublanguage identifier
    );

    //
    DWORD   dwLCID = MAKELCID(
      wLanguageID,          //  WORD wLanguageID,  // language identifier
      SORT_DEFAULT          //  WORD wSortID       // sorting identifier
    );

    //
    BOOL bSetted = SetThreadLocale (
        dwLCID      //  LCID Locale   // locale identifier
    );
#endif

    int iMRU = GetProfileInt ( "Settings", "Most Recently Used Files Count", -1 );
    if ( iMRU == -1 )
    {
        LoadStdProfileSettings();  // Load standard INI file options (including MRU)
        WriteProfileInt ( "Settings", "Most Recently Used Files Count", _AFX_MRU_COUNT );
    }
    else
    {
        LoadStdProfileSettings(iMRU);  // Load standard INI file options (including MRU)
    }

    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views.
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CWOE5ExtractDoc),
        RUNTIME_CLASS(CMainFrame),       // main SDI frame window
        RUNTIME_CLASS(CWOE5ExtractView));
    AddDocTemplate(pDocTemplate);

    // Enable DDE Execute open
    if ( GetProfileInt ( "Settings", "Filetype Association", FALSE ) )
    {
        EnableShellOpen();
        RegisterShellFileTypes( TRUE );
    }

    // Parse command line for standard shell commands, DDE, file open
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // Dispatch commands specified on the command line
    // cmdInfo.m_nShellCommand = CCommandLineInfo::FileNew;
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    // The one and only window has been initialized, so show and update it.
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();

    // Enable drag/drop open
    m_pMainWnd->DragAcceptFiles();

    return TRUE;
}

//
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
//
/////////////////////////////////////////////////////////////////////////////
class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    CButton m_Http;
    CButton m_MailTo;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    afx_msg void OnHttp();
    afx_msg void OnMailto();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
    CStatic m_Version_Name;
    CStatic m_Version_Date;
    virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    DDX_Control(pDX, IDC_HTTP, m_Http);
    DDX_Control(pDX, IDC_MAILTO, m_MailTo);
    DDX_Control(pDX, IDC_VERSION_NAME, m_Version_Name);
    DDX_Control(pDX, IDC_VERSION_DATE, m_Version_Date);
    //}}AFX_DATA_MAP
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    ON_BN_CLICKED(IDC_HTTP, OnHttp)
    ON_BN_CLICKED(IDC_MAILTO, OnMailto)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
/////////////////////////////////////////////////////////////////////////////
// App command to run the dialog
//
/////////////////////////////////////////////////////////////////////////////
void CWOE5ExtractApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

//
/////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractApp message handlers
//
/////////////////////////////////////////////////////////////////////////////
void CAboutDlg::OnHttp()
{
    // TODO: Add your control notification handler code here
    HINSTANCE           hInst;

    CString strPathname;
    m_Http.GetWindowText ( strPathname );
    hInst = ShellExecute ( NULL, "open", strPathname, "", "", SW_SHOWDEFAULT );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CAboutDlg::OnMailto()
{
    // TODO: Add your control notification handler code here
    HINSTANCE           hInst;

    CString strPathname;
    m_MailTo.GetWindowText ( strPathname );

    hInst = ShellExecute ( NULL, "open", strPathname, "", "", SW_SHOWDEFAULT );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CWOE5ExtractApp::SetMsgFilenameFormat()
{
    SetNameFormat ( 
        GetProfileInt ( "Settings", "Message Filename Value 1", MSG_NAME_OBJECT ),
        GetProfileInt ( "Settings", "Message Filename Value 2", MSG_NAME_MESSAGE_ID ),
        GetProfileInt ( "Settings", "Message Filename Value 3", MSG_NAME_NONE ),
        GetProfileInt ( "Settings", "Message Filename Value 4", MSG_NAME_NONE ),
        GetProfileInt ( "Settings", "Message Filename Size 1", 127 ),
        GetProfileInt ( "Settings", "Message Filename Size 2", 127 ),
        GetProfileInt ( "Settings", "Message Filename Size 3", 127 ),
        GetProfileInt ( "Settings", "Message Filename Size 4", 127 ) );

    SetAttFormat (  
        GetProfileInt ( "Settings", "Attachment Filename Value 1", MSG_NAME_OBJECT ),
        GetProfileInt ( "Settings", "Attachment Filename Value 2", MSG_NAME_ATT_NAME ),
        GetProfileInt ( "Settings", "Attachment Filename Value 3", MSG_NAME_NONE ),
        GetProfileInt ( "Settings", "Attachment Filename Value 4", MSG_NAME_NONE ),
        GetProfileInt ( "Settings", "Attachment Filename Value 5", MSG_NAME_NONE ),
        GetProfileInt ( "Settings", "Attachment Filename Size 1", 127 ),
        GetProfileInt ( "Settings", "Attachment Filename Size 2", 127 ),
        GetProfileInt ( "Settings", "Attachment Filename Size 3", 127 ),
        GetProfileInt ( "Settings", "Attachment Filename Size 4", 127 ),
        GetProfileInt ( "Settings", "Attachment Filename Size 5", 127 ) );

    CString strExtension;
    strExtension = GetProfileString ( "Settings", "Message File Type", ".nws" );
    SetMsgExtension ( strExtension );

    CString strAttExtension;
    strAttExtension = GetProfileString ( "Settings", "Attachment File Type", ".unk" );
    SetAttExtension ( strAttExtension );

    SetBoolMsgLeave ( GetProfileInt ( "Settings", "Message Overwrite", 1 ) == 0 );
    SetBoolLeave ( GetProfileInt ( "Settings", "Attachement Overwrite", 0 ) == 0 );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BOOL CAboutDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Ajoutez ici une initialisation supplémentaire
    m_Version_Name.SetWindowText ( PROGRAM_NAME_P " "  PROGRAM_VERSION );
    m_Version_Date.SetWindowText ( PROGRAM_DATE_F );
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}
