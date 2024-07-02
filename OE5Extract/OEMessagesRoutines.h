#ifndef	OEMESSAGESROUTINES_H
#define	OEMESSAGESROUTINES_H

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "OE5ExtractDefinitions.h"

/*
 *		Prototypes.
 */
static void ExitProgram ( int iError );

extern void CloseMsgFile ( );
extern void WriteMsgFile ( char *pBuffer, unsigned long lSize );
extern void CreateMsgFile ( char *pDirectory );
extern void RenameMsgFile ( char *pDirectory );
extern void DeleteMsgFile ( char *pDirectory );
extern void ReadMsgFile ( char *pLine, size_t iSize );
extern void SetBoolKeep ( bool bValue );
extern int MsgFileEof ( );
extern int MsgFileError ( );
extern void OpenMsgFile ( );
extern void ZeroNumOfMessages ();
extern int GetNumOfMessages ();
extern unsigned long GetBufferSize ( );
extern void AllocateBufferMemory ( );
extern void InitMsgBuffer ( );
extern void FreeBufferMemory ( );
extern char *GetMsgFilename ( );
extern void SetNameFormat (	int iName1,int iName2,int iName3,int iName4, int iSize1,int iSize2,int iSize3,int iSize4 );
extern char *GetMsgExtension ( );
extern void SetMsgExtension ( const char *pText );
extern void SetBoolMsgLeave ( bool bValue );

#endif