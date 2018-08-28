/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_THREADS_H
#define WINDOWS_THREADS_H

/* Disable all warnings */
#if defined(_MSC_VER)
    #pragma warning(push, 0)
#endif

#ifndef WINDOWS_BASE_H
#include "windows_base.h"
#endif
#if defined(__cplusplus)
extern "C" {
#endif

/* WaitForSingleObject, WaitForMultipleObjects, etc: */
#define INFINITE                0xffffffff

/* Originally defined in file.h */
#ifndef STANDARD_RIGHTS_REQUIRED
#define STANDARD_RIGHTS_REQUIRED    0x000F0000L
#endif
#ifndef SYNCHRONIZE
#define SYNCHRONIZE                 0x00100000L
#endif

#define STATUS_WAIT_0               ((DWORD)0x00000000L)
#define STATUS_ABANDONED_WAIT_0     ((DWORD)0x00000080L)
#define STATUS_TIMEOUT              ((DWORD)0x00000102L)
#define STATUS_PENDING              ((DWORD)0x00000103L)

#define WAIT_FAILED                 ((DWORD)0xffffffff)
#define WAIT_OBJECT_0               ((STATUS_WAIT_0) + 0)
#define WAIT_ABANDONED              ((STATUS_ABANDONED_WAIT_0) + 0)
#define WAIT_TIMEOUT                258L

/* TLS: */
#ifndef TLS_OUT_OF_INDEXES
#define TLS_OUT_OF_INDEXES          ((DWORD)0xFFFFFFFF)
#endif
#ifndef FLS_OUT_OF_INDEXES
#define FLS_OUT_OF_INDEXES          ((DWORD)0xFFFFFFFF)
#endif


/* Thread creation flags: */
#define CREATE_NEW_CONSOLE          0x00000010
#define CREATE_NO_WINDOW            0x08000000
#define CREATE_SUSPENDED            0x00000004
#define DETACHED_PROCESS            0x00000008

/* Thread Access Rights: */
#define THREAD_GET_CONTEXT          (0x0008)
#define THREAD_QUERY_INFORMATION    (0x0040)
#define THREAD_SUSPEND_RESUME       (0x0002)
#define THREAD_TERMINATE            (0x0001)
#define THREAD_ALL_ACCESS           \
    (STANDARD_RIGHTS_REQUIRED | \
     SYNCHRONIZE | \
     0xFFFF)

/* Semaphore Access Rights: */
#define SEMAPHORE_ALL_ACCESS        0x1F0003
#define SEMAPHORE_MODIFY_STATE      0x0002
#define EVENT_ALL_ACCESS            0x1F0003
#define EVENT_MODIFY_STATE          0x0002


/* ========================================================================== */
/* Structures: */
/* Magic for Thread Local Storage: */
typedef void (NTAPI *PIMAGE_TLS_CALLBACK)(
        PVOID DllHandle,
        DWORD Reason,
        PVOID Reserved);
typedef struct _IMAGE_TLS_DIRECTORY32 {
    DWORD       StartAddressOfRawData;
    DWORD       EndAddressOfRawData;
    DWORD       AddressOfIndex;
    DWORD       AddressOfCallbacks;
    DWORD       SizeOfZeroFill;
    DWORD       Characteristics;
} IMAGE_TLS_DIRECTORY32, *PIMAGE_TLS_DIRECTORY32;
typedef struct _IMAGE_TLS_DIRECTORY64 {
    ULONGLONG   StartAddressOfRawData;
    ULONGLONG   EndAddressOfRawData;
    ULONGLONG   AddressOfIndex;
    ULONGLONG   AddressOfCallbacks;
    DWORD       SizeOfZeroFill;
    DWORD       Characteristics;
} IMAGE_TLS_DIRECTORY64, *PIMAGE_TLS_DIRECTORY64;
#if defined(_WIN64)
typedef IMAGE_TLS_DIRECTORY64       IMAGE_TLS_DIRECTORY;
typedef PIMAGE_TLS_DIRECTORY64      PIMAGE_TLS_DIRECTORY;
#else
typedef IMAGE_TLS_DIRECTORY32       IMAGE_TLS_DIRECTORY;
typedef PIMAGE_TLS_DIRECTORY32      PIMAGE_TLS_DIRECTORY;
#endif

/* Linked List */
typedef struct _LIST_ENTRY {
   struct _LIST_ENTRY *Flink;
   struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY;

typedef struct _RTL_CRITICAL_SECTION_DEBUG {
    WORD        Type;
    WORD        CreatorBackTraceIndex;
    struct _RTL_CRITICAL_SECTION *CriticalSection;
    LIST_ENTRY  ProcessLocksList;
    DWORD       EntryCount;
    DWORD       ContentionCount;
    DWORD       Flags;
    WORD        CreatorBackTraceIndexHigh;
    WORD        SpareWORD;
} RTL_CRITICAL_SECTION_DEBUG, *PRTL_CRITICAL_SECTION_DEBUG;

#pragma pack(push, 8)
typedef struct _RTL_CRITICAL_SECTION {
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;
} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;
typedef RTL_CRITICAL_SECTION    CRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION   PCRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION   LPCRITICAL_SECTION;
#pragma pack(pop)

typedef struct _RTL_CONDITION_VARIABLE {
    PVOID Ptr;
} RTL_CONDITION_VARIABLE, *PRTL_CONDITION_VARIABLE;
#define RTL_CONDITION_VARIABLE_INIT {0}
#define RTL_CONDITION_VARIABLE_LOCKMODE_SHARED 0x1
typedef RTL_CONDITION_VARIABLE  CONDITION_VARIABLE;
typedef PRTL_CONDITION_VARIABLE PCONDITION_VARIABLE;

#define SRWLOCK_INIT {0}
typedef struct _RTL_SRWLOCK {
        PVOID Ptr;
} RTL_SRWLOCK, *PRTL_SRWLOCK;
typedef RTL_SRWLOCK SRWLOCK, *PSRWLOCK;

/* ========================================================================== */
/* Waiting Functions: */
DWORD WINAPI WaitForSingleObject(
        HANDLE  hHandle,
        DWORD   dwMilliseconds);
DWORD WINAPI WaitForMultipleObjects(
        DWORD   nCount,
  const HANDLE *lpHandles,
        BOOL    bWaitAll,
        DWORD   dwMilliseconds);

DWORD WINAPI WaitForSingleObjectEx(
        HANDLE hHandle,
        DWORD dwMilliseconds,
        BOOL bAlertable);
DWORD WINAPI WaitForMultipleObjectsEx(
        DWORD nCount,
  const HANDLE *lpHandles,
        BOOL bWaitAll,
        DWORD dwMilliseconds,
        BOOL bAlertable);

/* ========================================================================== */
/* Threading Functions: */
typedef DWORD (WINAPI *PTHREAD_START_ROUTINE)(LPVOID);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;
HANDLE WINAPI CreateThread(
        LPSECURITY_ATTRIBUTES lpThreadAttributes,
        SIZE_T dwStackSize,
        LPTHREAD_START_ROUTINE lpStartAddress,
        LPVOID lpParameter,
        DWORD dwCreationFlags,
        LPDWORD lpThreadId);
HANDLE WINAPI GetCurrentThread(void);
DWORD WINAPI GetCurrentThreadId(void);
DWORD_PTR WINAPI SetThreadAffinityMask(
        HANDLE hThread,
        DWORD_PTR dwThreadAffinityMask);
HANDLE WINAPI OpenThread(
        DWORD dwDesiredAccess,
        BOOL bInheritHandle,
        DWORD dwThreadId);
DWORD WINAPI SuspendThread(
        HANDLE hThread);
DWORD WINAPI ResumeThread(
        HANDLE hThread);
void WINAPI ExitThread(
        DWORD dwExitCode);
BOOL WINAPI GetProcessAffinityMask(
        HANDLE hProcess,
        PDWORD_PTR lpProcessAffinityMask,
        PDWORD_PTR lpSystemAffinityMask);
BOOL WINAPI SetProcessAffinityMask(
        HANDLE    hProcess,
        DWORD_PTR dwProcessAffinityMask);
BOOL WINAPI SwitchToThread(void);

/* ========================================================================== */
/* CriticalSection Functions: */
void WINAPI InitializeCriticalSection(
        LPCRITICAL_SECTION lpCriticalSection);
BOOL WINAPI InitializeCriticalSectionAndSpinCount(
        LPCRITICAL_SECTION lpCriticalSection,
        DWORD dwSpinCount);
DWORD WINAPI SetCriticalSectionSpinCount(
        LPCRITICAL_SECTION lpCriticalSection,
        DWORD dwSpinCount);
void WINAPI EnterCriticalSection(
        LPCRITICAL_SECTION lpCriticalSection);
BOOL WINAPI TryEnterCriticalSection(
        LPCRITICAL_SECTION lpCriticalSection);
void WINAPI LeaveCriticalSection(
        LPCRITICAL_SECTION lpCriticalSection);
void WINAPI DeleteCriticalSection(
        LPCRITICAL_SECTION lpCriticalSection);

/* ========================================================================== */
/* Condition Variable: */
void WINAPI InitializeConditionVariable(
        PCONDITION_VARIABLE ConditionVariable);
BOOL WINAPI SleepConditionVariableCS(
        PCONDITION_VARIABLE ConditionVariable,
        PCRITICAL_SECTION   CriticalSection,
        DWORD               dwMilliseconds);
void WINAPI WakeAllConditionVariable(
        PCONDITION_VARIABLE ConditionVariable);
void WINAPI WakeConditionVariable(
        PCONDITION_VARIABLE ConditionVariable);

/* ========================================================================== */
/* Mutex Functions: */
HANDLE WINAPI CreateMutexA(
        LPSECURITY_ATTRIBUTES lpMutexAttributes,
        BOOL bInitialOwner,
        LPCSTR lpName);
HANDLE WINAPI CreateMutexW(
        LPSECURITY_ATTRIBUTES lpMutexAttributes,
        BOOL bInitialOwner,
        LPCWSTR lpName);
BOOL WINAPI ReleaseMutex(
        HANDLE hMutex);

/* ========================================================================== */
/* Semaphore Functions: */
HANDLE WINAPI CreateSemaphoreA(
        LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
        LONG lInitialCount,
        LONG lMaximumCount,
        LPCSTR lpName);
HANDLE WINAPI CreateSemaphoreW(
        LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
        LONG lInitialCount,
        LONG lMaximumCount,
        LPCWSTR lpName);
BOOL WINAPI ReleaseSemaphore(
        HANDLE hSemaphore,
        LONG lReleaseCount,
        LPLONG lpPreviousCount);
HANDLE WINAPI OpenSemaphoreA(
        DWORD dwDesiredAccess,
        BOOL bInheritHandle,
        LPCSTR lpName);
HANDLE WINAPI OpenSemaphoreW(
        DWORD dwDesiredAccess,
        BOOL bInheritHandle,
        LPCWSTR lpName);


/* ========================================================================== */
/* Thread-Local Storage: */
DWORD WINAPI TlsAlloc(void);
BOOL WINAPI TlsSetValue(
        DWORD   dwTlsIndex,
        LPVOID  lpTlsValue);
LPVOID WINAPI TlsGetValue(
        DWORD   dwTlsIndex);
DWORD WINAPI TlsFree(
        DWORD   dwTlsIndex);

typedef void(WINAPI *PFLS_CALLBACK_FUNCTION)(PVOID);
DWORD WINAPI FlsAlloc(PFLS_CALLBACK_FUNCTION lpCallback);
BOOL WINAPI FlsFree(DWORD dwFlsIndex);
BOOL WINAPI FlsSetValue(DWORD dwFlsIndex, PVOID lpFlsData);
PVOID WINAPI FlsGetValue(DWORD dwFlsIndex);


/* ========================================================================== */
/* SRW Lock Functions: */
void WINAPI InitializeSRWLock(PSRWLOCK SRWLock);

void WINAPI AcquireSRWLockExclusive(PSRWLOCK SRWLock);
void WINAPI AcquireSRWLockShared(PSRWLOCK SRWLock);

void WINAPI ReleaseSRWLockExclusive(PSRWLOCK SRWLock);
void WINAPI ReleaseSRWLockShared(PSRWLOCK SRWLock);

BOOL WINAPI TryAcquireSRWLockExclusive(PSRWLOCK SRWLock);
BOOL WINAPI TryAcquireSRWLockShared(PSRWLOCK SRWLock);

BOOL WINAPI SleepConditionVariableSRW(
    PCONDITION_VARIABLE ConditionVariable,
    PSRWLOCK            SRWLock,
    DWORD               dwMilliseconds,
    ULONG               Flags);

/* ========================================================================== */
/* Waiting: */
BOOL  WINAPI WaitOnAddress(
    void   volatile *Address,
    PVOID           CompareAddress,
    SIZE_T          AddressSize,
    DWORD           dwMilliseconds);
void  WINAPI WakeByAddressSingle(
    PVOID Address);
void  WINAPI WakeByAddressAll(
    PVOID Address);

/* ========================================================================== */
/* Events: */
HANDLE WINAPI CreateEvent(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL                  bManualReset,
    BOOL                  bInitialState,
    LPCTSTR               lpName);
HANDLE WINAPI OpenEvent(
    DWORD   dwDesiredAccess,
    BOOL    bInheritHandle,
    LPCTSTR lpName);
BOOL WINAPI SetEvent(
    HANDLE hEvent);
BOOL WINAPI ResetEvent(
    HANDLE hEvent);


#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_THREADS_H */
#endif /* _WINDOWS_ */

