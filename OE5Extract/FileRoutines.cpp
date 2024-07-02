#include "stdafx.h"

#ifdef	_CONSOLE

#include <stdlib.h>
#include <stdio.h>
#include <direct.h>
#include "stdafx.h"

#include <malloc.h>
#include <string.h>
#include <stdarg.h>
//#include <error.h>
#include <errno.h>

#endif

#include "TextRoutines.h"
#include "FileRoutines.h"
#include "DisplayAndTrace.h"

//
///////////////////////////////////////////////////////////////////////////////
//		Find the type of a file.
//
///////////////////////////////////////////////////////////////////////////////
char *FindType ( char *pFilename )
{
	int		iX;

	iX = strlen ( pFilename ) - 1;

	while ( iX > 0 )
	{
		if ( pFilename [ iX ] == '.' )
		{
			return pFilename + iX;
		}

		iX--;
	}

	return ".";
}

//
///////////////////////////////////////////////////////////////////////////////
//		Find the type of a file.
//
///////////////////////////////////////////////////////////////////////////////
char *FindTypeOrNull ( char *pFilename )
{
	int		iX;

	iX = strlen ( pFilename ) - 1;

	while ( iX > 0 )
	{
		if ( pFilename [ iX ] == '.' )
		{
			return pFilename + iX;
		}

		iX--;
	}

	return NULL;
}

//
///////////////////////////////////////////////////////////////////////////////
//		Find the name of a file.
//
///////////////////////////////////////////////////////////////////////////////
char *FindFilename ( char *pFilename )
{
	int		iX;

	iX = strlen ( pFilename ) - 1;

	while ( iX > 0 )
	{
		if ( pFilename [ iX ] == '\\' )
		{
			return pFilename + iX + 1;
		}

		if ( pFilename [ iX ] == ':' )
		{
			return pFilename + iX + 1;
		}

		iX--;
	}

	return pFilename;
}

//
///////////////////////////////////////////////////////////////////////////////
//		Find the name of a file.
//
///////////////////////////////////////////////////////////////////////////////
char *FindDirectory ( const char *pFilename )
{
		int		iX;

static	char	szDirectory [ LEN_FILENAME ];

		strcpy_s ( szDirectory, sizeof ( szDirectory ), pFilename );

		iX = strlen ( szDirectory ) - 1;

		while ( iX > 0 )
		{
			if ( szDirectory [ iX ] == '\\' )
			{
				szDirectory [ iX ] = 0;
				return szDirectory;
			}

			if ( szDirectory [ iX ] == ':' )
			{
				szDirectory [ iX + 1 ] = '\\';
				szDirectory [ iX + 2 ] = 0;
				return szDirectory;
			}

			iX--;
		}

		return szDirectory;
}

//
///////////////////////////////////////////////////////////////////////////////
//		Correct directory name.
//
///////////////////////////////////////////////////////////////////////////////
void CorrectDirectory ( char *pFilename )
{
	while ( *pFilename )
	{
		if ( *pFilename < ' ' )
		{
			*pFilename = ' ';
		}

		if ( *pFilename >= 0x7f )
		{
			*pFilename = ' ';
		}

		if ( *pFilename == '*' )
		{
			*pFilename = '-';
		}

		if ( *pFilename == '?' )
		{
			*pFilename = '-';
		}

		if ( *pFilename == '<' )
		{
			*pFilename = '-';
		}

		if ( *pFilename == '>' )
		{
			*pFilename = '-';
		}

		if ( *pFilename == '|' )
		{
			*pFilename = '-';
		}

		if ( *pFilename == '\"' )
		{
			*pFilename = '-';
		}

		pFilename++;
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//		Correct filename.
//
///////////////////////////////////////////////////////////////////////////////
void CorrectFilename ( char *pFilename )
{
	CorrectDirectory ( pFilename );

	while ( *pFilename )
	{

		if ( *pFilename == '\\' )
		{
			*pFilename = '_';
		}

		if ( *pFilename == '/' )
		{
			*pFilename = '_';
		}

		if ( *pFilename == ':' )
		{
			*pFilename = '_';
		}

		pFilename++;
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//		Filter Name.
//
///////////////////////////////////////////////////////////////////////////////
void FilterName ( char *pString,  bool bDir )
{

		FilterWithCharSet ( pString );

		if ( bDir )
		{
			CorrectDirectory ( pString );
		}
		else
		{
			CorrectFilename  ( pString );
		}

        return;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RemoveLeadingDirectory ( char *pString, size_t iString, char *pUpDir )
{
        char            szTempName [ LEN_FILENAME ];
        char            szTempDir [ LEN_FILENAME ];
        char            szTempDir2 [ LEN_FILENAME ];

        strcpy_s ( szTempName, sizeof ( szTempName ), pString );
        strcpy_s ( szTempDir, sizeof ( szTempDir ), pUpDir );

		ReplaceCharacter ( szTempDir, '.', '_' );

        if ( strlen ( szTempDir ) == 1 )
        {
                return;
        }

        strcpy_s ( szTempDir2, sizeof ( szTempDir2 ), "The_" );
        strcat_s ( szTempDir2, sizeof ( szTempDir2 ), szTempDir );

        if ( CompareNString ( szTempName, szTempDir2, strlen ( szTempDir2 ) ) == 0 )
        {
                strcpy_s ( pString, iString, szTempName + strlen ( szTempDir2 ) );
        }

        if ( CompareNString ( szTempName, szTempDir, strlen ( szTempDir ) ) == 0 )
        {
                strcpy_s ( pString, iString, szTempName + strlen ( szTempDir ) );
        }


        return;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RemoveTrailingDirectory ( char *pString, size_t iString, char *pUpDir )
{
        char            szTempName [ LEN_FILENAME ];
        char            szTempDir [ LEN_FILENAME ];
        char            szTempDir2 [ LEN_FILENAME ];
        char            *pPointer;

        strcpy_s ( szTempName, sizeof ( szTempName ), pString );
        memset ( szTempDir, 0, sizeof ( szTempDir ) );
        strcpy_s ( szTempDir, sizeof ( szTempDir ), pUpDir );

        if ( strlen ( szTempDir ) == 1 )
        {
                return;
        }

		ReplaceCharacter ( szTempDir, '.', '_' );

        strcpy_s ( szTempDir2, sizeof ( szTempDir2 ), "_The" );
        strcat_s ( szTempDir2, sizeof ( szTempDir2 ), szTempDir );

        pPointer = SearchString ( szTempName, szTempDir2 );
        if ( pPointer != NULL )
        {
                *pPointer = '\0';
                strcpy_s ( pString, iString, szTempName );
                pPointer += strlen ( szTempDir2 );
                strcat_s ( pString, iString, pPointer );
        }

        pPointer = SearchString ( szTempName, szTempDir );
        if ( pPointer != NULL )
        {
                *pPointer = '\0';
                strcpy_s ( pString, iString, szTempName );
                pPointer += strlen ( szTempDir );
                strcat_s ( pString, iString, pPointer );
        }

        return;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RemoveTrailingNumbers ( char *pString, size_t iString )
{
        char            *pPointer;
        char            *pDot;
        char            szTemp [ LEN_FILENAME ];

        pDot = strchr ( pString, '.' );
        if ( pDot == NULL )
        {
                return ;
        }

        pPointer = pDot;
        pPointer--;

        if ( pPointer > pString + 1 )
        {
                if ( *pPointer == 'K' && *( pPointer - 1 ) >= '0'
                        &&  *( pPointer - 1 ) <= '9' )
                {
                        pPointer--;
                }
        }

        while (    ( pPointer > pString )
                && ( *pPointer >= '0' && *pPointer <= '9' ) )
        {
                pPointer--;
        }

        if ( pPointer < pString )
        {
                return ;
        }

        if  ( *( pPointer + 1 ) >= '0' &&  *( pPointer + 1 ) <= '9' )
        {
                if ( *pPointer == '_' )
                {
                        *pPointer = 0;
                }
                else
                {
                        *( pPointer + 1 ) = 0;
                }
                strcpy_s ( szTemp, sizeof ( szTemp ), pString );
                strcat_s ( szTemp, sizeof ( szTemp ), pDot );
                strcpy_s ( pString, iString, szTemp );
        }

        return;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
long GetFileLength ( FILE *hFile )
{
	if ( hFile == NULL )
	{
		return NULL;
	}

	long lPos = ftell ( hFile );

	fseek ( hFile, 0, SEEK_END );
	long lEnd = ftell ( hFile );

	fseek ( hFile, lPos, SEEK_SET );

	return lEnd;

}