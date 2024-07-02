#include "stdafx.h"

#ifdef  _CONSOLE
#include <windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <direct.h>

#include <malloc.h>
#include <string.h>
#include <stdarg.h>
// #include <error.h>
// #include <errno.h>
#endif

#include "DisplayAndTrace.h"

//
//      The error file.
static  char                    szLogFilename [ LEN_LOGPATHNAME ]   = "";
static  FILE                    *hLogFile                           = NULL;

//      Trace mode
static  bool                    bTrace                              = false;

static  bool                    bDisplayMessageBox                  = true;

//
///////////////////////////////////////////////////////////////////////////////
//      Display Last Windows Error
//
///////////////////////////////////////////////////////////////////////////////
static void DisplayLastError ( )
{
    LPVOID lpMsgBuf;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL
        );

#ifdef  _CONSOLE
        fprintf ( stderr, "Last Error: %s\n", (char *) lpMsgBuf );
#endif

    if ( hLogFile )
    {
        fprintf ( hLogFile, "Last Error: %s\n", (char *) lpMsgBuf );
    }

    LocalFree( lpMsgBuf );
}

//
///////////////////////////////////////////////////////////////////////////////
//      Display Error and Exit Program.
//
///////////////////////////////////////////////////////////////////////////////
void TraceOut ( char *pFormat, ... )
{
    va_list     pListe;

    if ( *pFormat != 0 )
    {
        va_start ( pListe, pFormat );
        if ( bTrace )
        {
#ifdef  _CONSOLE
            vfprintf ( stdout, pFormat, pListe );
#endif
        }

        va_end ( pListe );
    }

}

//
///////////////////////////////////////////////////////////////////////////////
//      Display Error and Exit Program.
//
///////////////////////////////////////////////////////////////////////////////
void DisplayErrorAndExit ( int iError, void ( *pExit )( int ), char *pText, char *pFormat, ... )
{
    va_list     pListe;

    if ( errno != 0 )
    {
#ifdef  _CONSOLE
        perror ( pText );
#endif
    }

    DisplayLastError ( );

    if ( *pFormat != 0 )
    {
        va_start ( pListe, pFormat );

#ifdef  _CONSOLE
        vfprintf ( stderr, pFormat, pListe );
#endif

#ifndef _CONSOLE
        if ( bDisplayMessageBox )
        {
            char        szTemp [ LEN_PATHNAME ];
            strcpy_s ( szTemp, sizeof ( szTemp ), pText );
            strcat_s ( szTemp, sizeof ( szTemp ), "\n" );
            vsprintf_s ( szTemp + strlen ( szTemp ),
                        sizeof ( szTemp ) - strlen ( szTemp ),
                        pFormat, pListe );
            strcat_s ( szTemp, sizeof ( szTemp ),
                        "\nSelect NO to hide message box" );
            strcat_s ( szTemp, sizeof ( szTemp ),
                        "\n    or YES to continue to see messages" );
            int iResult =
                ::MessageBox ( NULL, szTemp, "Outlook Express Extraction", MB_YESNO | MB_ICONEXCLAMATION );
            if ( iResult == IDNO )
            {
                bDisplayMessageBox = false;
            }
        }
#endif

        if ( hLogFile )
        {
            fprintf ( hLogFile, "%s - ", pText );
            vfprintf ( hLogFile, pFormat, pListe );
        }

        va_end ( pListe );
    }

    if ( pExit != NULL )
    {
        pExit ( iError );
    }
    else
    {
#ifdef  _CONSOLE
        exit ( iError );
#endif

    }

}

//
///////////////////////////////////////////////////////////////////////////////
//      Display Error
//
///////////////////////////////////////////////////////////////////////////////
void DisplayErrorOnly ( int iError, char *pText, char *pFormat, ... )
{
    va_list     pListe;

    if ( errno != 0 )
    {
#ifdef  _CONSOLE
        perror ( pText );
#endif
    }

    DisplayLastError ( );

    if ( *pFormat != 0 )
    {
        va_start ( pListe, pFormat );

#ifdef  _CONSOLE
        vfprintf ( stderr, pFormat, pListe );
#endif

#ifndef _CONSOLE
        if ( bDisplayMessageBox )
        {
            char        szTemp [ LEN_PATHNAME ];
            strcpy_s ( szTemp, sizeof ( szTemp ), pText );
            strcat_s ( szTemp, sizeof ( szTemp ), "\n" );
            vsprintf_s ( szTemp + strlen ( szTemp ),
                        sizeof ( szTemp ) - strlen ( szTemp ),
                        pFormat, pListe );
            strcat_s ( szTemp, sizeof ( szTemp ),
                        "\nSelect NO to hide message box" );
            strcat_s ( szTemp, sizeof ( szTemp ),
                        "\n    or YES to continue to see messages" );
            int iResult =
                ::MessageBox ( NULL, szTemp, "Outlook Express Extraction", MB_YESNO | MB_ICONEXCLAMATION );
            if ( iResult == IDNO )
            {
                bDisplayMessageBox = false;
            }
        }
#endif

        if ( hLogFile )
        {
            fprintf ( hLogFile, "%s - ", pText );
            vfprintf ( hLogFile, pFormat, pListe );
        }

        va_end ( pListe );
    }

}

//
///////////////////////////////////////////////////////////////////////////////
//      Display Error and Exit Program.
//
///////////////////////////////////////////////////////////////////////////////
void DisplayError ( char *pFormat, ... )
{
    va_list     pListe;

    if ( errno != 0 )
    {
#ifdef  _CONSOLE
        perror ( "Error " );
#endif
    }

    DisplayLastError ( );

    if ( *pFormat != 0 )
    {
        va_start ( pListe, pFormat );

#ifdef  _CONSOLE
        vfprintf ( stderr, pFormat, pListe );
#endif

#ifndef _CONSOLE
        if ( bDisplayMessageBox )
        {
            char        szTemp [ LEN_PATHNAME ];
            vsprintf_s ( szTemp, sizeof ( szTemp ), pFormat, pListe );
            strcat_s ( szTemp, sizeof ( szTemp ), "\nSelect NO to hide message box" );
            int iResult =
                ::MessageBox ( NULL, szTemp, "Outlook Express Extraction", MB_YESNO | MB_ICONEXCLAMATION );
            if ( iResult == IDNO )
            {
                bDisplayMessageBox = false;
            }
        }
#endif

        if ( hLogFile )
        {
            vfprintf ( hLogFile, pFormat, pListe );
        }

        va_end ( pListe );
    }

}

//
///////////////////////////////////////////////////////////////////////////////
//      Display Error and Exit Program.
//
///////////////////////////////////////////////////////////////////////////////
void DisplayWarning ( char *pFormat, ... )
{
    va_list     pListe;

    if ( errno != 0 )
    {
#ifdef  _CONSOLE
        perror ( "Error " );
#endif
    }

    DisplayLastError ( );

    if ( *pFormat != 0 )
    {
        va_start ( pListe, pFormat );

#ifdef  _CONSOLE
        vfprintf ( stderr, pFormat, pListe );
#endif

        if ( hLogFile )
        {
            vfprintf ( hLogFile, pFormat, pListe );
        }

        va_end ( pListe );
    }

}

//
///////////////////////////////////////////////////////////////////////////////
//      Display Text
//
///////////////////////////////////////////////////////////////////////////////
void DisplayText ( char *pFormat, ... )
{
    va_list     pListe;

    if ( *pFormat != 0 )
    {
        va_start ( pListe, pFormat );

#ifdef  _CONSOLE
        vfprintf ( stdout, pFormat, pListe );
#endif

        va_end ( pListe );
    }

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CloseLogFile ( )
{
    if ( hLogFile != NULL )
    {
        fclose ( hLogFile );
        hLogFile = NULL;
    }

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void SetBoolTrace ( bool bValue )
{
    bTrace = bValue;
}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void OpenLogFile ( char *pDirectory, void ( *pExit )( int )  )
{
    CloseLogFile ( );

    strcpy_s ( szLogFilename, sizeof ( szLogFilename ), pDirectory );
    strcat_s ( szLogFilename, sizeof ( szLogFilename ), "\\OutlookExtract.log" );
    hLogFile    = NULL;
    fopen_s ( &hLogFile, szLogFilename, "w" );
    if ( hLogFile == NULL )
    {
        DisplayError ( "Unable to create log file %s\n", szLogFilename );
        pExit ( 255 );
    }
}
