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

#include "DecodeRoutines.h"
#include "OEAddressRoutines.h"
#include "OEMessagesRoutines.h"
#include "TextRoutines.h"
#include "DisplayAndTrace.h"
#include "MimeRoutines.h"
#include "FileRoutines.h"
#include "RemoveStringsRoutines.h"
#include "FileTime.h"

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//
//		Begin
//
#define	SUBJECT					"Subject: "
#define	AUTHOR					"From: "
#define	EMAIL					"Reply-To: "
#define	DATE					"Date: "
#define	MESSAGE_ID				"Message-ID: "
#define	ISO_8859_1_B			"=?iso-8859-1?B?"
#define	ISO_8859_1_Q			"=?iso-8859-1?Q? mais je ne sais pas que faire"
#define	ISO_8859_1_END			"?="

#define	BEGIN_600				"begin 600 "
#define	BEGIN_640				"begin 640 "
#define	BEGIN_644				"begin 644 "
#define	BEGIN_666				"begin 666 "
#define	BEGIN_755				"begin 755 "
#define	BEGIN_6XX				"begin 6"
#define	BEGIN_7XX				"begin 7"
#define	END_BEGIN				"end"

#define	BASE_64					"Content-Transfer-Encoding: base64"
#define	FILENAME_EQUAL_1		"Content-Disposition: inline; filename=\""
#define	FILENAME_EQUAL_2		"filename=\""
#define	FILENAME_EQUAL_3		"Content-Disposition: attachment; filename="
#define	FILENAME_EQUAL_4		"filename="
#define	FILENAME_EQUAL_5		"Content-Type: *; name=\""
#define	FILENAME_EQUAL_6		"Content-Type: *; name="
#define	FILENAME_EQUAL_7		"name=\""
#define	FILENAME_EQUAL_8		"name="

#define	BASE_64_END_1			"----"
#define	BASE_64_END_2			"--"

#define	YENC_BEGIN				"=ybegin part=* line=* size=* name="
#define	YENC_BEGIN2				"=ybegin * name="
#define	YENC_PART				"=ypart begin=* end=*"
#define	YENC_END				"=yend size=* part=* pcrc32="


//
//		The attachement message file.
static	char					szAttFilename [ LEN_PATHNAME ]		= "";
static	char					szAttBasename [ LEN_FILENAME ]		= "";
static	char					szAttSubjectName [ LEN_PATHNAME ]	= "";
static	HANDLE					hAttFile							= INVALID_HANDLE_VALUE;

static	char					szDirectory [ LEN_DIRECTORY ]		= "";

//
//		The subject.
static	char					szSubject [ LEN_PATHNAME ]			= "";

//
//		The Messages ID
static	char					szMessageID [ LEN_PATHNAME ]		= "";

//
//		The Author.
static	char					szAuthor [ LEN_FILENAME ]			= "";

//
//		The E/Mail.
static	char					szEmail [ LEN_FILENAME ]			= "";

//
//		The date.
static	char					szDate [ LEN_FILENAME ]				= "";

static	int						iNumOfAttachement					= 0;
static	int						iNumOfBase64						= 0;
static	int						iNumOfYenc							= 0;

//		The attachement
static	int						iAttachementCount					= 0;
static	int						iAttachementType					= 0;

//		Name only.
static	bool					bName								= false;

//		Subject only.
static	bool					bSubject							= false;

//		Collapse strings
static	bool					bCollapse							= false;

//		Remove Numbers
static	bool					bRemoveNumbers						= false;

//		Remove Special characters
static	bool					bRemoveOther						= false;

//		Replace or not the attachement file.
static	bool					bLeave								= false;

//		Only message.
static	bool					bOnlyMessages						= false;

static	char					szAttExtension [ LEN_SMALLSTRING ]	= ".unk";

//
///////////////////////////////////////////////////////////////////////////////
//		The message filename parameters.
//
///////////////////////////////////////////////////////////////////////////////
static	int						tabValuesAtt [ 5 ]						=
	{
		MSG_NAME_OBJECT, 
		MSG_NAME_MESSAGE_ID,
		MSG_NAME_ATT_NUMB,
		MSG_NAME_NONE,
		MSG_NAME_NONE
	};
static	int						tabSizesAtt [ 5 ]						=
	{
		127, 127, 127, 127, 127
	};

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CloseAttFile ( )
{
	if ( hAttFile != NULL )
	{
		CloseHandle ( hAttFile );
		hAttFile = INVALID_HANDLE_VALUE;

		ModifyFileTime ( szAttFilename, GetDate () );
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//		Exit program.
//
///////////////////////////////////////////////////////////////////////////////
static void ExitProgram ( int iError )
{
	CloseDbxFile ( );

	CloseAttFile ( );

	CloseLogFile ( );

	CloseMsgFile ( );

#ifdef	_CONSOLE
	exit ( iError );
#endif

}

//
///////////////////////////////////////////////////////////////////////////////
//		Filter the filename.
//
///////////////////////////////////////////////////////////////////////////////
void FilterFilename ( char *pFilename )
{
	if ( bRemoveNumbers )
	{
		RemoveNumbers ( pFilename );
	}

	if ( bRemoveOther )
	{
		RemoveOther ( pFilename );
	}

	RemoveAllStrings ( pFilename );

	if ( bCollapse )
	{
		Collapse ( pFilename );
	}

	RemoveLeadingSpaces ( pFilename );

	RemoveTrailingSpaces ( pFilename );

}

//
///////////////////////////////////////////////////////////////////////////////
//		Make a unique filename.
//
///////////////////////////////////////////////////////////////////////////////
void CheckTheName ( )
{
	int				iX;
	bool			bNameIsUsed = false;
	bool			bObjectIsUsed = false;

	char szName [ LEN_PATHNAME ];
	char szFullName [ LEN_PATHNAME ];

	memset ( szName, 0, sizeof ( szName ) );
	for ( iX = 0; iX < sizeof ( tabValuesAtt ) / sizeof ( tabValuesAtt [ 1 ] ); iX++ )
	{

		switch ( tabValuesAtt [ iX ] )
		{

			case MSG_NAME_OBJECT :
			{
				bObjectIsUsed = true;
				break;
			}

			case MSG_NAME_ATT_NAME :
			{
				bNameIsUsed = true;
				break;
			}

			default :
			{
				break;
			}
		}
	}

	if ( bNameIsUsed && bObjectIsUsed )
	{
		RemoveString ( szSubject, szAttBasename );
	}

	for ( iX = 0; iX < sizeof ( tabValuesAtt ) / sizeof ( tabValuesAtt [ 1 ] ); iX++ )
	{

		switch ( tabValuesAtt [ iX ] )
		{

			case MSG_NAME_OBJECT :
			{
				CorrectFilename ( szSubject );
				strncat_s ( szName, sizeof ( szName ), szSubject, tabSizesAtt [ iX ] );
				break;
			}

			case MSG_NAME_DATE :
			{
				CorrectFilename ( szDate );
				strncat_s ( szName, sizeof ( szName ), szDate, tabSizesAtt [ iX ] );
 				break;
			}

			case MSG_NAME_AUTHOR :
			{
				CorrectFilename ( szAuthor );
				strncat_s ( szName, sizeof ( szName ), szAuthor, tabSizesAtt [ iX ] );
				break;
			}

			case MSG_NAME_EMAIL :
			{
				CorrectFilename ( szEmail );
				strncat_s ( szName, sizeof ( szName ), szEmail, tabSizesAtt [ iX ] );
				break;
			}

			case MSG_NAME_MESSAGE_ID :
			{
				CorrectFilename ( szMessageID );
				strncat_s ( szName, sizeof ( szName ), szMessageID, tabSizesAtt [ iX ] );
				break;
			}

			case MSG_NAME_ATT_NAME :
			{
				CorrectFilename ( szAttBasename );
				strncat_s ( szName, sizeof ( szName ), szAttBasename, tabSizesAtt [ iX ] );
				break;
			}

			case MSG_NAME_ATT_NUMB :
			{
				sprintf_s ( szName + strlen ( szName ),
							sizeof ( szName ) - strlen ( szName ),
							"[%02d]", iAttachementCount );
				break;
			}

			default :
			{
				break;
			}
		}
	}

	FilterFilename ( szName );
	CorrectFilename ( szName );

	strcpy_s ( szFullName, sizeof ( szFullName ), szDirectory );
	strcat_s ( szFullName, sizeof ( szFullName ), "\\" );
	strcat_s ( szFullName, sizeof ( szFullName ), szName );

	RemoveString ( szFullName, FindType ( szAttBasename ) );

	if ( FindTypeOrNull ( szAttBasename ) )
	{
		strcat_s ( szFullName, sizeof ( szFullName ), FindType ( szAttBasename ) );
	}
	else
	{
		strcat_s ( szFullName, sizeof ( szFullName ), szAttExtension );
	}

	int	iCount		= 0;

	do
	{
		strcpy_s ( szAttFilename, sizeof ( szAttFilename ), szFullName );

		//		Check if file exist.
		hAttFile = 
			CreateFile ( szAttFilename,			// file name
						GENERIC_READ,			// access mode
						NULL,					// share mode
						NULL,					// Security Attributes,
						OPEN_EXISTING,			// how to create
						FILE_ATTRIBUTE_NORMAL,	// file attributes
						NULL	);				// handle to template file

		if ( hAttFile == INVALID_HANDLE_VALUE )
		{
			hAttFile = 
				CreateFile ( szAttFilename,			// file name
							GENERIC_WRITE,			// access mode
							NULL,					// share mode
							NULL,					// Security Attributes,
							CREATE_ALWAYS,			// how to create
							FILE_ATTRIBUTE_NORMAL,	// file attributes
							NULL	);				// handle to template file

			if ( hAttFile != INVALID_HANDLE_VALUE )
			{
				strcpy_s ( szAttBasename, sizeof ( szAttBasename ), szName );

				CloseAttFile ( );

				return;
			}
		}
		else
		{
			//		If replace or not.
			if ( ! bLeave )
			{
				strcpy_s ( szAttBasename, sizeof ( szAttBasename ), szName );

				CloseAttFile ( );

				return;
			}
		}

		CloseAttFile ( );

		strcpy_s ( szFullName, sizeof ( szFullName ), szDirectory );
		strcat_s ( szFullName, sizeof ( szFullName ), "\\" );
		strcat_s ( szFullName, sizeof ( szFullName ), szName );

		RemoveString ( szFullName, FindType ( szAttBasename ) );
		if ( FindTypeOrNull ( szAttBasename ) )
		{
			sprintf_s ( szFullName + strlen ( szFullName ), 
						sizeof ( szFullName ) - strlen ( szFullName ),
						" (%d)%s", 
						iCount + 1, FindType ( szAttBasename ) );
		}
		else
		{
			sprintf_s ( szFullName + strlen ( szFullName ), 
						sizeof ( szFullName ) - strlen ( szFullName ), 
						" (%d)%s", 
						iCount + 1, szAttExtension );
		}
		iCount++;						
	}
	while ( iCount < 100 );

}

//
///////////////////////////////////////////////////////////////////////////////
//		Decode file.
//
///////////////////////////////////////////////////////////////////////////////
bool DecodeFileLines ( )
{

	char				szLine [ LEN_LINE ];
	char				szResult [ LEN_LINE ];
	int					iResult;

	//	Check if file exist
	CheckTheName ( );

	DisplayText ( "Treating Encoded file: %s\n", szAttFilename );

	//	Now treat Lines.
	hAttFile = 
		CreateFile ( szAttFilename,			// file name
					GENERIC_WRITE,			// access mode
					NULL,					// share mode
					NULL,					// Security Attributes,
					CREATE_ALWAYS,			// how to create
					FILE_ATTRIBUTE_NORMAL,	// file attributes
					NULL	);				// handle to template file
	if ( hAttFile == INVALID_HANDLE_VALUE )
	{
		DisplayError ( "001- Unable to open file %s\n", szAttFilename );
		return false;
	}

	while ( ! MsgFileEof (  ) )
	{
		memset ( szLine, 0, sizeof ( szLine ) );
		ReadMsgFile ( szLine, sizeof ( szLine ) );
		RemoveLeadingSpaces ( szLine );

		if ( MsgFileEof ( ) )
		{
			CloseAttFile ( );
			return true;
		}

		if ( MsgFileError ( ) )
		{
			DisplayErrorAndExit ( 255, &ExitProgram, "002 - fgets msg", "" );
			return false;
		}

		if ( *szLine == 0 )
		{
			continue;
		}

		if ( CompareNString ( szLine, END_BEGIN, strlen ( END_BEGIN ) ) == 0 )
		{
			CloseAttFile ( );

			return true;
		}

		if ( UUDecodeLine (  szLine,  szResult, &iResult ) )
		{
			if ( hAttFile != INVALID_HANDLE_VALUE )
			{
				DWORD NumberOfBytesWritten;
				BOOL bSuccess = 
					WriteFile(
					hAttFile,				// handle to file
					szResult,				// data buffer
					iResult,				// number of bytes to write
					&NumberOfBytesWritten,	// number of bytes written
					NULL );					// overlapped buffer
			}
		}
		else
		{
			DisplayError ( "003 - Error decoding file %s\n", szAttFilename );

			CloseAttFile ( );

			return false;
		}
	}

	CloseAttFile ( );

	return true;
}

//
///////////////////////////////////////////////////////////////////////////////
//		Decode file.
//
///////////////////////////////////////////////////////////////////////////////
bool DecodeFileLinesYenc ( )
{

	char				szLine [ LEN_LINE ];
	char				szResult [ LEN_LINE ];
	int					iResult;

	//	Check if file exist
	CheckTheName ( );

	DisplayText ( "Treating Encoded file: %s\n", szAttFilename );

	//	Now treat Lines.
	hAttFile = 
		CreateFile ( szAttFilename,			// file name
					GENERIC_WRITE,			// access mode
					NULL,					// share mode
					NULL,					// Security Attributes,
					CREATE_ALWAYS,			// how to create
					FILE_ATTRIBUTE_NORMAL,	// file attributes
					NULL	);				// handle to template file
	if ( hAttFile == INVALID_HANDLE_VALUE )
	{
		DisplayError ( "001- Unable to open file %s\n", szAttFilename );
		return false;
	}

	while ( ! MsgFileEof (  ) )
	{
		memset ( szLine, 0, sizeof ( szLine ) );
		ReadMsgFile ( szLine, sizeof ( szLine ) );

		if ( MsgFileEof ( ) )
		{
			CloseAttFile ( );
			return true;
		}

		if ( MsgFileError ( ) )
		{
			DisplayErrorAndExit ( 255, &ExitProgram, "002 - fgets msg", "" );
			return false;
		}

		if ( *szLine == 0 )
		{
			continue;
		}

		if (  StringMatch ( szLine, YENC_PART ) != NULL )
		{
			continue;
		}

		if ( StringMatch ( szLine, YENC_END ) != NULL )
		{
			CloseAttFile ( );

			return true;
		}

		if ( YencDecodeLine (  szLine,  szResult, &iResult ) )
		{
			if ( hAttFile != INVALID_HANDLE_VALUE )
			{
				DWORD NumberOfBytesWritten;
				BOOL bSuccess = 
					WriteFile(
					hAttFile,				// handle to file
					szResult,				// data buffer
					iResult,				// number of bytes to write
					&NumberOfBytesWritten,	// number of bytes written
					NULL );					// overlapped buffer
			}
		}
		else
		{
			DisplayError ( "003 - Error decoding file %s\n", szAttFilename );

			CloseAttFile ( );

			return false;
		}
	}

	CloseAttFile ( );

	return true;
}

//
///////////////////////////////////////////////////////////////////////////////
//		Decode file.
//
///////////////////////////////////////////////////////////////////////////////
bool DecodeFile64Lines ( )
{

	char				szLine [ LEN_LINE ];
	char				szResult [ LEN_LINE ];
	int					iResult;

	//	Check if file exist
	CheckTheName ( );

	DisplayText ( "Treating Base 64 file: %s\n", szAttFilename );

	//	Now treat Lines.
	hAttFile = 
		CreateFile ( szAttFilename,			// file name
					GENERIC_WRITE,			// access mode
					NULL,					// share mode
					NULL,					// Security Attributes,
					CREATE_ALWAYS,			// how to create
					FILE_ATTRIBUTE_NORMAL,	// file attributes
					NULL	);				// handle to template file
	if ( hAttFile == INVALID_HANDLE_VALUE )
	{
		DisplayError ( "004 - Unable to open file %s\n", szAttFilename );
		return false;
	}

	while ( ! MsgFileEof (  ) )
	{
		memset ( szLine, 0, sizeof ( szLine ) );
		ReadMsgFile ( szLine, sizeof ( szLine ) );
		RemoveLeadingSpaces ( szLine );

		if ( MsgFileEof (  ) )
		{
			CloseAttFile ( );
			return true;
		}

		if ( MsgFileError ( ) )
		{
			DisplayErrorAndExit ( 255, &ExitProgram, "005 - fgets msg", "" );
			return false;
		}

		if ( *szLine == 0 )
		{
			continue;
		}

		if ( CompareNString ( szLine, SUBJECT, strlen ( SUBJECT ) ) == 0 )
		{
			memset ( szSubject, 0, sizeof ( szSubject ) );
			strncpy_s ( szSubject, 
						sizeof ( szSubject ),
						szLine + strlen ( SUBJECT ),
						sizeof ( szSubject ) - 1 );

			RemoveLeadingSpaces ( szSubject );

			/*
			 *		Maybe the subject is Mime Encoded.
			 */
			if ( strncmp ( szSubject, ISO_8859_1_B, strlen ( ISO_8859_1_B ) ) == 0 )
			{
				int		iResult;
				char	szResult [ LEN_PATHNAME ];
				memset ( szResult, 0, sizeof ( szResult ) );
				char	*pStr = strstr ( szSubject, ISO_8859_1_END );
				if ( pStr )
				{
					*pStr = 0;
					bool bResult = 
						UUDecodeLine64 ( szSubject + strlen ( ISO_8859_1_B ),
										szResult, &iResult );
					if ( bResult )
					{
						strcpy_s ( szSubject, sizeof ( szSubject ), szResult );
					}
				}
			}

		}

		if ( CompareNString ( szLine, MESSAGE_ID, strlen ( MESSAGE_ID ) ) == 0 )
		{
			memset ( szMessageID, 0, sizeof ( szMessageID ) );
			strncpy_s ( szMessageID, 
						sizeof ( szMessageID ),
						szLine + strlen ( MESSAGE_ID ),
						sizeof ( szMessageID ) - 1 );
			CorrectFilename ( szMessageID );
		}

		if ( CompareNString ( szLine, AUTHOR, strlen ( AUTHOR ) ) == 0 )
		{
			memset ( szAuthor, 0, sizeof ( szAuthor ) );
			strncpy_s ( szAuthor, 
						sizeof ( szAuthor ),
						szLine + strlen ( AUTHOR ), sizeof ( szAuthor ) -1 );

			if ( strncmp ( szAuthor, ISO_8859_1_Q, strlen ( ISO_8859_1_Q ) ) == 0 )
			{
				int		iResult;
				char	szResult [ LEN_PATHNAME ];
				memset ( szResult, 0, sizeof ( szResult ) );
				char	*pStr = strstr ( szAuthor, ISO_8859_1_END );
				if ( pStr )
				{
					*pStr = 0;
					bool bResult = 
						UUDecodeLine64 ( szAuthor + strlen ( ISO_8859_1_Q ),
										szResult, &iResult );
					if ( bResult )
					{
						strcpy_s ( szAuthor, sizeof ( szAuthor ), szResult );
					}
				}
			}

		}

		if ( CompareNString ( szLine, EMAIL, strlen ( EMAIL ) ) == 0 )
		{
			memset ( szEmail, 0, sizeof ( szEmail ) );
			strncpy_s ( szEmail,
						sizeof ( szEmail ),
						szLine + strlen ( EMAIL ), sizeof ( szEmail ) -1 );
		}

		if ( CompareNString ( szLine, DATE, strlen ( DATE ) ) == 0 )
		{
			memset ( szDate, 0, sizeof ( szDate ) );
			strncpy_s ( szDate, sizeof ( szDate ),
						szLine + strlen ( DATE ), sizeof ( szDate ) -1 );
		}

		if ( CompareNString ( szLine, BASE_64_END_1, strlen ( BASE_64_END_1 ) ) == 0 )
		{
			CloseAttFile ( );

			return true;
		}

		if ( CompareNString ( szLine, BASE_64_END_2, strlen ( BASE_64_END_2 ) ) == 0 )
		{
			CloseAttFile ( );

			return true;
		}

		if ( (  strlen ( szLine ) / 4 ) * 4 == strlen ( szLine ) )
		{
			if ( UUDecodeLine64 (  szLine,  szResult, &iResult ) )
			{
				if ( hAttFile )
				{
					DWORD NumberOfBytesWritten;
					BOOL bSuccess = 
						WriteFile(
						hAttFile,				// handle to file
						szResult,				// data buffer
						iResult,				// number of bytes to write
						&NumberOfBytesWritten,	// number of bytes written
						NULL );					// overlapped buffer
				}
			}
			else
			{
				DisplayError ( "006 - Error decoding file %s\n", szAttFilename );

				CloseAttFile ( );

				return false;
			}
		}
		else
		{
			DisplayError ( "007 - Error decoding file %s size is %d\n", 
				szAttFilename, strlen ( szLine ) );

			CloseAttFile ( );

			return false;
		}

	}

	CloseAttFile ( );

	return true;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool DecodeFileYenc ( )
{
	if ( MsgFileEof (  ) )
	{
		return true;
	}

	if ( MsgFileError (  ) )
	{
		DisplayErrorAndExit ( 255, &ExitProgram, "008 - fgets msg", "" );
		return false;
	}

	iAttachementCount++;

	if ( DecodeFileLinesYenc () )
	{
		return true;
	}

	return false;
}

//
///////////////////////////////////////////////////////////////////////////////
//		Decode file base 64.
//
///////////////////////////////////////////////////////////////////////////////
bool DecodeFile64 ( )
{
	char				szLine [ LEN_LINE ];

	bool				bToDecode = false;

	//
	//		Read file.
	while ( ! MsgFileEof (  ) )
	{
		memset ( szLine, 0, sizeof ( szLine ) );
		ReadMsgFile ( szLine, sizeof ( szLine ) );
		RemoveLeadingSpaces ( szLine );

		if ( MsgFileEof (  ) )
		{
			return true;
		}

		if ( MsgFileError (  ) )
		{
			DisplayErrorAndExit ( 255, &ExitProgram, "008 - fgets msg", "" );
			return false;

		}

		if (  CompareNString ( szLine, FILENAME_EQUAL_1, strlen ( FILENAME_EQUAL_1 ) ) == 0 )
		{
			iAttachementCount++;

			strcpy_s (	szAttBasename, 
						sizeof ( szAttBasename ),
						szLine + strlen ( FILENAME_EQUAL_1 ) );
			if ( strlen ( szAttBasename ) )
			{
				if ( szAttBasename [ strlen ( szAttBasename ) - 1 ] == '\"' )
				{
					szAttBasename [ strlen ( szAttBasename ) - 1 ] = 0;
				}
			}

			if ( ! bSubject && ! bName)
			{
				RemoveString ( szAttSubjectName, szAttBasename );
			} 

			CorrectFilename ( szAttBasename );


			if ( DecodeFile64Lines () )
			{
//				continue;
				return true;
			}

			return false;

		}

		if (  CompareNString ( szLine, FILENAME_EQUAL_2, strlen ( FILENAME_EQUAL_2 ) ) == 0 )
		{
			iAttachementCount++;

			strcpy_s ( szAttBasename, sizeof ( szAttBasename ),
						szLine + strlen ( FILENAME_EQUAL_2 ) );
			if ( strlen ( szAttBasename ) )
			{
				if ( szAttBasename [ strlen ( szAttBasename ) - 1 ] == '\"' )
				{
					szAttBasename [ strlen ( szAttBasename ) - 1 ] = 0;
				}
			}

			if ( ! bSubject && ! bName)
			{
				RemoveString ( szAttSubjectName, szAttBasename );
			}

			CorrectFilename ( szAttBasename );

			if ( DecodeFile64Lines () )
			{
//				continue;
				return true;
			}

			return false;
		}

		if (  CompareNString ( szLine, FILENAME_EQUAL_3, strlen ( FILENAME_EQUAL_3 ) ) == 0 )
		{
			iAttachementCount++;

			strcpy_s (	szAttBasename, sizeof ( szAttBasename ),
						szLine + strlen ( FILENAME_EQUAL_3 ) );
			if ( strlen ( szAttBasename ) )
			{
				if ( szAttBasename [ strlen ( szAttBasename ) - 1 ] == '\"' )
				{
					szAttBasename [ strlen ( szAttBasename ) - 1 ] = 0;
				}
			}

			if ( ! bSubject && ! bName)
			{
				RemoveString ( szAttSubjectName, szAttBasename );
			}

			CorrectFilename ( szAttBasename );

			if ( DecodeFile64Lines () )
			{
//				continue;
				return true;
			}

			return false;
		}

		if (  CompareNString ( szLine, FILENAME_EQUAL_4, strlen ( FILENAME_EQUAL_4 ) ) == 0 )
		{
			iAttachementCount++;

			strcpy_s (	szAttBasename, sizeof ( szAttBasename ),
						szLine + strlen ( FILENAME_EQUAL_4 ) );
			if ( strlen ( szAttBasename ) )
			{
				if ( szAttBasename [ strlen ( szAttBasename ) - 1 ] == '\"' )
				{
					szAttBasename [ strlen ( szAttBasename ) - 1 ] = 0;
				}
			}

			if ( ! bSubject && ! bName)
			{
				RemoveString ( szAttSubjectName, szAttBasename );
			}

			CorrectFilename ( szAttBasename );

			if ( DecodeFile64Lines () )
			{
//				continue;
				return true;
			}

			return false;
		}

		char *pFound;
		pFound = StringMatch ( szLine, FILENAME_EQUAL_5 );

		if ( pFound == NULL )
		{
			pFound = StringMatch ( szLine, FILENAME_EQUAL_6 );
		}

		if ( pFound == NULL )
		{
			pFound = StringMatch ( szLine, FILENAME_EQUAL_7 );
		}

		if ( pFound == NULL )
		{
			pFound = StringMatch ( szLine, FILENAME_EQUAL_8 );
		}

		if (  pFound )
		{
			iAttachementCount++;

			strcpy_s (	szAttBasename, sizeof ( szAttBasename ), pFound );
			if ( strlen ( szAttBasename ) )
			{
				if ( szAttBasename [ strlen ( szAttBasename ) - 1 ] == '\"' )
				{
					szAttBasename [ strlen ( szAttBasename ) - 1 ] = 0;
				}
			}

			if ( DecodeFile64Lines () )
			{
//				continue;
				return true;
			}

			return false;
		}

		if ( *szLine == 0 )
		{
			bToDecode = true;
		}

		if ( bToDecode )
		{
			if ( ! bSubject && ! bName)
			{
				RemoveString ( szAttSubjectName, szAttBasename );
			}

			CorrectFilename ( szAttBasename );

			if ( DecodeFile64Lines () )
			{
				return true;
			}

			return false;
		}

	}

	return false;
}

//
///////////////////////////////////////////////////////////////////////////////
//		Decode file.
//
///////////////////////////////////////////////////////////////////////////////
bool DecodeFile ( )
{
	char				szLine [ LEN_LINE ];
	bool				bBase64;
	bool				bTreated;

	//
	//		Initialize base64 to false.
	bBase64 = false;

	//		Say we have not treated anything.
	bTreated = false;

	//		Open message file
	OpenMsgFile ( );

	//
	//		Reset subject and author.
	strcpy_s ( szSubject, sizeof ( szSubject ),		"No Subject" );
	strcpy_s ( szAuthor, sizeof ( szAuthor ),		"No Author" );
	strcpy_s ( szEmail, sizeof ( szEmail ),			"No E-Mail" );
	strcpy_s ( szDate, sizeof ( szDate ),			"No Date" );
	strcpy_s ( szMessageID, sizeof ( szMessageID ),	"" );

	iAttachementType		= 0;
	iAttachementCount		= 0;

	//
	//		Read file.
	while ( ! MsgFileEof (  ) )
	{
		memset ( szLine, 0, sizeof ( szLine ) );
		ReadMsgFile ( szLine, sizeof ( szLine ) - 1 );
		RemoveLeadingSpaces ( szLine );

		if ( MsgFileEof (  ) )
		{
			CloseMsgFile ( );
			return true;
		}

		if ( MsgFileError (  ) )
		{
			DisplayErrorAndExit ( 255, &ExitProgram, "010 - fgets msg", "" );
			return false;
		}

		if ( *szLine == 0 )
		{
			continue;
		}

		if ( CompareNString ( szLine, SUBJECT, strlen ( SUBJECT ) ) == 0 )
		{
			memset ( szSubject, 0, sizeof ( szSubject ) );
			strncpy_s ( szSubject, sizeof ( szSubject ),
						szLine + strlen ( SUBJECT ), sizeof ( szSubject ) - 1 );

			RemoveLeadingSpaces ( szSubject );

			/*
			 *		Maybe the subject is Mime Encoded.
			 */
			if ( strncmp ( szSubject, ISO_8859_1_B, strlen ( ISO_8859_1_B ) ) == 0 )
			{
				int		iResult;
				char	szResult [ LEN_PATHNAME ];
				memset ( szResult, 0, sizeof ( szResult ) );
				char	*pStr = strstr ( szSubject, ISO_8859_1_END );
				if ( pStr )
				{
					*pStr = 0;
					bool bResult = 
						UUDecodeLine64 ( szSubject + strlen ( ISO_8859_1_B ),
										szResult, &iResult );
					if ( bResult )
					{
						strcpy_s ( szSubject, sizeof ( szSubject ), szResult );
					}
				}
			}

		}

		if ( CompareNString ( szLine, MESSAGE_ID, strlen ( MESSAGE_ID ) ) == 0 )
		{
			memset ( szMessageID, 0, sizeof ( szMessageID ) );
			strncpy_s ( szMessageID, sizeof ( szMessageID ),
						szLine + strlen ( MESSAGE_ID ), sizeof ( szMessageID ) - 1 );
			char	*pFind = strchr ( szMessageID, '>' );
			if (  pFind != NULL )
			{
				*pFind = 0;
			}
			CorrectFilename ( szMessageID );
		}

		if ( CompareNString ( szLine, AUTHOR, strlen ( AUTHOR ) ) == 0 )
		{
			memset ( szAuthor, 0, sizeof ( szAuthor ) );
			strncpy_s ( szAuthor, sizeof ( szAuthor ),
						szLine + strlen ( AUTHOR ), sizeof ( szAuthor ) -1 );

			if ( strncmp ( szAuthor, ISO_8859_1_Q, strlen ( ISO_8859_1_Q ) ) == 0 )
			{
				int		iResult;
				char	szResult [ LEN_PATHNAME ];
				memset ( szResult, 0, sizeof ( szResult ) );
				char	*pStr = strstr ( szAuthor, ISO_8859_1_END );
				if ( pStr )
				{
					*pStr = 0;
					bool bResult = 
						UUDecodeLine64 ( szAuthor + strlen ( ISO_8859_1_Q ),
										szResult, &iResult );
					if ( bResult )
					{
						strcpy_s ( szAuthor, sizeof ( szAuthor ), szResult );
					}
				}
			}

		}

		if ( CompareNString ( szLine, EMAIL, strlen ( EMAIL ) ) == 0 )
		{
			memset ( szEmail, 0, sizeof ( szEmail ) );
			strncpy_s ( szEmail, sizeof ( szEmail ),
						szLine + strlen ( EMAIL ), sizeof ( szEmail ) -1 );
		}

		if ( CompareNString ( szLine, DATE, strlen ( DATE ) ) == 0 )
		{
			memset ( szDate, 0, sizeof ( szDate ) );
			strncpy_s ( szDate, sizeof ( szDate ),
						szLine + strlen ( DATE ), sizeof ( szDate ) -1 );
		}

		if (  CompareNString ( szLine, FILENAME_EQUAL_1, strlen ( FILENAME_EQUAL_1 ) ) == 0 )
		{
			iAttachementCount++;

			strcpy_s (	szAttBasename, sizeof ( szAttBasename ), 
						szLine + strlen ( FILENAME_EQUAL_1 ) );
			if ( strlen ( szAttBasename ) )
			{
				if ( szAttBasename [ strlen ( szAttBasename ) - 1 ] == '\"' )
				{
					szAttBasename [ strlen ( szAttBasename ) - 1 ] = 0;
				}
			}

		}

		if (  CompareNString ( szLine, FILENAME_EQUAL_2, strlen ( FILENAME_EQUAL_2 ) ) == 0 )
		{
			iAttachementCount++;

			strcpy_s (	szAttBasename, sizeof ( szAttBasename ), 
						szLine + strlen ( FILENAME_EQUAL_2 ) );
			if ( strlen ( szAttBasename ) )
			{
				if ( szAttBasename [ strlen ( szAttBasename ) - 1 ] == '\"' )
				{
					szAttBasename [ strlen ( szAttBasename ) - 1 ] = 0;
				}
			}

		}

		if (  CompareNString ( szLine, FILENAME_EQUAL_3, strlen ( FILENAME_EQUAL_3 ) ) == 0 )
		{
			iAttachementCount++;

			strcpy_s (	szAttBasename, sizeof ( szAttBasename ), 
						szLine + strlen ( FILENAME_EQUAL_3 ) );
			if ( strlen ( szAttBasename ) )
			{
				if ( szAttBasename [ strlen ( szAttBasename ) - 1 ] == '\"' )
				{
					szAttBasename [ strlen ( szAttBasename ) - 1 ] = 0;
				}
			}

		}

		if (  CompareNString ( szLine, FILENAME_EQUAL_4, strlen ( FILENAME_EQUAL_4 ) ) == 0 )
		{
			iAttachementCount++;

			strcpy_s (	szAttBasename, sizeof ( szAttBasename ), 
						szLine + strlen ( FILENAME_EQUAL_4 ) );
			if ( strlen ( szAttBasename ) )
			{
				if ( szAttBasename [ strlen ( szAttBasename ) - 1 ] == '\"' )
				{
					szAttBasename [ strlen ( szAttBasename ) - 1 ] = 0;
				}
			}

		}

		char *pFound;
		pFound = StringMatch ( szLine, FILENAME_EQUAL_5 );

		if ( pFound == NULL )
		{
			pFound = StringMatch ( szLine, FILENAME_EQUAL_6 );
		}

		if ( pFound == NULL )
		{
			pFound = StringMatch ( szLine, FILENAME_EQUAL_7 );
		}

		if ( pFound == NULL )
		{
			pFound = StringMatch ( szLine, FILENAME_EQUAL_8 );
		}

		if (  pFound )
		{
			iAttachementCount++;

			strcpy_s (	szAttBasename, sizeof ( szAttBasename ), pFound );
			if ( strlen ( szAttBasename ) )
			{
				if ( szAttBasename [ strlen ( szAttBasename ) - 1 ] == '\"' )
				{
					szAttBasename [ strlen ( szAttBasename ) - 1 ] = 0;
				}
			}

		}

		if (  CompareNString ( szLine, BASE_64, strlen ( BASE_64 ) ) == 0 )
		{
			iAttachementType = 1;

			if ( ! bOnlyMessages )
			{
				iNumOfBase64++;
				bTreated = true;
				if ( DecodeFile64 () )
				{
					continue;
				}
				
				CloseMsgFile ( );
				return false;
			}
			else
			{
				iAttachementCount++;
			}
		}

		char	*pMatch = StringMatch ( szLine, YENC_BEGIN );
		if ( pMatch != NULL )
		{
			iAttachementType = 3;

			if ( ! bOnlyMessages )
			{
				strcpy_s (	szAttBasename, sizeof ( szAttBasename ), pMatch );

				if ( ! bSubject && ! bName)
				{
					RemoveString ( szAttSubjectName, szAttBasename );
				}

				CorrectFilename ( szAttBasename );

				iNumOfYenc++;
				bTreated = true;
				if ( DecodeFileYenc () )
				{
					continue;
				}
				
				CloseMsgFile ( );
				return false;
			}
			else
			{
				iAttachementCount++;
			}
		}

		pMatch = StringMatch ( szLine, YENC_BEGIN2 );
		if ( pMatch != NULL )
		{
			iAttachementType = 3;

			if ( ! bOnlyMessages )
			{
				strcpy_s (	szAttBasename, sizeof ( szAttBasename ), pMatch );

				if ( ! bSubject && ! bName)
				{
					RemoveString ( szAttSubjectName, szAttBasename );
				}

				CorrectFilename ( szAttBasename );

				iNumOfYenc++;
				bTreated = true;
				if ( DecodeFileYenc () )
				{
					continue;
				}
				
				CloseMsgFile ( );
				return false;
			}
			else
			{
				iAttachementCount++;
			}
		}

		if (  CompareNString ( szLine, BEGIN_600, strlen ( BEGIN_600 ) ) == 0 )
		{
			iAttachementCount++;
			iAttachementType = 2;

			if ( ! bOnlyMessages )
			{
				strcpy_s (	szAttBasename, sizeof ( szAttBasename ), 
							szLine + strlen ( BEGIN_600 ) );

				if ( ! bSubject && ! bName)
				{
					RemoveString ( szAttSubjectName, szAttBasename );
				}

				CorrectFilename ( szAttBasename );

				iNumOfAttachement++;
				bTreated = true;
				if ( DecodeFileLines () )
				{
					continue;
				}

				CloseMsgFile ( );
				return false;
			}
		}

		else if (  CompareNString ( szLine, BEGIN_640, strlen ( BEGIN_640 ) ) == 0 )
		{
			iAttachementCount++;
			iAttachementType = 2;

			if ( ! bOnlyMessages )
			{
				strcpy_s (	szAttBasename, sizeof ( szAttBasename ), 
							szLine + strlen ( BEGIN_640 ) );

				if ( ! bSubject && ! bName)
				{
					RemoveString ( szAttSubjectName, szAttBasename );
				}

				CorrectFilename ( szAttBasename );

				iNumOfAttachement++;
				bTreated = true;
				if ( DecodeFileLines () )
				{
					continue;
				}

				CloseMsgFile ( );
				return false;
			}
		}

		else if (  CompareNString ( szLine, BEGIN_644, strlen ( BEGIN_644 ) ) == 0 )
		{
			iAttachementCount++;
			iAttachementType = 2;

			if ( ! bOnlyMessages )
			{
				strcpy_s (	szAttBasename, sizeof ( szAttBasename ), 
							szLine + strlen ( BEGIN_644 ) );

				if ( ! bSubject && ! bName)
				{
					RemoveString ( szAttSubjectName, szAttBasename );
				}

				CorrectFilename ( szAttBasename );

				iNumOfAttachement++;
				bTreated = true;
				if ( DecodeFileLines () )
				{
					continue;
				}

				CloseMsgFile ( );
				return false;
			}
		}

		else if (  CompareNString ( szLine, BEGIN_666, strlen ( BEGIN_666 ) ) == 0 )
		{
			iAttachementCount++;
			iAttachementType = 2;

			if ( ! bOnlyMessages )
			{
				strcpy_s (	szAttBasename, sizeof ( szAttBasename ), 
							szLine + strlen ( BEGIN_666 ) );

				if ( ! bSubject && ! bName)
				{
					RemoveString ( szAttSubjectName, szAttBasename );
				}

				CorrectFilename ( szAttBasename );

				iNumOfAttachement++;
				bTreated = true;
				if ( DecodeFileLines () )
				{
					continue;
				}

				CloseMsgFile ( );
				return false;
			}
		}

		else if (  CompareNString ( szLine, BEGIN_755, strlen ( BEGIN_755 ) ) == 0 )
		{
			iAttachementCount++;
			iAttachementType = 2;

			if ( ! bOnlyMessages )
			{
				strcpy_s (	szAttBasename, sizeof ( szAttBasename ), 
							szLine + strlen ( BEGIN_755 ) );

				if ( ! bSubject && ! bName)
				{
					RemoveString ( szAttSubjectName, szAttBasename );
				}

				CorrectFilename ( szAttBasename );

				iNumOfAttachement++;
				bTreated = true;
				if ( DecodeFileLines () )
				{
					continue;
				}

				CloseMsgFile ( );
				return false;
			}
		}

		else if (  CompareNString ( szLine, BEGIN_6XX, strlen ( BEGIN_6XX ) ) == 0 )
		{
			iAttachementCount++;
			iAttachementType = 2;

			if ( ! bOnlyMessages )
			{
				strcpy_s (	szAttBasename, sizeof ( szAttBasename ), 
							szLine + strlen ( BEGIN_6XX ) + 4 );

				if ( ! bSubject && ! bName)
				{
					RemoveString ( szAttSubjectName, szAttBasename );
				}

				CorrectFilename ( szAttBasename );

				iNumOfAttachement++;
				bTreated = true;
				if ( DecodeFileLines () )
				{
					continue;
				}

				CloseMsgFile ( );
				return false;
			}
		}

		else if (  CompareNString ( szLine, BEGIN_7XX, strlen ( BEGIN_7XX ) ) == 0 )
		{
			iAttachementCount++;
			iAttachementType = 2;

			if ( ! bOnlyMessages )
			{
				strcpy_s (	szAttBasename, sizeof ( szAttBasename ), 
							szLine + strlen ( BEGIN_7XX ) + 4 );

				if ( ! bSubject && ! bName)
				{
					RemoveString ( szAttSubjectName, szAttBasename );
				}

				CorrectFilename ( szAttBasename );

				iNumOfAttachement++;
				bTreated = true;
				if ( DecodeFileLines () )
				{
					continue;
				}

				CloseMsgFile ( );
				return false;
			}
		}

	}

	CloseMsgFile ( );

	return bTreated;
}


//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetBoolLeave ( bool bValue )
{
	bLeave = bValue;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetBoolSubject ( bool bValue )
{
	if ( bValue )
	{
		SetAttFormat ( 
			MSG_NAME_OBJECT, MSG_NAME_NONE, MSG_NAME_NONE, MSG_NAME_NONE, MSG_NAME_NONE,
			127, 127, 127, 127, 0 );
	}

	bSubject = bValue;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetBoolName ( bool bValue )
{
	if ( bValue )
	{
		SetAttFormat ( 
			MSG_NAME_ATT_NAME, MSG_NAME_NONE, MSG_NAME_NONE, MSG_NAME_NONE, MSG_NAME_NONE,
			127, 127, 127, 127, 0 );
	}

	bName = bValue;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetBoolCollapse ( bool bValue )
{
	bCollapse = bValue;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool GetBoolCollapse (  )
{
	return bCollapse;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetBoolRemoveNumbers ( bool bValue )
{
	bRemoveNumbers = bValue;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetBoolRemoveOther ( bool bValue )
{
	bRemoveOther = bValue;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetBoolOnlyMessages ( bool bValue )
{
	bOnlyMessages = bValue;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ZeroNumOfAttachement ( )
{
	iNumOfAttachement = 0;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ZeroNumOfBase64 ( )
{
	iNumOfBase64 = 0;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ZeroNumOfYenc ( )
{
	iNumOfYenc = 0;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int GetNumOfAttachement ( )
{
	return iNumOfAttachement;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int GetNumOfBase64 ( )
{
	return iNumOfBase64;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int GetNumOfYenc ( )
{
	return iNumOfYenc;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetDirectory ( const char *pPath )
{
	char		*pString;

	strcpy_s ( szDirectory, sizeof ( szDirectory ), pPath );
	pString = SearchString ( szDirectory, ".dbx" );
	if ( pString )
	{
		*pString = 0;
	}

	CorrectDirectory ( szDirectory );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetDirectoryFrom ( char *pDir, char *pPath )
{
	char		*pString;

	strcpy_s ( szDirectory, sizeof ( szDirectory ), pDir );
	if ( szDirectory [ strlen ( szDirectory ) - 1 ] != '\\' )
	{
		strcat_s ( szDirectory, sizeof ( szDirectory ), "\\" );
	}

	strcat_s ( szDirectory, sizeof ( szDirectory ), FindFilename ( pPath ) );

	pString = SearchString ( szDirectory, ".dbx" );
	if ( pString )
	{
		*pString = 0;
	}

	CorrectDirectory ( szDirectory );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetDrive ( const char *pDrive )
{
	//		A temporary string.
	char			szTemp [ LEN_DIRECTORY ];

	if ( szDirectory [ 1 ] == ':' )
	{
		szDirectory [ 0 ] = pDrive [ 0 ];
	}
	else
	{
		strcpy_s ( szTemp, sizeof ( szTemp ), pDrive );
		strcat_s ( szTemp, sizeof ( szTemp ), szDirectory );

		strcpy_s ( szDirectory, sizeof ( szDirectory ), szTemp );
	}

	CorrectDirectory ( szDirectory );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CreateDirectory ( )
{
	int				iResult;

	iResult = _mkdir ( szDirectory );
	if ( iResult != -1 )
	{
		return;
	}

	if ( errno == EEXIST )
	{
		return;
	}

	char	szEnvBuf [ LEN_DIRECTORY ];
	memset ( szEnvBuf, 0, sizeof ( szEnvBuf ) );
	size_t	iReturnSize;
	getenv_s ( &iReturnSize, szEnvBuf, sizeof ( szEnvBuf ), "TEMP" );
	strcpy_s ( szDirectory, sizeof ( szDirectory ), szEnvBuf );
	iResult = _mkdir ( szDirectory );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ProcessFileStep1 (		char *pPathname, 
							void ( *pCallBack )( void *, void * ), void *pParm )
{
	//		Test if directory is empty.
	if ( *szDirectory == 0 )
	{
		SetDirectory ( pPathname );
	}

	AllocateBlockMemory ( );
	AllocateBufferMemory ( );

	//		Read the file.
	ZeroNumOfMessages ( );
	ZeroNumOfAttachement ( );
	ZeroNumOfBase64 ( );
	ZeroNumOfYenc ( );

	//
	//		Create sub directory.
	CreateDirectory ( );
	
	//		Open log file.
	OpenLogFile ( szDirectory, &ExitProgram );

	//		Treat Outlook file
	ReadOutlookFileStep1 ( pPathname, szDirectory, pCallBack, pParm );

	FreeBufferMemory ( );
	FreeBlockMemory ( );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ProcessFileStep2 ( char *pPathname, void ( *pCallBack )( void *, void * ), void *pParm )
{
	AllocateBlockMemory ( );
	AllocateBufferMemory ( );

	//		Treat Outlook file
	ReadOutlookFileStep2 ( pPathname, szDirectory, pCallBack, pParm );

	//		Display Statistics.
	DisplayText ( "\nSummary\n" );
	DisplayText ( "Number of messages           treated: %8d\n", GetNumOfMessages () );
	DisplayText ( "Number of Mime   attachement treated: %8d\n", GetNumOfAttachement () );
	DisplayText ( "Number of Base64 attachement treated: %8d\n", GetNumOfBase64 () );
	DisplayText ( "Number of Yenc   attachement treated: %8d\n", GetNumOfYenc () );

	FreeBufferMemory ( );
	FreeBlockMemory ( );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ProcessFileStep3 ( char *pPathname, void ( *pCallBack )( void *, void * ), void *pParm )
{
	//		Test if directory is empty.
	if ( *szDirectory == 0 )
	{
		SetDirectory ( pPathname );
	}

	//
	//		Create sub directory.
	CreateDirectory ( );
	
	//		Open log file.
	OpenLogFile ( szDirectory, &ExitProgram );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *ProcessOneStep ( char *pPathname, unsigned long lPosition, void ( *pCallBack )( void *, void * ), void *pParm )
{
	char	*pFilename;

	AllocateBlockMemory ( );
	AllocateBufferMemory ( );

	ResetAddress ( );

	OpenDbxFile ( pPathname );

	//		Treat Outlook file
	pFilename = ReadOneFile ( pPathname, szDirectory, lPosition, pCallBack, pParm );

	CloseDbxFile( );

	FreeBufferMemory ( );
	FreeBlockMemory ( );

	return pFilename;
}


//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ProcessFile ( char *pPathname, void ( *pCallBack )( void *, void * ), void *pParm )
{
	ProcessFileStep1 ( pPathname, pCallBack, pParm );
	ProcessFileStep2 ( pPathname, pCallBack, pParm );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *GetSubject ( )
{
	return szSubject;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *GetMessageID ( )
{
	return szMessageID;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *GetDate ( )
{
	return szDate;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *GetAuthor ( )
{
	return szAuthor;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *GetEMail ( )
{
	return szEmail;
}

int GetAttachementType ( )
{
	return iAttachementType;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int GetAttachementCount ( )
{
	return iAttachementCount;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetAttFormat (	int iName1,int iName2,int iName3,int iName4,int iName5,
						int iSize1,int iSize2,int iSize3,int iSize4,int iSize5 )
{
	tabValuesAtt [ 0 ] = iName1;
	tabValuesAtt [ 1 ] = iName2;
	tabValuesAtt [ 2 ] = iName3;
	tabValuesAtt [ 3 ] = iName4;
	tabValuesAtt [ 4 ] = iName5;

	tabSizesAtt [ 0 ]	= iSize1;
	tabSizesAtt [ 1 ]	= iSize2;
	tabSizesAtt [ 2 ]	= iSize3;
	tabSizesAtt [ 3 ]	= iSize4;
	tabSizesAtt [ 4 ]	= iSize5;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetAttExtension ( const char *pText )
{
	strcpy_s ( szAttExtension, sizeof ( szAttExtension ), pText );
}