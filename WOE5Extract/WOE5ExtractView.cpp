// WOE5ExtractView.cpp : implementation of the CWOE5ExtractView class
//

#include "stdafx.h"
#include <Windows.h>

#include "WOE5Extract.h"

#include "WOE5ExtractDoc.h"
#include "WOE5ExtractView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DateTime.h"

#include "../OE5Extract/DecodeRoutines.h"
#include "../OE5Extract/OEAddressRoutines.h"
#include "../OE5Extract/OEMessagesRoutines.h"
#include "../OE5Extract/OEAddressDefinitions.h"
#include "ProgressThread.h"
#include "LoadingThread.h"
#include "ExtractingThread.h"

//
///////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractView
//
///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CWOE5ExtractView, CListView)

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CWOE5ExtractView, CListView)
	//{{AFX_MSG_MAP(CWOE5ExtractView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EXTRACT_ALL, OnExtractAll)
	ON_COMMAND(ID_EXTRACT_ATTACHEMENT, OnExtractAttachement)
	ON_COMMAND(ID_EXTRACT_MESSAGE, OnExtractMessage)
	ON_COMMAND(ID_SELECT_ALL, OnSelectAll)
	ON_COMMAND(ID_UNSELECT_ALL, OnUnselectAll)
	ON_COMMAND(ID_EXTRACT_SEL_ALL, OnExtractSelAll)
	ON_COMMAND(ID_EXTRACT_SEL_ATT, OnExtractSelAtt)
	ON_COMMAND(ID_EXTRACT_SEL_MSG, OnExtractSelMsg)
	ON_UPDATE_COMMAND_UI(ID_SELECT_ALL, OnUpdateSelectAll)
	ON_UPDATE_COMMAND_UI(ID_UNSELECT_ALL, OnUpdateUnselectAll)
	ON_UPDATE_COMMAND_UI(ID_EXTRACT_SEL_ALL, OnUpdateExtractSelAll)
	ON_UPDATE_COMMAND_UI(ID_EXTRACT_SEL_ATT, OnUpdateExtractSelAtt)
	ON_UPDATE_COMMAND_UI(ID_EXTRACT_SEL_MSG, OnUpdateExtractSelMsg)
	ON_UPDATE_COMMAND_UI(ID_EXTRACT_ALL, OnUpdateExtractAll)
	ON_UPDATE_COMMAND_UI(ID_EXTRACT_ATTACHEMENT, OnUpdateExtractAttachement)
	ON_UPDATE_COMMAND_UI(ID_EXTRACT_MESSAGE, OnUpdateExtractMessage)
	ON_NOTIFY_REFLECT(LVN_ODSTATECHANGED, OnOdstatechanged)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_COMMAND(ID_EXTRACT_EMAIL, OnExtractEmail)
	ON_UPDATE_COMMAND_UI(ID_EXTRACT_EMAIL, OnUpdateExtractEmail)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )
END_MESSAGE_MAP()

//
///////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractView construction/destruction
//
///////////////////////////////////////////////////////////////////////////////
CWOE5ExtractView::CWOE5ExtractView()
{
	// TODO: add construction code here
	bFirstTime = true;
	bHeaderDone = false;
	iCountList = 0;

	for ( int iX = 0; iX < MAX_LINES; iX++ )
	{
		pInfos [ iX ] = NULL;
	}

	m_imgAttachement16.Create ( IDB_ATTACHEMENT_ICONS16, 16, 32, CLR_NONE );
	m_imgAttachement32.Create ( IDB_ATTACHEMENT_ICONS32, 32, 32, CLR_NONE );
	m_imgSortOrder16.Create ( IDB_SORTORDER_ICONS16, 16, 32, CLR_NONE );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
CWOE5ExtractView::~CWOE5ExtractView()
{
	FreeAllItems ();
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BOOL CWOE5ExtractView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style = cs.style | LVS_REPORT | LVS_AUTOARRANGE | LVS_SHOWSELALWAYS | LVS_OWNERDATA;
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractView drawing

void CWOE5ExtractView::OnDraw(CDC* pDC)
{
	CWOE5ExtractDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CWOE5ExtractView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
	// Gain a reference to the list control itself

	if ( bFirstTime )
	{
		bFirstTime = false;

		DisplayHeader ( );

		//		Create the tip tool.
		m_ToolTip.Create ( this, TTS_ALWAYSTIP );

		RECT		Rect;
		GetClientRect ( &Rect );
		BOOL bRes = m_ToolTip.AddTool( this, LPSTR_TEXTCALLBACK );
		m_ToolTip.SetDelayTime ( TTDT_AUTOPOP, 30000 );
		m_ToolTip.Activate ( TRUE );
		EnableToolTips ( FALSE );

	}

}

/////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractView printing

BOOL CWOE5ExtractView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWOE5ExtractView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWOE5ExtractView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractView diagnostics

#ifdef _DEBUG
void CWOE5ExtractView::AssertValid() const
{
	CListView::AssertValid();
}

void CWOE5ExtractView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CWOE5ExtractDoc* CWOE5ExtractView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWOE5ExtractDoc)));
	return (CWOE5ExtractDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWOE5ExtractView message handlers

void CWOE5ExtractView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	// Line Click - will be used to start other windows
	CListCtrl& theCtrl = GetListCtrl();
	
	int iPos = GetFirstSelectedItem ( );

	ExtractMsgFile ( iPos );

	UnSelectAll ( );

	*pResult = 0;
}

void CWOE5ExtractView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CListCtrl& theCtrl = GetListCtrl();
	
	int iPos = GetFirstSelectedItem ( );

	ExtractMsgFile ( iPos );

	UnSelectAll ( );

	*pResult = 0;
}

void CWOE5ExtractView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	// Column Click	- Will be use to sort
	SortInfosItems ( pNMListView->iSubItem );

	CListCtrl& theCtrl = GetListCtrl();
	
	int	iFirst	= theCtrl.GetTopIndex ();
	int	iLast	= iFirst + theCtrl.GetCountPerPage ();
	theCtrl.RedrawItems( iFirst, iLast );

	*pResult = 0;
}


void CWOE5ExtractView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	DisplayValues ( );
}

void CWOE5ExtractView::DisplayHeader()
{
	// Insert a column. This override is the most convenient.
	if ( ! bHeaderDone )
	{
		CListCtrl& theCtrl = GetListCtrl();

		bHeaderDone = true;

		theCtrl.InsertColumn(COL_ATTACHEMENT, " ", LVCFMT_LEFT, 48);
		theCtrl.InsertColumn(COL_MESSAGE, "Message", LVCFMT_LEFT, 64);
		theCtrl.InsertColumn(COL_DATE, "Date", LVCFMT_LEFT, 224 );
		theCtrl.InsertColumn(COL_AUTHOR, "Author", LVCFMT_LEFT, 192);
		theCtrl.InsertColumn(COL_OBJECT, "Object", LVCFMT_LEFT, 384);
		theCtrl.InsertColumn(COL_SIZE, "Size", LVCFMT_RIGHT, 64);

		theCtrl.SetImageList ( &m_imgAttachement16, LVSIL_SMALL );
		theCtrl.SetImageList ( &m_imgAttachement32, LVSIL_NORMAL );

		theCtrl.SetExtendedStyle ( theCtrl.GetExtendedStyle () | LVS_EX_FULLROWSELECT );
		theCtrl.SetExtendedStyle ( theCtrl.GetExtendedStyle () | LVS_EX_HEADERDRAGDROP );
		theCtrl.SetExtendedStyle ( theCtrl.GetExtendedStyle () | LVS_EX_GRIDLINES );
		theCtrl.SetExtendedStyle ( theCtrl.GetExtendedStyle () | LVS_EX_TRACKSELECT );
		theCtrl.SetExtendedStyle ( theCtrl.GetExtendedStyle () | LVS_EX_ONECLICKACTIVATE );
		theCtrl.SetExtendedStyle ( theCtrl.GetExtendedStyle () | LVS_EX_UNDERLINEHOT );

		RestoreColumnsPosition ( );
	}

}

void CWOE5ExtractView::DisplayValues()
{
	DisplayHeader ( );

	CListCtrl& theCtrl = GetListCtrl();

	//		Delete all items
	theCtrl.DeleteAllItems ( );

	FreeAllItems ();

	theApp.m_View = this;

	//		get document
	CWOE5ExtractDoc *pDoc = GetDocument ();
	if ( pDoc == NULL )
	{
		return;
	}

	CString strPathname = pDoc->GetPathName ( );

	if ( RetrieveSummaryFile ( ) )
	{
		return;
	}

	if ( strPathname != "" )
	{

		if ( theApp.m_LoadingThread == NULL )
		{
			theApp.m_LoadingThread = AfxBeginThread ( RUNTIME_CLASS ( CLoadingThread ) );
		}

		if ( theApp.m_ProgressThread == NULL )
		{
			theApp.m_ProgressThread = AfxBeginThread ( RUNTIME_CLASS ( CProgressThread ) );
		}

	}
}


void CWOE5ExtractView::AddListItem(structInformation *pStruct)
{

	pInfos [ iCountList ] =
		( structInformation * )	malloc ( sizeof ( struct structInformation ) );
	*pInfos [ iCountList ] = *pStruct;

	char	*pSortDate = pInfos [ iCountList ]->szSortDate;
	char	*pDate = pInfos [ iCountList ]->szDate;

	try
	{
		class	CDateTime	clDate ( pDate );

		strcpy_s ( pSortDate, sizeof ( pInfos [ iCountList ]->szSortDate ),
					clDate.GetDateTime () );
	}
	catch ( ... )
	{
	}

	iCountList++;

}

void CWOE5ExtractView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	struct structInformation	*pStruct;

	if ( pDispInfo->item.iItem < MAX_LINES - 1 && pDispInfo->item.iItem < iCountList )
	{
		pStruct = pInfos [ pDispInfo->item.iItem ];
	}
	else
	{
		pStruct = NULL;
	}

	if ( pStruct != NULL )
	{
		if(pDispInfo->item.mask & LVIF_STATE )
		{
			//  Fill in the state information.
			//            pDispInfo->item.state |= rndItem.state;
		}

		if(pDispInfo->item.mask & LVIF_IMAGE )
		{
			//	Fill in the image information.
			pDispInfo->item.iImage = pStruct->iAttachementType;
		}

		if(pDispInfo->item.mask & LVIF_PARAM )
		{
			pDispInfo->item.lParam = pStruct->lPosition;
		}

		if(pDispInfo->item.mask & LVIF_INDENT )
		{
			//			pDispInfo->item...
		}

		if(pDispInfo->item.mask & LVIF_TEXT )
		{
			//  Fill in the text information.
			switch (pDispInfo->item.iSubItem)
			{
				case COL_ATTACHEMENT:
				{
					sprintf_s ( pDispInfo->item.pszText,
								pDispInfo->item.cchTextMax,
								"%d", pStruct->iAttachementCount );
					break;
				}
				case COL_MESSAGE:
				{
					sprintf_s (	pDispInfo->item.pszText, 
								pDispInfo->item.cchTextMax,
								"%08lx", pStruct->lPosition );
					break;
				}
				case COL_DATE:
				{
					strcpy_s (	pDispInfo->item.pszText, pDispInfo->item.cchTextMax,
								pStruct->szDate );
					break;
				}
				case COL_AUTHOR:
				{
					strcpy_s (	pDispInfo->item.pszText, pDispInfo->item.cchTextMax,
								pStruct->szAuthor );
					break;
				}
				case COL_OBJECT:
				{
					strcpy_s (	pDispInfo->item.pszText, pDispInfo->item.cchTextMax,
								pStruct->szSubject );
					break;
				}
				case COL_SIZE:
				{
					sprintf_s ( pDispInfo->item.pszText, pDispInfo->item.cchTextMax,
								"%ld", pStruct->lSize );
					break;
				}
				default:
				{
					break;
				}

			}

		}

	}

	*pResult = 0;
}

void CWOE5ExtractView::FreeAllItems()
{
	iCountList = 0;

	for ( int iX = 0; iX < MAX_LINES; iX++ )
	{
		if ( pInfos [ iX ] != NULL )
		{
			free ( pInfos [ iX ] );
			pInfos [ iX ] = NULL;
		}
	}

}

void CWOE5ExtractView::ExtractMsgFile(int iPos)
{
	char		szPathname [ LEN_PATHNAME ];
	char		*pFilename;

	if ( iPos >= iCountList || iPos < 0 )
	{
		return;
	}

	if ( theApp.m_ProgressThread != NULL )
	{
		return;
	}

	//		get document
	CWOE5ExtractDoc *pDoc = GetDocument ();
	if ( pDoc == NULL )
	{
		return;
	}

	CString strPathname = pDoc->GetPathName ( );

	strcpy_s ( szPathname, sizeof ( szPathname ), strPathname );

	if ( strPathname != "" )
	{
		SetBoolOnlyMessages ( true );
		SetBoolKeep ( true );

		//		First processing
		SetAddressRoutinesCancel ( false );

		pFilename = ProcessOneStep ( szPathname, pInfos [ iPos ]->lPosition, NULL, NULL );

		strPathname = pFilename;

		//		Execute Shell
		HINSTANCE			hInst;

		hInst = 
			ShellExecute ( NULL, "open", 
							strPathname, "", "", SW_SHOWDEFAULT );
	

	}
}

void CWOE5ExtractView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CRect		rect;
	GetClientRect ( &rect );
	ClientToScreen ( &rect );

	if ( rect.PtInRect ( point ) )
	{
		CMenu		menu;
		CListCtrl& theCtrl = GetListCtrl();

		menu.LoadMenu ( IDR_MAINFRAME );
		CMenu	*pContextMenu = menu.GetSubMenu ( 2 );

		UINT	iState;
		iState = MF_DISABLED | MF_GRAYED;
		if ( theCtrl.GetItemCount ( ) > 0 )
		{
			iState = MF_ENABLED;
		}
		pContextMenu->EnableMenuItem ( ID_EXTRACT_ALL, iState );
		pContextMenu->EnableMenuItem ( ID_EXTRACT_ATTACHEMENT, iState );
		pContextMenu->EnableMenuItem ( ID_EXTRACT_MESSAGE, iState );

		pContextMenu->EnableMenuItem ( ID_EXTRACT_EMAIL, iState );

		iState = MF_DISABLED | MF_GRAYED;
		if ( GetFirstSelectedItem () != -1 )
		{
			iState = MF_ENABLED;
		}
		pContextMenu->EnableMenuItem ( ID_EXTRACT_SEL_ALL, iState );
		pContextMenu->EnableMenuItem ( ID_EXTRACT_SEL_ATT, iState );
		pContextMenu->EnableMenuItem ( ID_EXTRACT_SEL_MSG, iState );

		pContextMenu->TrackPopupMenu (
			TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, 
			point.x, point.y, this );

		return;
	}
	
	
}

void CWOE5ExtractView::OnExtractSelAll() 
{
	// TODO: Add your command handler code here
	
	theApp.m_View = this;

	//		get document
	CWOE5ExtractDoc *pDoc = GetDocument ();
	if ( pDoc == NULL )
	{
		return;
	}

	CString strPathname = pDoc->GetPathName ( );

	if ( strPathname != "" )
	{

		SetBoolOnlyMessages ( false );
		SetBoolKeep ( true );
		SetNoneSelected ( );
		SetTheSelection ( );

		if ( theApp.m_ExtractingThread == NULL )
		{
			theApp.m_ExtractingThread = AfxBeginThread ( RUNTIME_CLASS ( CExtractingThread ) );
		}

		if ( theApp.m_ProgressThread == NULL )
		{
			theApp.m_ProgressThread = AfxBeginThread ( RUNTIME_CLASS ( CProgressThread ) );
		}

	}
	
}

void CWOE5ExtractView::OnExtractSelAtt() 
{
	// TODO: Add your command handler code here
	theApp.m_View = this;

	//		get document
	CWOE5ExtractDoc *pDoc = GetDocument ();
	if ( pDoc == NULL )
	{
		return;
	}

	CString strPathname = pDoc->GetPathName ( );

	if ( strPathname != "" )
	{

		SetBoolOnlyMessages ( false );
		SetBoolKeep ( false );
		SetNoneSelected ( );
		SetTheSelection ( );

		if ( theApp.m_ExtractingThread == NULL )
		{
			theApp.m_ExtractingThread = AfxBeginThread ( RUNTIME_CLASS ( CExtractingThread ) );
		}

		if ( theApp.m_ProgressThread == NULL )
		{
			theApp.m_ProgressThread = AfxBeginThread ( RUNTIME_CLASS ( CProgressThread ) );
		}

	}
}

void CWOE5ExtractView::OnExtractSelMsg() 
{
	// TODO: Add your command handler code here
	
	theApp.m_View = this;

	//		get document
	CWOE5ExtractDoc *pDoc = GetDocument ();
	if ( pDoc == NULL )
	{
		return;
	}

	CString strPathname = pDoc->GetPathName ( );

	if ( strPathname != "" )
	{

		SetBoolOnlyMessages ( true );
		SetBoolKeep ( true );
		SetNoneSelected ( );
		SetTheSelection ( );

		if ( theApp.m_ExtractingThread == NULL )
		{
			theApp.m_ExtractingThread = AfxBeginThread ( RUNTIME_CLASS ( CExtractingThread ) );
		}

		if ( theApp.m_ProgressThread == NULL )
		{
			theApp.m_ProgressThread = AfxBeginThread ( RUNTIME_CLASS ( CProgressThread ) );
		}

	}
}

void CWOE5ExtractView::OnExtractAll() 
{
	// TODO: Add your command handler code here
	
	theApp.m_View = this;

	//		get document
	CWOE5ExtractDoc *pDoc = GetDocument ();
	if ( pDoc == NULL )
	{
		return;
	}

	CString strPathname = pDoc->GetPathName ( );

	if ( strPathname != "" )
	{

		SetBoolOnlyMessages ( false );
		SetBoolKeep ( true );
		SetAllSelected ( );

		if ( theApp.m_ExtractingThread == NULL )
		{
			theApp.m_ExtractingThread = AfxBeginThread ( RUNTIME_CLASS ( CExtractingThread ) );
		}

		if ( theApp.m_ProgressThread == NULL )
		{
			theApp.m_ProgressThread = AfxBeginThread ( RUNTIME_CLASS ( CProgressThread ) );
		}

	}
}

void CWOE5ExtractView::OnExtractAttachement() 
{
	// TODO: Add your command handler code here
	
	theApp.m_View = this;

	//		get document
	CWOE5ExtractDoc *pDoc = GetDocument ();
	if ( pDoc == NULL )
	{
		return;
	}

	CString strPathname = pDoc->GetPathName ( );

	if ( strPathname != "" )
	{

		SetBoolOnlyMessages ( false );
		SetBoolKeep ( false );
		SetAllSelected ( );

		if ( theApp.m_ExtractingThread == NULL )
		{
			theApp.m_ExtractingThread = AfxBeginThread ( RUNTIME_CLASS ( CExtractingThread ) );
		}

		if ( theApp.m_ProgressThread == NULL )
		{
			theApp.m_ProgressThread = AfxBeginThread ( RUNTIME_CLASS ( CProgressThread ) );
		}

	}
}

void CWOE5ExtractView::OnExtractMessage() 
{
	// TODO: Add your command handler code here
	
	theApp.m_View = this;

	//		get document
	CWOE5ExtractDoc *pDoc = GetDocument ();
	if ( pDoc == NULL )
	{
		return;
	}

	CString strPathname = pDoc->GetPathName ( );

	if ( strPathname != "" )
	{

		SetBoolOnlyMessages ( true );
		SetBoolKeep ( true );
		SetAllSelected ( );

		if ( theApp.m_ExtractingThread == NULL )
		{
			theApp.m_ExtractingThread = AfxBeginThread ( RUNTIME_CLASS ( CExtractingThread ) );
		}

		if ( theApp.m_ProgressThread == NULL )
		{
			theApp.m_ProgressThread = AfxBeginThread ( RUNTIME_CLASS ( CProgressThread ) );
		}

	}
}

void CWOE5ExtractView::SaveColumnsPosition()
{
	CListCtrl& theCtrl = GetListCtrl();

	CHeaderCtrl* pHeaderCtrl = theCtrl.GetHeaderCtrl();

	if ( pHeaderCtrl != NULL )
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		LPINT pnOrder = (LPINT) malloc(nColumnCount*sizeof(int));
		ASSERT(pnOrder != NULL);

		theCtrl.GetColumnOrderArray ( pnOrder, nColumnCount );
		int iX;

		for ( iX = 0; iX < nColumnCount; iX++)
		{
			char	szTemp [ 32 ];
			sprintf_s ( szTemp, sizeof ( szTemp ), "Column %d", iX );
			theApp.WriteProfileInt ( "Settings", szTemp, pnOrder [ iX ] );
		}

		for ( iX = 0; iX < nColumnCount; iX++ )
		{
			char	szTemp [ 32 ];
			int iSize = theCtrl.GetColumnWidth ( iX );
			sprintf_s ( szTemp, sizeof ( szTemp ), "Column %d Width", iX );
			theApp.WriteProfileInt ( "Settings", szTemp, iSize );
		}

	   free(pnOrder);
	}

}

void CWOE5ExtractView::RestoreColumnsPosition()
{
	SetHeaderBitmap ( -1, true);

	CListCtrl& theCtrl = GetListCtrl();

	CHeaderCtrl* pHeaderCtrl = theCtrl.GetHeaderCtrl();

	if ( pHeaderCtrl != NULL )
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		LPINT pnOrder = (LPINT) malloc(nColumnCount*sizeof(int));
		ASSERT(pnOrder != NULL);

		int iX;
		for ( iX = 0; iX < nColumnCount; iX++)
		{
			char	szTemp [ 32 ];
			sprintf_s ( szTemp, sizeof ( szTemp ), "Column %d Width", iX );
			int iSize = theApp.GetProfileInt ( "Settings", szTemp, -1 );
			if ( iSize != - 1 )
			{
				theCtrl.SetColumnWidth ( iX, iSize );
			}
	   }

		for ( iX = 0; iX < nColumnCount; iX++)
		{
			char	szTemp [ 32 ];
			sprintf_s ( szTemp, sizeof ( szTemp ), "Column %d", iX );
			pnOrder [ iX ]  = theApp.GetProfileInt ( "Settings", szTemp, -1 );
			if ( pnOrder [ iX ] == -1 )
			{
				return;
			}
		}

	   theCtrl.SetColumnOrderArray(nColumnCount, pnOrder);

	   free(pnOrder);
	}

}

void CWOE5ExtractView::SortByAuthor ( )
{
	for ( int iX = 0; iX < iCountList; iX++ )
	{
		for ( int iY = iX; iY < iCountList; iY++ )
		{
			if ( bSortByAuthorAsc )
			{
				if ( strcmp ( pInfos [ iX ]->szAuthor, pInfos [ iY ]->szAuthor ) > 0 )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
			else
			{
				if ( strcmp ( pInfos [ iX ]->szAuthor, pInfos [ iY ]->szAuthor ) < 0 )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
		}
	}

	bSortByAuthorAsc = Negate ( bSortByAuthorAsc );
}

void CWOE5ExtractView::SortByObject ( )
{
	for ( int iX = 0; iX < iCountList; iX++ )
	{
		for ( int iY = iX; iY < iCountList; iY++ )
		{
			if ( bSortByObjectAsc )
			{
				if ( strcmp ( pInfos [ iX ]->szSubject, pInfos [ iY ]->szSubject ) > 0 )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
			else
			{
				if ( strcmp ( pInfos [ iX ]->szSubject, pInfos [ iY ]->szSubject ) < 0 )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
		}
	}

	bSortByObjectAsc = Negate ( bSortByObjectAsc );
}

void CWOE5ExtractView::SortByDate ( )
{
	for ( int iX = 0; iX < iCountList; iX++ )
	{
		for ( int iY = iX; iY < iCountList; iY++ )
		{
			if ( bSortByDateAsc )
			{
				if ( strcmp ( pInfos [ iX ]->szSortDate, pInfos [ iY ]->szSortDate ) > 0 )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
			else
			{
				if ( strcmp ( pInfos [ iX ]->szSortDate, pInfos [ iY ]->szSortDate ) < 0 )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
		}
	}

	bSortByDateAsc = Negate ( bSortByDateAsc );
}

void CWOE5ExtractView::SortBySize ( )
{
	for ( int iX = 0; iX < iCountList; iX++ )
	{
		for ( int iY = iX; iY < iCountList; iY++ )
		{
			if ( bSortBySizeAsc )
			{
				if ( pInfos [ iX ]->lSize > pInfos [ iY ]->lSize )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
			else
			{
				if ( pInfos [ iX ]->lSize < pInfos [ iY ]->lSize )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
		}
	}

	bSortBySizeAsc = Negate ( bSortBySizeAsc );
}

void CWOE5ExtractView::SortByAttach ( )
{
	for ( int iX = 0; iX < iCountList; iX++ )
	{
		for ( int iY = iX; iY < iCountList; iY++ )
		{
			if ( bSortByAttachAsc )
			{
				if ( pInfos [ iX ]->iAttachementCount > pInfos [ iY ]->iAttachementCount )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
			else
			{
				if ( pInfos [ iX ]->iAttachementCount < pInfos [ iY ]->iAttachementCount )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
		}
	}

	bSortByAttachAsc = Negate ( bSortByAttachAsc );
}

void CWOE5ExtractView::SortByMessage ( )
{
	for ( int iX = 0; iX < iCountList; iX++ )
	{
		for ( int iY = iX; iY < iCountList; iY++ )
		{
			if ( bSortByMessageAsc )
			{
				if ( pInfos [ iX ]->lPosition > pInfos [ iY ]->lPosition )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
			else
			{
				if ( pInfos [ iX ]->lPosition < pInfos [ iY ]->lPosition )
				{
					void	*pTemp;
					pTemp = pInfos [ iX ];
					pInfos [ iX ] = pInfos [ iY ];
					pInfos [ iY ] = ( struct structInformation * ) pTemp;
				}
			}
		}
	}

	bSortByMessageAsc = Negate ( bSortByMessageAsc );
}

void CWOE5ExtractView::SortInfosItems(int iColumn)
{
	switch ( iColumn )
	{
		case COL_SIZE:
		{
			SetHeaderBitmap ( iColumn, bSortBySizeAsc );
			SortBySize ( );
			break;
		}

		case COL_MESSAGE:
		{
			SetHeaderBitmap ( iColumn, bSortByMessageAsc );
			SortByMessage ( );
			break;
		}

		case COL_ATTACHEMENT:
		{
			SetHeaderBitmap ( iColumn, bSortByAttachAsc );
			SortByAttach ( );
			break;
		}

		case COL_AUTHOR:
		{
			SetHeaderBitmap ( iColumn, bSortByAuthorAsc );
			SortByAuthor ( );
			break;
		}

		case COL_OBJECT:
		{
			SetHeaderBitmap ( iColumn, bSortByObjectAsc );
			SortByObject ( );
			break;
		}

		case COL_DATE:
		{
			SetHeaderBitmap ( iColumn, bSortByDateAsc );
			SortByDate ( );
			break;
		}
	}
}


bool CWOE5ExtractView::Negate(bool bValue)
{
	if ( bValue )
	{
		return false;
	}

	return true;
}

void CWOE5ExtractView::SetHeaderBitmap(int iColumn, bool bAscending)
{
	HDITEM		tagHeaderInfo;
	char		szText [ 64 ];

	CListCtrl& theCtrl = GetListCtrl();

	CHeaderCtrl* pHeaderCtrl = theCtrl.GetHeaderCtrl();

	if ( iColumn == -1 )
	{
		pHeaderCtrl->SetImageList ( &m_imgSortOrder16 );
	}

	int  nColumnCount = pHeaderCtrl->GetItemCount();
	for ( int iX = 0; iX < nColumnCount; iX++ )
	{
		memset ( &tagHeaderInfo, 0, sizeof ( tagHeaderInfo ) );
		tagHeaderInfo.mask		= HDI_TEXT;
		tagHeaderInfo.pszText	= szText;
		tagHeaderInfo.cchTextMax	= sizeof ( szText ) - 1;


		pHeaderCtrl->GetItem ( iX, &tagHeaderInfo );

		tagHeaderInfo.mask		= HDI_TEXT | HDI_IMAGE | HDI_FORMAT;
		tagHeaderInfo.fmt		= HDF_IMAGE | HDF_STRING;
		tagHeaderInfo.pszText	= szText;
		if ( iX == iColumn )
		{
			if ( bAscending )
			{
				tagHeaderInfo.iImage	= 1;
			}
			else
			{
				tagHeaderInfo.iImage	= 2;
			}
		}
		else
		{
			tagHeaderInfo.iImage	= 0;
		}

		int iResult = pHeaderCtrl->SetItem ( iX, &tagHeaderInfo );
	}
}

void CWOE5ExtractView::ResetSortOrder()
{
	bSortByMessageAsc	= true;
	bSortByAuthorAsc	= true;
	bSortBySizeAsc		= true;
	bSortByAttachAsc	= true;
	bSortByObjectAsc	= true;
	bSortByDateAsc		= true;
}

void CWOE5ExtractView::UnSelectAll()
{
	int			iX;

	CListCtrl& theCtrl = GetListCtrl();

	for ( iX = 0; iX < theCtrl.GetItemCount ( ); iX++ )
	{
		theCtrl.SetItemState ( iX, 0, LVIS_SELECTED );
	}

}

int CWOE5ExtractView::GetFirstSelectedItem()
{
	CListCtrl& theCtrl = GetListCtrl();

	// check that one item gets the focus
	for ( int iX = 0; iX < theCtrl.GetItemCount(); iX++ )
	{
		if ( theCtrl.GetItemState( iX, LVIS_SELECTED) & LVIS_SELECTED )
		{
			return iX;
		}

	}

	return -1;

}

void CWOE5ExtractView::SelectAll()
{
	int			iX;

	CListCtrl& theCtrl = GetListCtrl();

	for ( iX = 0; iX < theCtrl.GetItemCount ( ); iX++ )
	{
		theCtrl.SetItemState ( iX, LVIS_SELECTED, LVIS_SELECTED );
	}

}

void CWOE5ExtractView::OnSelectAll() 
{
	// TODO: Add your command handler code here
	SelectAll();
}

void CWOE5ExtractView::OnUnselectAll() 
{
	// TODO: Add your command handler code here
	UnSelectAll();	
}


void CWOE5ExtractView::SetTheSelection()
{
	int			iX;

	CListCtrl& theCtrl = GetListCtrl();

	for ( iX = 0; iX < theCtrl.GetItemCount ( ); iX++ )
	{
		if ( theCtrl.GetItemState( iX, LVIS_SELECTED) & LVIS_SELECTED )
		{
			SetSelection ( pInfos [ iX ]->lPosition, TRUE );
		}
	}
}

void CWOE5ExtractView::OnUpdateSelectAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CListCtrl& theCtrl = GetListCtrl();

	pCmdUI->Enable ( theCtrl.GetItemCount ( ) > 0 );	
}

void CWOE5ExtractView::OnUpdateUnselectAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable ( GetFirstSelectedItem () != -1 );	
	
}

void CWOE5ExtractView::OnUpdateExtractSelAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable ( GetFirstSelectedItem () != -1 );	
}

void CWOE5ExtractView::OnUpdateExtractSelAtt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable ( GetFirstSelectedItem () != -1 );	
}

void CWOE5ExtractView::OnUpdateExtractSelMsg(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable ( GetFirstSelectedItem () != -1 );	
}

void CWOE5ExtractView::OnUpdateExtractAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CListCtrl& theCtrl = GetListCtrl();

	pCmdUI->Enable ( theCtrl.GetItemCount ( ) > 0 );
	
}

void CWOE5ExtractView::OnUpdateExtractAttachement(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CListCtrl& theCtrl = GetListCtrl();

	pCmdUI->Enable ( theCtrl.GetItemCount ( ) > 0 );
	
}

void CWOE5ExtractView::OnUpdateExtractMessage(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CListCtrl& theCtrl = GetListCtrl();

	pCmdUI->Enable ( theCtrl.GetItemCount ( ) > 0 );
	
}

BOOL CWOE5ExtractView::OnToolTipNotify(UINT id, NMHDR *pNMH, LRESULT *pResult)
{
	TOOLTIPTEXT *pText = (TOOLTIPTEXT *)pNMH;

	CListCtrl& theCtrl = GetListCtrl();

	int iPos		= theCtrl.GetSelectionMark ( );

	if ( iPos >= 0 )
	{
		m_ToolTipText = "Informations on Message";
		m_ToolTipText += " - Object: ";
		m_ToolTipText += pInfos [ iPos ]->szSubject;
		m_ToolTipText += " - Author: ";
		m_ToolTipText += pInfos [ iPos ]->szAuthor;
		m_ToolTipText += " - Date: ";
		m_ToolTipText += pInfos [ iPos ]->szDate;

		pText->lpszText = m_ToolTipText.GetBuffer ( LEN_PATHNAME );

		return TRUE;
	}

	return FALSE;
}

BOOL CWOE5ExtractView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent ( pMsg );

	return CListView::PreTranslateMessage(pMsg);
}

void CWOE5ExtractView::OnOdstatechanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLVODSTATECHANGE* pStateChanged = (NMLVODSTATECHANGE*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_ToolTip.Activate ( FALSE );
	m_ToolTip.Activate ( TRUE );
	m_ToolTip.Update ( );

	*pResult = 0;
}

void CWOE5ExtractView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_ToolTip.Activate ( FALSE );
	m_ToolTip.Activate ( TRUE );
	m_ToolTip.Update ( );

	*pResult = 0;
}

void CWOE5ExtractView::OnExtractEmail() 
{
	// TODO: Add your command handler code here
	char *szFilter = "CSV File (*.csv)|*.csv|Text File (*.txt)|*.txt|All Files (*.*)|*.*||";

 	CFileDialog		*dlgFile;

	dlgFile = 
		new CFileDialog ( FALSE, ".csv", "email.csv", OFN_OVERWRITEPROMPT, szFilter, this );

	if ( dlgFile->DoModal ( ) == IDOK )
	{
		CString strFile = dlgFile->GetPathName ( );

		CreateMailAddressFile ( strFile );
	}

	delete dlgFile;

}

void CWOE5ExtractView::OnUpdateExtractEmail(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	CListCtrl& theCtrl = GetListCtrl();

	pCmdUI->Enable ( theCtrl.GetItemCount ( ) > 0 );	
}

void CWOE5ExtractView::CreateMailAddressFile(CString strFile)
{
	FILE *hFile = NULL;
	fopen_s ( &hFile, strFile, "w" );

	if ( hFile )
	{

		fprintf ( hFile, "Name;E-Mail\r\n" );
		for ( int iX = 0; iX < iCountList; iX++ )
		{
			fprintf ( hFile, "%s;%s\r\n",
				pInfos [ iX ]->szAuthor, pInfos [ iX ]->szEmail );
		}

		fclose ( hFile );
	}
}


void CWOE5ExtractView::SaveSummaryFile()
{
	if ( theApp.GetProfileInt ( "Settings", "Create Index Files", FALSE ) == FALSE )
	{
		return;
	}

	CDocument *pDoc = GetDocument ();
	if ( pDoc == NULL )
	{
		return;
	}

	CString strPath = pDoc->GetPathName ( );
	if ( strPath == "" )
	{
		return;
	}

	CListCtrl& theCtrl = GetListCtrl();

	strPath = strPath + ".idx";

	FILE *hFile = NULL;

	fopen_s ( &hFile, strPath, "wb" );
	if ( hFile != NULL )
	{
		for ( int iX = 0; iX < theCtrl.GetItemCount ( ); iX++ )
		{
			fwrite ( pInfos [ iX ], 1, sizeof ( structInformation ), hFile );
		}

		fclose ( hFile );

		strPath = strPath + "pos";
		SaveAddresses ( strPath );
	}

}

bool CWOE5ExtractView::RetrieveSummaryFile()
{
	structInformation		strTemp;

	CDocument *pDoc = GetDocument ();
	if ( pDoc == NULL )
	{
		return false;
	}

	CString strPath = pDoc->GetPathName ( );
	if ( strPath == "" )
	{
		return false;
	}

	//		Retrieve file and time for main file.
	OFSTRUCT	ofStruct;

	HFILE hFile = OpenFile ( strPath, &ofStruct, OF_READ );
	if ( hFile == HFILE_ERROR )
	{
		return false;
	}

	FILETIME CreationTime, LastAccessTime, LastWriteTime;

	BOOL bDate = GetFileTime ( ( HANDLE ) hFile, &CreationTime, &LastAccessTime, &LastWriteTime );

	CloseHandle ( ( HANDLE ) hFile );

	if ( ! bDate )
	{
		return false;
	}

	//		Retrieve file and time for main file.
	strPath = strPath + ".idx";

	hFile = OpenFile ( strPath, &ofStruct, OF_READ );
	if ( hFile == HFILE_ERROR )
	{
		return false;
	}

	FILETIME SumCreationTime, SumLastAccessTime, SumLastWriteTime;

	bDate = GetFileTime ( ( HANDLE ) hFile, &SumCreationTime, &SumLastAccessTime, &SumLastWriteTime );

	CloseHandle ( ( HANDLE ) hFile );
	if ( ! bDate )
	{
		return false;
	}

	//		Compare file time
	if (  ( CompareFileTime ( &CreationTime, &SumCreationTime ) == 1 ) ||
		  ( CompareFileTime ( &LastWriteTime, &SumLastWriteTime ) == 1 )    )
	{
		return false;
	}

	//		Retrieve informations on index file.
	CListCtrl& theCtrl = GetListCtrl();

	FILE *hIdxFile = NULL;
	fopen_s ( &hIdxFile, strPath, "rb" );
	if ( hIdxFile != NULL )
	{

		iCountList = 0;

		while ( ! feof ( hIdxFile ) && ! ferror ( hIdxFile ) )
		{
			fread ( &strTemp, 1, sizeof ( structInformation ), hIdxFile );
			if ( ! feof ( hIdxFile ) && ! ferror ( hIdxFile ) )
			{
				pInfos [ iCountList ] =
					( structInformation * )	malloc ( sizeof ( struct structInformation ) );
				memcpy ( pInfos [ iCountList ], &strTemp, sizeof ( strTemp ) );

				iCountList++;
			}
		}

		fclose ( hIdxFile );

		strPath = strPath + "pos";
		if ( ! RestoreAddresses ( strPath ) )
		{
			FreeAllItems();
			return false;
		}

		theCtrl.SetItemCount ( iCountList );

		PrepareDirectory ();

		return true;

	}
	else
	{
		return false;
	}

	return false;

}

void CWOE5ExtractView::PrepareDirectory()
{
	CWOE5ExtractDoc *pDoc = GetDocument ();
	if ( pDoc == NULL )
	{
		return;
	}

	CListCtrl& theCtrl = GetListCtrl();

	CString strPathname = pDoc->GetPathName ( );
	char		szPathname [ LEN_PATHNAME ];
	strcpy_s ( szPathname, sizeof ( szPathname ), strPathname );

	if ( strPathname != "" )
	{
		CString strDirectory = 
			theApp.GetProfileString ( "Settings", "Working Directory", "" );
		CString strDiskDrive = 
			theApp.GetProfileString ( "Settings", "Working Disk Drive", "" );

		//		First processing
		if ( strDirectory == "" )
		{
			SetDirectory ( szPathname );
		}
		else
		{
			SetDirectory ( (LPCTSTR) strDirectory );
		}

		if ( strDiskDrive != "" )
		{
			SetDrive ( (LPCTSTR) strDiskDrive );
		}

		ProcessFileStep3 ( szPathname, NULL, this );

	}

}
