// AttFmtComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "WOE5Extract.h"
#include "AttFmtComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
///////////////////////////////////////////////////////////////////////////////
// CAttFmtComboBox

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
CAttFmtComboBox::CAttFmtComboBox()
{
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
CAttFmtComboBox::~CAttFmtComboBox()
{
}


//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAttFmtComboBox, CComboBox)
    //{{AFX_MSG_MAP(CAttFmtComboBox)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
///////////////////////////////////////////////////////////////////////////////
// CAttFmtComboBox message handlers
//
///////////////////////////////////////////////////////////////////////////////
void CAttFmtComboBox::Init()
{
    AddString ( "00 - None" );
    AddString ( "01 - Object" );
    AddString ( "02 - Date" );
    AddString ( "03 - Author" );
    AddString ( "04 - Message ID" );
    AddString ( "05 - E-Mail Address" );
    AddString ( "06 - Attachement Name" );
    AddString ( "07 - Attachement Number" );

}
