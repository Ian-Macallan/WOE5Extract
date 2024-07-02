#include "stdafx.h"

#ifdef	_CONSOLE

#include <stdlib.h>
#include <stdio.h>
#include <direct.h>

#include <malloc.h>
#include <string.h>
#include <stdarg.h>
// #include <error.h>
#include <errno.h>

#endif

#include "MimeRoutines.h"
#include "DisplayAndTrace.h"

//
//		Tables for conversions in Base 64.
static	char						Base64Digits [ 64 + 1 ]				=
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static	char						DecodeTable [ 256 ];

static	bool					bDecodeTable = false;

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static void BuildDecodeTable ( )
{
	if ( bDecodeTable )
	{
		return;
	}

	bDecodeTable = true;

	int			iX;

	for ( iX = 0; iX < 256; iX++ )
	{
		DecodeTable [ iX ] = 0;
	}

	for ( iX = 0; iX < 64; iX++ )
	{
		DecodeTable [ Base64Digits [ iX ] ] = ' ' + iX;
	}

	DecodeTable [ '=' ] = ' ';

}

//
///////////////////////////////////////////////////////////////////////////////
//		UUDecode
//
///////////////////////////////////////////////////////////////////////////////
bool UUDecodeBytes (  char cByte1,  char cByte2,  char cByte3,  char cByte4,  char pResult [ 3 ] )
{
	long			lResult;
	char			cTemp;

	BuildDecodeTable ( );

	if ( cByte1 < ' ' || cByte2 < ' ' || cByte3 < ' ' || cByte4 < ' ' )
	{
		return false;
	}

	cByte1 -= 0x20;
	cByte2 -= 0x20;
	cByte3 -= 0x20;
	cByte4 -= 0x20;

	if ( cByte1 > 64 || cByte2 > 64 || cByte3 > 64 || cByte4 > 64 )
	{
		return false;
	}

	cByte1 &= 0x3f;
	cByte2 &= 0x3f;
	cByte3 &= 0x3f;
	cByte4 &= 0x3f;

	lResult = cByte1;
	lResult *= 64;
	lResult += cByte2;
	lResult *= 64;
	lResult += cByte3;
	lResult *= 64;
	lResult += cByte4;

	memcpy ( pResult, ( char * ) ( & lResult ), 3 );
	cTemp = pResult [ 0 ];
	pResult [ 0 ] = pResult [ 2 ];
	pResult [ 2 ] = cTemp;

	return true;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool UUDecodeFourBytes (  char *pBytes,  char *pResult )
{
	BuildDecodeTable ( );

	return ( UUDecodeBytes ( pBytes [ 0 ], pBytes [ 1 ], pBytes [ 2 ], pBytes [ 3 ], pResult ) );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool UUDecodeLine (  char *pLine,  char *pResult, int *piResult )
{
	int			iNbBytes, iLength, iStringLength;
	char		szTemp [ 5 ];
	char		*pSave;

	BuildDecodeTable ( );

	pSave = pLine;

	//	Get line size.
	iNbBytes		 = *pLine;
	iNbBytes		-= 0x20;
	iNbBytes		&= 0x3f;

	iNbBytes		 = ( iNbBytes + 2 ) / 3;
	iNbBytes		 = iNbBytes * 4;
	iLength			 = iNbBytes;

	iStringLength	 = strlen ( pLine );

	*piResult = 0;

	pLine++;
	while ( iNbBytes > 0 )
	{
		memset ( szTemp, ' ', sizeof ( szTemp ) - 1 );
		szTemp [ sizeof ( szTemp ) - 1 ] = 0;

		if ( strlen ( pLine ) >= 4 )
		{
			memcpy ( szTemp, pLine, 4 );
		}
		else
		{
			if ( strlen ( pLine ) > 0 )
			{
				memcpy ( szTemp, pLine, strlen ( pLine ) );
			}
		}

		if ( UUDecodeFourBytes ( szTemp, pResult ) == false )
		{
			DisplayError ( "Error: Bytes:%d String Length:%d <%s>\n", 
				iStringLength, iStringLength, pSave );

			return false;
		}

		pLine		+= 4;
		pResult		+= 3;

		iNbBytes	-= 4;
		*piResult	+= 3;
	}

	return true;
}

//
///////////////////////////////////////////////////////////////////////////////
//	Inner encoding loop
//	-------------------
//	Fetch the character
//	Add 42
//	Check for NULL, TAB(ascii 9), LF(ascii 10), CR (ascii 13) and '='
//	If one of the critical chars encounters then write '=' as escape
//	character to the output stream followed by the critical+64.
//	(NULL -> =@,   TAB --> =I,  LF --> =J,  CR --> =M,  '=' --> =}
//
///////////////////////////////////////////////////////////////////////////////
bool YencDecodeLine (  char *pLine,  char *pResult, int *piResult )
{
	*piResult = 0;

	while ( *pLine )
	{
		if ( *pLine == '=' )
		{
			//	Store Anyway
			int	iResult = *pLine;

			iResult += ( 256 - 42 );
			iResult &= 0xff;

			*pResult = iResult;

			//	Test if next byte is a special character.
			int iNextResult = * ( pLine + 1);
			iNextResult += ( 256 - 64 );
			iNextResult &= 0xff;
			if ( iNextResult == 0x00 || iNextResult == 0x0a ||
					iNextResult == 0x0d || iNextResult == '=' )
			{
				iNextResult += ( 256 - 42 );
				iNextResult &= 0xff;
				*pResult = iNextResult;
				pLine++;
			}
			else
			{
				iNextResult += ( 256 - 42 );
				iNextResult &= 0xff;
				*pResult = iNextResult;
				pLine++;
			}
		}
		else
		{
			//	Store - Not an escape character
			int	iResult = *pLine;

			iResult += 256 - 42;
			iResult &= 0xff;

			*pResult = iResult;
		}

		pLine++;
		pResult++;
		*piResult = *piResult + 1;
	}

	return true;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool UUDecodeLine64 (  char *pLine,  char *pResult, int *piResult )
{
	int			iNbBytes;

	BuildDecodeTable ( );

	//	Get line size.
	iNbBytes = strlen ( pLine );

	*piResult = 0;

	while ( iNbBytes > 0 )
	{
		pLine [ 0 ] = DecodeTable [ pLine [ 0 ] ];
		pLine [ 1 ] = DecodeTable [ pLine [ 1 ] ];
		pLine [ 2 ] = DecodeTable [ pLine [ 2 ] ];
		pLine [ 3 ] = DecodeTable [ pLine [ 3 ] ];

		if ( UUDecodeBytes ( pLine [ 0 ], pLine [ 1 ], pLine [ 2 ], pLine [ 3 ], pResult ) == false )
		{
			return false;
		}

		pLine		+= 4;
		pResult		+= 3;

		iNbBytes	-= 4;
		*piResult	+= 3;
	}

	return true;
}
