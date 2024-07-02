#include "stdafx.h"

#ifdef	_CONSOLE
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>

#include <malloc.h>
#include <string.h>
#include <stdarg.h>
//#include <error.h>
#include <errno.h>
#endif

#include "TextRoutines.h"

/*
 *		A table for the charset.
 */
static	unsigned char			CharSet [ 256 ];
static	bool					bCharSet		= false;

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static void BuildCharSet ( )
{
	int		iX;

	if ( bCharSet )
	{
		return;
	}

	bCharSet = true;

	for ( iX = 0; iX < sizeof ( CharSet ); iX++ )
	{
		CharSet [ iX ] = iX;
	}

	for ( iX = 'A'; iX <= 'Z'; iX++ )
	{
		CharSet [ iX ] = iX + ' ';
	}

	CharSet [ ( unsigned char ) 'à' ] = 'a';
	CharSet [ ( unsigned char ) 'â' ] = 'a';
	CharSet [ ( unsigned char ) 'ä' ] = 'a';
	CharSet [ ( unsigned char ) 'ã' ] = 'a';

	CharSet [ ( unsigned char ) 'ç' ] = 'c';

	CharSet [ ( unsigned char ) 'é' ] = 'e';
	CharSet [ ( unsigned char ) 'è' ] = 'e';
	CharSet [ ( unsigned char ) 'ê' ] = 'e';
	CharSet [ ( unsigned char ) 'ë' ] = 'e';

	CharSet [ ( unsigned char ) 'î' ] = 'i';
	CharSet [ ( unsigned char ) 'ï' ] = 'i';

	CharSet [ ( unsigned char ) 'ô' ] = 'o';
	CharSet [ ( unsigned char ) 'ö' ] = 'o';

	CharSet [ ( unsigned char ) 'ù' ] = 'u';
	CharSet [ ( unsigned char ) 'û' ] = 'u';
	CharSet [ ( unsigned char ) 'ü' ] = 'u';

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool IsDigit ( char cByte )
{
        if ( cByte >= '0' && cByte <= '9' )
        {
                return true;
        }

        return false;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool IsNumber ( char cByte )
{
        if ( IsDigit ( cByte ) )
        {
                return true;
        }

        if ( cByte == '.' )
        {
                return true;
        }

        return false;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool IsSignedNumber ( char cByte )
{
        if ( IsNumber ( cByte ) )
        {
                return true;
        }

        if ( cByte == '-' )
        {
                return true;
        }

        return false;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool IsUpper ( char cByte )
{
        if ( cByte >= 'A' && cByte <= 'Z' )
        {
                return true;
        }

        return false;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool IsLower ( char cByte )
{
        if ( cByte >= 'a' && cByte <= 'z' )
        {
                return true;
        }

        return false;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool IsLetter ( char cByte )
{
        if ( IsLower ( cByte ) )
        {
                return true;
        }

        if ( IsUpper ( cByte ) )
        {
                return true;
        }

        return false;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool CapitalizeName ( char *pString )
{
        bool            bChanged;
        char            cLast;

        bChanged = false;
        cLast     = '_';

        while ( *pString && ( *pString != '.' ) )
        {
                if ( IsLetter ( cLast  ) )
                {
                        if ( IsUpper ( *pString  ) )
                        {
                                *pString += 0x20;
                                bChanged = true;
                        }
                }
                else
                {
                        if ( IsLower ( *pString  ) )
                        {
                                *pString -= 0x20;
                                bChanged = true;
                        }
                }

                cLast = *pString;

                pString++;
        }

        return ( bChanged );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool CapitalizeFullName ( char *pString )
{
        bool            bChanged;
        char            cLast;

        bChanged = false;
        cLast     = '_';

        while ( *pString )
        {
                if ( IsLetter ( cLast  ) )
                {
                        if ( IsUpper ( *pString  ) )
                        {
                                *pString += 0x20;
                                bChanged = true;
                        }
                }
                else
                {
                        if ( IsLower ( *pString  ) )
                        {
                                *pString -= 0x20;
                                bChanged = true;
                        }
                }

                cLast = *pString;

                pString++;
        }

        return ( bChanged );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool LowerName ( char *pString )
{
        bool             bChanged;

        bChanged = false;

        while ( *pString )
        {
                if ( IsUpper ( *pString ) )
                {
                        *pString += 0x20;
                        bChanged = true;
                }
                pString++;
        }

        return ( bChanged );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool UpperName ( char *pString )
{
        bool            bChanged;

        bChanged = false;

        while ( *pString )
        {
                if ( IsLower ( *pString ) )
                {
                        *pString -= 0x20;
                        bChanged = true;
                }
                pString++;
        }

        return ( bChanged );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int CompareStringU ( unsigned char *pOne, unsigned char *pTwo )
{
	BuildCharSet ( );

	while ( *pOne != 0 && *pTwo != 0 )
	{
		if ( CharSet [ *pOne ] < CharSet [ *pTwo ] )
		{
			return -1;
		}

		if ( CharSet [ *pOne ] > CharSet [ *pTwo ] )
		{
			return 1;
		}

		pOne++;
		pTwo++;
	}

	if ( CharSet [ *pOne ] < CharSet [ *pTwo ] )
	{
		return -1;
	}

	if ( CharSet [ *pOne ] > CharSet [ *pTwo ] )
	{
		return 1;
	}

	return 0;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int CompareString ( char *pOne, char *pTwo )
{

	return CompareStringU ( ( unsigned char * ) pOne, ( unsigned char * ) pTwo );
	
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int CompareNStringU ( unsigned char *pOne, unsigned char *pTwo, size_t iLen )
{
	BuildCharSet ( );

	while ( *pOne != 0 && *pTwo != 0 && iLen > 0 )
	{
		if ( CharSet [ *pOne ] < CharSet [ *pTwo ] )
		{
			return -1;
		}

		if ( CharSet [ *pOne ] > CharSet [ *pTwo ] )
		{
			return 1;
		}

		pOne++;
		pTwo++;

		iLen--;
	}

	if ( iLen == 0 )
	{
		return 0;
	}

	if ( CharSet [ *pOne ] < CharSet [ *pTwo ] )
	{
		return -1;
	}

	if ( CharSet [ *pOne ] > CharSet [ *pTwo ] )
	{
		return 1;
	}

	return 0;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int CompareNString ( char *pOne, char *pTwo, size_t iLen )
{

	return CompareNStringU ( ( unsigned char * ) pOne, ( unsigned char * ) pTwo, iLen );
	
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
unsigned char *StringSearchU ( unsigned char *pString, unsigned char *pSearched )
{
	BuildCharSet ( );

	if ( *pString == 0 )
	{
		return NULL;
	}

	if ( *pSearched == 0 )
	{
		return pString;
	}

	while ( *pString != 0 )
	{
		if ( CompareNStringU ( pString, pSearched, strlen ( ( char * ) pSearched ) ) == 0 )
		{
			return pString;
		}

		pString++;
	}

	return NULL;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *StringSearch ( char *pString, char *pSearched )
{

	return ( char * ) StringSearchU ( ( unsigned char * ) pString , ( unsigned char * ) pSearched );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
unsigned char *StringSearchMatchU ( unsigned char *pString, unsigned char *pSearched )
{
	BuildCharSet ( );

	if ( *pString == 0 )
	{
		return NULL;
	}

	if ( *pSearched == 0 )
	{
		return pString;
	}

	while ( *pString != 0 )
	{
		unsigned char	*pFound;

		pFound = StringMatchU ( pString, pSearched );
		if ( pFound != NULL )
		{
			return pString;
		}

		pString++;
	}

	return NULL;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *StringSearchMatch ( char *pString, char *pSearched )
{

	return ( char * ) StringSearchMatchU ( ( unsigned char * ) pString , ( unsigned char * ) pSearched );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
unsigned char *StringMatchU ( unsigned char *pOne, unsigned char *pTwo )
{

	BuildCharSet ( );

	while ( *pOne != 0 && *pTwo != 0 )
	{
		if ( CharSet [ *pTwo ] != '?' && CharSet [ *pTwo ] != '*' )
		{
			if ( CharSet [ *pOne ] != CharSet [ *pTwo ] )
			{
				return NULL;
			}
		}

		if ( CharSet [ *pTwo ] == '*' )
		{
			pTwo++;
			unsigned char *pFound = StringSearchMatchU ( pOne, pTwo );
			if ( pFound == NULL )
			{
				return NULL;
			}
			pOne = pFound;
		}
		else
		{
			pOne++;
			pTwo++;
		}
	}

	if ( CharSet [ *pTwo ] == 0 || CharSet [ *pTwo ] == '*' )
	{
		return pOne;
	}

	if ( CharSet [ *pOne ] != CharSet [ *pTwo ] )
	{
		return NULL;
	}

	return pOne;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *StringMatch ( char *pOne, char *pTwo )
{
	
	return ( char * ) StringMatchU ( ( unsigned char * ) pOne, ( unsigned char * ) pTwo );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *SearchString ( char *pString, char *pSearched )
{
	while ( *pString )
	{
		if ( CompareNString ( pString, pSearched, strlen ( pSearched ) ) == 0 )
		{
			return pString;
		}

		pString++;
	}

	return NULL;
}
 
//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool RemoveString ( char *pString, char *pRemove )
{
	char			*pFound;

	if ( pRemove == NULL || pString == NULL )
	{
		return false;
	}

	if ( strlen ( pRemove ) == 0 || strlen ( pString ) == 0 )
	{
		return false;
	}

	pFound = SearchString ( pString, pRemove );
	if ( pFound == NULL )
	{
		return false;
	}

	memmove ( pFound, pFound + strlen ( pRemove ), strlen ( pFound + strlen ( pRemove ) ) + 1 );

	return true;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ReplaceCharacter ( char *pString, char cRemove, char cInsert )
{
	while ( *pString )
	{
		if ( *pString == cRemove )
		{
			*pString = cInsert;
		}

		pString++;
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ReplaceTabAndSo ( char *pString )
{
	ReplaceCharacter ( pString, '\t', ' ' );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool ReplaceString ( char *pString, char *pRemove, char *pInsert )
{
	char			*pFound;

	if ( pRemove == NULL || pString == NULL )
	{
		return false;
	}

	if ( strlen ( pRemove ) == 0 || strlen ( pString ) == 0 )
	{
		return false;
	}

	pFound = SearchString ( pString, pRemove );
	if ( pFound == NULL )
	{
		return false;
	}

	//		Remove String
	memmove ( pFound, pFound + strlen ( pRemove ), strlen ( pFound + strlen ( pRemove ) ) + 1 );

	//		Isert String.
	if ( strlen ( pInsert ) > 0 )
	{
		memmove ( pFound + strlen ( pInsert ), pFound, strlen ( pFound ) + 1 );
		memcpy ( pFound, pInsert, strlen ( pInsert ) );
	}

	return true;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RemoveNumbers ( char *pString )
{
	while ( *pString )
	{
		if ( IsDigit ( *pString ) )
		{
			*pString = ' ';
		}
		pString++;
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RemoveOther ( char *pString )
{
	while ( *pString )
	{
		if ( ! IsNumber ( *pString ) && ! IsLower ( *pString ) && ! IsUpper ( *pString ) )
		{
			*pString = ' ';
		}
		pString++;
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RemoveLeadingChars ( char *pString, const char cByte )
{
	while ( pString [ 0 ] == cByte )
	{
		memmove ( pString, pString + 1, strlen ( pString ) );
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RemoveLeadingSpaces ( char *pString )
{
	ReplaceTabAndSo ( pString );

	RemoveLeadingChars ( pString, ' ' );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RemoveLeadingUnderscore ( char *pString )
{
	RemoveLeadingChars ( pString, '_' );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RemoveTrailingSpaces ( char *pString )
{
	int			iX;
	int			iL;

	ReplaceTabAndSo ( pString );

	iL = strlen ( pString );
	if ( iL > 0 )
	{
		for ( iX = iL - 1; iX >= 0; iX-- )
		{
			if ( pString [ iX ] != ' ' && pString [ iX ] != '\t' )
			{
				return;
			}
			pString [ iX ] = 0;
		}
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void FilterWithCharSetU ( unsigned char *pString )
{
	BuildCharSet ( );

	while ( *pString )
	{
		*pString = CharSet [ *pString ];
		pString++;
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void FilterWithCharSet ( char *pString )
{
	FilterWithCharSetU ( ( unsigned char * ) pString );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RemoveMultipleDot ( char *pString )
{
	if ( SearchString ( pString, ".." ) )
	{
		while ( ReplaceString ( pString, "..", "." ) );
		return;
	}

	return;

}

//
///////////////////////////////////////////////////////////////////////////////
//		Remove space dot sequence.
//
///////////////////////////////////////////////////////////////////////////////
void ReplaceSpaceDot ( char *pString )
{
	if ( SearchString ( pString, " ." ) )
	{
		while ( ReplaceString ( pString, " .", "." ) );
		return;
	}

	return;

}

//
///////////////////////////////////////////////////////////////////////////////
//		Remove multiple underscore.
//
///////////////////////////////////////////////////////////////////////////////
void RemoveMultipleUnderscore ( char *pString )
{
	if ( SearchString ( pString, "__" ) )
	{
		while ( ReplaceString ( pString, "__", "_" ) );
		return;
	}

	return;

}

//
///////////////////////////////////////////////////////////////////////////////
//		Leave only on dot.
//
///////////////////////////////////////////////////////////////////////////////
void LeaveOneDot ( char *pString )
{
	bool	bDot;
	int		iX;

	bDot = false;
	iX = strlen ( pString );

	while ( iX > 0 )
	{
		if ( pString [ iX - 1 ] == '.' )
		{
			if ( bDot )
			{
				pString [ iX - 1 ] = ' ';
			}
			else
			{
				bDot = true;
			}
		}

		iX--;
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//		Collapse
//
///////////////////////////////////////////////////////////////////////////////
bool Collapse ( char *pFilename )
{
	ReplaceTabAndSo ( pFilename );

	if ( SearchString ( pFilename, "  " ) )
	{
		while ( ReplaceString ( pFilename, "  ", " " ) );
		return true;
	}

	return false;
}

