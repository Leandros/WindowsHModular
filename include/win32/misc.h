/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef WINDOWS_MISC_H
#define WINDOWS_MISC_H

#include "windows_base.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* MMRESULT: */
typedef UINT MMRESULT;
#define TIMERR_BASE                     96
#define TIMERR_NOERROR                  (0)
#define TIMERR_NOCANDO                  (TIMERR_BASE+1)
#define TIMERR_STRUCT                   (TIMERR_BASE+33)

/* Code Pages: */
#define CP_INSTALLED                0x00000001
#define CP_SUPPORTED                0x00000002
#define CP_ACP                      0
#define CP_OEMCP                    1
#define CP_MACCP                    2
#define CP_THREAD_ACP               3
#define CP_SYMBOL                   42
#define CP_UTF7                     65000
#define CP_UTF8                     65001


/* ========================================================================== */
/* Structures: */
/* Time: */
typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME;
typedef PSYSTEMTIME LPSYSTEMTIME;

typedef struct _TIME_ZONE_INFORMATION {
    LONG       Bias;
    WCHAR      StandardName[32];
    SYSTEMTIME StandardDate;
    LONG       StandardBias;
    WCHAR      DaylightName[32];
    SYSTEMTIME DaylightDate;
    LONG       DaylightBias;
} TIME_ZONE_INFORMATION, *PTIME_ZONE_INFORMATION;
typedef PTIME_ZONE_INFORMATION LPTIME_ZONE_INFORMATION;


/* ========================================================================== */
/* Functions: */
/*
 * I could've implemented them in assembly, they're like 4 lines, but this is
 * avoiding the cost of a function call, if optimizations are turned on.
 */
#define _byteswap_ulong(x)      (((unsigned long)(x) << 24) | \
                                (((unsigned long)(x) << 8) & 0xff0000) | \
                                (((unsigned long)(x) >> 8) & 0xff00) | \
                                ((unsigned long)(x) >> 24))
#define _byteswap_uint64(x)     (((unsigned __int64)(x) << 56) | \
                                (((unsigned __int64)(x) << 40) & 0xff000000000000ULL) | \
                                (((unsigned __int64)(x) << 24) & 0xff0000000000ULL) | \
                                (((unsigned __int64)(x) << 8)  & 0xff00000000ULL) | \
                                (((unsigned __int64)(x) >> 8)  & 0xff000000ULL) | \
                                (((unsigned __int64)(x) >> 24) & 0xff0000ULL) | \
                                (((unsigned __int64)(x) >> 40) & 0xff00ULL) | \
                                ((unsigned __int64)(x)  >> 56))
unsigned int _rotl(unsigned int value, int shift);
unsigned __int64 _rotl64(unsigned __int64 value, int shift);
unsigned char _BitScanForward(unsigned long * Index, unsigned long Mask);
unsigned char _BitScanForward64(unsigned long * Index, unsigned __int64 Mask);

/* ========================================================================== */
/* UTF-16 <-> UTF-8 conversion Functions: */
int WINAPI WideCharToMultiByte(
    UINT        CodePage,
    DWORD       dwFlags,
    LPCWSTR     lpWideCharStr,
    int         cchWideChar,
    LPSTR       lpMultiByteStr,
    int         cbMultiByte,
    LPCSTR      lpDefaultChar,
    LPBOOL      lpUsedDefaultChar);
int WINAPI MultiByteToWideChar(
    UINT        CodePage,
    DWORD       dwFlags,
    LPCSTR      lpMultiByteStr,
    int         cbMultiByte,
    LPWSTR      lpWideCharStr,
    int         cchWideChar);
int WINAPI lstrlenA(
        LPCSTR  lpString);
int WINAPI lstrlenW(
        LPCWSTR lpString);
LPCSTR WINAPI lstrcpyA(
        LPCSTR  lpString1,
        LPCSTR  lpString2);
LPCWSTR WINAPI lstrcpyW(
        LPCWSTR lpString1,
        LPCWSTR lpString2);

/* ========================================================================== */
/* Time: */
void WINAPI GetSystemTime(
        LPSYSTEMTIME lpSystemTime);
void WINAPI GetLocalTime(
        LPSYSTEMTIME lpSystemTime);
BOOL WINAPI QueryProcessCycleTime(
        HANDLE      hProcess,
        PULONG64    CycleTime);
BOOL WINAPI SystemTimeToFileTime(
  const SYSTEMTIME *    lpSystemTime,
        LPFILETIME      lpFileTime);
BOOL WINAPI FileTimeToSystemTime(
  const FILETIME *      lpFileTime,
        LPSYSTEMTIME    lpSystemTime);
void WINAPI GetSystemTimeAsFileTime(
        LPFILETIME lpSystemTimeAsFileTime);
BOOL WINAPI SystemTimeToTzSpecificLocalTime(
        LPTIME_ZONE_INFORMATION lpTimeZone,
        LPSYSTEMTIME lpUniversalTime,
        LPSYSTEMTIME lpLocalTime);
DWORD timeGetTime(void);
MMRESULT timeBeginPeriod(
        UINT uPeriod);

/* ========================================================================== */
/* Environment: */
BOOL WINAPI SetEnvironmentVariableA(
        LPCSTR  lpName,
        LPCSTR  lpValue);
BOOL WINAPI SetEnvironmentVariableW(
        LPCWSTR lpName,
        LPCWSTR lpValue);
DWORD WINAPI GetEnvironmentVariableA(
        LPCSTR  lpName,
        LPCSTR  lpBuffer,
        DWORD   nSize);
DWORD WINAPI GetEnvironmentVariableW(
        LPCWSTR lpName,
        LPCWSTR lpBuffer,
        DWORD   nSize);

/* ========================================================================== */
/* Misc Functions: */
BOOL WINAPI DisableThreadLibraryCalls(
        HMODULE hModule);
DWORD WINAPI GetLastError(void);
void WINAPI Sleep(
        DWORD dwMilliseconds);
DWORD WINAPI SleepEx(
        DWORD dwMilliseconds,
        BOOL bAlertable);
HMODULE WINAPI GetModuleHandleA(
        LPCSTR lpModuleName);
HMODULE WINAPI GetModuleHandleW(
        LPCWSTR lpModuleName);

/* ========================================================================== */
/* Timer Functions: */
DWORD WINAPI GetTickCount(void);
ULONGLONG WINAPI GetTickCount64(void);
BOOL WINAPI QueryPerformanceFrequency(
        LARGE_INTEGER *lpFrequency);
BOOL WINAPI QueryPerformanceCounter(
        LARGE_INTEGER *lpPerformanceCount);

/* ========================================================================== */
/* DLL Functions: */
HMODULE WINAPI LoadLibraryA(
        LPCSTR lpFileName);
HMODULE WINAPI LoadLibraryW(
        LPCWSTR lpFileName);
FARPROC WINAPI GetProcAddress(
        HMODULE hModule,
        LPCSTR lProcName);
PROC WINAPI wglGetProcAddress(
        LPCSTR lpszProc);
BOOL WINAPI FreeLibrary(
        HMODULE hModule);


#if defined(__cplusplus)
}
#endif

#endif /* WINDOWS_MISC_H */

