// PreferencesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WOE5Extract.h"
#include "PreferencesDialog.h"
#include <shlobj.h>

#include <direct.h>

#include "WOE5Extract.h"
#include "../OE5Extract/OE5ExtractDefinitions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreferencesDialog dialog


CPreferencesDialog::CPreferencesDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CPreferencesDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CPreferencesDialog)
    //}}AFX_DATA_INIT
}


void CPreferencesDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CPreferencesDialog)
    DDX_Control(pDX, IDC_INDEX_FILES, m_CreateIndexFiles);
    DDX_Control(pDX, IDC_MRU_COUNT_SPIN, m_MRU_Count_Spin);
    DDX_Control(pDX, IDC_MRU_COUNT, m_MRU_Count);
    DDX_Control(pDX, IDC_DISK_BUTTON, m_Disk_Button);
    DDX_Control(pDX, IDC_DIR_BUTTON, m_Dir_Button);
    DDX_Control(pDX, IDC_OVER, m_Over);
    DDX_Control(pDX, IDC_ATT_OVER, m_Att_Over);
    DDX_Control(pDX, IDC_ATT_EXTENSION, m_Att_Extension);
    DDX_Control(pDX, IDC_EXTENSION, m_Extension);
    DDX_Control(pDX, IDC_MSGFMT_VALUE_9, m_MsgFmt_Value_9);
    DDX_Control(pDX, IDC_MSGFMT_VALUE_8, m_MsgFmt_Value_8);
    DDX_Control(pDX, IDC_MSGFMT_VALUE_7, m_MsgFmt_Value_7);
    DDX_Control(pDX, IDC_MSGFMT_VALUE_6, m_MsgFmt_Value_6);
    DDX_Control(pDX, IDC_MSGFMT_VALUE_5, m_MsgFmt_Value_5);
    DDX_Control(pDX, IDC_MSGFMT_SPIN_9, m_MsgFmt_Spin_9);
    DDX_Control(pDX, IDC_MSGFMT_SPIN_8, m_MsgFmt_Spin_8);
    DDX_Control(pDX, IDC_MSGFMT_SPIN_7, m_MsgFmt_Spin_7);
    DDX_Control(pDX, IDC_MSGFMT_SPIN_6, m_MsgFmt_Spin_6);
    DDX_Control(pDX, IDC_MSGFMT_SPIN_5, m_MsgFmt_Spin_5);
    DDX_Control(pDX, IDC_MSGFMT_SIZE_9, m_MsgFmt_Size_9);
    DDX_Control(pDX, IDC_MSGFMT_SIZE_8, m_MsgFmt_Size_8);
    DDX_Control(pDX, IDC_MSGFMT_SIZE_7, m_MsgFmt_Size_7);
    DDX_Control(pDX, IDC_MSGFMT_SIZE_6, m_MsgFmt_Size_6);
    DDX_Control(pDX, IDC_MSGFMT_SIZE_5, m_MsgFmt_Size_5);
    DDX_Control(pDX, IDC_MSGFMT_VALUE_4, m_MsgFmt_Value_4);
    DDX_Control(pDX, IDC_MSGFMT_VALUE_3, m_MsgFmt_Value_3);
    DDX_Control(pDX, IDC_MSGFMT_VALUE_2, m_MsgFmt_Value_2);
    DDX_Control(pDX, IDC_MSGFMT_SPIN_4, m_MsgFmt_Spin_4);
    DDX_Control(pDX, IDC_MSGFMT_SPIN_3, m_MsgFmt_Spin_3);
    DDX_Control(pDX, IDC_MSGFMT_SPIN_2, m_MsgFmt_Spin_2);
    DDX_Control(pDX, IDC_MSGFMT_SIZE_4, m_MsgFmt_Size_4);
    DDX_Control(pDX, IDC_MSGFMT_SIZE_3, m_MsgFmt_Size_3);
    DDX_Control(pDX, IDC_MSGFMT_SIZE_2, m_MsgFmt_Size_2);
    DDX_Control(pDX, IDC_MSGFMT_VALUE_1, m_MsgFmt_Value_1);
    DDX_Control(pDX, IDC_MSGFMT_SPIN_1, m_MsgFmt_Spin_1);
    DDX_Control(pDX, IDC_MSGFMT_SIZE_1, m_MsgFmt_Size_1);
    DDX_Control(pDX, IDC_ASSOCIATE, m_AssociateDbx);
    DDX_Control(pDX, IDC_DIRECTORY, m_Directory);
    DDX_Control(pDX, IDC_DISKDRIVE, m_DiskDrive);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreferencesDialog, CDialog)
    //{{AFX_MSG_MAP(CPreferencesDialog)
    ON_BN_CLICKED(IDC_DIR_BUTTON, OnDirButton)
    ON_BN_CLICKED(IDC_DISK_BUTTON, OnDiskButton)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreferencesDialog message handlers

int CALLBACK BrowseCallbackProc ( HWND hwnd, UINT uMsg, LPARAM lp, LPARAM pData)
{
         TCHAR szDir[MAX_PATH];

         switch(uMsg)
         {
            case BFFM_INITIALIZED:
            {
                if ( GetCurrentDirectory (sizeof ( szDir ) /sizeof ( TCHAR ), szDir))
                {
                  // WParam is TRUE since you are passing a path.
                  // It would be FALSE if you were passing a pidl.
                  SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)szDir);
                }
                break;
            }

            case BFFM_SELCHANGED:
            {
                // Set the status window to the currently selected path.
                if (SHGetPathFromIDList((LPITEMIDLIST) lp ,szDir))
                {
                    SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
                }
                break;
            }

            default:
            {
               break;
            }
         }
         return 0;
}


BOOL CPreferencesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    CString strDiskDrive =
        theApp.GetProfileString ( "Settings", "Working Disk Drive", "" );
    m_DiskDrive.SetWindowText ( strDiskDrive );
    
    CString strDirectory =
        theApp.GetProfileString ( "Settings", "Working Directory", "" );
    m_Directory.SetWindowText ( strDirectory );

    UINT iAssociation =
        theApp.GetProfileInt ( "Settings", "Filetype Association", FALSE );
    m_AssociateDbx.SetCheck ( iAssociation );

    UINT iCreateIndexFile =
        theApp.GetProfileInt ( "Settings", "Create Index Files", FALSE );
    m_CreateIndexFiles.SetCheck ( iCreateIndexFile );

    UINT iMruCount =
        theApp.GetProfileInt ( "Settings", "Most Recently Used Files Count", _AFX_MRU_COUNT );
    char    szNumber [ LEN_SMALLSTRING ];
    sprintf_s ( szNumber, sizeof ( szNumber ), "%d", iMruCount );
    m_MRU_Count.SetWindowText ( szNumber );
    m_MRU_Count_Spin.SetBuddy ( &m_MRU_Count );
    m_MRU_Count_Spin.SetRange ( 0, 9 );
    m_MRU_Count_Spin.SetPos ( theApp.GetProfileInt ( "Settings", "Most Recently Used Files Count", _AFX_MRU_COUNT ) );

    //  Message
    m_MsgFmt_Value_1.Init ( );
    m_MsgFmt_Value_1.SetCurSel ( theApp.GetProfileInt ( "Settings", "Message Filename Value 1", MSG_NAME_OBJECT ) );
    m_MsgFmt_Spin_1.SetBuddy ( &m_MsgFmt_Size_1 );
    m_MsgFmt_Spin_1.SetRange ( 0, 255 );
    m_MsgFmt_Spin_1.SetPos ( theApp.GetProfileInt ( "Settings", "Message Filename Size 1", 127 ) );

    m_MsgFmt_Value_2.Init ( );
    m_MsgFmt_Value_2.SetCurSel ( theApp.GetProfileInt ( "Settings", "Message Filename Value 2", MSG_NAME_MESSAGE_ID ) );
    m_MsgFmt_Spin_2.SetBuddy ( &m_MsgFmt_Size_2 );
    m_MsgFmt_Spin_2.SetRange ( 0, 255 );
    m_MsgFmt_Spin_2.SetPos ( theApp.GetProfileInt ( "Settings", "Message Filename Size 2", 127 ) );

    m_MsgFmt_Value_3.Init ( );
    m_MsgFmt_Value_3.SetCurSel ( theApp.GetProfileInt ( "Settings", "Message Filename Value 3", MSG_NAME_NONE ) );
    m_MsgFmt_Spin_3.SetBuddy ( &m_MsgFmt_Size_3 );
    m_MsgFmt_Spin_3.SetRange ( 0, 255 );
    m_MsgFmt_Spin_3.SetPos ( theApp.GetProfileInt ( "Settings", "Message Filename Size 3", 127 ) );

    m_MsgFmt_Value_4.Init ( );
    m_MsgFmt_Value_4.SetCurSel ( theApp.GetProfileInt ( "Settings", "Message Filename Value 4", MSG_NAME_NONE ) );
    m_MsgFmt_Spin_4.SetBuddy ( &m_MsgFmt_Size_4 );
    m_MsgFmt_Spin_4.SetRange ( 0, 255 );
    m_MsgFmt_Spin_4.SetPos ( theApp.GetProfileInt ( "Settings", "Message Filename Size 4", 127 ) );

    //  Attachement
    m_MsgFmt_Value_5.Init ( );
    m_MsgFmt_Value_5.SetCurSel ( theApp.GetProfileInt ( "Settings", "Attachment Filename Value 1", MSG_NAME_OBJECT ) );
    m_MsgFmt_Spin_5.SetBuddy ( &m_MsgFmt_Size_5 );
    m_MsgFmt_Spin_5.SetRange ( 0, 255 );
    m_MsgFmt_Spin_5.SetPos ( theApp.GetProfileInt ( "Settings", "Attachment Filename Size 1", 127 ) );

    m_MsgFmt_Value_6.Init ( );
    m_MsgFmt_Value_6.SetCurSel ( theApp.GetProfileInt ( "Settings", "Attachment Filename Value 2", MSG_NAME_MESSAGE_ID ) );
    m_MsgFmt_Spin_6.SetBuddy ( &m_MsgFmt_Size_6 );
    m_MsgFmt_Spin_6.SetRange ( 0, 255 );
    m_MsgFmt_Spin_6.SetPos ( theApp.GetProfileInt ( "Settings", "Attachment Filename Size 2", 127 ) );

    m_MsgFmt_Value_7.Init ( );
    m_MsgFmt_Value_7.SetCurSel ( theApp.GetProfileInt ( "Settings", "Attachment Filename Value 3", MSG_NAME_ATT_NUMB ) );
    m_MsgFmt_Spin_7.SetBuddy ( &m_MsgFmt_Size_7 );
    m_MsgFmt_Spin_7.SetRange ( 0, 255 );
    m_MsgFmt_Spin_7.SetPos ( theApp.GetProfileInt ( "Settings", "Attachment Filename Size 3", 127 ) );

    m_MsgFmt_Value_8.Init ( );
    m_MsgFmt_Value_8.SetCurSel ( theApp.GetProfileInt ( "Settings", "Attachment Filename Value 4", MSG_NAME_NONE ) );
    m_MsgFmt_Spin_8.SetBuddy ( &m_MsgFmt_Size_8 );
    m_MsgFmt_Spin_8.SetRange ( 0, 255 );
    m_MsgFmt_Spin_8.SetPos ( theApp.GetProfileInt ( "Settings", "Attachment Filename Size 4", 127 ) );

    m_MsgFmt_Value_9.Init ( );
    m_MsgFmt_Value_9.SetCurSel ( theApp.GetProfileInt ( "Settings", "Attachment Filename Value 5", MSG_NAME_NONE ) );
    m_MsgFmt_Spin_9.SetBuddy ( &m_MsgFmt_Size_9 );
    m_MsgFmt_Spin_9.SetRange ( 0, 255 );
    m_MsgFmt_Spin_9.SetPos ( theApp.GetProfileInt ( "Settings", "Attachment Filename Size 5", 127 ) );

    CString strExtension =
        theApp.GetProfileString ( "Settings", "Message File Type", ".nws" );
    m_Extension.SetWindowText ( strExtension );

    CString strAttExtension =
        theApp.GetProfileString ( "Settings", "Attachment File Type", ".unk" );
    m_Att_Extension.SetWindowText ( strAttExtension );

    m_Over.SetCheck ( theApp.GetProfileInt ( "Settings", "Message Overwrite", 0 ) );

    m_Att_Over.SetCheck ( theApp.GetProfileInt ( "Settings", "Attachement Overwrite", 1 ) );

    //      Create the tip tool.
    m_ToolTip.Create ( this, TTS_ALWAYSTIP );

    RECT        Rect;
    GetClientRect ( &Rect );

    BOOL bRes;
    bRes = m_ToolTip.AddTool ( &m_AssociateDbx, IDS_TOOLTIP_TEXT_0002 );
    bRes = m_ToolTip.AddTool ( &m_Att_Extension, IDS_TOOLTIP_TEXT_0001 );
    bRes = m_ToolTip.AddTool ( &m_Att_Over, IDS_TOOLTIP_TEXT_0003 );
    bRes = m_ToolTip.AddTool ( &m_Dir_Button, IDS_TOOLTIP_TEXT_0004 );
    bRes = m_ToolTip.AddTool ( &m_Directory, IDS_TOOLTIP_TEXT_0005 );
    bRes = m_ToolTip.AddTool ( &m_Disk_Button, IDS_TOOLTIP_TEXT_0006 );
    bRes = m_ToolTip.AddTool ( &m_DiskDrive,IDS_TOOLTIP_TEXT_0007 );
    bRes = m_ToolTip.AddTool ( &m_Extension,IDS_TOOLTIP_TEXT_0008 );

    bRes = m_ToolTip.AddTool ( &m_MRU_Count, IDS_TOOLTIP_TEXT_0009 );
    bRes = m_ToolTip.AddTool ( &m_MRU_Count_Spin, IDS_TOOLTIP_TEXT_0009 );

    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Size_1, IDS_TOOLTIP_TEXT_0010 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Size_2, IDS_TOOLTIP_TEXT_0010 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Size_3, IDS_TOOLTIP_TEXT_0010 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Size_4, IDS_TOOLTIP_TEXT_0010 );

    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Spin_1, IDS_TOOLTIP_TEXT_0010 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Spin_2, IDS_TOOLTIP_TEXT_0010 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Spin_3, IDS_TOOLTIP_TEXT_0010 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Spin_4, IDS_TOOLTIP_TEXT_0010 );

    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Value_1, IDS_TOOLTIP_TEXT_0011 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Value_2, IDS_TOOLTIP_TEXT_0012 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Value_3, IDS_TOOLTIP_TEXT_0013 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Value_4, IDS_TOOLTIP_TEXT_0014 );

    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Size_5, IDS_TOOLTIP_TEXT_0015 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Size_6, IDS_TOOLTIP_TEXT_0015 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Size_7, IDS_TOOLTIP_TEXT_0015 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Size_8, IDS_TOOLTIP_TEXT_0015 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Size_9, IDS_TOOLTIP_TEXT_0015 );

    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Spin_5, IDS_TOOLTIP_TEXT_0015 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Spin_6, IDS_TOOLTIP_TEXT_0015 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Spin_7, IDS_TOOLTIP_TEXT_0015 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Spin_8, IDS_TOOLTIP_TEXT_0015 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Spin_9, IDS_TOOLTIP_TEXT_0015 );

    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Value_5, IDS_TOOLTIP_TEXT_0016 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Value_6, IDS_TOOLTIP_TEXT_0017 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Value_7, IDS_TOOLTIP_TEXT_0018 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Value_8, IDS_TOOLTIP_TEXT_0019 );
    bRes = m_ToolTip.AddTool ( &m_MsgFmt_Value_9, IDS_TOOLTIP_TEXT_0020 );


    bRes = m_ToolTip.AddTool ( &m_Over, IDS_TOOLTIP_TEXT_0021 );

    bRes = m_ToolTip.AddTool ( &m_CreateIndexFiles, IDS_TOOLTIP_TEXT_0022 );

    m_ToolTip.SetDelayTime ( TTDT_AUTOPOP, 30000 );
    m_ToolTip.Activate ( TRUE );
    EnableToolTips ( TRUE );

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPreferencesDialog::OnOK()
{
    // TODO: Add extra validation here

    CString strDiskDrive;
    m_DiskDrive.GetWindowText ( strDiskDrive );

    CString strDirectory;
    m_Directory.GetWindowText ( strDirectory );

    theApp.WriteProfileString ( "Settings", "Working Disk Drive", strDiskDrive );
    theApp.WriteProfileString ( "Settings", "Working Directory", strDirectory );
    theApp.WriteProfileInt ( "Settings", "Filetype Association", m_AssociateDbx.GetCheck ( ) );
    theApp.WriteProfileInt ( "Settings", "Create Index Files", m_CreateIndexFiles.GetCheck ( ) );

    CString strExtension;
    m_Extension.GetWindowText ( strExtension );
    theApp.WriteProfileString ( "Settings", "Message File Type", strExtension );

    CString strAttExtension;
    m_Att_Extension.GetWindowText ( strAttExtension );
    theApp.WriteProfileString ( "Settings", "Attachment File Type", strAttExtension );

    theApp.WriteProfileInt ( "Settings", "Message Overwrite", m_Over.GetCheck ( ) );
    theApp.WriteProfileInt ( "Settings", "Attachement Overwrite", m_Att_Over.GetCheck ( ) );

    if ( ! m_AssociateDbx.GetCheck ( ) )
    {
        DWORD           dwReserved;
        DWORD           dwType;
        char            szData [ 128 ];
        DWORD           dwLength;
        DWORD           ulOptions;
        HKEY            hKey;
        REGSAM          samDesired;


        memset ( szData, 0, sizeof ( szData ) );

        dwLength    = sizeof ( szData ) - 1;
        dwReserved  = NULL;
        dwType      = REG_SZ;
        ulOptions   = NULL;
        samDesired = KEY_READ;

        LONG lResult =
            RegOpenKeyEx(
                HKEY_CLASSES_ROOT,  // handle to open key
                ".dbx",             // subkey name
                ulOptions,          // reserved
                samDesired,         // security access mask
                &hKey               // handle to open key
            );

        lResult =
            RegQueryValueEx(
                hKey,                           // handle to key
                "",                             // value name
                &dwReserved,                    // reserved
                &dwType,                        // type buffer      
                ( unsigned char * ) szData,     // data buffer
                &dwLength                       // size of data buffer
            );

        if ( lResult == ERROR_SUCCESS )
        {
            if ( strcmp ( szData, "WOE5Extract.Document" ) == 0 )
            {
                memset ( szData, 0, sizeof ( szData ) );
                lResult = RegSetValueEx ( hKey, "", dwReserved, dwType, ( unsigned char * ) szData, 1 );

                // lResult = RegDeleteKey ( HKEY_CLASSES_ROOT, ".dbx" );
            }
        }
    }

    theApp.WriteProfileInt ( "Settings", "Message Filename Value 1", m_MsgFmt_Value_1.GetCurSel ( ) );
    theApp.WriteProfileInt ( "Settings", "Message Filename Value 2", m_MsgFmt_Value_2.GetCurSel ( ) );
    theApp.WriteProfileInt ( "Settings", "Message Filename Value 3", m_MsgFmt_Value_3.GetCurSel ( ) );
    theApp.WriteProfileInt ( "Settings", "Message Filename Value 4", m_MsgFmt_Value_4.GetCurSel ( ) );

    theApp.WriteProfileInt ( "Settings", "Attachment Filename Value 1", m_MsgFmt_Value_5.GetCurSel ( ) );
    theApp.WriteProfileInt ( "Settings", "Attachment Filename Value 2", m_MsgFmt_Value_6.GetCurSel ( ) );
    theApp.WriteProfileInt ( "Settings", "Attachment Filename Value 3", m_MsgFmt_Value_7.GetCurSel ( ) );
    theApp.WriteProfileInt ( "Settings", "Attachment Filename Value 4", m_MsgFmt_Value_8.GetCurSel ( ) );
    theApp.WriteProfileInt ( "Settings", "Attachment Filename Value 5", m_MsgFmt_Value_9.GetCurSel ( ) );

    theApp.WriteProfileInt ( "Settings", "Message Filename Size 1", m_MsgFmt_Spin_1.GetPos ( ) );
    theApp.WriteProfileInt ( "Settings", "Message Filename Size 2", m_MsgFmt_Spin_2.GetPos ( ) );
    theApp.WriteProfileInt ( "Settings", "Message Filename Size 3", m_MsgFmt_Spin_3.GetPos ( ) );
    theApp.WriteProfileInt ( "Settings", "Message Filename Size 4", m_MsgFmt_Spin_4.GetPos ( ) );

    theApp.WriteProfileInt ( "Settings", "Attachment Filename Size 1", m_MsgFmt_Spin_5.GetPos ( ) );
    theApp.WriteProfileInt ( "Settings", "Attachment Filename Size 2", m_MsgFmt_Spin_6.GetPos ( ) );
    theApp.WriteProfileInt ( "Settings", "Attachment Filename Size 3", m_MsgFmt_Spin_7.GetPos ( ) );
    theApp.WriteProfileInt ( "Settings", "Attachment Filename Size 4", m_MsgFmt_Spin_8.GetPos ( ) );
    theApp.WriteProfileInt ( "Settings", "Attachment Filename Size 5", m_MsgFmt_Spin_9.GetPos ( ) );

    if ( ( m_MRU_Count_Spin.GetPos () >= 0 ) && ( m_MRU_Count_Spin.GetPos () <= 9 ) )
    {
        theApp.WriteProfileInt ( "Settings", "Most Recently Used Files Count", m_MRU_Count_Spin.GetPos () );
    }
    else
    {
        theApp.WriteProfileInt ( "Settings", "Most Recently Used Files Count", _AFX_MRU_COUNT );
    }

    CDialog::OnOK();
}

void CPreferencesDialog::OnCancel()
{
    // TODO: Add extra cleanup here
    
    CDialog::OnCancel();
}

void CPreferencesDialog::OnDirButton()
{
    // TODO: Add your control notification handler code here
    // TODO: Add your control notification handler code here
    CString         szDirectory;
    LPITEMIDLIST    pitemList;
    BROWSEINFO      browseInfo;
    char            szPath [ LEN_PATHNAME ];

    m_Directory.GetWindowText ( szDirectory );
    strcpy_s ( szPath, sizeof ( szPath ), szDirectory );
    if ( *szPath == '\0' )
    {
        _getcwd ( szPath, sizeof ( szPath ) );
        m_Directory.SetWindowText ( szPath );
    }

    browseInfo.hwndOwner        = m_hWnd;
    browseInfo.pidlRoot         = NULL;
    browseInfo.pszDisplayName   = szPath;
    browseInfo.lpszTitle        = "Select Working Directory";
    browseInfo.ulFlags          = BIF_DONTGOBELOWDOMAIN | BIF_STATUSTEXT;
    browseInfo.lpfn             = BrowseCallbackProc;
    browseInfo.lParam           = 0;
    browseInfo.iImage           = 0;

    int iRes1 = _chdrive ( *szPath - 'A' + 1 );
    int iRes2 = _chdir ( szPath );

    DWORD   pvReserved = NULL;
    HRESULT hResult = CoInitialize ( &pvReserved );
    pitemList = SHBrowseForFolder ( &browseInfo );
    if ( pitemList != NULL )
    {
        if ( SHGetPathFromIDList ( pitemList, szPath ) )
        {
            if ( strlen ( szPath ) > 0 )
            {
                if ( szPath [ strlen ( szPath ) - 1 ] == '\\' )
                {
                    szPath [ strlen ( szPath ) - 1 ] = 0;
                }
            }

            m_Directory.SetWindowText ( szPath );
        }
    }
    
    
}

//
//
void CPreferencesDialog::OnDiskButton()
{
    // TODO: Add your control notification handler code here
    CString         szDiskDrive;
    LPITEMIDLIST    pitemList;
    BROWSEINFO      browseInfo;
    char            szPath [ LEN_PATHNAME ];

    m_DiskDrive.GetWindowText ( szDiskDrive );
    strcpy_s ( szPath, sizeof ( szPath ), szDiskDrive );
    if ( *szPath == '\0' )
    {
        _getcwd ( szPath, sizeof ( szPath ) );
        m_DiskDrive.SetWindowText ( szPath );
    }

    browseInfo.hwndOwner        = m_hWnd;
    browseInfo.pidlRoot         = NULL;
    browseInfo.pszDisplayName   = szPath;
    browseInfo.lpszTitle        = "Select Working Disk Drive";
    browseInfo.ulFlags          = BIF_DONTGOBELOWDOMAIN | BIF_STATUSTEXT;
    browseInfo.lpfn             = BrowseCallbackProc;
    browseInfo.lParam           = 0;
    browseInfo.iImage           = 0;

    int iRes1 = _chdrive ( *szPath - 'A' + 1 );
    int iRes2 = _chdir ( szPath );

    DWORD   pvReserved = NULL;
    HRESULT hResult = CoInitialize ( &pvReserved );

    pitemList = SHBrowseForFolder ( &browseInfo );
    if ( pitemList != NULL )
    {
        if ( SHGetPathFromIDList ( pitemList, szPath ) )
        {
            if ( strlen ( szPath ) > 2 )
            {
                szPath [ 2 ] = 0;
            }

            m_DiskDrive.SetWindowText ( szPath );
        }
    }
    
}

BOOL CPreferencesDialog::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent ( pMsg );
    
    return CDialog::PreTranslateMessage(pMsg);
}
