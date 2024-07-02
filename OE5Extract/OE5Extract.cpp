//
//		Outlook Extract objects.
//

#include <stdlib.h>
#include <stdio.h>
#include <direct.h>

#include <malloc.h>
#include <string.h>
#include <stdarg.h>
//#include <error.h>
#include <errno.h>

#include <process.h>
#include <dos.h>
#include <io.h>

#include "AutomaticVersionHeader.h"

#include "OE5ExtractDefinitions.h"

#include "TextRoutines.h"
#include "MimeRoutines.h"
#include "FileRoutines.h"
#include "DisplayAndTrace.h"
#include "DecodeRoutines.h"
#include "RemoveStringsRoutines.h"
#include "OEAddressRoutines.h"
#include "OEMessagesRoutines.h"
#include "DecodeRoutines.h"


//
//		The file path.
static	char					szPathname [ LEN_PATHNAME ]			= "";

//
//		The destination drive.
static	char					szDestDrive [ LEN_PATHNAME ]		= "";

//
//		The destination directory.
static	char					szDestDirectory [ LEN_DIRECTORY ]	= "";


//		Change directory
static	bool					bDirectory							= false;

//		Change disk only.
static	bool					bDiskDrive							= false;

//		Ok the argument are corrects.
static	bool					bFilename							= false;

//		Alter Name Only
static	bool					bAlterNameOnly						= false;

//		Remove directory
static	bool					bRemoveTrailingDirectory			= false;
static	bool					bRemoveLeadingDirectory				= false;
static	bool					bRemoveTrailingNumbers				= false;

//		Modify type
static	bool					bModifyType							= false;
static	char					szDefinedType [ LEN_FILETYPE ]		= "";

//
//		Prototypes.
void RenameTreatDirectory ( const char *pWildName, char *pUpperDirectory );

//
//		Exit program.
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
//		Display usage and exit.
//
///////////////////////////////////////////////////////////////////////////////
void DisplayUsageAndExit ( char *pCmd )
{
		DisplayText ( "Usage is %s [-options] [-options] [-f ] filename\n", pCmd );
		DisplayText ( "Where options is one or more command modifiers:\n" );
		DisplayText ( "-a   or -alternameonly to rename files only\n" );
		DisplayText ( "-c   or -collapse to collapse spaces on final name\n" );
		DisplayText ( "-d   or -disk to set the destination disk (ex: -d E:)\n" );
		DisplayText ( "-f   or -file to specify input file (ex: -f c:\\temp\\newsfolder.dbx)\n" );
		DisplayText ( "-h   or -help to display this text\n" );
		DisplayText ( "-k   or -keep to keep intermediate files (.nws files)\n" );
		DisplayText ( "-l   or -leave do not overwrite existing files\n" );
		DisplayText ( "-m   or -modifytype set the file type (ex: -m .mid)\n" );
		DisplayText ( "-n   or -name set the file name as the name of the attachement\n" );
		DisplayText ( "-o   or -onlymessages (no attachement extraction)\n" );
		DisplayText ( "-p   or -path to set the destination directory (ex: -D F:\\TEMP)\n" );
		DisplayText ( "-rld or -removeleadingdirectory remove directory inside the name\n" );
		DisplayText ( "-rn  or -removenumbers remove numbers from the name\n" );
		DisplayText ( "-ro  or -removeother remove other signs from the name\n" );
		DisplayText ( "-rs  or -removestring remove a string from the name (ex: -rs \"string 1\")\n" );
		DisplayText ( "-rtd or -removetrailingdirectory remove directory inside the name\n" );
		DisplayText ( "-rtn or -removetrailingnumbers remove trailing numbers inside the name\n" );
		DisplayText ( "-s   or -subject set the name of the file as the subject of the message\n" );
		DisplayText ( "-t   or -trace to trace information on display\n" );
		DisplayText ( "-v   or -verbose to trace more information on display (use with -t)\n" );
		DisplayText ( "\n" );
		DisplayText ( "Example: %s c:\\temp\\newsfolder.dbx\n", pCmd );


		ExitProgram ( 255 );
}

//
///////////////////////////////////////////////////////////////////////////////
//		Get arguments for program.
//
///////////////////////////////////////////////////////////////////////////////
void GetArguments ( int nArgs, char *pArgs [] )
{
	//		A index
	int				iX;

	//		Say we have not all arguments.
	bFilename			= false;

	//		Reset flags
	SetBoolTrace ( false );
	SetBoolVerbose ( false );
	SetBoolKeep ( false );
	bDirectory					= false;
	bDiskDrive					= false;
	SetBoolLeave ( false );
	SetBoolSubject ( false );
	SetBoolName ( false );
	SetBoolCollapse	( false );
	SetBoolRemoveNumbers ( false );
	SetBoolRemoveOther ( false );
	bAlterNameOnly				= false;
	bRemoveTrailingDirectory	= false;
	bRemoveLeadingDirectory		= false;
	bRemoveTrailingNumbers		= false;
	bModifyType					= false;
	SetBoolOnlyMessages ( false );


	//		Loop on all arguments.
	for ( iX = 1; iX < nArgs; iX++ )
	{

		if ( CompareStringB ( pArgs [ iX ], "-t" ) == 0 || CompareStringB ( pArgs [ iX ], "-trace" ) == 0 )
		{
				SetBoolTrace ( true );
		}
		else if ( CompareStringB ( pArgs [ iX ], "-v" ) == 0 || CompareStringB ( pArgs [ iX ], "-verbose" ) == 0 )
		{
			SetBoolVerbose ( true );
		}
		else if ( CompareStringB ( pArgs [ iX ], "-rn" ) == 0 || CompareStringB ( pArgs [ iX ], "-removenumbers" ) == 0 )
		{
			SetBoolRemoveNumbers ( true );
		}
		else if ( CompareStringB ( pArgs [ iX ], "-ro" ) == 0 || CompareStringB ( pArgs [ iX ], "-removeother" ) == 0 )
		{
			SetBoolRemoveOther ( true ); 
		}
		else if ( CompareStringB ( pArgs [ iX ], "-c" ) == 0 || CompareStringB ( pArgs [ iX ], "-collapse" ) == 0 )
		{
			SetBoolCollapse ( true );
		}
		else if ( CompareStringB ( pArgs [ iX ], "-k" ) == 0 || CompareStringB ( pArgs [ iX ], "-keep" ) == 0 )
		{
			SetBoolKeep ( true );
		}
		else if ( CompareStringB ( pArgs [ iX ], "-o" ) == 0 || CompareStringB ( pArgs [ iX ], "-onlymessages" ) == 0 )
		{
			SetBoolOnlyMessages ( true );
			SetBoolKeep ( true );
		}
		else if ( CompareStringB ( pArgs [ iX ], "-a" ) == 0 || CompareStringB ( pArgs [ iX ], "-alternameonly" ) == 0 )
		{
			bAlterNameOnly	= true;
		}
		else if ( CompareStringB ( pArgs [ iX ], "-l" ) == 0 || CompareStringB ( pArgs [ iX ], "-leave" ) == 0 )
		{
			SetBoolLeave ( true );
		}
		else if ( CompareStringB ( pArgs [ iX ], "-n" ) == 0  || CompareStringB ( pArgs [ iX ], "-name" ) == 0 )
		{
			SetBoolName	( true );
		}
		else if ( CompareStringB ( pArgs [ iX ], "-s" ) == 0  || CompareStringB ( pArgs [ iX ], "-subject" ) == 0 )
		{
			SetBoolSubject ( true );
		}
		else if ( CompareStringB ( pArgs [ iX ], "-h" ) == 0  || CompareStringB ( pArgs [ iX ], "-help" ) == 0 )
		{
			DisplayUsageAndExit ( pArgs [ 0 ] );
		}
		else if ( CompareStringB ( pArgs [ iX ], "-rtd" ) == 0  || CompareStringB ( pArgs [ iX ], "-removetrailingdirectory" ) == 0 )
		{
			bRemoveTrailingDirectory = true;
		}
		else if ( CompareStringB ( pArgs [ iX ], "-rld" ) == 0  || CompareStringB ( pArgs [ iX ], "-removeleadingdirectory" ) == 0 )
		{
			bRemoveLeadingDirectory = true;
		}
		else if ( CompareStringB ( pArgs [ iX ], "-rtn" ) == 0  || CompareStringB ( pArgs [ iX ], "-removetrailingnumbers" ) == 0 )
		{
			bRemoveTrailingNumbers = true;
		}
		else if ( CompareStringB ( pArgs [ iX ], "-rs" ) == 0 || CompareStringB ( pArgs [ iX ], "-removestring" ) == 0  )
		{
			iX++;
			if ( iX < nArgs )
			{
				AllocRemoveStrings ( pArgs [ iX ] );
			}
			else
			{
				DisplayUsageAndExit ( pArgs [ 0 ] );
			}
		}
		else if ( CompareStringB ( pArgs [ iX ], "-d" ) == 0 || CompareStringB ( pArgs [ iX ], "-disk" ) == 0  )
		{
			iX++;
			if ( iX < nArgs )
			{
				strcpy_s ( szDestDrive, sizeof ( szDestDrive ), pArgs [ iX ] );
				bDiskDrive = true;
			}
			else
			{
				DisplayUsageAndExit ( pArgs [ 0 ] );
			}
		}
		else if ( CompareStringB ( pArgs [ iX ], "-m" ) == 0 || CompareStringB ( pArgs [ iX ], "-modifytype" ) == 0  )
		{
			iX++;
			if ( iX < nArgs )
			{
				strcpy_s ( szDefinedType, sizeof ( szDefinedType ), pArgs [ iX ] );
				bModifyType = true;
			}
			else
			{
				DisplayUsageAndExit ( pArgs [ 0 ] );
			}
		}
		else if ( CompareStringB ( pArgs [ iX ], "-p" ) == 0 || CompareStringB ( pArgs [ iX ], "-path" ) == 0 )
		{
			iX++;
			if ( iX < nArgs )
			{
				strcpy_s ( szDestDirectory, sizeof ( szDestDirectory ), pArgs [ iX ] );
				bDirectory = true;
			}
			else
			{
				DisplayUsageAndExit ( pArgs [ 0 ] );
			}
		}
		else if ( CompareStringB ( pArgs [ iX ], "-f" ) == 0 || CompareStringB ( pArgs [ iX ], "-file" ) == 0 )
		{
			if ( ! bFilename )
			{
				iX++;
				if ( iX < nArgs )
				{
					strcpy_s ( szPathname, sizeof ( szPathname ), pArgs [ iX ] );
					bFilename = true;
				}
				else
				{
					DisplayUsageAndExit ( pArgs [ 0 ] );
				}
			}
			else
			{
				DisplayUsageAndExit ( pArgs [ 0 ] );
			}
		}
		else if ( *pArgs [ iX ] != '-' )
		{
			if ( ! bFilename )
			{
				strcpy_s ( szPathname, sizeof ( szPathname ), pArgs [ iX ] );
				bFilename = true;
			}
			else
			{
				DisplayUsageAndExit ( pArgs [ 0 ] );
			}
		}
		else
		{
			DisplayUsageAndExit ( pArgs [ 0 ] );
		}

	}

	if ( ! bFilename )
	{
		DisplayUsageAndExit ( pArgs [ 0 ] );
	}

	//		Set the Default Message directory.
	if ( ! bDirectory )
	{
		SetDirectory ( szPathname );
	}
	else
	{
		SetDirectoryFrom ( szDestDirectory, szPathname );
	}

	//		Test if we override the disk drive.
	if ( bDiskDrive )
	{
		SetDrive ( szDestDrive );
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
unsigned long RenameGetLength ( char *pString )
{
        FILE            *hFile;
        unsigned long   lCount;

        hFile = NULL;
		fopen_s ( &hFile, pString, "r" );
        if ( hFile == NULL )
        {
            return ( 0 );
        }

        lCount = fseek ( hFile, 0L, SEEK_END );
        if ( ferror ( hFile ) )
        {
            return ( 0 );
        }

        lCount = ftell ( hFile );
        if ( ferror ( hFile ) )
        {
            return ( 0 );
        }

        fclose ( hFile );

        return ( lCount );
}


//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void MakeName ( char *pFilename, size_t iFilename, char *szName )
{
        char            *pDot;
        unsigned long   lCount;
        char            szFilename [ LEN_FILENAME ];

        lCount = RenameGetLength ( szName );

        pDot = FindTypeOrNull ( pFilename );
        if ( pDot != NULL )
        {
                *pDot = '\0';
                pDot++;
                sprintf_s ( szFilename, sizeof ( szFilename ),
							"%s_%06d.%s", pFilename, lCount, pDot );
        }
        else
        {
                sprintf_s ( szFilename, sizeof ( szFilename ),
							"%s_%06d", pFilename, lCount );
        }

        strcpy_s ( pFilename, iFilename, szFilename );
}

//
///////////////////////////////////////////////////////////////////////////////
//		Remove Some
//
///////////////////////////////////////////////////////////////////////////////
void RemoveSome ( char *pString )
{
	RemoveLeadingUnderscore ( pString );

	RemoveLeadingSpaces ( pString );

	RemoveTrailingSpaces ( pString );

	if ( GetBoolCollapse ( ) )
	{
		Collapse ( pString );
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RenameTreatFile ( struct _finddatai64_t *pFile, const char *pWildName, char *pUpperDirectory )
{
        char            szNewFilename [ LEN_FILENAME ];
        char            *pString;
        int             iStatus;

        bool            bToRename;
        bool			bCapitalizeOnly;

        int             iCount;
        bool            bIsDir;

        unsigned long   lExistingIfAny;
        unsigned long   lCurrent;

		//		Is the file a directory.
        bIsDir = false;
        if ( pFile->attrib & _A_SUBDIR )
        {
            bIsDir = true;

            if ( ( strcmp ( pFile->name, "."  ) != 0 ) &&
                 ( strcmp ( pFile->name, ".." ) != 0 ) )
            {
		        char            szOldDirectory [ LEN_FILENAME ];

                memset ( szOldDirectory, 0, sizeof ( szOldDirectory ) );

                _getcwd (   szOldDirectory, sizeof ( szOldDirectory ) - 1 );
                _chdir ( pFile->name );

                RenameTreatDirectory ( pWildName, pFile->name );

                _chdir ( szOldDirectory );

            }
			//		We are on . or .. directory so return
            else
            {
                return;
            }
        }

		//
		//		Get the name.
        strcpy_s ( szNewFilename, sizeof ( szNewFilename ), pFile->name );

        bToRename       = false;
        bCapitalizeOnly = false;

        /*
         *      Remove some bytes.
         */
		RemoveSome ( szNewFilename );

		//		Filter name.
        FilterName ( szNewFilename, ( pFile->attrib & _A_SUBDIR ) != 0 );

		RemoveSome ( szNewFilename );

        iCount = 0;

        if ( bIsDir )
        {
            CapitalizeFullName ( szNewFilename );
        }
        else
        {
			FilterFilename ( szNewFilename );
			RemoveSome ( szNewFilename );

			if ( bModifyType )
			{
				if ( FindTypeOrNull ( szNewFilename ) == NULL )
				{
					strcat_s ( szNewFilename, sizeof ( szNewFilename ), szDefinedType );
					RemoveSome ( szNewFilename );
				}
			}

			if ( bRemoveLeadingDirectory )
			{
	            RemoveLeadingDirectory ( szNewFilename, sizeof ( szNewFilename ),
											pUpperDirectory );
				RemoveSome ( szNewFilename );
			}

			if ( bRemoveTrailingDirectory )
			{
				RemoveTrailingDirectory ( szNewFilename, sizeof ( szNewFilename ),
											pUpperDirectory );
				RemoveSome ( szNewFilename );
			}

			RemoveMultipleDot ( szNewFilename );
			RemoveSome ( szNewFilename );

			ReplaceSpaceDot ( szNewFilename );
			RemoveSome ( szNewFilename );

			LeaveOneDot ( szNewFilename );
			RemoveSome ( szNewFilename );

			RemoveMultipleUnderscore ( szNewFilename );
			RemoveSome ( szNewFilename );

            CapitalizeName ( szNewFilename );
			RemoveSome ( szNewFilename );

			if ( bRemoveTrailingNumbers )
			{
				RemoveTrailingNumbers ( szNewFilename, sizeof ( szNewFilename ) );
				RemoveSome ( szNewFilename );
			}

            pString = strchr ( szNewFilename, '.' );
            if ( pString != NULL )
            {
                LowerName ( pString );
            }
        }

		RemoveSome ( szNewFilename );

        if ( ! ( pFile->attrib & _A_SUBDIR ) )
        {
            /*
             *      Get File Size.
             */
            lCurrent = RenameGetLength ( pFile->name );

            /*
             *      Get the size of an previous existing file.
             */
            lExistingIfAny = RenameGetLength ( szNewFilename );
        }

        bToRename = ( strcmp ( szNewFilename, pFile->name ) != 0 );
		bCapitalizeOnly = ( CompareStringB ( szNewFilename, pFile->name ) == 0 );

		//
		//		Rename file.
        while ( bToRename )
        {
            /*
             *      Rename if size are different or subdirectory.
             */
            if ( ( lExistingIfAny != lCurrent ) || ( bCapitalizeOnly ) || ( pFile->attrib & _A_SUBDIR  ) )
            {
                DisplayText ( "Rename %s into %s\n", pFile->name, szNewFilename  );
                iStatus = rename ( pFile->name, szNewFilename );
                if ( iStatus != 0 )
                {
#ifdef	_CONSOLE
                    perror ( "Rename " );
#endif
                    MakeName ( szNewFilename, sizeof ( szNewFilename ), pFile->name );
                    iCount++;
                    if ( iCount > 1 )
                    {
                        strcpy_s ( szNewFilename, sizeof ( szNewFilename ), pFile->name );
                        strcat_s ( szNewFilename, sizeof ( szNewFilename ), ".del" );
                        DisplayText ( "Rename %s into %s\n", pFile->name, szNewFilename  );
                        // iStatus = rename ( pFile->name, szNewFilename );
                        bToRename = false;
                    }
                }
                else
                {
                    bToRename = false;
                }
            }
            else
            {
                strcpy_s ( szNewFilename, sizeof ( szNewFilename ), pFile->name );
                strcat_s ( szNewFilename, sizeof ( szNewFilename ), ".del" );
                DisplayText ( "Rename %s into %s\n", pFile->name, szNewFilename  );
                // iStatus = rename ( pFile->name, szNewFilename );
                bToRename = false;
            }
        }

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RenameTreatDirectory ( const char *pWildName, char *pUpperDirectory )
{
        /*
         *      General purpose index.
         */
        long                iStream;

        /*
         *      Structure for find file.
         */
        struct _finddatai64_t   tagFile;

        /*
         *      Find first name.
         */
		DisplayText ( "Treating %s in %s\n", pWildName, pUpperDirectory );

        iStream = _findfirsti64 ( pWildName, &tagFile );
        if ( iStream != -1 )
        {
            RenameTreatFile ( &tagFile, pWildName, pUpperDirectory );

            while ( _findnexti64 ( iStream, &tagFile ) == 0 )
            {
                RenameTreatFile ( &tagFile, pWildName, pUpperDirectory );
            }
        }
        else
        {
            DisplayError ( "No file %s\n",  pWildName );
        }

        return;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int RenameFiles ( char *pPathName )
{

        RenameTreatDirectory ( pPathName, "." );

        ExitProgram ( 0 );

        return 0;

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
int main ( int nArgs, char *pArgs [] )
{
	//		Result for opérations.
	//
	//		Display Copyright.
	DisplayText ( "%s - Extract attachements from Outlook Express mails and news\n", PROGRAM_NAME );
	DisplayText ( "(c) 2001-%s - %s - %s\n", PROGRAM_YEAR, PROGRAM_VERSION, PROGRAM_MAIL );
	DisplayText ( "\n" );


	//		Get all arguments.
	GetArguments ( nArgs, pArgs );

	if ( ! bAlterNameOnly )
	{
		//		Process file
		ProcessFile ( szPathname, NULL, NULL );

	}
	else
	{
		RenameFiles ( szPathname );
	}

	ExitProgram ( 0 );

	return 0;


}
