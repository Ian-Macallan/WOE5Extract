#pragma once

#ifndef AUTOMATICPRODUCTNAME_H
#define AUTOMATICPRODUCTNAME_H    1

#ifdef _WIN64
#ifdef UNICODE
#define ORIGINAL_FILENAME   L"WOE5Extract (x64 Unicode) (MSVC)\0"
#define PRODUCT_NAME        L"WOE5Extract - Version 1.3.01.003\r\n(Build 164) - (x64 Unicode) (MSVC)\0"
#else
#define ORIGINAL_FILENAME   "WOE5Extract (x64 MBCS) (MSVC)\0"
#define PRODUCT_NAME        "WOE5Extract - Version 1.3.01.003\r\n(Build 164) - (x64 MBCS) (MSVC)\0"
#endif
#elif _WIN32
#ifdef UNICODE
#define ORIGINAL_FILENAME   L"WOE5Extract (x86 Unicode) (MSVC)\0"
#define PRODUCT_NAME        L"WOE5Extract - Version 1.3.01.003\r\n(Build 164) - (x86 Unicode) (MSVC)\0"
#else
#define ORIGINAL_FILENAME   "WOE5Extract (x86 MBCS) (MSVC)\0"
#define PRODUCT_NAME        "WOE5Extract - Version 1.3.01.003\r\n(Build 164) - (x86 MBCS) (MSVC)\0"
#endif
#else
#define ORIGINAL_FILENAME   "WOE5Extract (MSVC)\0"
#define PRODUCT_NAME        "WOE5Extract - Version 1.3.01.003\r\n(Build 164) - (MSVC)\0"
#endif

#endif
