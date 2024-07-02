#include "stdafx.h"

#ifdef	_CONSOLE
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include <malloc.h>
#include <string.h>
#include <stdarg.h>

#endif
#include <direct.h>
#include <errno.h>

#include "OEMessagesRoutines.h"
#include "FileRoutines.h"
#include "DisplayAndTrace.h"
#include "OEAddressRoutines.h"
#include "DecodeRoutines.h"
#include "FileTime.h"

//
//		The message  file.
static	char					szMsgFilename [ LEN_PATHNAME ]		= "";
static	HANDLE					hMsgFile							= INVALID_HANDLE_VALUE;
static	FILE					*hMsgFile2							= NULL;
static	unsigned long			iMsgFile							= 0;

//
//		Full buffer
static char						*pBufferAddress						= NULL;
static unsigned long			lBufferLength						= 0;
static unsigned long			lBufferPosition						= 0;
static unsigned long			lBufferOffset						= 0;
static bool						bBufferInvalid						= false;

//
//		Some counters.
static	int						iNumOfMessages						= 0;

//		Keep Files
static	bool					bKeep								= false;

//		Over Write or Leave
static	bool					bMsgLeave							= true;

//		The message filename parameters.
static	int						tabValuesName [ 4 ]					=
	{
		MSG_NAME_OBJECT, 
		MSG_NAME_MESSAGE_ID,
		MSG_NAME_NONE,
		MSG_NAME_NONE
	};
static	int						tabSizesName [ 4 ]					=
	{
		127, 127, 127, 127
	};

static	char					szExtension [ LEN_SMALLSTRING ]		= ".nws";

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void AllocateBufferMemory ( )
{
	if ( pBufferAddress == NULL )
	{
//		Allocate the buffer.
		lBufferLength = 2 * 1024 * 1024;

		pBufferAddress = ( char * ) malloc ( lBufferLength );
		if ( pBufferAddress == NULL )
		{
			DisplayError ( "Unable to allocate %08lx bytes\n", lBufferLength );
			ExitProgram ( 255 );
		}

		InitMsgBuffer ( );
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void FreeBufferMemory ( )
{
	//		Free buffer
	if ( pBufferAddress != NULL )
	{
		free ( pBufferAddress );
		pBufferAddress = NULL;
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void InitMsgBuffer ( )
{
	if ( pBufferAddress != NULL && lBufferLength != 0 )
	{
		//
		//	Initialize buffer.
		lBufferPosition	= 0;
		lBufferOffset	= 0;
		memset ( pBufferAddress, 0, lBufferLength );
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
unsigned long GetBufferSize ( )
{
	return lBufferPosition;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CloseMsgFile ( )
{
	if ( hMsgFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle ( hMsgFile );
		hMsgFile = INVALID_HANDLE_VALUE;

        if  ( strlen(szMsgFilename) > 0 )
        {
		    ModifyFileTime ( szMsgFilename, GetDate ( ) );
        }
	}

	if ( hMsgFile2 != NULL )
	{
		fclose ( hMsgFile2 );
		hMsgFile2 = NULL;

        if  ( strlen(szMsgFilename) > 0 )
        {
    		ModifyFileTime ( szMsgFilename, GetDate ( ) );
        }
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//		Open new file.
//
///////////////////////////////////////////////////////////////////////////////
static void OpenNewMsgFile ( )
{
	hMsgFile = 
		CreateFile ( szMsgFilename,			// file name
					GENERIC_WRITE,			// access mode
					NULL,					// share mode
					NULL,					// Security Attributes,
					CREATE_ALWAYS,			// how to create
					FILE_ATTRIBUTE_NORMAL,	// file attributes
					NULL	);				// handle to template file
	if ( hMsgFile == INVALID_HANDLE_VALUE )
	{
		DisplayErrorAndExit ( 255, &ExitProgram, "001 - fopen msgfile", "Error creating %s\n", szMsgFilename );
		return;
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//		Create the message file.
//
///////////////////////////////////////////////////////////////////////////////
void CreateMsgFile ( char *pDirectory )
{
	InitMsgBuffer ( );
	bBufferInvalid	= false;
	lBufferPosition	= 0;
	lBufferOffset	= 0;

	sprintf_s ( szMsgFilename, sizeof ( szMsgFilename ),  "%s\\OutLookExtract%08d%s", 
				pDirectory, iMsgFile, szExtension );

	iNumOfMessages++;

	iMsgFile++;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static void WriteNewMsgFile ( char *pBuffer, unsigned long lSize )
{
	if ( hMsgFile == INVALID_HANDLE_VALUE )
	{
		DisplayErrorAndExit ( 255, &ExitProgram, "001 - fopen msgfile", "Error creating %s\n", szMsgFilename );
		return;
	}

	DWORD NumberOfBytesWritten;
	BOOL bSuccess = 
		WriteFile(
		hMsgFile,				// handle to file
		pBuffer,				// data buffer
		lSize,					// number of bytes to write
		&NumberOfBytesWritten,	// number of bytes written
		NULL );					// overlapped buffer

}
//
///////////////////////////////////////////////////////////////////////////////
//		Create the message file.
//
///////////////////////////////////////////////////////////////////////////////
void WriteMsgFile ( char *pBuffer, unsigned long lSize )
{
	//		Store the buffer in memory.
	if ( lSize > 0 )
	{
		if ( lBufferPosition + lSize < lBufferLength && ! bKeep )
		{
			memcpy ( pBufferAddress + lBufferPosition, pBuffer, lSize );
			lBufferPosition += lSize;
		}
		else
		{
			//	If the buffer was not previuosly invalid; create file
			//	and write buffer.
			if ( ! bBufferInvalid )
			{
				OpenNewMsgFile ( );

				if ( lBufferPosition != 0 )
				{
					WriteNewMsgFile ( pBufferAddress, lBufferPosition );
				}
			}

			bBufferInvalid	= true;

			WriteNewMsgFile ( pBuffer, lSize );
		}
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//		Delete the message file.
//
///////////////////////////////////////////////////////////////////////////////
void RenameMsgFile ( char *pDirectory )
{
	if ( bBufferInvalid || bKeep )
	{

		char szName [ LEN_PATHNAME ];
		char szNewName [ LEN_PATHNAME ];

		memset ( szName, 0, sizeof ( szName ) );
		strcpy_s ( szName, sizeof ( szName ), pDirectory );
		strcat_s ( szName, sizeof ( szName ), "\\" );

		for ( int iX = 0; iX < sizeof ( tabValuesName ) / sizeof ( tabValuesName [ 1 ] ); iX++ )
		{

			switch ( tabValuesName [ iX ] )
			{

				case MSG_NAME_OBJECT :
				{
					CorrectFilename ( GetSubject ( ) );
					strncat_s ( szName, sizeof ( szName ),
								GetSubject ( ), tabSizesName [ iX ] );
					break;
				}

				case MSG_NAME_DATE :
				{
					CorrectFilename ( GetDate ( ) );
					strncat_s ( szName, sizeof ( szName ),
								GetDate ( ), tabSizesName [ iX ] );
 					break;
				}

				case MSG_NAME_AUTHOR :
				{
					CorrectFilename ( GetAuthor ( ) );
					strncat_s ( szName, sizeof ( szName ),
								GetAuthor ( ), tabSizesName [ iX ] );
					break;
				}

				case MSG_NAME_EMAIL :
				{
					CorrectFilename ( GetEMail ( ) );
					strncat_s ( szName, sizeof ( szName ),
								GetEMail ( ), tabSizesName [ iX ] );
					break;
				}

				case MSG_NAME_MESSAGE_ID :
				{
					CorrectFilename ( GetMessageID ( ) );
					strncat_s ( szName, sizeof ( szName ), 
								GetMessageID ( ), tabSizesName [ iX ] );
					break;
				}

				default :
				{
					break;
				}
			}
		}

		strcpy_s ( szNewName, sizeof ( szNewName ), szName );
		strcat_s ( szNewName, sizeof ( szNewName ), szExtension );

		int	iStatus;
		int	iCount		= 0;

		do
		{
			if ( ! bMsgLeave )
			{
				_unlink ( szNewName );
			}

			iStatus = rename ( szMsgFilename, szNewName );
			if ( iStatus == 0 )
			{
				strcpy_s ( szMsgFilename, sizeof ( szMsgFilename ), szNewName );
			}
			else
			{
				strcpy_s ( szNewName, sizeof ( szNewName ), szName );
				sprintf_s ( szNewName + strlen ( szNewName ), 
							sizeof ( szNewName ) - strlen ( szNewName ),
							" (%d)%s", 
							iCount + 1, szExtension );
			}

			iCount++;						
		}
		while ( iStatus != 0 && iCount < 100 );
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//		Delete the message file.
//
///////////////////////////////////////////////////////////////////////////////
void DeleteMsgFile ( char *pDirectory )
{
	if ( bBufferInvalid || bKeep )
	{
		if ( szMsgFilename )
		{
			if ( ! bKeep )
			{
				_unlink ( szMsgFilename );
			}
			else
			{
				RenameMsgFile ( pDirectory );
			}
		}
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//		Read msg file.
//
///////////////////////////////////////////////////////////////////////////////
void ReadMsgFile ( char *pLine, size_t iSize )
{
	char		*pTemp;

	memset ( pLine, 0, iSize );

	if ( bBufferInvalid )
	{
		if ( hMsgFile2 != NULL )
		{
			fgets ( pLine, iSize - 1, hMsgFile2 );
			if ( feof ( hMsgFile2 ) || ferror ( hMsgFile2 ) )
			{
				return;
			}

			while ( strlen ( pLine ) )
			{
				if (	pLine [ strlen ( pLine ) - 1 ] != '\n' 
					&&	pLine [ strlen ( pLine ) - 1 ] != '\r' )
				{
					return;
				}
				pLine [ strlen ( pLine ) - 1 ] = 0;

			}
		}
	}
	else
	{
		pTemp = pLine;
		while ( lBufferOffset < lBufferPosition && iSize > 0 )
		{
			*pTemp = pBufferAddress [ lBufferOffset ];
			lBufferOffset++;

			if ( *pTemp == '\n' || iSize <= 1 )
			{
				while ( strlen ( pLine ) > 0 )
				{
					if (	pLine [ strlen ( pLine ) - 1 ] != '\n' 
						&&	pLine [ strlen ( pLine ) - 1 ] != '\r' )
					{
						return;
					}
					pLine [ strlen ( pLine ) - 1 ] = 0;

				}

				return;
			}

			iSize--;
			pTemp++;

		}
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetBoolKeep ( bool bValue )
{
	bKeep = bValue;
}

//
///////////////////////////////////////////////////////////////////////////////
//		Exit program.
//
///////////////////////////////////////////////////////////////////////////////
static void ExitProgram ( int iError )
{
	CloseDbxFile ( );

	CloseLogFile ( );

	CloseMsgFile ( );

#ifdef	_CONSOLE
	exit ( iError );
#endif

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int MsgFileEof ( )
{
	if ( bBufferInvalid )
	{
		if ( hMsgFile2 != NULL )
		{
			return ( feof ( hMsgFile2 ) );
		}
		else
		{
			return TRUE;
		}
	}

	return ( lBufferOffset >= lBufferPosition );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int MsgFileError ( )
{
	if ( bBufferInvalid )
	{
		if ( hMsgFile2 != NULL )
		{
			return ( ferror ( hMsgFile2 ) );
		}
		else
		{
			return TRUE;
		}
	}

	return 0;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void OpenMsgFile ( )
{
	//
	//		Open file.
	lBufferOffset	= 0;

	if ( bBufferInvalid )
	{
		hMsgFile2 = NULL;
		fopen_s ( &hMsgFile2, szMsgFilename, "r" );
		if ( hMsgFile2 == NULL )
		{
			DisplayErrorAndExit ( 255, &ExitProgram, "009 - fopen msg", "" );
			return;
		}
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ZeroNumOfMessages ()
{
	iNumOfMessages	= 0;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int GetNumOfMessages ()
{
	return iNumOfMessages;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *GetMsgFilename ( )
{
	return szMsgFilename;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetNameFormat (	int iName1,int iName2,int iName3,int iName4,
						int iSize1,int iSize2,int iSize3,int iSize4 )
{
	tabValuesName [ 0 ] = iName1;
	tabValuesName [ 1 ] = iName2;
	tabValuesName [ 2 ] = iName3;
	tabValuesName [ 3 ] = iName4;
	tabSizesName [ 0 ]	= iSize1;
	tabSizesName [ 1 ]	= iSize2;
	tabSizesName [ 2 ]	= iSize3;
	tabSizesName [ 3 ]	= iSize4;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *GetMsgExtension ( )
{
	return szExtension;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetMsgExtension ( const char *pText )
{
	strcpy_s ( szExtension, sizeof ( szExtension ), pText );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetBoolMsgLeave ( bool bValue )
{
	bMsgLeave = bValue;
}
