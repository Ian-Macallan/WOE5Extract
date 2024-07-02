#ifndef DISPLAYANDTRACE_H
#define DISPLAYANDTRACE_H

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "OE5ExtractDefinitions.h"

/*
 *      Prototypes.
 */
extern void TraceOut ( char *pFormat, ... );
extern void DisplayErrorAndExit ( int iError, void ( *pExit )( int ), char *pText, char *pFormat, ... );
extern void DisplayErrorOnly ( int iError, char *pText, char *pFormat, ... );
extern void DisplayError ( char *pFormat, ... );
extern void DisplayWarning ( char *pFormat, ... );
extern void DisplayText ( char *pFormat, ... );
extern void CloseLogFile ( );
extern void SetBoolTrace ( bool bValue );
extern void OpenLogFile ( char *pDirectory, void ( *pExit )( int ) );

#endif
