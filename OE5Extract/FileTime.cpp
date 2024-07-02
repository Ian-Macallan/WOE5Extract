#include "stdafx.h"

//
//		Outlook Extract objects.
//


#ifdef	_CONSOLE
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>

#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#endif


#include "OE5ExtractDefinitions.h"
#include "DisplayAndTrace.h"

#include "FileTime.h"

static char	*pDay [ 7 ] = {	"Sun", "Mon", "Twe", "Wed", "Thu", "Fri", "Sat" };

static char	*pMonth [ 12 ] = {	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
								"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

static	FILETIME	fileTime;
static	SYSTEMTIME	sysTime;

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static bool TestDayOfWeek( char *pDate )
{
	for ( int iX = 0; iX < 7; iX++ )
	{
		if ( strncmp ( pDate, pDay [ iX ], strlen ( pDay [ iX ] ) ) == 0 )
		{
			sysTime.wDayOfWeek = iX;
			return true;
		}
	}

	sysTime.wDayOfWeek = -1;
	return false;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static char *SkipSpace(char *pDate)
{
	while ( *pDate )
	{
		if ( *pDate != ' ' )
		{
			return pDate;
		}
		pDate++;
	}

	return pDate;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static char *SkipSemi(char *pDate)
{
	while ( *pDate )
	{
		if ( *pDate != ':' )
		{
			return pDate;
		}
		pDate++;
	}

	return pDate;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static char *SkipNonSpace(char *pDate)
{
	while ( *pDate )
	{
		if ( *pDate == ' ' )
		{
			return pDate;
		}
		pDate++;
	}

	return pDate;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static char *SkipNonSemi(char *pDate)
{
	while ( *pDate )
	{
		if ( *pDate == ':' )
		{
			return pDate;
		}
		pDate++;
	}

	return pDate;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static bool TestMonth ( char *pDate )
{
	for ( int iX = 0; iX < 12; iX++ )
	{
		if ( strncmp ( pDate, pMonth [ iX ], strlen ( pMonth [ iX ] ) ) == 0 )
		{
			sysTime.wMonth = iX + 1;
			return true;
		}
	}

	sysTime.wMonth = 0;

	return false;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static void SetDateTime(char *pDate)
{
	memset ( &sysTime, 0 , sizeof ( sysTime ) );

	if ( TestDayOfWeek ( pDate ) )
	{
		pDate = SkipNonSpace ( pDate );
		pDate = SkipSpace ( pDate );
	}

	sysTime.wDay = atoi ( pDate );
	pDate = SkipNonSpace ( pDate );
	pDate = SkipSpace ( pDate );

	if ( TestMonth ( pDate ) )
	{
		pDate = SkipNonSpace ( pDate );
		pDate = SkipSpace ( pDate );
	}

	sysTime.wYear = atoi ( pDate );
	pDate = SkipNonSpace ( pDate );
	pDate = SkipSpace ( pDate );

	sysTime.wHour = atoi ( pDate );
	pDate = SkipNonSemi ( pDate );
	pDate = SkipSemi ( pDate );

	sysTime.wMinute = atoi ( pDate );
	pDate = SkipNonSemi ( pDate );
	pDate = SkipSemi ( pDate );

	sysTime.wSecond = atoi ( pDate );
	pDate = SkipNonSemi ( pDate );
	pDate = SkipSemi ( pDate );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ModifyFileTime ( char *szPath, char *szAscDate )
{
	OFSTRUCT	ofStruct;

	SetDateTime ( szAscDate );

	memset ( &ofStruct, 0, sizeof ( ofStruct ) );

	ofStruct.cBytes = sizeof ( ofStruct );

	DWORD dwDesiredAccess		= GENERIC_WRITE;
	DWORD dwShareMode			= FILE_SHARE_READ;
	DWORD dwCreationDisposition	= OPEN_EXISTING;
	DWORD dwFlagsAndAttributes	= FILE_ATTRIBUTE_ARCHIVE;
	HANDLE hFile = CreateFile(
	  szPath,					// file name
	  dwDesiredAccess,			// access mode
	  dwShareMode,				// share mode
	  NULL,						// Security
	  dwCreationDisposition,	// how to create
	  dwFlagsAndAttributes,		// file attributes
	  NULL						// handle to template file
	);

	if ( hFile != INVALID_HANDLE_VALUE )
	{

		BOOL bConvert = SystemTimeToFileTime ( &sysTime, &fileTime );
		if ( ! bConvert )
		{
			DisplayWarning ( 
				"ModifyFileTime - Error during SystemTimeToFileTime \n\tFile:'%s'\n\tDate:'%s'\n", 
				szPath, szAscDate );
		}

		BOOL bSet = SetFileTime ( hFile, &fileTime, &fileTime, &fileTime );
		if ( ! bSet )
		{
			DisplayWarning ( 
				"ModifyFileTime - Error during SetFileTime \n\tFile:'%s'\n\tDate:'%s'\n", 
				szPath, szAscDate );
		}

		BOOL bClose = CloseHandle ( hFile );
	}
	else
	{
			DisplayWarning ( 
				"ModifyFileTime - File not found \n\tFile:'%s'\n\tDate:'%s'\n", 
				szPath, szAscDate );
	}
}
