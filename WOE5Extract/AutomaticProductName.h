#pragma once

#ifndef AUTOMATICPRODUCTNAME_H
#define AUTOMATICPRODUCTNAME_H    1

#ifdef _WIN64
#ifdef UNICODE
#define ORIGINAL_FILENAME   L"WOE5Extract (x64 Unicode) (MSVC)\0"
#define PRODUCT_NAME        L"WOE5Extract - Version 2.0.00.002\r\n(Build 168) - (x64 Unicode) (MSVC)\0"
#else
#define ORIGINAL_FILENAME   "WOE5Extract (x64 MBCS) (MSVC)\0"
#define PRODUCT_NAME        "WOE5Extract - Version 2.0.00.002\r\n(Build 168) - (x64 MBCS) (MSVC)\0"
#endif
#elif _WIN32
#ifdef UNICODE
#define ORIGINAL_FILENAME   L"WOE5Extract (x86 Unicode) (MSVC)\0"
#define PRODUCT_NAME        L"WOE5Extract - Version 2.0.00.002\r\n(Build 168) - (x86 Unicode) (MSVC)\0"
#else
#define ORIGINAL_FILENAME   "WOE5Extract (x86 MBCS) (MSVC)\0"
#define PRODUCT_NAME        "WOE5Extract - Version 2.0.00.002\r\n(Build 168) - (x86 MBCS) (MSVC)\0"
#endif
#else
#define ORIGINAL_FILENAME   "WOE5Extract (MSVC)\0"
#define PRODUCT_NAME        "WOE5Extract - Version 2.0.00.002\r\n(Build 168) - (MSVC)\0"
#endif

#endif
