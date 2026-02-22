// https://msdn.microsoft.com/en-us/library/ms997538.aspx
#pragma once

#include <windows.h>

// https://learn.microsoft.com/en-us/windows/win32/menurc/using-icons

#pragma pack(push, 1)
struct ICONDIR {
    WORD idReserved;
    WORD idType;
    WORD idCount;
};

struct ICONDIRENTRY {
    BYTE  bWidth;
    BYTE  bHeight;
    BYTE  bColorCount;
    BYTE  bReserved;
    WORD  wPlanes;
    WORD  wBitCount;
    DWORD dwBytesInRes;
    DWORD dwImageOffset;
};

//  Group Icons
struct GRPICONDIR {
    WORD idReserved;
    WORD idType;
    WORD idCount;
};

struct GRPICONDIRENTRY {
    BYTE  bWidth;
    BYTE  bHeight;
    BYTE  bColorCount;
    BYTE  bReserved;
    WORD  wPlanes;
    WORD  wBitCount;
    DWORD dwBytesInRes;
    WORD  nID;
};
#pragma pack(pop)

//  Data
extern HICON hIcon_check_ico;
extern HICON hIcon_checkblack_ico;
extern HICON hIcon_close_ico;
extern HICON hIcon_minimize_ico;
extern HICON hIcon_maximize_ico;
extern HICON hIcon_windowed_ico;

extern HICON CreateIconFromIcoMemory(const BYTE* buffer, DWORD size, int cx, int cy);
extern void CreateAllUsedIcons ();

#if 0

bool SaveIcon(const char* exePath, const char* outPath)
{
    HMODULE hExe = LoadLibraryExA(exePath, NULL, LOAD_LIBRARY_AS_DATAFILE);
    if (!hExe) return false;

    HRSRC hGroup = FindResourceA(hExe, MAKEINTRESOURCEA(1), RT_GROUP_ICON);
    if (!hGroup) return false;

    HGLOBAL hRes = LoadResource(hExe, hGroup);
    GRPICONDIR* grp = (GRPICONDIR*)LockResource(hRes);

    std::vector<GRPICONDIRENTRY> entries(grp->idCount);
    memcpy(entries.data(), grp + 1, grp->idCount * sizeof(GRPICONDIRENTRY));

    std::ofstream out(outPath, std::ios::binary);
    if (!out) return false;

    ICONDIR iconDir = { 0, 1, grp->idCount };
    out.write((char*)&iconDir, sizeof(iconDir));

    DWORD offset = sizeof(ICONDIR) + grp->idCount * sizeof(ICONDIRENTRY);
    std::vector<std::vector<BYTE>> images;

    for (auto& e : entries)
    {
        HRSRC hIcon = FindResourceA(hExe, MAKEINTRESOURCEA(e.nID), RT_ICON);
        HGLOBAL hIconRes = LoadResource(hExe, hIcon);
        DWORD size = SizeofResource(hExe, hIcon);
        BYTE* data = (BYTE*)LockResource(hIconRes);

        images.emplace_back(data, data + size);
    }

    for (size_t i = 0; i < entries.size(); i++)
    {
        ICONDIRENTRY ide{};
        ide.bWidth = entries[i].bWidth;
        ide.bHeight = entries[i].bHeight;
        ide.bColorCount = entries[i].bColorCount;
        ide.bReserved = 0;
        ide.wPlanes = entries[i].wPlanes;
        ide.wBitCount = entries[i].wBitCount;
        ide.dwBytesInRes = entries[i].dwBytesInRes;
        ide.dwImageOffset = offset;

        out.write((char*)&ide, sizeof(ide));
        offset += entries[i].dwBytesInRes;
    }

    for (auto& img : images)
        out.write((char*)img.data(), img.size());

    out.close();
    FreeLibrary(hExe);
    return true;
}

int main()
{
    const char* exe = "C:\\Windows\\System32\\notepad.exe";
    const char* out = "dump.ico";

    if (SaveIcon(exe, out))
        std::cout << "Icône extraite dans " << out << "\n";
    else
        std::cout << "Échec de l'extraction\n";

    return 0;
}

#endif

