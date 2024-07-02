#ifndef MIMEROUTINES_H
#define MIMEROUTINES_H

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "OE5ExtractDefinitions.h"

/*
 *      Prototypes.
 */
static void BuildDecodeTable ( );

extern bool UUDecodeBytes (  char cByte1,  char cByte2,  char cByte3,  char cByte4,  char pResult [ 3 ] );
extern bool UUDecodeFourBytes (  char *pBytes,  char *pResult );
extern bool UUDecodeLine (  char *pLine,  char *pResult, int *piResult );
extern bool YencDecodeLine (  char *pLine,  char *pResult, int *piResult );
extern bool UUDecodeLine64 (  char *pLine,  char *pResult, int *piResult );

#endif
