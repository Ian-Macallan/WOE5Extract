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

#include "RemoveStringsRoutines.h"
#include "TextRoutines.h"

//		The table of strings to remove
static	char					*RemoveStrings [ MAX_REMOVE ];
static	int						iNbRemoveStrings					= 0;

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void RemoveAllStrings ( char *pFilename )
{
	int			iX;

	iX = 0;
	while ( iX < iNbRemoveStrings )
	{
		RemoveString ( pFilename, RemoveStrings [ iX ] );
		iX++;
	}

}

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void AllocRemoveStrings ( char *pText )
{
	RemoveStrings [ iNbRemoveStrings ] = ( char * ) malloc ( strlen ( pText ) + 1 );
	strcpy_s ( RemoveStrings [ iNbRemoveStrings ], strlen ( pText ) + 1, pText );
	iNbRemoveStrings++;
}
