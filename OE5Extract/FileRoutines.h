#ifndef	FILEROUTINES_H
#define	FILEROUTINES_H

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "OE5ExtractDefinitions.h"

/*
 *		Prototypes.
 */
extern char *FindType ( char *pFilename );
extern char *FindTypeOrNull ( char *pFilename );
extern char *FindFilename ( char *pFilename );
extern void CorrectDirectory ( char *pFilename );
extern void CorrectFilename ( char *pFilename );
extern void FilterName ( char *pString,  bool bDir );
extern void RemoveLeadingDirectory ( char *pString, size_t iString, char *pUpDir );
extern void RemoveTrailingDirectory ( char *pString, size_t iString, char *pUpDir );
extern void RemoveTrailingNumbers ( char *pString, size_t iString );
extern long GetFileLength ( FILE *hFile );
extern char *FindDirectory ( const char *pFilename );

#endif