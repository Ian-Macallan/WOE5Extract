#ifndef DECODEROUTINES_H
#define DECODEROUTINES_H

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "OE5ExtractDefinitions.h"

/*
 *      Prototypes.
 */
//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
static void ExitProgram ( int iError );
extern void CloseAttFile ( );
extern void FilterFilename ( char *pFilename );
extern void CheckTheName ( );
extern bool DecodeFileLines ( );
extern bool DecodeFile64Lines ( );
extern bool DecodeFile64 ( );
extern bool DecodeFile ( );
extern void SetBoolLeave ( bool bValue );
extern void SetBoolSubject ( bool bValue );
extern void SetBoolName ( bool bValue );
extern void SetBoolCollapse ( bool bValue );
extern bool GetBoolCollapse ( );
extern void SetBoolRemoveNumbers ( bool bValue );
extern void SetBoolRemoveOther ( bool bValue );
extern void SetBoolOnlyMessages ( bool bValue );
extern void ZeroNumOfAttachement ( );
extern void ZeroNumOfBase64 ( );
extern int GetNumOfAttachement ( );
extern int GetNumOfBase64 ( );
extern void SetDirectory ( const char *pPath );
extern void SetDirectoryFrom ( char *pDir, char *pPath );
extern void SetDrive ( const char *pDrive );
extern void CreateDirectory ( );
extern void ProcessFile ( char *pPathname, void ( *pCallBack )( void *, void * ), void *pParm );
extern void ProcessFileStep1 ( char *pPathname, void ( *pCallBack )( void *, void * ), void *pParm );
extern void ProcessFileStep2 ( char *pPathname, void ( *pCallBack )( void *, void * ), void *pParm );
extern void ProcessFileStep3 ( char *pPathname, void ( *pCallBack )( void *, void * ), void *pParm );
extern char *GetDate ( );
extern char *GetAuthor ( );
extern char *GetEMail ( );
extern char *GetSubject ( );
extern char *GetMessageID ( );
extern int GetAttachementCount ( );
extern int GetAttachementType ( );
extern char *ProcessOneStep ( char *pPathname, unsigned long lPosition, void ( *pCallBack )( void *, void * ), void *pParm );
extern void SetAttFormat (  int iName1,int iName2,int iName3,int iName4,int iName5,
                        int iSize1,int iSize2,int iSize3,int iSize4,int iSize5 );
extern void SetAttExtension ( const char *pText );

#endif
