#include "stdafx.h"

#include "MCXIcons.h"

#include "Check.ico.h"
#include "CheckBlack.ico.h"
#include "Close.ico.h"
#include "Maximize.ico.h"
#include "Minimize.ico.h"
#include "Windowed.ico.h"

HICON hIcon_check_ico       = NULL;
HICON hIcon_checkblack_ico  = NULL;
HICON hIcon_close_ico       = NULL;
HICON hIcon_minimize_ico    = NULL;
HICON hIcon_maximize_ico    = NULL;
HICON hIcon_windowed_ico    = NULL;

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
HICON CreateIconFromIcoMemory(const BYTE* buffer, DWORD size, int cx, int cy)
{
    if (!buffer || size < 6) // at least 6 bytes
        return nullptr;

    // start of file  .ico contains icons directory
    const BYTE* pDir = buffer;

    // TRUE = icône (FALSE = curseur)
    int offset = LookupIconIdFromDirectoryEx(
        (PBYTE)pDir,
        TRUE,
        cx,
        cy,
        LR_DEFAULTCOLOR
    );

    if (offset == 0)
        return nullptr;

    // RT_ICON starts at buffer + offset
    const BYTE* pIconBits   = buffer + offset;
    DWORD iconBitsSize      = size - offset;

    HICON hIcon = CreateIconFromResourceEx(
        (PBYTE)pIconBits,
        iconBitsSize,
        TRUE,
        0x00030000,   // version Win32
        cx,
        cy,
        LR_DEFAULTCOLOR
    );

    return hIcon;
}

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CreateAllUsedIcons ()
{
    hIcon_check_ico = CreateIconFromIcoMemory(IconData_check_ico, sizeof(IconData_check_ico), 16, 16);
    hIcon_checkblack_ico = CreateIconFromIcoMemory(IconData_checkblack_ico, sizeof(IconData_checkblack_ico), 16, 16);

    hIcon_close_ico = CreateIconFromIcoMemory(IconData_close_ico, sizeof(IconData_close_ico), 16, 16);
    hIcon_minimize_ico = CreateIconFromIcoMemory(IconData_minimize_ico, sizeof(IconData_minimize_ico), 16, 16);
    hIcon_maximize_ico = CreateIconFromIcoMemory(IconData_maximize_ico, sizeof(IconData_maximize_ico), 16, 16);
    hIcon_windowed_ico = CreateIconFromIcoMemory(IconData_windowed_ico, sizeof(IconData_windowed_ico), 16, 16);
}