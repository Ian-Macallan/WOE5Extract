// DateTime.h: interface for the CDateTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATETIME_H__58A317A1_6830_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_DATETIME_H__58A317A1_6830_11D5_A09F_0000E8C97BDE__INCLUDED_

#include "../OE5Extract/OEAddressDefinitions.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDateTime
{
public:
    void SetDateTime ( char *pDate );
    char * GetDateTime();
    bool TestDayOfWeek ( char *pDate );
    bool TestMonth ( char *pDate );
    CDateTime ( char *pDate );
    CDateTime();
    virtual ~CDateTime();

protected:
    char *SkipSpace ( char *pDate );
    char *SkipNonSpace ( char *pDate );
    int iDay;
    int iMonth;
    int iYear;
    int iHour;
    int iMinutes;
    int iSeconds;
    int iDayOfWeek;

    char    szAscTime [ LEN_FILENAME ];
};

#endif // !defined(AFX_DATETIME_H__58A317A1_6830_11D5_A09F_0000E8C97BDE__INCLUDED_)
