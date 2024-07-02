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

#include "OEAddressDefinitions.h"
#include "OEAddressRoutines.h"
#include "OEMessagesRoutines.h"
#include "DisplayAndTrace.h"
#include "DecodeRoutines.h"
#include "FileRoutines.h"

#define	POSIT_EMPTY			0x00
#define	POSIT_VALID			0x01
#define	POSIT_NEXT			0x02
#define	POSIT_MASK			0x0f
#define	POSIT_TREATED		0x10

#define	SPECIAL_FEATURE_1	0x01
#define	QUICK_SEARCH		0x01

//
//		The file handle.
static	FILE					*hDbxFile							= NULL;

//
//		The table of addresses.
#ifdef	_CONSOLE
#define	MAX_ADDRESSES			(256*1024)
#endif

#ifndef	_CONSOLE
#define	MAX_ADDRESSES			(8*1024*1024)
#endif

static	unsigned long			*FilePositions						= NULL;
static	unsigned long			*FilePositNext						= NULL;
static	char					*FilePositFlag						= NULL;

#ifndef	_CONSOLE
static	char					*FilePositSeld						= NULL;
#endif

static	int						iNumbAddresses						= 0;
static	int						iNumbAddrsNext						= 0;

//		Trace mode
static	bool					bVerbose							= false;

//
//		Data Structure for header.
static struct structHeader1		tagBufferHeader1;

static struct structHeader2		tagBufferHeader2;

static struct structHeader3		tagBufferHeader3;

static struct structHeader4		tagBufferHeader4;

//
//		Current block read.	
#define	MAX_BLOC_SIZE			0x4000
static char						*pBlockAddress						=	NULL;
static unsigned long			lBlockLength						=	0;


//
//		Message indicator.
static bool						bMessageIndicator					= false;
static bool						bMessageTrailing					= false;

static structInformation		tagInformation;

static char						szProcessStep [ LEN_FILENAME ]		= "";

static long						lFileLength							= 0;

static long						lFilePosition						= 0;

static	char					szMessageFilename [ LEN_PATHNAME ]	= "";

static	bool					bAddressRoutinesCancel				= false;

//
///////////////////////////////////////////////////////////////////////////////
//		Allocate memory
//
///////////////////////////////////////////////////////////////////////////////
static void AllocateBuffers ( )
{
	if ( FilePositions == NULL )
	{
		FilePositions = ( unsigned long * )
						malloc ( sizeof ( unsigned long ) * MAX_ADDRESSES );
		memset ( FilePositions, 0, sizeof ( unsigned long ) * MAX_ADDRESSES );
	}

	if ( FilePositNext == NULL )
	{
		FilePositNext = ( unsigned long * )
						malloc ( sizeof ( unsigned long ) * MAX_ADDRESSES );
		memset ( FilePositNext, 0, sizeof ( unsigned long ) * MAX_ADDRESSES );
	}

	if ( FilePositFlag == NULL )
	{
		FilePositFlag = ( char * ) malloc ( sizeof ( char ) * MAX_ADDRESSES );
		memset ( FilePositFlag, 0, sizeof ( char ) * MAX_ADDRESSES );
	}

#ifndef	_CONSOLE
	if ( FilePositSeld == NULL )
	{
		FilePositSeld = ( char * ) malloc ( sizeof ( char ) * MAX_ADDRESSES );
		memset ( FilePositSeld, 0, sizeof ( char ) * MAX_ADDRESSES );
	}
#endif

}

//
///////////////////////////////////////////////////////////////////////////////
//		Close Dbx file.
//
///////////////////////////////////////////////////////////////////////////////
void CloseDbxFile ( )
{
	if ( hDbxFile != NULL )
	{
		fclose ( hDbxFile );
		hDbxFile = NULL;
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void OpenDbxFile ( char *pFilename )
{
	hDbxFile = NULL,
	fopen_s ( &hDbxFile, pFilename, "rb" );
	if ( hDbxFile == NULL )
	{
		DisplayErrorAndExit ( 255, &ExitProgram, "011 - fopen", "" );
		return;
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//		Set Next Address Flag
//
///////////////////////////////////////////////////////////////////////////////
void SetAddressNextFlag ( int iPos )
{

	AllocateBuffers ( );

	if ( iPos < 0 || iPos >= MAX_ADDRESSES )
	{
		return;
	}

	FilePositFlag [ iPos ] = POSIT_NEXT;

	return;

}

//
///////////////////////////////////////////////////////////////////////////////
//		Store address.
//
///////////////////////////////////////////////////////////////////////////////
int StoreAddress ( unsigned long lAddress )
{

	AllocateBuffers ( );

	if ( lAddress == 0 )
	{
		return iNumbAddresses;
	}

	if ( iNumbAddresses < 0 || iNumbAddresses >= MAX_ADDRESSES )
	{
		return iNumbAddresses;
	}

	FilePositions [ iNumbAddresses ] = lAddress;
	FilePositFlag [ iNumbAddresses ] = POSIT_VALID;

	iNumbAddresses++;

	return iNumbAddresses - 1;

}

//
///////////////////////////////////////////////////////////////////////////////
//		Store address.
//
///////////////////////////////////////////////////////////////////////////////
int StoreNextAddress ( unsigned long lAddress )
{
	AllocateBuffers ( );

	if ( lAddress == 0 )
	{
		return iNumbAddrsNext;
	}

	if ( iNumbAddrsNext < 0 || iNumbAddrsNext >= MAX_ADDRESSES )
	{
		return iNumbAddrsNext;
	}

	FilePositNext [ iNumbAddrsNext ] = lAddress;

	iNumbAddrsNext++;

	return iNumbAddrsNext - 1;

}

//
///////////////////////////////////////////////////////////////////////////////
//		Search an addresse.
//
///////////////////////////////////////////////////////////////////////////////
static int SortCompare ( const void *pElem1, const void *pElem2  )
{
	if ( * ( ( unsigned long * )( pElem1 ) ) > * ( ( unsigned long * )( pElem2 ) ) )
	{
		return 1;
	}

	if ( * ( ( unsigned long * )( pElem1 ) ) == * ( ( unsigned long * )( pElem2 ) ) )
	{
		return 0;
	}

	if ( * ( ( unsigned long * )( pElem1 ) ) < * ( ( unsigned long * )( pElem2 ) ) )
	{
		return -1;
	}

	return 0;
}

//
///////////////////////////////////////////////////////////////////////////////
//		Sort addresses
//
///////////////////////////////////////////////////////////////////////////////
void	SortAddress ( )
{

	AllocateBuffers ( );

	DisplayText ( "Sorting... 1," );

	if ( iNumbAddresses > 0 )
	{
		qsort ( FilePositions, iNumbAddresses, sizeof ( unsigned long ), &SortCompare );
	}

	DisplayText ( " 2\n" );

	if ( iNumbAddrsNext )
	{
		qsort ( FilePositNext, iNumbAddrsNext, sizeof ( unsigned long ), &SortCompare );
	}

	return;
}

//
///////////////////////////////////////////////////////////////////////////////
//		Search an addresse.
//
///////////////////////////////////////////////////////////////////////////////
int	SearchAddress ( unsigned long lAddress )
{

	//
	int			iMin;
	int			iMax;
	int			iX;

	AllocateBuffers ( );

	if ( lAddress == 0 )
	{
		return -1;
	}

	if ( iNumbAddresses <= 0 )
	{
		return -1;
	}

	//
	//		Set bording values.
	iMin	= 0;
	iMax	= iNumbAddresses - 1;

	//
	//		Loop.
	do
	{
		iX = ( iMax + iMin ) / 2;

		if (  lAddress == FilePositions [ iX ] )
		{
			return iX;
		}

		if (  lAddress > FilePositions [ iX ] )
		{
			iMin = iX;
		}

		if (  lAddress < FilePositions [ iX ] )
		{
			iMax = iX;
		}

	}
	while ( iMax - iMin > 1 );

	//
	if (  lAddress == FilePositions [ iMin ] )
	{
		return iMin;
	}

	if (  lAddress == FilePositions [ iMax ] )
	{
		return iMax;
	}

	return -1;

}

//
///////////////////////////////////////////////////////////////////////////////
//		Search an addresse.
//
///////////////////////////////////////////////////////////////////////////////
int	SearchAddressNext ( unsigned long lAddress )
{

	//
	int			iMin;
	int			iMax;
	int			iX;

	AllocateBuffers ( );

	if ( lAddress == 0 )
	{
		return -1;
	}

	if ( iNumbAddrsNext <= 0 )
	{
		return -1;
	}

	//
	//		Set bording values.
	iMin	= 0;
	iMax	= iNumbAddrsNext - 1;

	//
	//		Loop.
	do
	{
		iX = ( iMax + iMin ) / 2;

		if (  lAddress == FilePositNext [ iX ] )
		{
			return iX;
		}

		if (  lAddress > FilePositNext [ iX ] )
		{
			iMin = iX;
		}

		if (  lAddress < FilePositNext [ iX ] )
		{
			iMax = iX;
		}

	}
	while ( iMax - iMin > 1 );

	//
	if (  lAddress == FilePositNext [ iMin ] )
	{
		return iMin;
	}

	if (  lAddress == FilePositNext [ iMax ] )
	{
		return iMax;
	}

	return -1;

}

//
///////////////////////////////////////////////////////////////////////////////
//		Check Loop
//
///////////////////////////////////////////////////////////////////////////////
bool AlreadyTreated ( unsigned long lAddress )
{
	int			iX;

	AllocateBuffers ( );

	if ( lAddress == 0 )
	{
		return false;
	}

	iX = SearchAddress ( lAddress );
	if ( iX != -1 )
	{
		if ( FilePositFlag [ iX ] & POSIT_TREATED )
		{
			return true;
		}
		else
		{
			FilePositFlag [ iX ] |= POSIT_TREATED;
			return false;
		}
	}

	//
	//		Add the verified address
	iX = StoreAddress ( lAddress );
	if ( iX != -1 )
	{
		if ( FilePositFlag [ iX ] & POSIT_TREATED )
		{
			return true;
		}
		else
		{
			FilePositFlag [ iX ] |= POSIT_TREATED;
			return false;
		}
	}

	printf ( "Address not found %lx \n", lAddress );

	return false;

}

//
///////////////////////////////////////////////////////////////////////////////
//		Clean addresses.
//
///////////////////////////////////////////////////////////////////////////////
void CleanAddressesTable ( )
{
	int			iX;
	int			iY;

	AllocateBuffers ( );

	DisplayText ( "Cleaning Addresses " );

	int	iCountNext = 0;
	for ( iX = 0; iX < iNumbAddrsNext; iX++ )
	{
		iY = SearchAddress ( FilePositNext [ iX ] );
		if ( iY != -1 )
		{
			FilePositFlag [ iY ] = POSIT_NEXT;
			iCountNext++;
		}
		else
		{

#ifdef	_CONSOLE
			fprintf ( stdout, "%lx not found\n", FilePositNext [ iX ] );
#endif

		}

		if ( iX % 1000 == 0)
		{
			DisplayText ( "." );
		}

	}

	DisplayText ( "\n" );

	//
	//		Trace addresses.
	int	iCountValid = 0;
	for ( iX = 0; iX < iNumbAddresses; iX++ )
	{
		if ( FilePositFlag [ iX ] == POSIT_VALID )
		{
			iCountValid++;
			if ( bVerbose )
			{
				TraceOut ( "Address to be treated %08lx\n", FilePositions [ iX ] );
			}
		}
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//		Build addresses table.
//
///////////////////////////////////////////////////////////////////////////////
void BuildAddressesTable ( )
{
	fpos_t			stPosition;
	fpos_t			stSavePosition;
	size_t			stNbRead;
	int				iResult;

	AllocateBuffers ( );

	memset ( FilePositions, 0, sizeof ( unsigned long ) * MAX_ADDRESSES );
	memset ( FilePositNext, 0, sizeof ( unsigned long ) * MAX_ADDRESSES );
	memset ( FilePositFlag, POSIT_EMPTY, sizeof ( char ) * MAX_ADDRESSES );

	iNumbAddresses	= 0;
	iNumbAddrsNext	= 0;

	DisplayText ( "Building Addresses  " );

	while ( hDbxFile != NULL && ! feof ( hDbxFile ) && ! bAddressRoutinesCancel )
	{
		//		Get Current position in file
		iResult = fgetpos ( hDbxFile, &stPosition );
		if ( iResult != 0 )
		{
			DisplayErrorAndExit ( 255, &ExitProgram, "012 - fgetpos", "" );
			return;
		}

		//		Read the first header.
		stNbRead = fread ( & tagBufferHeader1, 1, sizeof ( tagBufferHeader1 ), hDbxFile );
		if ( feof ( hDbxFile ) )
		{
			DisplayText ( "\n" );

			return;

			break;
		}

		if ( ferror ( hDbxFile ) )
		{
			DisplayErrorAndExit ( 255, &ExitProgram, "013 - fread hdr 1", "" );

			return;
		}

		lFilePosition = ftell ( hDbxFile );

		iResult = fgetpos ( hDbxFile, &stSavePosition );
		if ( iResult != 0 )
		{
			DisplayErrorAndExit ( 255, &ExitProgram, "012 - fgetpos", "" );

			return;
		}

		if( stNbRead != sizeof ( tagBufferHeader1 ) )
		{
			DisplayErrorAndExit ( 255, &ExitProgram, "014 - fread hdr 1", "" );

			return;
		}

		//
		//		We have a possible address 
		//		if the current position is the one found in the file
		if ( stPosition == tagBufferHeader1.lAddress )
		{

			//		Now get the length of the block.
			stNbRead = fread ( & tagBufferHeader2, 1, sizeof ( tagBufferHeader2 ), hDbxFile );
			if ( feof ( hDbxFile ) )
			{
				DisplayText ( "\n" );

				return;
			}

			if ( ferror ( hDbxFile ) )
			{
				DisplayErrorAndExit ( 255, &ExitProgram, "015 - fread hdr 2", "" );
				return;
			}

			lFilePosition = ftell ( hDbxFile );

			if( stNbRead != sizeof ( tagBufferHeader2 ) )
			{
				DisplayErrorAndExit ( 255, &ExitProgram, "016 - fread hdr 2", "" );
				return;
			}

			//	Allocate the buffer if needed.
			//	Blocks are always lesser than 0x200
			if ( tagBufferHeader2.lLengthAllocated <= 0x0200 )
			{

				if ( tagBufferHeader2.lLengthAllocated > lBlockLength )
				{
					FreeBlockMemory ( );

					AllocateBlockMemory ( tagBufferHeader2.lLengthAllocated );
				}

				//		Get Current position in file
				iResult = fgetpos ( hDbxFile, &stPosition );
				if ( iResult != 0 )
				{
					DisplayErrorAndExit ( 255, &ExitProgram, "018 - fgetpos", "" );
					return;
				}

				//		Now read the remaining of the block header.
				stNbRead = 
					fread ( & tagBufferHeader3, 1, sizeof ( tagBufferHeader3 ), hDbxFile );
				if ( feof ( hDbxFile ) )
				{
					DisplayText ( "\n" );

					return;
				}

				if ( ferror ( hDbxFile ) )
				{
					DisplayErrorAndExit ( 255, &ExitProgram, "019 - fread hdr 3", "" );
					return;
				}

				lFilePosition = ftell ( hDbxFile );

				if( stNbRead != sizeof ( tagBufferHeader3 ) )
				{
					DisplayErrorAndExit ( 255, &ExitProgram, "020 - fread hdr 3", "" );
					return;
				}

				//
				//		Test if we are on a good buffer.

				//
				//		Here is the place where it goes wrong !!!
				//		Yann 22/05/2006

#ifdef	SPECIAL_FEATURE_1

				if (	tagBufferHeader3.lLengthUsed == 0x210 && 
						tagBufferHeader2.lLengthAllocated == 0x1fc	)
				{
					//		Now read the remaining of the block header.
					stNbRead = 
						fread ( 
							& tagBufferHeader4, 1, sizeof ( tagBufferHeader4 ), hDbxFile );
					if ( feof ( hDbxFile ) )
					{
						DisplayText ( "\n" );

						return;
					}

					if ( feof ( hDbxFile ) )
					{
						DisplayText ( "\n" );

						return;
					}

					if ( ferror ( hDbxFile ) )
					{
						DisplayErrorAndExit ( 255, &ExitProgram, "021 - fread hdr 4", "" );
						return;
					}

					//
					//		Locally 22/05/2006
					long lFilePosition = ftell ( hDbxFile );

					if( stNbRead != sizeof ( tagBufferHeader4 ) )
					{
						DisplayErrorAndExit ( 255, &ExitProgram, "021 - fread hdr 4", "" );
						return;
					}

					if ( tagBufferHeader3.lNextAddress > ( unsigned ) lFilePosition )
					{
						tagBufferHeader3.lLengthUsed = 
							tagBufferHeader3.lNextAddress - lFilePosition;
					}

					if ( tagBufferHeader3.lLengthUsed > tagBufferHeader2.lLengthAllocated )
					{
						tagBufferHeader3.lLengthUsed = tagBufferHeader2.lLengthAllocated;
					}

				}

#endif	//	SPECIAL_FEATURE_1

				//
				//		Normal situation
				if ( tagBufferHeader3.lLengthUsed <= tagBufferHeader2.lLengthAllocated 
					&& tagBufferHeader2.lLengthAllocated != 0 )
				{
					if ( bVerbose )
					{
						TraceOut ( "Address Match at address %8lx ", stPosition );
						TraceOut ( "- Block %4lx / %4lx - Next %8lx\n",
							tagBufferHeader3.lLengthUsed,
							tagBufferHeader2.lLengthAllocated,
							tagBufferHeader3.lNextAddress );
					}

					//
					//		Is it the end of the message.
					bMessageIndicator	= true;
					if ( tagBufferHeader3.lNextAddress == 0 )
					{
						bMessageTrailing	= true;
					}
					else
					{
						bMessageTrailing	= false;
					}

					//
					//		Store The Address
					if ( tagBufferHeader1.lAddress != 0 )
					{
						StoreAddress ( tagBufferHeader1.lAddress );

						if ( tagBufferHeader3.lNextAddress != 0 )
						{
							StoreNextAddress ( tagBufferHeader3.lNextAddress );
						}
					}

					//
					if ( iNumbAddresses % 1000 == 0 )
					{
						DisplayText ( ".", iNumbAddresses );
					}

				}
				else
				{
					iResult = fseek ( hDbxFile, ( size_t ) stPosition, SEEK_SET );
					if ( iResult != 0 )
					{
						DisplayErrorAndExit ( 255, &ExitProgram, "022 - fseek", "" );
						return;
					}

					tagBufferHeader3.lLengthUsed	= tagBufferHeader2.lLengthAllocated;
					tagBufferHeader3.lNextAddress	= 0;

					bMessageIndicator	= false;
					bMessageTrailing	= false;

				}

				//		Now read the remaining of the block header
				//		if length is not null.
				//		To Be Positionned to the next record
#ifdef	QUICK_SEARCH
				if ( tagBufferHeader3.lLengthUsed != 0 && bMessageIndicator )
				{
					iResult = fseek ( hDbxFile, 
						( size_t ) tagBufferHeader2.lLengthAllocated + 
						tagBufferHeader1.lAddress, SEEK_SET );
					if ( iResult != 0 )
					{
						DisplayErrorAndExit ( 255, &ExitProgram, "022 - fseek", "" );
						return;
					}
				}
#endif

				//
				//	Here we have a message

				//
			}
			else	//	if ( tagBufferHeader2.lLengthAllocated <= 0x0200 )
			{
				iResult = fseek ( hDbxFile, ( size_t ) stSavePosition, SEEK_SET );
				if ( iResult != 0 )
				{
					DisplayErrorAndExit ( 255, &ExitProgram, "022 - fseek", "" );
					return;
				}

			}		//	else if ( tagBufferHeader2.lLengthAllocated <= 0x0200 )
		}
		else	//	if ( stPosition == tagBufferHeader1.lAddress )
		{
			iResult = fseek ( hDbxFile, ( size_t ) stSavePosition, SEEK_SET );
			if ( iResult != 0 )
			{
				DisplayErrorAndExit ( 255, &ExitProgram, "022 - fseek", "" );
				return;
			}
		}	//	else if ( stPosition == tagBufferHeader1.lAddress )
	}

	DisplayText ( "\n" );

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool GetBoolVerbose ( )
{
	return bVerbose;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetBoolVerbose ( bool bValue )
{
	bVerbose = bValue;
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

#ifdef	_CONSOLE
	exit ( iError );
#endif

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void ResetAddress ( )
{
	AllocateBuffers ( );

	int		iX;

	for ( iX = 0;iX < iNumbAddresses; iX++ )
	{
		FilePositFlag [ iX ] &= POSIT_MASK;
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//		ReadOneFile.
//
///////////////////////////////////////////////////////////////////////////////
char *ReadOneFile ( char *pFilename, char *pDirectory, unsigned long lPosition,
						  void ( *pCallBack )( void *, void * ), void *pParm )
{
	AllocateBuffers ( );

	size_t			stNbRead;
	int				iResult;

	tagBufferHeader3.lNextAddress		= lPosition;

	tagInformation.lPosition			= lPosition;
	*tagInformation.szAuthor			= NULL;
	*tagInformation.szDate				= NULL;
	tagInformation.lSize				= 0;
	*tagInformation.szSubject			= NULL;
	tagInformation.iAttachementType		= 0;
	tagInformation.iAttachementCount	= 0;

	//
	//		Test if Position is below the file size

	//
	//		Create the output file.
	CreateMsgFile ( pDirectory );

	strcpy_s ( szMessageFilename, sizeof ( szMessageFilename ), GetMsgFilename ( ) );

	do
	{
		//
		//	Check if we have not already treated the record.
		if ( ! AlreadyTreated ( tagBufferHeader3.lNextAddress ) && hDbxFile != NULL )
		{

			iResult = fseek ( hDbxFile, ( size_t ) tagBufferHeader3.lNextAddress, SEEK_SET );
			if ( iResult != 0 )
			{
				DisplayErrorOnly ( 255, "022 - fseek", "" );
				return szMessageFilename;
			}

			//		Read the first header.
			stNbRead = fread ( & tagBufferHeader1, 1, sizeof ( tagBufferHeader1 ), hDbxFile );
			if ( feof ( hDbxFile ) )
			{
				DisplayErrorOnly ( 255, "022 - fread", "" );
				return szMessageFilename;
			}

			if ( ferror ( hDbxFile ) )
			{
				DisplayErrorOnly ( 255, "013 - fread hdr 1", "" );
				return szMessageFilename;
			}

			lFilePosition = ftell ( hDbxFile );

			if( stNbRead != sizeof ( tagBufferHeader1 ) )
			{
				DisplayErrorOnly ( 255, "014 - fread hdr 1", "" );
				return szMessageFilename;
			}

			//		We have an address
			if ( tagBufferHeader3.lNextAddress == tagBufferHeader1.lAddress )
			{

				//		Now get the length of the block.
				stNbRead = fread ( & tagBufferHeader2, 1, sizeof ( tagBufferHeader2 ), hDbxFile );
				if ( feof ( hDbxFile ) )
				{
					DisplayErrorOnly ( 255, "012 - fread", "" );
					return szMessageFilename;
				}

				if ( ferror ( hDbxFile ) )
				{
					DisplayErrorOnly ( 255, "015 - fread hdr 2", "" );
					return szMessageFilename;
				}

				lFilePosition = ftell ( hDbxFile );

				if( stNbRead != sizeof ( tagBufferHeader2 ) )
				{
					DisplayErrorOnly ( 255, "016 - fread hdr 2", "" );
					return szMessageFilename;
				}

				//	Allocate the buffer if needed.
				if ( tagBufferHeader2.lLengthAllocated <= 0x0200 )
				{

					if ( tagBufferHeader2.lLengthAllocated > lBlockLength )
					{
						FreeBlockMemory ( );

						AllocateBlockMemory ( tagBufferHeader2.lLengthAllocated );
					}

					//		Now read the remaining of the block header.
					stNbRead = fread ( & tagBufferHeader3, 1, sizeof ( tagBufferHeader3 ), hDbxFile );
					if ( feof ( hDbxFile ) )
					{
						DisplayErrorOnly ( 255, "012 - fread", "" );
						return szMessageFilename;
					}

					if ( ferror ( hDbxFile ) )
					{
						DisplayErrorOnly ( 255, "019 - fread hdr 3", "" );
						return szMessageFilename;
					}

					lFilePosition = ftell ( hDbxFile );

					if ( stNbRead != sizeof ( tagBufferHeader3 ) )
					{
						DisplayErrorOnly ( 255, "020 - fread hdr 3", "" );
						return szMessageFilename;
					}

					//
					//		Here is the place where it goes wrong !!!
					//		Yann 22/05/2006
					if (	tagBufferHeader3.lLengthUsed == 0x210 && 
							tagBufferHeader2.lLengthAllocated == 0x1fc	)
					{
						//		Now read the remaining of the block header.
						stNbRead = 
							fread ( 
								& tagBufferHeader4, 1, sizeof ( tagBufferHeader4 ), hDbxFile );
						if ( feof ( hDbxFile ) )
						{
							DisplayErrorOnly ( 255, "0201 - fread", "" );

							return szMessageFilename;
						}

						if ( feof ( hDbxFile ) )
						{
							DisplayErrorOnly ( 255, "0202 - fread", "" );

							return szMessageFilename;
						}

						if ( ferror ( hDbxFile ) )
						{
							DisplayErrorOnly ( 255, "0203 - fread hdr 4", "" );
							return szMessageFilename;
						}

						//
						//		Locally 22/05/2006
						long lFilePosition = ftell ( hDbxFile );

						if( stNbRead != sizeof ( tagBufferHeader4 ) )
						{
							DisplayErrorOnly ( 255, "0204 - fread hdr 4", "" );
							return szMessageFilename;
						}

						if ( tagBufferHeader3.lNextAddress > ( unsigned ) lFilePosition )
						{
							tagBufferHeader3.lLengthUsed = 
								tagBufferHeader3.lNextAddress - lFilePosition;
						}

						if ( tagBufferHeader3.lLengthUsed > tagBufferHeader2.lLengthAllocated )
						{
							tagBufferHeader3.lLengthUsed = tagBufferHeader2.lLengthAllocated;
						}
					}

					//
					//		Test if we are on a godd buffer.
					if ( tagBufferHeader3.lLengthUsed > tagBufferHeader2.lLengthAllocated 
						|| tagBufferHeader2.lLengthAllocated == 0 )
					{
						DisplayErrorOnly ( 255, "022 - Synchronization Error", "" );
						return szMessageFilename;
					}

					//		Now read the remaining of the block header
					//		if length is not null.
					if ( tagBufferHeader3.lLengthUsed != 0 )
					{
						if ( pBlockAddress == NULL )
						{
							AllocateBlockMemory ( lBlockLength );
						}

						memset ( pBlockAddress, 0, lBlockLength );

						stNbRead = 
							fread ( pBlockAddress, 1, tagBufferHeader2.lLengthAllocated, hDbxFile );
						if ( feof ( hDbxFile ) )
						{
							break;
						}

						if ( ferror ( hDbxFile ) )
						{
							DisplayErrorOnly ( 255, "023 - fread blk 1", "" );
							return szMessageFilename;
						}

						lFilePosition = ftell ( hDbxFile );

						if( stNbRead != tagBufferHeader2.lLengthAllocated )
						{
							DisplayErrorOnly ( 255, "024 - fread blk 1", "" );
							return szMessageFilename;
						}

						//		Here use length used or allocated.
						WriteMsgFile ( pBlockAddress, tagBufferHeader3.lLengthUsed );
					}
				}
			}
		}
		else
		{
//			DisplayErrorAndExit ( 255, &ExitProgram, "022 - infinite loop", "Next address is %8lx\n",
//				tagBufferHeader3.lNextAddress );
			DisplayError ( "022 - infinite loop - Next address is %8lx\n", 
							tagBufferHeader3.lNextAddress );
			tagBufferHeader3.lNextAddress = 0;
			return szMessageFilename;
		}

	}
	while ( tagBufferHeader3.lNextAddress != 0 && hDbxFile != NULL );

	//
	//		Create the output file.
	CloseMsgFile ( );

	// DecodeFullMessageBuffer ( pBufferAddress, lBufferPosition );
	if ( DecodeFile ( ) )
	{
		if ( pCallBack != NULL )
		{
			memset ( tagInformation.szAuthor, 0, sizeof ( tagInformation.szAuthor ) );
			strncpy_s ( tagInformation.szAuthor, 
						sizeof ( tagInformation.szAuthor ), 
						GetAuthor ( ), sizeof ( tagInformation.szAuthor ) - 1 );
			memset ( tagInformation.szEmail, 0, sizeof ( tagInformation.szEmail ) );
			strncpy_s ( tagInformation.szEmail, 
						sizeof ( tagInformation.szEmail ), 
						GetEMail ( ), sizeof ( tagInformation.szEmail ) - 1 );
			memset ( tagInformation.szDate, 0, sizeof ( tagInformation.szDate ) );
			strncpy_s ( tagInformation.szDate, 
						sizeof ( tagInformation.szDate ), 
						GetDate ( ), sizeof ( tagInformation.szDate ) - 1 );
			tagInformation.lSize	= GetBufferSize ( );
			memset ( tagInformation.szSubject, 0, sizeof ( tagInformation.szSubject ) );
			strncpy_s ( tagInformation.szSubject, 
						sizeof ( tagInformation.szSubject ), 
						GetSubject ( ), sizeof ( tagInformation.szSubject ) - 1 );
			tagInformation.iAttachementType = GetAttachementType ( );
			tagInformation.iAttachementCount = GetAttachementCount ( );

			pCallBack ( pParm, &tagInformation );
		}

		DeleteMsgFile ( pDirectory );
		strcpy_s (	szMessageFilename,
					sizeof ( szMessageFilename ), GetMsgFilename ( ) );
	}
	else
	{
		RenameMsgFile ( pDirectory );
		strcpy_s (	szMessageFilename,
					sizeof ( szMessageFilename ), GetMsgFilename ( ) );
	}

	return szMessageFilename;

}

//
///////////////////////////////////////////////////////////////////////////////
//		Read the file.
//
///////////////////////////////////////////////////////////////////////////////
int ReadOutlookFileStep1 ( char *pFilename, char *pDirectory, 
						  void ( *pCallBack )( void *, void * ), void *pParm )
{
	
	AllocateBuffers ( );

	strcpy_s ( szProcessStep, sizeof ( szProcessStep ), "Step One" );

	OpenDbxFile ( pFilename );

	lFileLength = GetFileLength ( hDbxFile );

	//
	//		Build address table.
	BuildAddressesTable ( );

	//
	//		Sort address table.
	SortAddress ( );

	//
	//		Clean address table.
	CleanAddressesTable ( );

	//		Close file.
	CloseDbxFile ( );

	return 0;
}

//
///////////////////////////////////////////////////////////////////////////////
//		Read the file.
//
///////////////////////////////////////////////////////////////////////////////
int ReadOutlookFileStep2 ( char *pFilename, char *pDirectory, 
						  void ( *pCallBack )( void *, void * ), void *pParm )
{
	int				iX;
	
	AllocateBuffers ( );

	strcpy_s ( szProcessStep, sizeof ( szProcessStep ), "Step Two" );

	ResetAddress ( );

	hDbxFile = NULL;
	fopen_s ( &hDbxFile, pFilename, "rb" );
	if ( hDbxFile == NULL )
	{
		DisplayErrorAndExit ( 255, &ExitProgram, "011 - fopen", "" );
		return 0;
	}

	lFileLength = GetFileLength ( hDbxFile );

	//
	//		Now loop on the table to read data.
	
	iX = 0;
	while ( iX < iNumbAddresses && ! bAddressRoutinesCancel )
	{

		if ( FilePositFlag [ iX ] == POSIT_VALID )
		{
#ifndef	_CONSOLE
			if ( FilePositSeld [ iX ] )
			{
#endif
				ReadOneFile (	pFilename, pDirectory, FilePositions [ iX ], 
								pCallBack, pParm );
#ifndef	_CONSOLE
			}
#endif
		}

		iX++;
	}

	//	Close File
	CloseDbxFile ( );

	return 0;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int ReadOutlookFile ( char *pFilename, char *pDirectory, 
					 void ( *pCallBack )( void *, void * ), void *pParm )
{
	strcpy_s ( szProcessStep, sizeof ( szProcessStep ), "Starting" );

	ReadOutlookFileStep1 ( pFilename, pDirectory, pCallBack, pParm );

	return ( ReadOutlookFileStep2 ( pFilename, pDirectory, pCallBack, pParm ) );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void AllocateBlockMemory ( )
{

	if ( pBlockAddress == NULL )
	{
		//		Allocate the block buffer.
		lBlockLength = MAX_BLOC_SIZE;
		pBlockAddress = ( char * ) malloc ( lBlockLength * 2 );
		if ( pBlockAddress == NULL )
		{
			DisplayError ( "Unable to allocate %08lx bytes\n", lBlockLength );
			ExitProgram ( 255 );
		}

		memset ( pBlockAddress, 0, lBlockLength * 2 );
	}
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void AllocateBlockMemory ( unsigned long iLength )
{

	if ( iLength <= 0 || iLength > MAX_BLOC_SIZE )
	{
		DisplayError ( "Unable to allocate %08lx bytes\n", lBlockLength );
		ExitProgram ( 255 );
	}

	if ( pBlockAddress == NULL )
	{
		//		Allocate the block buffer.
		lBlockLength = iLength;
		pBlockAddress = ( char * ) malloc ( lBlockLength * 2 );
		if ( pBlockAddress == NULL )
		{
			DisplayError ( "Unable to allocate %08lx bytes\n", lBlockLength );
			ExitProgram ( 255 );
		}

		memset ( pBlockAddress, 0, lBlockLength * 2 );

	}
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void FreeBlockMemory ( )
{
	//		Free buffer
	if ( pBlockAddress != NULL )
	{
		free ( pBlockAddress );
		pBlockAddress = NULL;
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int GetNextIndexFilePosition ( int iStart )
{

	AllocateBuffers ( );

	int			iX;

	for ( iX = iStart; iX < iNumbAddresses; iX++ )
	{
		if ( FilePositFlag [ iX ] == POSIT_VALID )
		{
			return iX;
		}
	}

	return -1;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
unsigned long GetFilePosition ( int iX )
{
	AllocateBuffers ( );

	if ( iX < MAX_ADDRESSES )
	{
		return FilePositions [ iX ];
	}

	return 0L;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
char *GetProcessStep ( )
{
	return szProcessStep;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
long GetFileLength ( )
{
	return lFileLength;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
long GetFilePosition ( )
{
	return lFilePosition;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetAddressRoutinesCancel ( bool bValue )
{
	bAddressRoutinesCancel = bValue;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetAllSelected ( int bValue )
{
	AllocateBuffers ( );

#ifndef	_CONSOLE
	memset ( FilePositSeld, bValue, sizeof ( char ) * MAX_ADDRESSES );
#endif

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetNoneSelected ( )
{
	SetAllSelected ( 0 );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetSelection ( unsigned long lAddress, int bValue )
{
	AllocateBuffers ( );

	int		iX;
	iX = SearchAddress ( lAddress );

#ifndef	_CONSOLE
	FilePositSeld [ iX ] = bValue;
#endif
	
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetNoSelection ( unsigned long lAddress )
{
	SetSelection ( lAddress, 0 );
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool SaveAddresses ( const char *pFile )
{
	AllocateBuffers ( );

	FILE *hFile = NULL;
	fopen_s ( &hFile, pFile, "wb" );
	if ( hFile )
	{
		fwrite ( &iNumbAddresses, 1, sizeof ( iNumbAddresses ), hFile );
		fwrite ( FilePositions, 1, sizeof ( unsigned long ) * iNumbAddresses, hFile );
		fwrite ( &iNumbAddrsNext, 1, sizeof ( iNumbAddrsNext ), hFile );
		fwrite ( FilePositNext, 1, sizeof ( unsigned long ) * iNumbAddrsNext, hFile );
		fclose ( hFile );
		return true;
	}

	return false;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
bool RestoreAddresses ( const char *pFile )
{
	AllocateBuffers ( );

	FILE *hFile = NULL;
	fopen_s ( &hFile, pFile, "rb" );
	if ( hFile )
	{
		fread ( &iNumbAddresses, 1, sizeof ( iNumbAddresses ), hFile );
		fread ( FilePositions, 1, sizeof ( unsigned long ) * iNumbAddresses, hFile );
		fread ( &iNumbAddrsNext, 1, sizeof ( iNumbAddrsNext ), hFile );
		fread ( FilePositNext, 1, sizeof ( unsigned long ) * iNumbAddrsNext, hFile );
		fclose ( hFile );

		for ( int iX = 0; iX < iNumbAddresses; iX++ )
		{
			FilePositFlag [ iX ] = POSIT_VALID;
		}

		return true;
	}

	return false;
}

