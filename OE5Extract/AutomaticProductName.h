#pragma once

#ifndef AUTOMATICPRODUCTNAME_H
#define AUTOMATICPRODUCTNAME_H    1

#ifdef _WIN64
#ifdef UNICODE
#define ORIGINAL_FILENAME   L"OutlookExtract (x64 Unicode) (MSVC)\0"
#define PRODUCT_NAME        L"OutlookExtract - Version 2.0.00.003\r\n(Build 48) - (x64 Unicode) (MSVC)\0"
#else
#define ORIGINAL_FILENAME   "OutlookExtract (x64 MBCS) (MSVC)\0"
#define PRODUCT_NAME        "OutlookExtract - Version 2.0.00.003\r\n(Build 48) - (x64 MBCS) (MSVC)\0"
#endif
#elif _WIN32
#ifdef UNICODE
#define ORIGINAL_FILENAME   L"OutlookExtract (x86 Unicode) (MSVC)\0"
#define PRODUCT_NAME        L"OutlookExtract - Version 2.0.00.003\r\n(Build 48) - (x86 Unicode) (MSVC)\0"
#else
#define ORIGINAL_FILENAME   "OutlookExtract (x86 MBCS) (MSVC)\0"
#define PRODUCT_NAME        "OutlookExtract - Version 2.0.00.003\r\n(Build 48) - (x86 MBCS) (MSVC)\0"
#endif
#else
#define ORIGINAL_FILENAME   "OutlookExtract (MSVC)\0"
#define PRODUCT_NAME        "OutlookExtract - Version 2.0.00.003\r\n(Build 48) - (MSVC)\0"
#endif

#endif
