#ifndef OEADDRESSROUTINES_H
#define OEADDRESSROUTINES_H

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "OE5ExtractDefinitions.h"

/*
 *      Prototypes.
 */
static void ExitProgram ( int iError );
static int SortCompare ( const void *pElem1, const void *pElem2  );

extern void CloseDbxFile ( );
extern void OpenDbxFile ( char *pFilename );
extern void SetAddressNextFlag ( int iPos );
extern int StoreAddress ( unsigned long lAddress );
extern int StoreNextAddress ( unsigned long lAddress );
extern void SortAddress ( );
extern int  SearchAddress ( unsigned long lAddress );
extern int  SearchAddressNext ( unsigned long lAddress );
extern bool AlreadyTreated ( unsigned long lAddress );
extern void CleanAddressesTable ( );
extern void BuildAddressesTable ( );
extern bool GetBoolVerbose ( );
extern void SetBoolVerbose ( bool bValue );
extern int ReadOutlookFile ( char *pFilename, char *pDirectory, void ( *pCallBack )( void *, void * ), void *pParm );
extern int ReadOutlookFileStep1 ( char *pFilename, char *pDirectory, void ( *pCallBack )( void *, void * ), void *pParm );
extern int ReadOutlookFileStep2 ( char *pFilename, char *pDirectory, void ( *pCallBack )( void *, void * ), void *pParm );
extern void AllocateBlockMemory ( );
extern void AllocateBlockMemory ( unsigned long iLength );
extern void FreeBlockMemory ( );
extern int GetNextIndexFilePosition ( int iStart );
extern unsigned long GetFilePosition ( int iX );
extern char *GetProcessStep ( );
extern long GetFileLength ( );
extern long GetFilePosition ( );
extern char *ReadOneFile ( char *pFilename, char *pDirectory, unsigned long lPosition, void ( *pCallBack )( void *, void * ), void *pParm );
extern void ResetAddress ( );

extern void SetAddressRoutinesCancel ( bool bValue );
extern void SetAllSelected ( int bValue = 1 );
extern void SetNoneSelected ( );
extern void SetSelection ( unsigned long lAddress, int bValue = 1 );
extern void SetNoSelection ( unsigned long lAddress );

extern bool SaveAddresses ( const char *pFile );
extern bool RestoreAddresses ( const char *pFile );

#endif
