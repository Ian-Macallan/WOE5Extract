#pragma once

#ifndef AUTOMATICPRODUCTNAME_H
#define AUTOMATICPRODUCTNAME_H    1

#ifdef _WIN64
#ifdef UNICODE
#define ORIGINAL_FILENAME   L"OE5Extract (x64 Unicode) (MSVC)\0"
#define PRODUCT_NAME        L"OE5Extract - Version 2.0.00.010\r\n(Build 55) - (x64 Unicode) (MSVC)\0"
#else
#define ORIGINAL_FILENAME   "OE5Extract (x64 MBCS) (MSVC)\0"
#define PRODUCT_NAME        "OE5Extract - Version 2.0.00.010\r\n(Build 55) - (x64 MBCS) (MSVC)\0"
#endif
#elif _WIN32
#ifdef UNICODE
#define ORIGINAL_FILENAME   L"OE5Extract (x86 Unicode) (MSVC)\0"
#define PRODUCT_NAME        L"OE5Extract - Version 2.0.00.010\r\n(Build 55) - (x86 Unicode) (MSVC)\0"
#else
#define ORIGINAL_FILENAME   "OE5Extract (x86 MBCS) (MSVC)\0"
#define PRODUCT_NAME        "OE5Extract - Version 2.0.00.010\r\n(Build 55) - (x86 MBCS) (MSVC)\0"
#endif
#else
#define ORIGINAL_FILENAME   "OE5Extract (MSVC)\0"
#define PRODUCT_NAME        "OE5Extract - Version 2.0.00.010\r\n(Build 55) - (MSVC)\0"
#endif

#endif
