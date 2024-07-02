// MsgFmtComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "../OE5Extract/OE5ExtractDefinitions.h"
#include "MsgFmtComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgFmtComboBox

CMsgFmtComboBox::CMsgFmtComboBox()
{
}

CMsgFmtComboBox::~CMsgFmtComboBox()
{
}


BEGIN_MESSAGE_MAP(CMsgFmtComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMsgFmtComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgFmtComboBox message handlers

void CMsgFmtComboBox::Init()
{
	AddString ( "00 - None" );
	AddString ( "01 - Object" );
	AddString ( "02 - Date" );
	AddString ( "03 - Author" );
	AddString ( "04 - Message ID" );
	AddString ( "05 - E-Mail Address" );
}
