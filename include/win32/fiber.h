/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef WINDOWS_FIBER_H
#define WINDOWS_FIBER_H

/* Disable all warnings */
#if defined(_MSC_VER)
    #pragma warning(push, 0)
#endif

#ifndef WINDOWS_BASE_H
    #include "windows_base.h"
#endif

/* dbghelp contains __readfsdword / __readgsqword */
#ifndef WINDOWS_DBGHELP_H
    #include "dbghelp.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif


/* ========================================================================= */
/* Fiber                                                                     */
/* ========================================================================= */
typedef void (WINAPI *PFIBER_START_ROUTINE)(LPVOID lpFiberParameter);
typedef PFIBER_START_ROUTINE LPFIBER_START_ROUTINE;
typedef void(NTAPI *PFLS_CALLBACK_FUNCTION)(PVOID lpFlsData);

BOOL WINAPI IsThreadAFiber(void);

void WINAPI SwitchToFiber(LPVOID lpFiber);
void WINAPI DeleteFiber(LPVOID lpFiber);

BOOL WINAPI ConvertFiberToThread(void);

LPVOID WINAPI CreateFiber(
    SIZE_T                dwStackSize,
    LPFIBER_START_ROUTINE lpStartAddress,
    LPVOID                lpParameter);
LPVOID WINAPI CreateFiberEx(
    SIZE_T dwStackCommitSize,
    SIZE_T dwStackReserveSize,
    DWORD dwFlags,
    LPFIBER_START_ROUTINE lpStartAddress,
    LPVOID lpParameter);

LPVOID WINAPI ConvertThreadToFiber(LPVOID lpParameter);
LPVOID WINAPI ConvertThreadToFiberEx(
    LPVOID lpParameter,
    DWORD dwFlags);

#ifdef _AMD64_
__inline PVOID
GetCurrentFiber(void)
{
    return (PVOID)(ULONG_PTR)__readgsqword(0x20);
}
#else
__inline PVOID
GetCurrentFiber(void)
{
    return (PVOID)(ULONG_PTR)__readfsdword(0x10);
}
#endif

__forceinline PVOID
GetFiberData(void)
{
    return *(PVOID *)GetCurrentFiber();
}


/* ========================================================================= */
/* Fiber Local Storage                                                       */
/* ========================================================================= */
#ifndef FLS_OUT_OF_INDEXES
#define FLS_OUT_OF_INDEXES ((DWORD)0xFFFFFFFF)
#endif

DWORD WINAPI FlsAlloc(PFLS_CALLBACK_FUNCTION lpCallback);
PVOID WINAPI FlsGetValue(DWORD dwFlsIndex);
BOOL WINAPI FlsSetValue(DWORD dwFlsIndex, PVOID lpFlsData);
BOOL WINAPI FlsFree(DWORD dwFlsIndex);


#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_FIBER_H */

