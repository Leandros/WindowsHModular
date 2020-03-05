#ifndef _WINDOWS_
#pragma once
#ifndef _INC_WINDOWS
#define _INC_WINDOWS
#ifndef WINDOWS_H
#define WINDOWS_H


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_BASE_H
#define WINDOWS_BASE_H

/* Disable all warnings */
#if defined(_MSC_VER)
    #pragma warning(push, 0)
#endif
#if defined(__cplusplus)
extern "C" {
#endif

/* size_t */
/* #include <stddef.h> */


/*
 * Windows Version requirements: Vista
 * See here for more information regarding this define:
 * https://msdn.microsoft.com/en-us/library/aa383745(VS.85).aspx
 */
#ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0600
#endif

/* Magic: */
#define _CRTALLOC(x)        __declspec(allocate(x))
#define DECLSPEC_ALIGN(x)   __declspec(align(x))

/* Basic Defines: */
#define NTAPI __stdcall
#define WINAPI __stdcall
#define APIENTRY __stdcall
#define CALLBACK __stdcall
#define TRUE (1)
#define FALSE (0)
#ifndef FORCEINLINE
#define FORCEINLINE __forceinline
#endif
#ifdef UNICODE
#define __TEXT(x) L ## x
#define TEXT(x) __TEXT(x)
#else
#define TEXT(x) x
#endif
#define PATH_MAX 260
#define MAX_PATH 260

#define MAKEWORD(a, b) \
            ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | \
            ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b) \
            ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | \
            ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))

#if !defined(_68K_) \
    && !defined(_MPPC_) \
    && !defined(_X86_) \
    && !defined(_IA64_) \
    && !defined(_AMD64_) \
    && defined(_M_AMD64)
#define _AMD64_
#endif

/*
 * Windows uses the `interface` define to create interfaces for both C and C++.
 * Only the C version is defined here and not the C++ version.
 * Both can be found in BaseTyps.h
 */
#define STDMETHODCALLTYPE           __stdcall
#define STDMETHODVCALLTYPE          __cdecl
#define STDAPICALLTYPE              __stdcall
#define STDAPIVCALLTYPE             __cdecl

#define interface                   struct
#define PURE
#define THIS_                       INTERFACE * This,
#define THIS                        INTERFACE * This
#define STDMETHOD(method)           HRESULT (STDMETHODCALLTYPE * method)
#define STDMETHOD_(type, method)    type (STDMETHODCALLTYPE * method)
#define STDMETHODV(method)          HRESULT (STDMETHODVCALLTYPE * method)
#define STDMETHODV_(type, method)   type (STDMETHODVCALLTYPE * method)

#define IFACEMETHOD(method)         __override STDMETHOD(method)
#define IFACEMETHOD_(type, method)  __override STDMETHOD_(type,method)
#define IFACEMETHODV(method)        __override STDMETHODV(method)
#define IFACEMETHODV_(type, method) __override STDMETHODV_(type,method)

#define BEGIN_INTERFACE
#define END_INTERFACE

#ifdef CONST_VTABLE
#undef CONST_VTBL
#define CONST_VTBL const
#define DECLARE_INTERFACE(iface)                                              \
    typedef interface iface {                                                 \
        const struct iface##Vtbl * lpVtbl;                                    \
    } iface;                                                                  \
    typedef const struct iface##Vtbl iface##Vtbl;                             \
    const struct iface##Vtbl

#else

#undef CONST_VTBL
#define CONST_VTBL
#define DECLARE_INTERFACE(iface)                                              \
    typedef interface iface {                                                 \
        struct iface##Vtbl * lpVtbl;                                          \
    } iface;                                                                  \
    typedef struct iface##Vtbl iface##Vtbl;                                   \
    struct iface##Vtbl

#endif /* CONST_VTABLE */

#define DECLARE_INTERFACE_(iface, baseiface)    DECLARE_INTERFACE(iface)


#define HRESULT_IS_WIN32(x) \
    ((((x) >> 16) & 0xFFFF) == 0x8)
#define HRESULT_IS_FAILURE(x) \
    ((((x) >> 31) & 0x1) == 0x1)
#define HRESULT_FACILITY(x) \
    (((x) >> 16) & 0xFFFF)
#define HRESULT_CODE(x) \
    ((x) & 0xFFFF)
#define HRESULT_FROM_WIN32(x) \
    (0x80070000 | (x))


/* ========================================================================== */
/* Basic Types: */
/* https://msdn.microsoft.com/en-us/library/windows/desktop/aa383751(v=vs.85).aspx */
/* ========================================================================== */

#if defined(_MSC_VER)
    /* 1300 == VC 6.0 */
    #if _MSC_VER < 1300
        typedef signed char         int8_t;
        typedef unsigned char       uint8_t;
        typedef signed short        int16_t;
        typedef unsigned short      uint16_t;
        typedef signed int          int32_t;
        typedef unsigned int        uint32_t;
    #else
        typedef signed __int8       int8_t;
        typedef unsigned __int8     uint8_t;
        typedef signed __int16      int16_t;
        typedef unsigned __int16    uint16_t;
        typedef signed __int32      int32_t;
        typedef unsigned __int32    uint32_t;
    #endif
    typedef signed __int64          int64_t;
    typedef unsigned __int64        uint64_t;
#else
    #include <stdint.h>
#endif


typedef int                 BOOL;
typedef char                CHAR;
typedef short               SHORT;
typedef int                 INT;
typedef long                LONG;
typedef unsigned char       UCHAR;
typedef unsigned short      USHORT;
typedef unsigned int        UINT;
typedef unsigned long       ULONG;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef unsigned long       DWORD;
#ifndef HAVE_WCHAR_T
#define HAVE_WCHAR_T
#if !defined(__cplusplus)
typedef unsigned short      wchar_t;
#endif
#endif
typedef wchar_t             WCHAR;
typedef wchar_t *           PWCHAR;
typedef WORD                ATOM;
typedef unsigned int        ULONG32;
typedef uint64_t            DWORD64;
typedef uint64_t            ULONG64;
typedef signed int          INT32;
typedef signed __int64      INT64;
typedef uint64_t            DWORDLONG;

typedef CHAR *              PCHAR;
typedef ULONG *             PULONG;
typedef ULONG64 *           PULONG64;
typedef DWORD64 *           PDWORD64;

#if !defined(_M_IX86)
typedef int64_t             LONGLONG;
typedef uint64_t            ULONGLONG;
#else
typedef double              LONGLONG;
typedef double              ULONGLONG;
#endif

typedef void                VOID;
typedef void *              PVOID;
typedef void *              LPVOID;
typedef BOOL *              PBOOL;
typedef BOOL *              LPBOOL;
typedef WORD *              PWORD;
typedef LONG *              PLONG;
typedef LONG *              LPLONG;
typedef DWORD *             PDWORD;

typedef LPVOID              HANDLE;
typedef HANDLE              HINSTANCE;
typedef HANDLE              HWND;
typedef HINSTANCE           HMODULE;
typedef HANDLE              HDC;
typedef HANDLE              HGLRC;
typedef HANDLE              HMENU;
typedef HANDLE *            PHANDLE;
typedef HANDLE *            LPHANDLE;

#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name

typedef WCHAR *             PWSTR;
typedef BYTE *              LPBYTE;
typedef long *              LPLONG;
typedef DWORD *             LPDWORD;
typedef const void *        LPCVOID;

#if defined(_WIN64)
typedef int64_t             INT_PTR;
typedef int64_t             LONG_PTR;
typedef uint64_t            UINT_PTR;
typedef uint64_t            ULONG_PTR;
#else
typedef int                 INT_PTR;
typedef long                LONG_PTR;
typedef unsigned int        UINT_PTR;
typedef unsigned long       ULONG_PTR;
#endif
typedef ULONG_PTR           DWORD_PTR;
typedef DWORD_PTR *         PDWORD_PTR;

typedef ULONG_PTR           SIZE_T;
typedef LONG_PTR            SSIZE_T;

typedef CHAR *              LPSTR;
typedef WCHAR *             LPWSTR;
typedef const CHAR *        LPCSTR;
typedef const WCHAR *       LPCWSTR;
#if defined(UNICODE)
typedef WCHAR               TCHAR;
typedef WCHAR               TBYTE;
typedef LPCWSTR             LPCTSTR;
typedef LPWSTR              LPTSTR;
#else
typedef char                TCHAR;
typedef unsigned char       TBYTE;
typedef LPCSTR              LPCTSTR;
typedef LPSTR               LPTSTR;
#endif

#define MINCHAR             0x80
#define MAXCHAR             0x7f
#define MINSHORT            0x8000
#define MAXSHORT            0x7fff
#define MINLONG             0x80000000
#define MAXLONG             0x7fffffff
#define MAXBYTE             0xff
#define MAXWORD             0xffff
#define MAXDWORD            0xffffffff

#if defined(_WIN64)
typedef INT_PTR (WINAPI *FARPROC)(void);
typedef INT_PTR (WINAPI *NEARPROC)(void);
typedef INT_PTR (WINAPI *PROC)(void);
#else
typedef int (WINAPI *FARPROC)(void);
typedef int (WINAPI *NEARPROC)(void);
typedef int (WINAPI *PROC)(void);
#endif

typedef DWORD               ACCESS_MASK;
typedef ACCESS_MASK *       PACCESS_MASK;

typedef HANDLE              HICON;
typedef HANDLE              HBRUSH;
typedef HICON               HCURSOR;

typedef LONG                HRESULT;
typedef LONG_PTR            LRESULT;
typedef LONG_PTR            LPARAM;
typedef UINT_PTR            WPARAM;

typedef void *              HGDIOBJ;

typedef HANDLE              HKEY;
typedef HKEY *              PHKEY;
typedef ACCESS_MASK         REGSAM;


/* ========================================================================== */
/* Errors: */
/* ========================================================================== */
#define ERROR_SUCCESS               0L
#define ERROR_FILE_NOT_FOUND        2L
#define ERROR_PATH_NOT_FOUND        3L
#define ERROR_TOO_MANY_OPEN_FILES   4L
#define ERROR_ACCESS_DENIED         5L
#define ERROR_NO_MORE_FILES         18L
#define ERROR_SHARING_VIOLATION     32L
#define ERROR_FILE_EXISTS           80L
#define ERROR_INSUFFICIENT_BUFFER   122L
#define ERROR_ALREADY_EXISTS        183L
#define ERROR_MORE_DATA             234L


/* ========================================================================== */
/* Enums                                                                      */
/* ========================================================================== */
/* DllMain Reason: */
#define DLL_PROCESS_ATTACH      (1)
#define DLL_PROCESS_DETACH      (0)
#define DLL_THREAD_ATTACH       (2)
#define DLL_THREAD_DETACH       (3)


/* ========================================================================== */
/* Structures: */
/* ========================================================================== */
typedef struct _SECURITY_ATTRIBUTES {
    DWORD           nLength;
    LPVOID          lpSecurityDescriptor;
    BOOL            bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef union _LARGE_INTEGER {
    struct {
        DWORD LowPart;
        LONG HighPart;
    };
    struct {
        DWORD LowPart;
        LONG HighPart;
    } u;
    LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
    struct {
        DWORD LowPart;
        DWORD HighPart;
    };
    struct {
        DWORD LowPart;
        DWORD HighPart;
    } u;
    ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

/* Filetime: */
typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;


#if defined(__cplusplus)
}
#endif
/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_BASE_H */
#endif /* _WINDOWS_ */


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_ATOMIC_H
#define WINDOWS_ATOMIC_H

/* Disable all warnings */
#if defined(_MSC_VER)
    #pragma warning(push, 0)
#endif

#include "intrin.h"

#if defined(__cplusplus)
extern "C" {
#endif


/* ========================================================================== */
/* Atomic Functions: */
/* ========================================================================== */

/* ========================================================================== */
/* 8-Bit Atomic Intrinsics:                                                   */
/* Exchange */
char _InterlockedExchange8(
        char volatile *Target,
        char Value);
char _InterlockedExchangeAdd8(
        char volatile *Addend,
        char Value);

/* Bit Operations */
char _InterlockedExchangeAnd8(
        char volatile *Destination,
        char Value);
char _InterlockedExchangeOr8(
        char volatile *Destination,
        char Value);
char _InterlockedExchangeXor8(
        char volatile *Destination,
        char Value);

/* Increment & Decrement */
char _InterlockedDecrement8(
        char volatile *Addend);
char _InterlockedIncrement8(
        char volatile *Addend);

/* Compare & Exchang */
char _InterlockedCompareExchange8(
        char volatile *Destination,
        char Exchange,
        char Comparand);
char _InterlockedCompareExchange8_HLEAcquire(
        char volatile *Destination,
        char Exchange,
        char Comparand);
char _InterlockedCompareExchange8_HLERelease(
        char volatile *Destination,
        char Exchange,
        char Comparand);


/* ========================================================================== */
/* 16-Bit Atomic Intrinsics:                                                  */
/* Exchange */
short _InterlockedExchange16(
        short volatile *Target,
        short Value);
short _InterlockedExchangeAdd16(
        short volatile *Addend,
        short Value);

/* Bit Operations */
short _InterlockedExchangeAnd16(
        short volatile *Destination,
        short Value);
short _InterlockedExchangeOr16(
        short volatile *Destination,
        short Value);
short _InterlockedExchangeXor16(
        short volatile *Destination,
        short Value);

/* Increment & Decrement */
short _InterlockedDecrement16(
        short volatile *Addend);
short _InterlockedIncrement16(
        short volatile *Addend);

/* Compare & Exchang */
short _InterlockedCompareExchange16(
        short volatile *Destination,
        short Exchange,
        short Comparand);
short _InterlockedCompareExchange16_HLEAcquire(
        short volatile *Destination,
        short Exchange,
        short Comparand);
short _InterlockedCompareExchange16_HLERelease(
        short volatile *Destination,
        short Exchange,
        short Comparand);


/* ========================================================================== */
/* 32-Bit Atomic Intrinsics:                                                  */
/* Exchange */
long _InterlockedExchange(
        long volatile *Target,
        long Value);
long _InterlockedExchangeAdd(
        long volatile *Addend,
        long Value);

/* Bit Operations */
long _InterlockedExchangeAnd(
        long volatile *Destination,
        long Value);
long _InterlockedExchangeOr(
        long volatile *Destination,
        long Value);
long _InterlockedExchangeXor(
        long volatile *Destination,
        long Value);

/* Increment & Decrement */
long _InterlockedDecrement(
        long volatile *Addend);
long _InterlockedIncrement(
        long volatile *Addend);

/* Compare & Exchang */
long _InterlockedCompareExchange(
        long volatile *Destination,
        long Exchange,
        long Comparand);
long _InterlockedCompareExchange_HLEAcquire(
        long volatile *Destination,
        long Exchange,
        long Comparand);
long _InterlockedCompareExchange_HLERelease(
        long volatile *Destination,
        long Exchange,
        long Comparand);

/* ========================================================================== */
/* 64-Bit Atomic Intrinsics:                                                  */
#ifdef _AMD64_
/* Exchange */
__int64 _InterlockedExchange64(
        __int64 volatile *Target,
        __int64 Value);
__int64 _InterlockedExchangeAdd64(
        __int64 volatile *Addend,
        __int64 Value);

/* Bit Operations */
__int64 _InterlockedExchangeAnd64(
        __int64 volatile *Destination,
        __int64 Value);
__int64 _InterlockedExchangeOr64(
        __int64 volatile *Destination,
        __int64 Value);
__int64 _InterlockedExchangeXor64(
        __int64 volatile *Destination,
        __int64 Value);

/* Increment & Decrement */
__int64 _InterlockedDecrement64(
        __int64 volatile *Addend);
__int64 _InterlockedIncrement64(
        __int64 volatile *Addend);

/* Compare & Exchang */
__int64 _InterlockedCompareExchange64(
        __int64 volatile *Destination,
        __int64 Exchange,
        __int64 Comparand);
__int64 _InterlockedCompareExchange64_HLEAcquire(
        __int64 volatile *Destination,
        __int64 Exchange,
        __int64 Comparand);
__int64 _InterlockedCompareExchange64_HLERelease(
        __int64 volatile *Destination,
        __int64 Exchange,
        __int64 Comparand);

/* ========================================================================== */
/* 128-Bit Atomic Intrinsics:                                                 */
/* Exchange */
unsigned char _InterlockedCompareExchange128(
        __int64 volatile *Destination,
        __int64 ExchangeHigh,
        __int64 ExchangeLow,
        __int64 *ComparandResult);

#endif

/* Win32 InterlockedXX functions are defined as macros */
#define InterlockedExchange8                    _InterlockedExchange8
#define InterlockedExchangeAdd8                 _InterlockedExchangeAdd8
#define InterlockedExchangeAnd8                 _InterlockedExchangeAnd8
#define InterlockedExchangeOr8                  _InterlockedExchangeOr8
#define InterlockedExchangeXor8                 _InterlockedExchangeXor8
#define InterlockedDecrement8                   _InterlockedDecrement8
#define InterlockedIncrement8                   _InterlockedIncrement8
#define InterlockedCompareExchange8             _InterlockedCompareExchange8

#define InterlockedExchange16                   _InterlockedExchange16
#define InterlockedExchangeAdd16                _InterlockedExchangeAdd16
#define InterlockedExchangeAnd16                _InterlockedExchangeAnd16
#define InterlockedExchangeOr16                 _InterlockedExchangeOr16
#define InterlockedExchangeXor16                _InterlockedExchangeXor16
#define InterlockedDecrement16                  _InterlockedDecrement16
#define InterlockedIncrement16                  _InterlockedIncrement16
#define InterlockedCompareExchange16            _InterlockedCompareExchange16

#define InterlockedExchange                     _InterlockedExchange
#define InterlockedExchangeAdd                  _InterlockedExchangeAdd
#define InterlockedExchangeAnd                  _InterlockedExchangeAnd
#define InterlockedExchangeOr                   _InterlockedExchangeOr
#define InterlockedExchangeXor                  _InterlockedExchangeXor
#define InterlockedDecrement                    _InterlockedDecrement
#define InterlockedIncrement                    _InterlockedIncrement
#define InterlockedCompareExchange              _InterlockedCompareExchange

#ifdef _AMD64_
    #define InterlockedExchange64               _InterlockedExchange64
    #define InterlockedExchangeAdd64            _InterlockedExchangeAdd64
    #define InterlockedExchangeAnd64            _InterlockedExchangeAnd64
    #define InterlockedExchangeOr64             _InterlockedExchangeOr64
    #define InterlockedExchangeXor64            _InterlockedExchangeXor64
    #define InterlockedDecrement64              _InterlockedDecrement64
    #define InterlockedIncrement64              _InterlockedIncrement64
    #define InterlockedCompareExchange64        _InterlockedCompareExchange64

    #define InterlockedCompareExchange128       _InterlockedCompareExchange128
#endif


/* ========================================================================== */
/* Barriers:                                                                  */
void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#ifdef _AMD64_
    #define MemoryBarrier __faststorefence
    #define YieldProcessor _mm_pause

#elif defined(_M_IX86)
    FORCEINLINE void
    MemoryBarrier(void)
    {
        LONG Barrier;
        __asm {
            xchg Barrier, eax
        }
    }
    #define YieldProcessor __asm { rep nop }
#endif

#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_ATOMIC_H */
#endif /* _WINDOWS_ */


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_DBGHELP_H
#define WINDOWS_DBGHELP_H

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

/* Exceptions: */
#define EXCEPTION_MAXIMUM_PARAMETERS    15
#define EXCEPTION_EXECUTE_HANDLER       0x1
#define EXCEPTION_CONTINUE_EXECUTION    0xFFFFFFFF
#define EXCEPTION_CONTINUE_SEARCH       0x0

#define EXCEPTION_ACCESS_VIOLATION          ((DWORD)0xC0000005L)
#define EXCEPTION_DATATYPE_MISALIGNMENT     ((DWORD)0x80000002L)
#define EXCEPTION_BREAKPOINT                ((DWORD)0x80000003L)
#define EXCEPTION_SINGLE_STEP               ((DWORD)0x80000004L)
#define EXCEPTION_ARRAY_BOUNDS_EXCEEDED     ((DWORD)0xC000008CL)
#define EXCEPTION_FLT_DENORMAL_OPERAND      ((DWORD)0xC000008DL)
#define EXCEPTION_FLT_DIVIDE_BY_ZERO        ((DWORD)0xC000008EL)
#define EXCEPTION_FLT_INEXACT_RESULT        ((DWORD)0xC000008FL)
#define EXCEPTION_FLT_INVALID_OPERATION     ((DWORD)0xC0000090L)
#define EXCEPTION_FLT_OVERFLOW              ((DWORD)0xC0000091L)
#define EXCEPTION_FLT_STACK_CHECK           ((DWORD)0xC0000092L)
#define EXCEPTION_FLT_UNDERFLOW             ((DWORD)0xC0000093L)
#define EXCEPTION_INT_DIVIDE_BY_ZERO        ((DWORD)0xC0000094L)
#define EXCEPTION_INT_OVERFLOW              ((DWORD)0xC0000095L)
#define EXCEPTION_PRIV_INSTRUCTION          ((DWORD)0xC0000096L)
#define EXCEPTION_IN_PAGE_ERROR             ((DWORD)0xC0000006L)
#define EXCEPTION_STACK_OVERFLOW            ((DWORD)0xC00000FDL)
#define EXCEPTION_ILLEGAL_INSTRUCTION       ((DWORD)0xC000001DL)
#define EXCEPTION_NONCONTINUABLE_EXCEPTION  ((DWORD)0xC0000025L)
#define EXCEPTION_INVALID_DISPOSITION       ((DWORD)0xC0000026L)
#define EXCEPTION_GUARD_PAGE                ((DWORD)0x80000001L)
#define EXCEPTION_INVALID_HANDLE            ((DWORD)0xC0000008L)
#define EXCEPTION_POSSIBLE_DEADLOCK         ((DWORD)0xC0000194L)
#define CONTROL_C_EXIT                      ((DWORD)0xC000013AL)

/* User defined. */
#ifndef EXCEPTION_ASSERTION
#define EXCEPTION_ASSERTION                 ((DWORD)0xEF000001L)
#endif

/* Snapshotting: */
#define TH32CS_SNAPTHREAD           0x00000004
#define IMAGE_FILE_MACHINE_I386     0x014c
#define IMAGE_FILE_MACHINE_AMD64    0x8664
#define CONTEXT_AMD64               0x100000
#define CONTEXT_CONTROL             (CONTEXT_AMD64 | 0x1L)
#define CONTEXT_INTEGER             (CONTEXT_AMD64 | 0x2L)
#define CONTEXT_SEGMENTS            (CONTEXT_AMD64 | 0x4L)
#define CONTEXT_FLOATING_POINT      (CONTEXT_AMD64 | 0x8L)
#define CONTEXT_DEBUG_REGISTERS     (CONTEXT_AMD64 | 0x10L)


#define CONTEXT_FULL                \
    (CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_FLOATING_POINT)

#define CONTEXT_ALL                 \
    (CONTEXT_CONTROL |\
     CONTEXT_INTEGER |\
     CONTEXT_SEGMENTS |\
     CONTEXT_FLOATING_POINT |\
     CONTEXT_DEBUG_REGISTERS)

/* Symbol Options: */
#define SYMOPT_CASE_INSENSITIVE         0x00000001
#define SYMOPT_UNDNAME                  0x00000002
#define SYMOPT_DEFERRED_LOADS           0x00000004
#define SYMOPT_NO_CPP                   0x00000008
#define SYMOPT_LOAD_LINES               0x00000010
#define SYMOPT_OMAP_FIND_NEAREST        0x00000020
#define SYMOPT_LOAD_ANYTHING            0x00000040
#define SYMOPT_IGNORE_CVREC             0x00000080
#define SYMOPT_NO_UNQUALIFIED_LOADS     0x00000100
#define SYMOPT_FAIL_CRITICAL_ERRORS     0x00000200
#define SYMOPT_EXACT_SYMBOLS            0x00000400
#define SYMOPT_ALLOW_ABSOLUTE_SYMBOLS   0x00000800
#define SYMOPT_IGNORE_NT_SYMPATH        0x00001000
#define SYMOPT_INCLUDE_32BIT_MODULES    0x00002000
#define SYMOPT_PUBLICS_ONLY             0x00004000
#define SYMOPT_NO_PUBLICS               0x00008000
#define SYMOPT_AUTO_PUBLICS             0x00010000
#define SYMOPT_NO_IMAGE_SEARCH          0x00020000
#define SYMOPT_SECURE                   0x00040000
#define SYMOPT_NO_PROMPTS               0x00080000
#define SYMOPT_OVERWRITE                0x00100000
#define SYMOPT_IGNORE_IMAGEDIR          0x00200000
#define SYMOPT_FLAT_DIRECTORY           0x00400000
#define SYMOPT_FAVOR_COMPRESSED         0x00800000
#define SYMOPT_ALLOW_ZERO_ADDRESS       0x01000000
#define SYMOPT_DISABLE_SYMSRV_AUTODETECT 0x02000000

#define SYMOPT_DEBUG                    0x80000000

enum SymTagEnum {
   SymTagNull,
   SymTagExe,
   SymTagCompiland,
   SymTagCompilandDetails,
   SymTagCompilandEnv,
   SymTagFunction,
   SymTagBlock,
   SymTagData,
   SymTagAnnotation,
   SymTagLabel,
   SymTagPublicSymbol,
   SymTagUDT,
   SymTagEnum,
   SymTagFunctionType,
   SymTagPointerType,
   SymTagArrayType,
   SymTagBaseType,
   SymTagTypedef,
   SymTagBaseClass,
   SymTagFriend,
   SymTagFunctionArgType,
   SymTagFuncDebugStart,
   SymTagFuncDebugEnd,
   SymTagUsingNamespace,
   SymTagVTableShape,
   SymTagVTable,
   SymTagCustom,
   SymTagThunk,
   SymTagCustomType,
   SymTagManagedType,
   SymTagDimension,
   SymTagCallSite,
   SymTagInlineSite,
   SymTagBaseInterface,
   SymTagVectorType,
   SymTagMatrixType,
   SymTagHLSLType
};

/* Thread-Information Block: */
typedef struct _NT_TIB {                    /*   x86  /   x64  */
    void *          ExceptionList;          /* 0x0000 / 0x0000 */
    void *          StackBase;              /* 0x0004 / 0x0008 */
    void *          StackLimit;             /* 0x0008 / 0x0010 */
    void *          SubSystemTib;           /* 0x000c / 0x0018 */
    union {
        void *      FiberData;              /* 0x0010 / 0x0020 */
        DWORD       Version;                /* 0x0010 / 0x0020 */
    };
    void *          ArbitraryUserPointer;   /* 0x0014 / 0x0028 */
    struct _NT_TIB *Self;                   /* 0x0018 / 0x0030 */
} NT_TIB, *LPNT_TIB, *PNT_TIB;

/* Exceptions: */
#if defined(_WIN64)
typedef struct DECLSPEC_ALIGN(16) _M128A {
    ULONGLONG       Low;
    LONGLONG        High;
} M128A, *PM128A;
typedef struct DECLSPEC_ALIGN(16) _XSAVE_FORMAT {
    WORD            ControlWord;
    WORD            StatusWord;
    BYTE            TagWord;
    BYTE            Reserved1;
    WORD            ErrorOpcode;
    DWORD           ErrorOffset;
    WORD            ErrorSelector;
    WORD            Reserved2;
    DWORD           DataOffset;
    WORD            DataSelector;
    WORD            Reserved3;
    DWORD           MxCsr;
    DWORD           MxCsr_Mask;
    M128A           FloatRegisters[8];

#if defined(_WIN64)
    M128A           XmmRegisters[16];
    BYTE            Reserved4[96];
#else
    M128A           XmmRegisters[8];
    BYTE            Reserved4[192];

    DWORD           StackControl[7];
    DWORD           Cr0NpxState;
#endif
} XSAVE_FORMAT, *PXSAVE_FORMAT;
typedef XSAVE_FORMAT XMM_SAVE_AREA32, *PXMM_SAVE_AREA32;

typedef struct DECLSPEC_ALIGN(16) _CONTEXT {
    DWORD64 P1Home;
    DWORD64 P2Home;
    DWORD64 P3Home;
    DWORD64 P4Home;
    DWORD64 P5Home;
    DWORD64 P6Home;

    DWORD ContextFlags;
    DWORD MxCsr;

    WORD   SegCs;
    WORD   SegDs;
    WORD   SegEs;
    WORD   SegFs;
    WORD   SegGs;
    WORD   SegSs;
    DWORD EFlags;

    DWORD64 Dr0;
    DWORD64 Dr1;
    DWORD64 Dr2;
    DWORD64 Dr3;
    DWORD64 Dr6;
    DWORD64 Dr7;

    DWORD64 Rax;
    DWORD64 Rcx;
    DWORD64 Rdx;
    DWORD64 Rbx;
    DWORD64 Rsp;
    DWORD64 Rbp;
    DWORD64 Rsi;
    DWORD64 Rdi;
    DWORD64 R8;
    DWORD64 R9;
    DWORD64 R10;
    DWORD64 R11;
    DWORD64 R12;
    DWORD64 R13;
    DWORD64 R14;
    DWORD64 R15;
    DWORD64 Rip;

    union {
        XMM_SAVE_AREA32 FltSave;
        struct {
            M128A Header[2];
            M128A Legacy[8];
            M128A Xmm0;
            M128A Xmm1;
            M128A Xmm2;
            M128A Xmm3;
            M128A Xmm4;
            M128A Xmm5;
            M128A Xmm6;
            M128A Xmm7;
            M128A Xmm8;
            M128A Xmm9;
            M128A Xmm10;
            M128A Xmm11;
            M128A Xmm12;
            M128A Xmm13;
            M128A Xmm14;
            M128A Xmm15;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    M128A VectorRegister[26];
    DWORD64 VectorControl;

    DWORD64 DebugControl;
    DWORD64 LastBranchToRip;
    DWORD64 LastBranchFromRip;
    DWORD64 LastExceptionToRip;
    DWORD64 LastExceptionFromRip;
} CONTEXT, *PCONTEXT;
typedef PCONTEXT LPCONTEXT;
#elif _WIN32
typedef struct _FLOATING_SAVE_AREA
{
    ULONG ControlWord;
    ULONG StatusWord;
    ULONG TagWord;
    ULONG ErrorOffset;
    ULONG ErrorSelector;
    ULONG DataOffset;
    ULONG DataSelector;
    UCHAR RegisterArea[80];
    ULONG Cr0NpxState;
} FLOATING_SAVE_AREA, *PFLOATING_SAVE_AREA;
#define MAXIMUM_SUPPORTED_EXTENSION     512
typedef struct _CONTEXT {
    DWORD ContextFlags;
    DWORD   Dr0;
    DWORD   Dr1;
    DWORD   Dr2;
    DWORD   Dr3;
    DWORD   Dr6;
    DWORD   Dr7;

    FLOATING_SAVE_AREA FloatSave;

    DWORD   SegGs;
    DWORD   SegFs;
    DWORD   SegEs;
    DWORD   SegDs;

    DWORD   Edi;
    DWORD   Esi;
    DWORD   Ebx;
    DWORD   Edx;
    DWORD   Ecx;
    DWORD   Eax;

    DWORD   Ebp;
    DWORD   Eip;
    DWORD   SegCs;
    DWORD   EFlags;
    DWORD   Esp;
    DWORD   SegSs;

    BYTE    ExtendedRegisters[MAXIMUM_SUPPORTED_EXTENSION];

} CONTEXT, *PCONTEXT;
typedef PCONTEXT LPCONTEXT;
#endif
typedef struct _EXCEPTION_RECORD {
    DWORD                       ExceptionCode;
    DWORD                       ExceptionFlags;
    struct _EXCEPTION_RECORD *  ExceptionRecord;
    PVOID                       ExceptionAddress;
    DWORD                       NumberParameters;
    ULONG_PTR                   ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
} EXCEPTION_RECORD, *PEXCEPTION_RECORD;
typedef struct _EXCEPTION_POINTERS {
    PEXCEPTION_RECORD   ExceptionRecord;
    PCONTEXT            ContextRecord;
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;
typedef PEXCEPTION_POINTERS LPEXCEPTION_POINTERS;
typedef LONG (WINAPI *PTOP_LEVEL_EXCEPTION_FILTER)(
        struct _EXCEPTION_POINTERS *ExceptionInfo);
typedef PTOP_LEVEL_EXCEPTION_FILTER LPTOP_LEVEL_EXCEPTION_FILTER;
typedef LONG (WINAPI *PVECTORED_EXCEPTION_HANDLER)(
        struct _EXCEPTION_POINTERS *ExceptionInfo);

/* Symbols: */
typedef struct _SYMBOL_INFO {
    ULONG   SizeOfStruct;
    ULONG   TypeIndex;
    ULONG64 Reserved[2];
    ULONG   Index;
    ULONG   Size;
    ULONG64 ModBase;
    ULONG   Flags;
    ULONG64 Value;
    ULONG64 Address;
    ULONG   Register;
    ULONG   Scope;
    ULONG   Tag;
    ULONG   NameLen;
    ULONG   MaxNameLen;
    CHAR    Name[1];
} SYMBOL_INFO, *PSYMBOL_INFO;

typedef struct _SYMBOL_INFOW {
    ULONG   SizeOfStruct;
    ULONG   TypeIndex;
    ULONG64 Reserved[2];
    ULONG   Index;
    ULONG   Size;
    ULONG64 ModBase;
    ULONG   Flags;
    ULONG64 Value;
    ULONG64 Address;
    ULONG   Register;
    ULONG   Scope;
    ULONG   Tag;
    ULONG   NameLen;
    ULONG   MaxNameLen;
    WCHAR   Name[1];
} SYMBOL_INFOW, *PSYMBOL_INFOW;

typedef struct _IMAGEHLP_LINE64 {
    DWORD    SizeOfStruct;
    PVOID    Key;
    DWORD    LineNumber;
    PCHAR    FileName;
    DWORD64  Address;
} IMAGEHLP_LINE64, *PIMAGEHLP_LINE64;

typedef struct _IMAGEHLP_LINEW64 {
    DWORD    SizeOfStruct;
    PVOID    Key;
    DWORD    LineNumber;
    PWSTR    FileName;
    DWORD64  Address;
} IMAGEHLP_LINEW64, *PIMAGEHLP_LINEW64;

/* Thread Walking: */
typedef struct tagTHREADENTRY32 {
    DWORD dwSize;
    DWORD cntUsage;
    DWORD th32ThreadID;
    DWORD th32OwnerProcessID;
    LONG  tpBasePri;
    LONG  tpDeltaPri;
    DWORD dwFlags;
} THREADENTRY32, *PTHREADENTRY32;
typedef PTHREADENTRY32 LPTHREADENTRY32;

/* Stack Walking: */
typedef enum {
    AddrMode1616,
    AddrMode1632,
    AddrModeReal,
    AddrModeFlat
} ADDRESS_MODE;
typedef struct _tagADDRESS64 {
    DWORD64      Offset;
    WORD         Segment;
    ADDRESS_MODE Mode;
} ADDRESS64, *LPADDRESS64;
typedef struct _KDHELP64 {
    DWORD64   Thread;
    DWORD   ThCallbackStack;
    DWORD   ThCallbackBStore;
    DWORD   NextCallback;
    DWORD   FramePointer;
    DWORD64   KiCallUserMode;
    DWORD64   KeUserCallbackDispatcher;
    DWORD64   SystemRangeStart;
    DWORD64   KiUserExceptionDispatcher;
    DWORD64   StackBase;
    DWORD64   StackLimit;
    DWORD64   Reserved[5];
} KDHELP64, *PKDHELP64;
typedef struct _tagSTACKFRAME64 {
    ADDRESS64 AddrPC;
    ADDRESS64 AddrReturn;
    ADDRESS64 AddrFrame;
    ADDRESS64 AddrStack;
    ADDRESS64 AddrBStore;
    PVOID     FuncTableEntry;
    DWORD64   Params[4];
    BOOL      Far;
    BOOL      Virtual;
    DWORD64   Reserved[3];
    KDHELP64  KdHelp;
} STACKFRAME64, *LPSTACKFRAME64;

/* Some weird stuff: */
typedef struct _LUID {
    DWORD LowPart;
    LONG HighPart;
} LUID, *PLUID;
#pragma pack(push,4)
typedef struct _LUID_AND_ATTRIBUTES {
    LUID Luid;
    DWORD Attributes;
} LUID_AND_ATTRIBUTES, *PLUID_AND_ATTRIBUTES;
#pragma pack(pop)
typedef struct _TOKEN_PRIVILEGES {
    DWORD PrivilegeCount;
    LUID_AND_ATTRIBUTES Privileges[1];
} TOKEN_PRIVILEGES, *PTOKEN_PRIVILEGES;


/* ========================================================================== */
/* Debugging: */
void WINAPI DebugBreak(void);
BOOL WINAPI IsDebuggerPresent(void);
BOOL WINAPI CheckRemoteDebuggerPresent(
        HANDLE  hProcess,
        PBOOL   hbDebuggerPresent);
void WINAPI OutputDebugStringA(
        LPCSTR  lpOutputString);
void WINAPI OutputDebugStringW(
        LPCWSTR lpOutputString);
BOOL WINAPI GetThreadContext(
        HANDLE      hThread,
        LPCONTEXT   lpContext);
BOOL WINAPI DebugActiveProcess(
        DWORD       dwProcessId);
BOOL WINAPI DebugActiveProcessStop(
        DWORD       dwProcessId);

/* ========================================================================== */
/* Symbols: */
DWORD WINAPI SymSetOptions(
        DWORD   SymOptions);
BOOL WINAPI SymInitialize(
        HANDLE  hProcess,
        LPCSTR  UserSearchPath,
        BOOL    fInvadeProcess);
BOOL WINAPI SymInitializeW(
        HANDLE  hProcess,
        LPCWSTR UserSearchPath,
        BOOL    fInvadeProcess);
BOOL WINAPI SymFromAddr(
        HANDLE          hProcess,
        DWORD64         Address,
        PDWORD64        Displacement,
        PSYMBOL_INFO    Symbol);
BOOL WINAPI SymFromAddrW(
        HANDLE          hProcess,
        DWORD64         Address,
        PDWORD64        Displacement,
        PSYMBOL_INFOW   Symbol);
PVOID WINAPI SymFunctionTableAccess64(
        HANDLE          hProcess,
        DWORD64         AddrBase);
DWORD64 WINAPI SymGetModuleBase64(
        HANDLE          hProcess,
        DWORD64         dwAddr);
typedef BOOL (*PSYM_ENUMERATESYMBOLS_CALLBACK)(
        PSYMBOL_INFO    pSymInfo,
        ULONG           SymbolSize,
        PVOID           UserContext
);
typedef BOOL (*PSYM_ENUMERATESYMBOLS_CALLBACKW)(
        PSYMBOL_INFOW   pSymInfo,
        ULONG           SymbolSize,
        PVOID           UserContext
);
BOOL WINAPI SymSearch(
        HANDLE          hProcess,
        ULONG64         BaseOfDll,
        DWORD           Index,
        DWORD           SymTag,
        LPCSTR          Mask,
        DWORD64         Address,
        PSYM_ENUMERATESYMBOLS_CALLBACK EnumSymbolsCallback,
        PVOID           UserContext,
        DWORD           Options);
BOOL WINAPI SymSearchW(
        HANDLE          hProcess,
        ULONG64         BaseOfDll,
        DWORD           Index,
        DWORD           SymTag,
        LPCWSTR         Mask,
        DWORD64         Address,
        PSYM_ENUMERATESYMBOLS_CALLBACKW EnumSymbolsCallback,
        PVOID           UserContext,
        DWORD           Options);
BOOL WINAPI SymRefreshModuleList(
        HANDLE          hProcess);

typedef BOOL (*PSYM_ENUMMODULES_CALLBACK64)(
        LPCSTR  ModuleName,
        DWORD64 BaseOfDll,
        PVOID   UserContext
);
typedef BOOL (*PSYM_ENUMMODULES_CALLBACKW64)(
        LPCWSTR ModuleName,
        DWORD64 BaseOfDll,
        PVOID   UserContext
);
BOOL WINAPI SymEnumerateModules64(
        HANDLE                      hProcess,
        PSYM_ENUMMODULES_CALLBACK64 EnumModulesCallback,
        PVOID                       UserContext
);
BOOL WINAPI SymEnumerateModulesW64(
        HANDLE                       hProcess,
        PSYM_ENUMMODULES_CALLBACKW64 EnumModulesCallback,
        PVOID                        UserContext
);

BOOL WINAPI SymSetSearchPath(
        HANDLE          hProcess,
        LPCSTR          SearchPath);
BOOL WINAPI SymSetSearchPathW(
        HANDLE          hProcess,
        LPCWSTR         SearchPath);

BOOL WINAPI SymGetSearchPath(
        HANDLE          hProcess,
        LPSTR           SearchPath,
        DWORD           SearchPathLength);
BOOL WINAPI SymGetSearchPathW(
        HANDLE          hProcess,
        LPWSTR          SearchPath,
        DWORD           SearchPathLength);

BOOL WINAPI SymCleanup(
        HANDLE          hProcess);

BOOL WINAPI SymGetLineFromAddr64(
    HANDLE           hProcess,
    DWORD64          dwAddr,
    PDWORD           pdwDisplacement,
    PIMAGEHLP_LINE64 Line
);

BOOL WINAPI SymGetLineFromAddrW64(
    HANDLE            hProcess,
    DWORD64           dwAddr,
    PDWORD            pdwDisplacement,
    PIMAGEHLP_LINEW64 Line
);

/* ========================================================================== */
/* Exceptions: */
LPTOP_LEVEL_EXCEPTION_FILTER WINAPI SetUnhandledExceptionFilter(
        LPTOP_LEVEL_EXCEPTION_FILTER    lpTopLevelExceptionFilter);
LONG WINAPI UnhandledExceptionFilter(
        struct _EXCEPTION_POINTERS *    ExceptionInfo);

PVOID WINAPI AddVectoredExceptionHandler(
    ULONG                       FirstHandler,
    PVECTORED_EXCEPTION_HANDLER VectoredHandler);

ULONG WINAPI RemoveVectoredExceptionHandler(
    PVOID Handler);

#define CaptureStackBackTrace RtlCaptureStackBackTrace
USHORT WINAPI RtlCaptureStackBackTrace(
        ULONG       FramesToSkip,
        ULONG       FramesToCapture,
        PVOID *     BackTrace,
        PULONG      BackTraceHash);
void WINAPI RtlCaptureContext(
        PCONTEXT    ContextRecord);
void WINAPI RaiseException(
        DWORD       dwExceptionCode,
        DWORD       dwExceptionFlags,
        DWORD       nNumberOfArguments,
  const ULONG_PTR * lpArguments);

/* ========================================================================== */
/* Thread Walking: */
HANDLE WINAPI CreateToolhelp32Snapshot(
        DWORD       dwFlags,
        DWORD       th32ProcessID);
BOOL WINAPI Thread32First(
        HANDLE      hSnapshot,
        LPTHREADENTRY32 lpte);
BOOL WINAPI Thread32Next(
        HANDLE      hSnapshot,
        LPTHREADENTRY32 lpte);

/* ========================================================================== */
/* Stack Walking: */
typedef BOOL (__stdcall *PREAD_PROCESS_MEMORY_ROUTINE64)(
        HANDLE hProcess,
        DWORD64 qwBaseAddress,
        PVOID lpBuffer,
        DWORD nSize,
        LPDWORD lpNumberOfBytesRead);

typedef PVOID (__stdcall *PFUNCTION_TABLE_ACCESS_ROUTINE64)(
        HANDLE ahProcess,
        DWORD64 AddrBase);

typedef DWORD64 (__stdcall *PGET_MODULE_BASE_ROUTINE64)(
        HANDLE hProcess,
        DWORD64 Address);

typedef DWORD64 (__stdcall *PTRANSLATE_ADDRESS_ROUTINE64)(
        HANDLE hProcess,
        HANDLE hThread,
        LPADDRESS64 lpaddr);

BOOL WINAPI StackWalk64(
        DWORD                            MachineType,
        HANDLE                           hProcess,
        HANDLE                           hThread,
        LPSTACKFRAME64                   StackFrame,
        PVOID                            ContextRecord,
        PREAD_PROCESS_MEMORY_ROUTINE64   ReadMemoryRoutine,
        PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
        PGET_MODULE_BASE_ROUTINE64       GetModuleBaseRoutine,
        PTRANSLATE_ADDRESS_ROUTINE64     TranslateAddress
);

/* ========================================================================== */
/* Minidumps: */
/* == VS Version == */
typedef struct tagVS_FIXEDFILEINFO
{
    DWORD   dwSignature;            /* e.g. 0xfeef04bd */
    DWORD   dwStrucVersion;         /* e.g. 0x00000042 = "0.42" */
    DWORD   dwFileVersionMS;        /* e.g. 0x00030075 = "3.75" */
    DWORD   dwFileVersionLS;        /* e.g. 0x00000031 = "0.31" */
    DWORD   dwProductVersionMS;     /* e.g. 0x00030010 = "3.10" */
    DWORD   dwProductVersionLS;     /* e.g. 0x00000031 = "0.31" */
    DWORD   dwFileFlagsMask;        /* = 0x3F for version "0.42" */
    DWORD   dwFileFlags;            /* e.g. VFF_DEBUG | VFF_PRERELEASE */
    DWORD   dwFileOS;               /* e.g. VOS_DOS_WINDOWS16 */
    DWORD   dwFileType;             /* e.g. VFT_DRIVER */
    DWORD   dwFileSubtype;          /* e.g. VFT2_DRV_KEYBOARD */
    DWORD   dwFileDateMS;           /* e.g. 0 */
    DWORD   dwFileDateLS;           /* e.g. 0 */
} VS_FIXEDFILEINFO;

/* == Type == */
typedef enum _MINIDUMP_TYPE {
    MiniDumpNormal                         = 0x00000000,
    MiniDumpWithDataSegs                   = 0x00000001,
    MiniDumpWithFullMemory                 = 0x00000002,
    MiniDumpWithHandleData                 = 0x00000004,
    MiniDumpFilterMemory                   = 0x00000008,
    MiniDumpScanMemory                     = 0x00000010,
    MiniDumpWithUnloadedModules            = 0x00000020,
    MiniDumpWithIndirectlyReferencedMemory = 0x00000040,
    MiniDumpFilterModulePaths              = 0x00000080,
    MiniDumpWithProcessThreadData          = 0x00000100,
    MiniDumpWithPrivateReadWriteMemory     = 0x00000200,
    MiniDumpWithoutOptionalData            = 0x00000400,
    MiniDumpWithFullMemoryInfo             = 0x00000800,
    MiniDumpWithThreadInfo                 = 0x00001000,
    MiniDumpWithCodeSegs                   = 0x00002000,
    MiniDumpWithoutAuxiliaryState          = 0x00004000,
    MiniDumpWithFullAuxiliaryState         = 0x00008000,
    MiniDumpWithPrivateWriteCopyMemory     = 0x00010000,
    MiniDumpIgnoreInaccessibleMemory       = 0x00020000,
    MiniDumpWithTokenInformation           = 0x00040000,
    MiniDumpValidTypeFlags                 = 0x0007ffff,
} MINIDUMP_TYPE;

/* == Exception Info == */
typedef struct _MINIDUMP_EXCEPTION_INFORMATION {
    DWORD ThreadId;
    PEXCEPTION_POINTERS ExceptionPointers;
    BOOL ClientPointers;
} MINIDUMP_EXCEPTION_INFORMATION, *PMINIDUMP_EXCEPTION_INFORMATION;
typedef struct _MINIDUMP_EXCEPTION_INFORMATION64 {
    DWORD ThreadId;
    ULONG64 ExceptionRecord;
    ULONG64 ContextRecord;
    BOOL ClientPointers;
} MINIDUMP_EXCEPTION_INFORMATION64, *PMINIDUMP_EXCEPTION_INFORMATION64;

/* == Callback Input Hell == */
typedef struct _MINIDUMP_THREAD_CALLBACK {
    ULONG ThreadId;
    HANDLE ThreadHandle;
    CONTEXT Context;
    ULONG SizeOfContext;
    ULONG64 StackBase;
    ULONG64 StackEnd;
} MINIDUMP_THREAD_CALLBACK, *PMINIDUMP_THREAD_CALLBACK;
typedef struct _MINIDUMP_THREAD_EX_CALLBACK {
    ULONG ThreadId;
    HANDLE ThreadHandle;
    CONTEXT Context;
    ULONG SizeOfContext;
    ULONG64 StackBase;
    ULONG64 StackEnd;
    ULONG64 BackingStoreBase;
    ULONG64 BackingStoreEnd;
} MINIDUMP_THREAD_EX_CALLBACK, *PMINIDUMP_THREAD_EX_CALLBACK;
typedef struct _MINIDUMP_MODULE_CALLBACK {
    PWCHAR FullPath;
    ULONG64 BaseOfImage;
    ULONG SizeOfImage;
    ULONG CheckSum;
    ULONG TimeDateStamp;
    VS_FIXEDFILEINFO VersionInfo;
    PVOID CvRecord;
    ULONG SizeOfCvRecord;
    PVOID MiscRecord;
    ULONG SizeOfMiscRecord;
} MINIDUMP_MODULE_CALLBACK, *PMINIDUMP_MODULE_CALLBACK;
typedef struct _MINIDUMP_INCLUDE_THREAD_CALLBACK {
    ULONG ThreadId;
} MINIDUMP_INCLUDE_THREAD_CALLBACK, *PMINIDUMP_INCLUDE_THREAD_CALLBACK;
typedef struct _MINIDUMP_INCLUDE_MODULE_CALLBACK {
    ULONG64 BaseOfImage;
} MINIDUMP_INCLUDE_MODULE_CALLBACK, *PMINIDUMP_INCLUDE_MODULE_CALLBACK;
typedef struct _MINIDUMP_IO_CALLBACK {
    HANDLE Handle;
    ULONG64 Offset;
    PVOID Buffer;
    ULONG BufferBytes;
} MINIDUMP_IO_CALLBACK, *PMINIDUMP_IO_CALLBACK;
typedef struct _MINIDUMP_READ_MEMORY_FAILURE_CALLBACK
{
    ULONG64 Offset;
    ULONG Bytes;
    HRESULT FailureStatus;
} MINIDUMP_READ_MEMORY_FAILURE_CALLBACK,
  *PMINIDUMP_READ_MEMORY_FAILURE_CALLBACK;
typedef struct _MINIDUMP_CALLBACK_INPUT {
    ULONG ProcessId;
    HANDLE ProcessHandle;
    ULONG CallbackType;
    union {
        HRESULT Status;
        MINIDUMP_THREAD_CALLBACK Thread;
        MINIDUMP_THREAD_EX_CALLBACK ThreadEx;
        MINIDUMP_MODULE_CALLBACK Module;
        MINIDUMP_INCLUDE_THREAD_CALLBACK IncludeThread;
        MINIDUMP_INCLUDE_MODULE_CALLBACK IncludeModule;
        MINIDUMP_IO_CALLBACK Io;
        MINIDUMP_READ_MEMORY_FAILURE_CALLBACK ReadMemoryFailure;
        ULONG SecondaryFlags;
    };
} MINIDUMP_CALLBACK_INPUT, *PMINIDUMP_CALLBACK_INPUT;

/* == Callback Output Hell == */
typedef struct _MINIDUMP_MEMORY_INFO {
    ULONG64 BaseAddress;
    ULONG64 AllocationBase;
    ULONG32 AllocationProtect;
    ULONG32 __alignment1;
    ULONG64 RegionSize;
    ULONG32 State;
    ULONG32 Protect;
    ULONG32 Type;
    ULONG32 __alignment2;
} MINIDUMP_MEMORY_INFO, *PMINIDUMP_MEMORY_INFO;
typedef struct _MINIDUMP_CALLBACK_OUTPUT {
    union {
        ULONG ModuleWriteFlags;
        ULONG ThreadWriteFlags;
        ULONG SecondaryFlags;
        struct {
            ULONG64 MemoryBase;
            ULONG MemorySize;
        };
        struct {
            BOOL CheckCancel;
            BOOL Cancel;
        };
        HANDLE Handle;
        struct {
            MINIDUMP_MEMORY_INFO VmRegion;
            BOOL Continue;
        };
        HRESULT Status;
    };
} MINIDUMP_CALLBACK_OUTPUT, *PMINIDUMP_CALLBACK_OUTPUT;

/* == Callback Hell == */
typedef BOOL (WINAPI *MINIDUMP_CALLBACK_ROUTINE)(
    PVOID                       CallbackParam,
    PMINIDUMP_CALLBACK_INPUT    CallbackInput,
    PMINIDUMP_CALLBACK_OUTPUT   CallbackOutput);
typedef struct _MINIDUMP_CALLBACK_INFORMATION {
    MINIDUMP_CALLBACK_ROUTINE   CallbackRoutine;
    PVOID                       CallbackParam;
} MINIDUMP_CALLBACK_INFORMATION, *PMINIDUMP_CALLBACK_INFORMATION;

/* == User Stream Information == */
typedef struct _MINIDUMP_USER_STREAM {
    ULONG32 Type;
    ULONG BufferSize;
    PVOID Buffer;
} MINIDUMP_USER_STREAM, *PMINIDUMP_USER_STREAM;
typedef struct _MINIDUMP_USER_STREAM_INFORMATION {
    ULONG UserStreamCount;
    PMINIDUMP_USER_STREAM UserStreamArray;
} MINIDUMP_USER_STREAM_INFORMATION, *PMINIDUMP_USER_STREAM_INFORMATION;

/* Function (all this shit above is required for this simple function). */
BOOL WINAPI MiniDumpWriteDump(
        HANDLE hProcess,
        DWORD ProcessId,
        HANDLE hFile,
        MINIDUMP_TYPE DumpType,
        PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
        PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
        PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

/* Priviliges: */
BOOL WINAPI OpenProcessToken (
        HANDLE ProcessHandle,
        DWORD DesiredAccess,
        PHANDLE TokenHandle);
BOOL WINAPI LookupPrivilegeValueA(
        LPCSTR  lpSystemName,
        LPCSTR  lpName,
        PLUID   lpLuid);
BOOL WINAPI LookupPrivilegeValueW(
        LPCWSTR lpSystemName,
        LPCWSTR lpName,
        PLUID   lpLuid);
BOOL WINAPI AdjustTokenPrivileges(
        HANDLE TokenHandle,
        BOOL DisableAllPrivileges,
        PTOKEN_PRIVILEGES NewState,
        DWORD BufferLength,
        PTOKEN_PRIVILEGES PreviousState,
        PDWORD ReturnLength);

/* ========================================================================== */
/* Segment Registers: */
void                __debugbreak(void);
#if _WIN64
unsigned char       __readgsbyte(unsigned long Offset);
unsigned short      __readgsword(unsigned long Offset);
unsigned long       __readgsdword(unsigned long Offset);
unsigned __int64    __readgsqword(unsigned long Offset);
#else
unsigned char       __readfsbyte(unsigned long Offset);
unsigned short      __readfsword(unsigned long Offset);
unsigned long       __readfsdword(unsigned long Offset);
unsigned __int64    __readfsqword(unsigned long Offset);
#endif

static NT_TIB *
GetTib(void)
{
#if _WIN64
    return (NT_TIB *)__readgsqword(0x30);
#else
    return (NT_TIB *)__readfsdword(0x18);
#endif
}


#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_DBGHELP_H */
#endif /* _WINDOWS_ */


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_DDS_H
#define WINDOWS_DDS_H

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

#ifndef DXGI_FORMAT_DEFINED
#define DXGI_FORMAT_DEFINED 1
typedef enum DXGI_FORMAT
{
    DXGI_FORMAT_UNKNOWN	                    = 0,
    DXGI_FORMAT_R32G32B32A32_TYPELESS       = 1,
    DXGI_FORMAT_R32G32B32A32_FLOAT          = 2,
    DXGI_FORMAT_R32G32B32A32_UINT           = 3,
    DXGI_FORMAT_R32G32B32A32_SINT           = 4,
    DXGI_FORMAT_R32G32B32_TYPELESS          = 5,
    DXGI_FORMAT_R32G32B32_FLOAT             = 6,
    DXGI_FORMAT_R32G32B32_UINT              = 7,
    DXGI_FORMAT_R32G32B32_SINT              = 8,
    DXGI_FORMAT_R16G16B16A16_TYPELESS       = 9,
    DXGI_FORMAT_R16G16B16A16_FLOAT          = 10,
    DXGI_FORMAT_R16G16B16A16_UNORM          = 11,
    DXGI_FORMAT_R16G16B16A16_UINT           = 12,
    DXGI_FORMAT_R16G16B16A16_SNORM          = 13,
    DXGI_FORMAT_R16G16B16A16_SINT           = 14,
    DXGI_FORMAT_R32G32_TYPELESS             = 15,
    DXGI_FORMAT_R32G32_FLOAT                = 16,
    DXGI_FORMAT_R32G32_UINT                 = 17,
    DXGI_FORMAT_R32G32_SINT                 = 18,
    DXGI_FORMAT_R32G8X24_TYPELESS           = 19,
    DXGI_FORMAT_D32_FLOAT_S8X24_UINT        = 20,
    DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS    = 21,
    DXGI_FORMAT_X32_TYPELESS_G8X24_UINT     = 22,
    DXGI_FORMAT_R10G10B10A2_TYPELESS        = 23,
    DXGI_FORMAT_R10G10B10A2_UNORM           = 24,
    DXGI_FORMAT_R10G10B10A2_UINT            = 25,
    DXGI_FORMAT_R11G11B10_FLOAT             = 26,
    DXGI_FORMAT_R8G8B8A8_TYPELESS           = 27,
    DXGI_FORMAT_R8G8B8A8_UNORM              = 28,
    DXGI_FORMAT_R8G8B8A8_UNORM_SRGB         = 29,
    DXGI_FORMAT_R8G8B8A8_UINT               = 30,
    DXGI_FORMAT_R8G8B8A8_SNORM              = 31,
    DXGI_FORMAT_R8G8B8A8_SINT               = 32,
    DXGI_FORMAT_R16G16_TYPELESS             = 33,
    DXGI_FORMAT_R16G16_FLOAT                = 34,
    DXGI_FORMAT_R16G16_UNORM                = 35,
    DXGI_FORMAT_R16G16_UINT                 = 36,
    DXGI_FORMAT_R16G16_SNORM                = 37,
    DXGI_FORMAT_R16G16_SINT                 = 38,
    DXGI_FORMAT_R32_TYPELESS                = 39,
    DXGI_FORMAT_D32_FLOAT                   = 40,
    DXGI_FORMAT_R32_FLOAT                   = 41,
    DXGI_FORMAT_R32_UINT                    = 42,
    DXGI_FORMAT_R32_SINT                    = 43,
    DXGI_FORMAT_R24G8_TYPELESS              = 44,
    DXGI_FORMAT_D24_UNORM_S8_UINT           = 45,
    DXGI_FORMAT_R24_UNORM_X8_TYPELESS       = 46,
    DXGI_FORMAT_X24_TYPELESS_G8_UINT        = 47,
    DXGI_FORMAT_R8G8_TYPELESS               = 48,
    DXGI_FORMAT_R8G8_UNORM                  = 49,
    DXGI_FORMAT_R8G8_UINT                   = 50,
    DXGI_FORMAT_R8G8_SNORM                  = 51,
    DXGI_FORMAT_R8G8_SINT                   = 52,
    DXGI_FORMAT_R16_TYPELESS                = 53,
    DXGI_FORMAT_R16_FLOAT                   = 54,
    DXGI_FORMAT_D16_UNORM                   = 55,
    DXGI_FORMAT_R16_UNORM                   = 56,
    DXGI_FORMAT_R16_UINT                    = 57,
    DXGI_FORMAT_R16_SNORM                   = 58,
    DXGI_FORMAT_R16_SINT                    = 59,
    DXGI_FORMAT_R8_TYPELESS                 = 60,
    DXGI_FORMAT_R8_UNORM                    = 61,
    DXGI_FORMAT_R8_UINT                     = 62,
    DXGI_FORMAT_R8_SNORM                    = 63,
    DXGI_FORMAT_R8_SINT                     = 64,
    DXGI_FORMAT_A8_UNORM                    = 65,
    DXGI_FORMAT_R1_UNORM                    = 66,
    DXGI_FORMAT_R9G9B9E5_SHAREDEXP          = 67,
    DXGI_FORMAT_R8G8_B8G8_UNORM             = 68,
    DXGI_FORMAT_G8R8_G8B8_UNORM             = 69,
    DXGI_FORMAT_BC1_TYPELESS                = 70,
    DXGI_FORMAT_BC1_UNORM                   = 71,
    DXGI_FORMAT_BC1_UNORM_SRGB              = 72,
    DXGI_FORMAT_BC2_TYPELESS                = 73,
    DXGI_FORMAT_BC2_UNORM                   = 74,
    DXGI_FORMAT_BC2_UNORM_SRGB              = 75,
    DXGI_FORMAT_BC3_TYPELESS                = 76,
    DXGI_FORMAT_BC3_UNORM                   = 77,
    DXGI_FORMAT_BC3_UNORM_SRGB              = 78,
    DXGI_FORMAT_BC4_TYPELESS                = 79,
    DXGI_FORMAT_BC4_UNORM                   = 80,
    DXGI_FORMAT_BC4_SNORM                   = 81,
    DXGI_FORMAT_BC5_TYPELESS                = 82,
    DXGI_FORMAT_BC5_UNORM                   = 83,
    DXGI_FORMAT_BC5_SNORM                   = 84,
    DXGI_FORMAT_B5G6R5_UNORM                = 85,
    DXGI_FORMAT_B5G5R5A1_UNORM              = 86,
    DXGI_FORMAT_B8G8R8A8_UNORM              = 87,
    DXGI_FORMAT_B8G8R8X8_UNORM              = 88,
    DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM  = 89,
    DXGI_FORMAT_B8G8R8A8_TYPELESS           = 90,
    DXGI_FORMAT_B8G8R8A8_UNORM_SRGB         = 91,
    DXGI_FORMAT_B8G8R8X8_TYPELESS           = 92,
    DXGI_FORMAT_B8G8R8X8_UNORM_SRGB         = 93,
    DXGI_FORMAT_BC6H_TYPELESS               = 94,
    DXGI_FORMAT_BC6H_UF16                   = 95,
    DXGI_FORMAT_BC6H_SF16                   = 96,
    DXGI_FORMAT_BC7_TYPELESS                = 97,
    DXGI_FORMAT_BC7_UNORM                   = 98,
    DXGI_FORMAT_BC7_UNORM_SRGB              = 99,
    DXGI_FORMAT_FORCE_UINT                  = 0xffffffff
} DXGI_FORMAT;
#endif

/* Value for magic header */
#define FOURCC_DDS      (0x20534444)

/* Values for DDS_PIXELFORMAT.dwFlags */
#define DDPF_FOURCC     (0x00000004)

#pragma pack(push,1)

typedef struct {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwFourCC;
    DWORD dwRGBBitCount;
    DWORD dwRBitMask;
    DWORD dwGBitMask;
    DWORD dwBBitMask;
    DWORD dwABitMask;
} DDS_PIXELFORMAT;

typedef struct {
    DWORD dwSize;
    DWORD dwHeaderFlags;
    DWORD dwHeight;
    DWORD dwWidth;
    DWORD dwPitchOrLinearSize;
    DWORD dwDepth; // only if DDS_HEADER_FLAGS_VOLUME is set in dwHeaderFlags
    DWORD dwMipMapCount;
    DWORD dwReserved1[11];
    DDS_PIXELFORMAT ddspf;
    DWORD dwSurfaceFlags;
    DWORD dwCubemapFlags;
    DWORD dwReserved2[3];
} DDS_HEADER;

typedef struct {
    DXGI_FORMAT dxgiFormat;
    UINT resourceDimension;
    UINT miscFlag;
    UINT arraySize;
    UINT reserved;
} DDS_HEADER_DXT10;

/* Values for DDS_PIXELFORMAT.dwFourCC */
#define FMT_DX10                (0x30315844)
#define FMT_DXT1                (0x31545844) /* DXGI_FORMAT_BC1_UNORM */
#define FMT_DXT3                (0x33545844) /* DXGI_FORMAT_BC2_UNORM */
#define FMT_DXT5                (0x35545844) /* DXGI_FORMAT_BC3_UNORM */

/* Values for dwFlags */
#define DDSD_CAPS               0x00000001
#define DDSD_HEIGHT             0x00000002
#define DDSD_WIDTH              0x00000004
#define DDSD_PITCH              0x00000008
#define DDSD_PIXELFORMAT        0x00001000
#define DDSD_MIPMAPCOUNT        0x00020000
#define DDSD_LINEARSIZE         0x00080000
#define DDSD_DEPTH              0x00800000

/* Values for dwCaps */
#define DDSCAPS_COMPLEX         0x00000008
#define DDSCAPS_MIPMAP          0x04000000
#define DDSCAPS_TEXTURE         0x00001000

/* Blocksizes */
#define BLOCKSIZE_DXT1          0x8
#define BLOCKSIZE_DXT3          0x10
#define BLOCKSIZE_DXT5          0x10

#pragma pack(pop)


#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_DDS_H */
#endif /* _WINDOWS_ */


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_FILE_H
#define WINDOWS_FILE_H

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

/* CreateFile.dwShareMode Enums: */
#define FILE_SHARE_DELETE           0x00000004
#define FILE_SHARE_READ             0x00000001
#define FILE_SHARE_WRITE            0x00000002

/* Generic Access Rights: */
#define GENERIC_READ                0x80000000L
#define GENERIC_WRITE               0x40000000L
#define GENERIC_EXECUTE             0x20000000L
#define GENERIC_ALL                 0x10000000L

/* Standard Access Rights: */
#define DELETE                      0x00010000L
#define READ_CONTROL                0x00020000L
#define WRITE_DAC                   0x00040000L
#define WRITE_OWNER                 0x00080000L
#define SYNCHRONIZE                 0x00100000L

#define STANDARD_RIGHTS_REQUIRED    0x000F0000L

#define STANDARD_RIGHTS_READ        READ_CONTROL
#define STANDARD_RIGHTS_WRITE       READ_CONTROL
#define STANDARD_RIGHTS_EXECUTE     READ_CONTROL

#define STANDARD_RIGHTS_ALL         0x001F0000L
#define SPECIFIC_RIGHTS_ALL         0x0000FFFFL

/* Commulated Access Rights: */
#define FILE_READ_DATA              0x0001
#define FILE_LIST_DIRECTORY         0x0001
#define FILE_WRITE_DATA             0x0002
#define FILE_ADD_FILE               0x0002
#define FILE_APPEND_DATA            0x0004
#define FILE_ADD_SUBDIRECTORY       0x0004
#define FILE_CREATE_PIPE_INSTANCE   0x0004
#define FILE_READ_EA                0x0008
#define FILE_WRITE_EA               0x0010
#define FILE_EXECUTE                0x0020
#define FILE_TRAVERSE               0x0020
#define FILE_DELETE_CHILD           0x0040
#define FILE_READ_ATTRIBUTES        0x0080
#define FILE_WRITE_ATTRIBUTES       0x0100
#define FILE_ALL_ACCESS             \
    (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)

#define FILE_GENERIC_READ           \
    (STANDARD_RIGHTS_READ | \
     FILE_READ_DATA | \
     FILE_READ_ATTRIBUTES | \
     FILE_READ_EA | \
     SYNCHRONIZE)

#define FILE_GENERIC_WRITE          \
    (STANDARD_RIGHTS_WRITE | \
     FILE_WRITE_DATA | \
     FILE_WRITE_ATTRIBUTES | \
     FILE_WRITE_EA | \
     FILE_APPEND_DATA | \
     SYNCHRONIZE)

#define FILE_GENERIC_EXECUTE        \
    (STANDARD_RIGHTS_EXECUTE | \
     FILE_READ_ATTRIBUTES | \
     FILE_EXECUTE | \
     SYNCHRONIZE)

/* Creation Disposition: */
#define CREATE_ALWAYS               2
#define CREATE_NEW                  1
#define OPEN_ALWAYS                 4
#define OPEN_EXISTING               3
#define TRUNCATE_EXISTING           5

/* File Attributes: */
#define INVALID_FILE_ATTRIBUTES         0xffffffff
#define FILE_ATTRIBUTE_HIDDEN           0x2
#define FILE_ATTRIBUTE_NORMAL           0x80
#define FILE_ATTRIBUTE_DIRECTORY        0x10
#define FILE_ATTRIBUTE_TEMPORARY        0x100
#define FILE_ATTRIBUTE_REPARSE_POINT    0x400

/* File Offsets: */
#define FILE_BEGIN                  0
#define FILE_CURRENT                1
#define FILE_END                    2

/* File Mapping: */
#define SECTION_QUERY                   0x0001
#define SECTION_MAP_WRITE               0x0002
#define SECTION_MAP_READ                0x0004
#define SECTION_MAP_EXECUTE             0x0008
#define SECTION_EXTEND_SIZE             0x0010
#define SECTION_MAP_EXECUTE_EXPLICIT    0x0020
#define SECTION_ALL_ACCESS \
    (STANDARD_RIGHTS_REQUIRED |\
     SECTION_QUERY |\
     SECTION_MAP_WRITE |\
     SECTION_MAP_READ |\
     SECTION_MAP_EXECUTE |\
     SECTION_EXTEND_SIZE)

#define FILE_MAP_COPY                   SECTION_QUERY
#define FILE_MAP_WRITE                  SECTION_MAP_WRITE
#define FILE_MAP_READ                   SECTION_MAP_READ
#define FILE_MAP_ALL_ACCESS             SECTION_ALL_ACCESS
#define FILE_MAP_EXECUTE                SECTION_MAP_EXECUTE_EXPLICIT

#define PAGE_EXECUTE_READ               0x20
#define PAGE_EXECUTE_READWRITE          0x40
#define PAGE_EXECUTE_WRITECOPY          0x80
#define PAGE_READONLY                   0x02
#define PAGE_READWRITE                  0x04
#define PAGE_WRITECOPY                  0x08

/* File Change Notifications: */
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100

/* File Type: */
#define FILE_TYPE_UNKNOWN               0x0000
#define FILE_TYPE_DISK                  0x0001
#define FILE_TYPE_CHAR                  0x0002
#define FILE_TYPE_PIPE                  0x0003
#define FILE_TYPE_REMOTE                0x8000

/* Move Flags: */
#define MOVEFILE_COPY_ALLOWED           0x2
#define MOVEFILE_REPLACE_EXISTING       0x1

typedef DWORD SECURITY_INFORMATION, *PSECURITY_INFORMATION;
typedef HANDLE PSECURITY_DESCRIPTOR;


/* ========================================================================== */
/* Structures: */
typedef struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union {
        struct {
            DWORD Offset;
            DWORD OffsetHigh;
        };
        PVOID Pointer;
    };
    HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;

/* File Iteration: */
typedef struct _WIN32_FIND_DATAA {
    DWORD    dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD    nFileSizeHigh;
    DWORD    nFileSizeLow;
    DWORD    dwReserved0;
    DWORD    dwReserved1;
    CHAR     cFileName[MAX_PATH];
    CHAR     cAlternateFileName[14];
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
typedef struct _WIN32_FIND_DATAW {
    DWORD    dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD    nFileSizeHigh;
    DWORD    nFileSizeLow;
    DWORD    dwReserved0;
    DWORD    dwReserved1;
    WCHAR    cFileName[MAX_PATH];
    WCHAR    cAlternateFileName[14];
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;


/* ========================================================================== */
/* File I/O Functions: */
HANDLE WINAPI CreateFileA(
        LPCSTR lpFileName,
        DWORD dwDesiredAccess,
        DWORD dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD dwCreationDisposition,
        DWORD dwFlagsAndAttributes,
        HANDLE hTemplateFile);
HANDLE WINAPI CreateFileW(
        LPCWSTR lpFileName,
        DWORD dwDesiredAccess,
        DWORD dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD dwCreationDisposition,
        DWORD dwFlagsAndAttributes,
        HANDLE hTemplateFile);

BOOL WINAPI WriteFile(
        HANDLE hFile,
        LPCVOID lpBuffer,
        DWORD nNumberOfBytesToWrite,
        LPDWORD lpNumberOfBytesWritten,
        LPOVERLAPPED lpOverlapped);
BOOL WINAPI ReadFile(
        HANDLE hFile,
        LPVOID lpBuffer,
        DWORD nNumberOfBytesToRead,
        LPDWORD lpNumberOfBytesRead,
        LPOVERLAPPED lpOverlapped);
DWORD WINAPI SetFilePointer(
        HANDLE hFile,
        LONG lDistanceToMove,
        PLONG lpDistanceToMoveHigh,
        DWORD dwMoveMethod);
BOOL WINAPI SetFilePointerEx(
        HANDLE hFile,
        LARGE_INTEGER liDistanceToMove,
        PLARGE_INTEGER lpNewFilePointer,
        DWORD dwMoveMethod);
BOOL WINAPI FlushFileBuffers(
        HANDLE hFile);
DWORD WINAPI GetModuleFileNameA(
        HMODULE hModule,
        LPSTR   lpFileName,
        DWORD   nSize);
DWORD WINAPI GetModuleFileNameW(
        HMODULE hModule,
        LPWSTR  lpFileName,
        DWORD   nSize);
DWORD WINAPI GetModuleFileNameExA(
        HANDLE  hProcess,
        HMODULE hModule,
        LPSTR   lpFileName,
        DWORD   nSize);
DWORD WINAPI GetModuleFileNameExW(
        HANDLE  hProcess,
        HMODULE hModule,
        LPWSTR  lpFileName,
        DWORD   nSize);
HANDLE WINAPI OpenFileMappingA(
        DWORD   dwDesiredAccess,
        BOOL    bInheritHandle,
        LPCSTR  lpName);
HANDLE WINAPI OpenFileMappingW(
        DWORD   dwDesiredAccess,
        BOOL    bInheritHandle,
        LPCWSTR lpName);
LPVOID WINAPI MapViewOfFile(
        HANDLE  hFileMappingObject,
        DWORD   dwDesiredAccess,
        DWORD   dwFileOffsetHigh,
        DWORD   dwFileOffsetLow,
        SIZE_T  dwNumberOfBytesToMap);
LPVOID WINAPI MapViewOfFileEx(
        HANDLE  hFileMappingObject,
        DWORD   dwDesiredAccess,
        DWORD   dwFileOffsetHigh,
        DWORD   dwFileOffsetLow,
        SIZE_T  dwNumberOfBytesToMap,
        LPVOID  lpBaseAddress);
HANDLE WINAPI CreateFileMappingA(
        HANDLE                  hFile,
        LPSECURITY_ATTRIBUTES   lpAttributes,
        DWORD                   flProtect,
        DWORD                   dwMaximumSizeHigh,
        DWORD                   dwMaximumSizeLow,
        LPCSTR                  lpName);
HANDLE WINAPI CreateFileMappingW(
        HANDLE                  hFile,
        LPSECURITY_ATTRIBUTES   lpAttributes,
        DWORD                   flProtect,
        DWORD                   dwMaximumSizeHigh,
        DWORD                   dwMaximumSizeLow,
        LPCWSTR                 lpName);
BOOL WINAPI UnmapViewOfFile(
        LPCVOID lpBaseAddress);
DWORD WINAPI GetFileAttributesA(
        LPCSTR lpFileName);
DWORD WINAPI GetFileAttributesW(
        LPCWSTR lpFileName);

typedef enum _GET_FILEEX_INFO_LEVELS {
    GetFileExInfoStandard,
    GetFileExMaxInfoLevel
} GET_FILEEX_INFO_LEVELS;
typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
} WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;
BOOL WINAPI GetFileAttributesExA(
    LPCSTR lpFileName,
    GET_FILEEX_INFO_LEVELS fInfoLevelId,
    LPVOID lpFileInformation);
BOOL WINAPI GetFileAttributesExW(
    LPCWSTR lpFileName,
    GET_FILEEX_INFO_LEVELS fInfoLevelId,
    LPVOID lpFileInformation);

BOOL WINAPI GetFileTime(
        HANDLE  hFile,
        LPFILETIME lpCreationTime,
        LPFILETIME lpLastAccessTime,
        LPFILETIME lpLastWriteTime);
BOOL WINAPI SetEndOfFile(
        HANDLE hFile);
BOOL WINAPI CreateDirectoryA(
        LPCSTR      lpPathName,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes);
BOOL WINAPI CreateDirectoryW(
        LPCWSTR     lpPathName,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes);
BOOL WINAPI CopyFileA(
        LPCSTR  lpExistingFileName,
        LPCSTR  lpNewFileName,
        BOOL    bFailIfExists);
BOOL WINAPI CopyFileW(
        LPCWSTR lpExistingFileName,
        LPCWSTR lpNewFileName,
        BOOL    bFailIfExists);
BOOL WINAPI DeleteFileA(
        LPCSTR  lpFileName);
BOOL WINAPI DeleteFileW(
        LPCWSTR lpFileName);
BOOL WINAPI MoveFileA(
        LPCSTR  lpExistingFileName,
        LPCSTR  lpNewFileName);
BOOL WINAPI MoveFileW(
        LPCWSTR lpExistingFileName,
        LPCWSTR lpNewFileName);
BOOL WINAPI MoveFileExA(
        LPCSTR  lpExistingFileName,
        LPCSTR  lpNewFileName,
        DWORD   dwFlags);
BOOL WINAPI MoveFileExW(
        LPCWSTR lpExistingFileName,
        LPCWSTR lpNewFileName,
        DWORD   dwFlags);
BOOL WINAPI RemoveDirectoryA(
        LPCSTR  lpPathName);
BOOL WINAPI RemoveDirectoryW(
        LPCWSTR lpPathName);
BOOL WINAPI GetFileSizeEx(
        HANDLE  hFile,
        PLARGE_INTEGER lpFileSize);
BOOL WINAPI FlushViewOfFile(
        LPCVOID lpBaseAddress,
        SIZE_T  dwNumberOfBytesToFlush);


/* ========================================================================== */
/* File Iteration Functions: */
HANDLE WINAPI FindFirstFileA(
        LPCSTR lpFileName,
        LPWIN32_FIND_DATAA lpFindFileData);
HANDLE WINAPI FindFirstFileW(
        LPCWSTR lpFileName,
        LPWIN32_FIND_DATAW lpFindFileData);
BOOL WINAPI FindNextFileA(
        HANDLE hFindFile,
        LPWIN32_FIND_DATAA lpFindFileData);
BOOL WINAPI FindNextFileW(
        HANDLE hFindFile,
        LPWIN32_FIND_DATAW lpFindFileData);
BOOL WINAPI FindClose(
        HANDLE hFindFile);

/* ========================================================================== */
/* File Change Functions: */
HANDLE WINAPI FindFirstChangeNotificationA(
        LPCSTR  lpPathName,
        BOOL    bWatchSubtree,
        DWORD   dwNotifyFilter);
HANDLE WINAPI FindFirstChangeNotificationW(
        LPCWSTR lpPathName,
        BOOL    bWatchSubtree,
        DWORD   dwNotifyFilter);
BOOL WINAPI FindNextChangeNotification(
        HANDLE  hChangeHandle);
BOOL WINAPI FindCloseChangeNotification(
        HANDLE  hChangeHandle);

/* ========================================================================== */
/* File Misc: */
DWORD WINAPI GetFileType(
        HANDLE hFile);

/* ========================================================================== */
/* Temp File: */
UINT WINAPI GetTempFileNameW(
    LPCWSTR lpPathName,
    LPCWSTR lpPrefixString,
    UINT    uUnique,
    LPWSTR  lpTempFileName
);

DWORD WINAPI GetTempPathW(
    DWORD  nBufferLength,
    LPWSTR lpBuffer
);

/* ========================================================================== */
/* File Security: */
BOOL WINAPI GetFileSecurityA(
    LPCSTR               lpFileName,
    SECURITY_INFORMATION RequestedInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    DWORD                nLength,
    LPDWORD              lpnLengthNeeded);
BOOL WINAPI GetFileSecurityW(
    LPCWSTR              lpFileName,
    SECURITY_INFORMATION RequestedInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    DWORD                nLength,
    LPDWORD              lpnLengthNeeded);


#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_FILE_H */
#endif /* _WINDOWS_ */


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_GDI_H
#define WINDOWS_GDI_H

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

/* GDI: */
#define BLACK_BRUSH                 4


/* Icons / Cursor: */
#define MAKEINTRESOURCE(res)        ((ULONG_PTR)(USHORT)res)
#define IDI_APPLICATION             MAKEINTRESOURCE(32512)
#define IDC_ARROW                   MAKEINTRESOURCE(32512)


/* ========================================================================= */
/* Functions                                                                 */
HCURSOR WINAPI LoadCursorA(
        HINSTANCE hInstance,
        LPCSTR  lpCursorName);
HCURSOR WINAPI LoadCursorW(
        HINSTANCE hInstance,
        LPCWSTR lpCursorName);
HICON WINAPI LoadIconA(
        HINSTANCE hInstance,
        LPCSTR  lpIconName);
HICON WINAPI LoadIconW(
        HINSTANCE hInstance,
        LPCWSTR lpIconName);
HGDIOBJ WINAPI GetStockObject(
        int     fnObject);
HCURSOR WINAPI SetCursor(
        HCURSOR hCursor);


#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_GDI_H */
#endif /* _WINDOWS_ */


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_IO_H
#define WINDOWS_IO_H

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

/* GetStdHandle: */
#define STD_INPUT_HANDLE        ((DWORD)-10)
#define STD_OUTPUT_HANDLE       ((DWORD)-11)
#define STD_ERROR_HANDLE        ((DWORD)-12)
#define INVALID_HANDLE_VALUE    ((HANDLE)(LONG_PTR)-1)
#define ATTACH_PARENT_PROCESS   ((DWORD)-1)

#define HANDLE_FLAG_INHERIT             0x00000001
#define HANDLE_FLAG_PROTECT_FROM_CLOSE  0x00000002

/* Console Colors: */
#define FOREGROUND_BLUE         0x0001
#define FOREGROUND_GREEN        0x0002
#define FOREGROUND_RED          0x0004
#define FOREGROUND_INTENSITY    0x0008
#define BACKGROUND_BLUE         0x0010
#define BACKGROUND_GREEN        0x0020
#define BACKGROUND_RED          0x0040
#define BACKGROUND_INTENSITY    0x0080

/* Console Handler */
#define CTRL_C_EVENT            0x0
#define CTRL_BREAK_EVENT        0x1
#define CTRL_CLOSE_EVENT        0x2
#define CTRL_LOGOFF_EVENT       0x5
#define CTRL_SHUTDOWN_EVENT     0x6

/* HeapAlloc, HeapReAlloc, etc: */
#define HEAP_NO_SERIALIZE           0x00000001
#define HEAP_ZERO_MEMORY            0x00000008
#define HEAP_REALLOC_IN_PLACE_ONLY  0x00000010

/* Heap / Memory: */
typedef enum _HEAP_INFORMATION_CLASS {
    HeapCompatibilityInformation = 0,
    HeapEneableTerminationOnCorruption = 1,
    HeapOptimizeResources = 3
} HEAP_INFORMATION_CLASS;

/* VirtualAlloc.flAllocationType: */
#define MEM_COMMIT                  0x00001000
#define MEM_RESERVE                 0x00002000
#define MEM_RESET                   0x00080000
#define MEM_RESET_UNDO              0x01000000
#define MEM_LARGE_PAGES             0x20000000
#define MEM_PHYSICAL                0x00400000
#define MEM_TOP_DOWN                0x00100000
#define MEM_WRITE_WATCH             0x00200000

/* VirtualAlloc.flProtect: */
#define PAGE_EXECUTE                0x10
#define PAGE_EXECUTE_READ           0x20
#define PAGE_EXECUTE_READWRITE      0x40
#define PAGE_EXECUTE_WRITECOPY      0x80
#define PAGE_NOACCESS               0x01
#define PAGE_READONLY               0x02
#define PAGE_READWRITE              0x04
#define PAGE_WRITECOPY              0x08
#define PAGE_TARGETS_INVALID        0x40000000
#define PAGE_TARGETS_NO_UPDATE      0x40000000
#define PAGE_GUARD                  0x100
#define PAGE_NOCACHE                0x200
#define PAGE_WRITECOMBINE           0x400

/* VirtualFree.dwFreeType: */
#define MEM_DECOMMIT                0x4000
#define MEM_RELEASE                 0x8000

/* VirtualQuery State and Type: */
#define MEM_FREE                    0x10000
#define MEM_IMAGE                   0x1000000
#define MEM_MAPPED                  0x40000
#define MEM_PRIVATE                 0x20000


/* ========================================================================== */
/* Structures:                                                                */
typedef struct _COORD {
    SHORT       X;
    SHORT       Y;
} COORD, *PCOORD;

typedef struct _SMALL_RECT {
    SHORT       Left;
    SHORT       Top;
    SHORT       Right;
    SHORT       Bottom;
} SMALL_RECT;

typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
    COORD       dwSize;
    COORD       dwCursorPosition;
    WORD        wAttributes;
    SMALL_RECT  srWindow;
    COORD       dwMaximumWindowSize;
} CONSOLE_SCREEN_BUFFER_INFO, *PCONSOLE_SCREEN_BUFFER_INFO;

typedef BOOL (WINAPI *PHANDLER_ROUTINE)(DWORD dwCtrlType);

typedef struct _MEMORY_BASIC_INFORMATION32 {
    DWORD       BaseAddress;
    DWORD       AllocationBase;
    DWORD       AllocationProtect;
    DWORD       RegionSize;
    DWORD       State;
    DWORD       Protect;
    DWORD       Type;
} MEMORY_BASIC_INFORMATION32, *PMEMORY_BASIC_INFORMATION32;

typedef struct __declspec(align(16)) _MEMORY_BASIC_INFORMATION64 {
    ULONGLONG   BaseAddress;
    ULONGLONG   AllocationBase;
    DWORD       AllocationProtect;
    DWORD       __alignment1;
    ULONGLONG   RegionSize;
    DWORD       State;
    DWORD       Protect;
    DWORD       Type;
    DWORD       __alignment2;
} MEMORY_BASIC_INFORMATION64, *PMEMORY_BASIC_INFORMATION64;
#if defined(_WIN64)
typedef MEMORY_BASIC_INFORMATION64  MEMORY_BASIC_INFORMATION;
typedef PMEMORY_BASIC_INFORMATION64 PMEMORY_BASIC_INFORMATION;
#else
typedef MEMORY_BASIC_INFORMATION32  MEMORY_BASIC_INFORMATION;
typedef PMEMORY_BASIC_INFORMATION32 PMEMORY_BASIC_INFORMATION;
#endif


/* ========================================================================== */
/* I/O Functions: */
HANDLE WINAPI GetStdHandle(
        DWORD nStdHandle);
BOOL WINAPI GetConsoleScreenBufferInfo(
        HANDLE hConsoleOutput,
        PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo);
BOOL WINAPI SetConsoleTextAttribute(
        HANDLE hConsoleOutput,
        WORD wAttributes);
BOOL WINAPI CloseHandle(
        HANDLE hObject);
BOOL WINAPI SetHandleInformation(
        HANDLE hObject,
        DWORD  dwMask,
        DWORD  dwFlags);
BOOL WINAPI DuplicateHandle(
        HANDLE hSourceProcessHandle,
        HANDLE hSourceHandle,
        HANDLE hTargetProcessHandle,
        LPHANDLE lpTargetHandle,
        DWORD dwDesiredAccess,
        BOOL bInheritHandle,
        DWORD dwOptions);


LPSTR WINAPI GetCommandLineA(void);
LPWSTR WINAPI GetCommandLineW(void);
#ifdef UNICODE
#define GetCommandLine GetCommandLineW
#else
#define GetCommandLine GetCommandLineA
#endif

/* ========================================================================== */
/* Console Functions: */
BOOL WINAPI AllocConsole(void);
BOOL WINAPI FreeConsole(void);
BOOL WINAPI AttachConsole(
        DWORD dwProcessId);
BOOL WINAPI WriteConsoleA(
        HANDLE hConsoleOutput,
        const void *lpBuffer,
        DWORD nNumberOfCharsToWrite,
        LPDWORD lpNumberOfCHarsWritten,
        LPVOID lpReserved);
BOOL WINAPI WriteConsoleW(
        HANDLE hConsoleOutput,
        const void *lpBuffer,
        DWORD nNumberOfCharsToWrite,
        LPDWORD lpNumberOfCHarsWritten,
        LPVOID lpReserved);
BOOL WINAPI SetConsoleCtrlHandler(
        PHANDLER_ROUTINE HandlerRoutine,
        BOOL Add);
HWND WINAPI GetConsoleWindow(void);
BOOL WINAPI SetConsoleOutputCP(
    UINT wCodePageID);
UINT WINAPI GetConsoleOutputCP(void);

/* ========================================================================== */
/* Heap Functions: */
HANDLE WINAPI GetProcessHeap(void);
LPVOID WINAPI HeapAlloc(
        HANDLE hHeap,
        DWORD dwFlags,
        SIZE_T dwBytes);
LPVOID WINAPI HeapReAlloc(
        HANDLE hHeap,
        DWORD dwFlags,
        LPVOID lpMem,
        SIZE_T dwBytes);
BOOL WINAPI HeapFree(
        HANDLE hHeap,
        DWORD dwFlags,
        LPVOID lpMem);
BOOL WINAPI HeapsetInformation(
        HANDLE HeapHandle,
        HEAP_INFORMATION_CLASS HeapInformationClass,
        PVOID HeapInformation,
        SIZE_T HeapInformationLength);
LPVOID WINAPI VirtualAlloc(
        LPVOID lpAddress,
        SIZE_T dwSize,
        DWORD flAllocationType,
        DWORD flProtect);
SIZE_T WINAPI VirtualQuery(
        LPCVOID lpAddress,
        PMEMORY_BASIC_INFORMATION lpBuffer,
        SIZE_T dwLength);
BOOL WINAPI VirtualFree(
        LPVOID lpAddress,
        SIZE_T dwSize,
        DWORD dwFreeType);
BOOL WINAPI VirtualProtect(
        LPVOID lpAddress,
        SIZE_T dwSize,
        DWORD flNewProtect,
        PDWORD lpflOldProtect);
BOOL WINAPI FlushInstructionCache(
        HANDLE hProcess,
        LPCVOID lpBaseAddress,
        SIZE_T dwSize);


/* ========================================================================== */
/* Pipe Functions: */
BOOL WINAPI CreatePipe(
        PHANDLE hReadPipe,
        PHANDLE hWritePipe,
        LPSECURITY_ATTRIBUTES lpPipeAttributes,
        DWORD nSize);
BOOL WINAPI PeekNamedPipe(
        HANDLE  hNamedPipe,
        LPVOID  lpBuffer,
        DWORD   nBufferSize,
        LPDWORD lpBytesRead,
        LPDWORD lpTotalBytesAvail,
        LPDWORD lpBytesLeftThisMessage);

/* ========================================================================== */
/* Path Functions: */
DWORD WINAPI GetFullPathNameA(
        LPCSTR lpFileName,
        DWORD   nBufferLength,
        LPSTR  lpBuffer,
        LPSTR  *lpFilePart);
DWORD WINAPI GetFullPathNameW(
        LPCWSTR lpFileName,
        DWORD   nBufferLength,
        LPWSTR  lpBuffer,
        LPWSTR  *lpFilePart);
BOOL WINAPI SetCurrentDirectoryA(
        LPCSTR lpPathName);
BOOL WINAPI SetCurrentDirectoryW(
        LPCWSTR lpPathName);
DWORD WINAPI GetCurrentDirectoryA(
        DWORD  nBufferLength,
        LPSTR lpBuffer);
DWORD WINAPI GetCurrentDirectoryW(
        DWORD  nBufferLength,
        LPWSTR lpBuffer);

#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_IO_H */
#endif /* _WINDOWS_ */


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_MISC_H
#define WINDOWS_MISC_H

/* Disable all warnings */
#if defined(_MSC_VER)
    #pragma warning(push, 0)
#endif

#include <stdarg.h>

#ifndef WINDOWS_BASE_H
#include "windows_base.h"
#endif
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

/* Format: */
#define FORMAT_MESSAGE_ALLOCATE_BUFFER  0x00000100
#define FORMAT_MESSAGE_ARGUMENT_ARRAY   0x00002000
#define FORMAT_MESSAGE_FROM_SYSTEM      0x00001000
#define FORMAT_MESSAGE_IGNORE_INSERTS   0x00000200
#define FORMAT_MESSAGE_FROM_HMODULE     0x00000800
#define FORMAT_MESSAGE_FROM_STRING      0x00000400

/* Language ID: */
#define MAKELANGID(p, s)                ((((WORD)(s)) << 10) | (WORD  )(p))
#define PRIMARYLANGID(lgid)             ((WORD)(lgid) & 0x3ff)
#define SUBLANGID(lgid)                 ((WORD)(lgid) >> 10)

#define LANG_NEUTRAL                    0x00
#define LANG_INVARIANT                  0x7f
#define LANG_ENGLISH                    0x09
#define LANG_GERMAN                     0x07

#define SUBLANG_NEUTRAL                 0x00
#define SUBLANG_DEFAULT                 0x01
#define SUBLANG_SYS_DEFAULT             0x02
#define SUBLANG_CUSTOM_DEFAULT          0x03
#define SUBLANG_CUSTOM_UNSPECIFIED      0x04
#define SUBLANG_UI_CUSTOM_DEFAULT       0x05
#define SUBLANG_ENGLISH_US              0x01
#define SUBLANG_ENGLISH_UK              0x02
#define SUBLANG_GERMAN                  0x01


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
#ifdef WIN32_BYTESWAP_MACROS
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
#else
unsigned short   __cdecl _byteswap_ushort(unsigned short   Number);
unsigned long    __cdecl _byteswap_ulong (unsigned long    Number);
unsigned __int64 __cdecl _byteswap_uint64(unsigned __int64 Number);
#endif

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
LONG WINAPI CompareFileTime(
  const FILETIME *      lpFileTime1,
  const FILETIME *      lpFileTime2);
void WINAPI GetSystemTimeAsFileTime(
        LPFILETIME lpSystemTimeAsFileTime);
BOOL WINAPI SystemTimeToTzSpecificLocalTime(
        LPTIME_ZONE_INFORMATION lpTimeZone,
        LPSYSTEMTIME lpUniversalTime,
        LPSYSTEMTIME lpLocalTime);
DWORD timeGetTime(void);

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
DWORD WINAPI FormatMessageA(
        DWORD   dwFlags,
        LPCVOID lpSource,
        DWORD   dwMessageId,
        DWORD   dwLanguageId,
        LPSTR   lpBuffer,
        DWORD   nSize,
        va_list *Arguments);
DWORD WINAPI FormatMessageW(
        DWORD   dwFlags,
        LPCVOID lpSource,
        DWORD   dwMessageId,
        DWORD   dwLanguageId,
        LPWSTR  lpBuffer,
        DWORD   nSize,
        va_list *Arguments);


/* ========================================================================== */
/* Timer Functions: */
DWORD WINAPI GetTickCount(void);
ULONGLONG WINAPI GetTickCount64(void);
BOOL WINAPI QueryPerformanceFrequency(
        LARGE_INTEGER *lpFrequency);
BOOL WINAPI QueryPerformanceCounter(
        LARGE_INTEGER *lpPerformanceCount);


/* ========================================================================== */
/* Multi Media Timer:                                                         */
#define TIMERR_NOERROR        (0)                  /* no error */
#define TIMERR_NOCANDO        (TIMERR_BASE+1)      /* request not completed */
#define TIMERR_STRUCT         (TIMERR_BASE+33)     /* time struct size */

typedef struct timecaps_tag {
    UINT    wPeriodMin;     /* minimum period supported  */
    UINT    wPeriodMax;     /* maximum period supported  */
} TIMECAPS, *PTIMECAPS, *NPTIMECAPS, *LPTIMECAPS;
typedef UINT MMRESULT;

MMRESULT WINAPI timeGetDevCaps(LPTIMECAPS ptc, UINT cbtc);
MMRESULT WINAPI timeBeginPeriod(UINT uPeriod);
MMRESULT WINAPI timeEndPeriod(UINT uPeriod);


/* ========================================================================== */
/* DLL Functions: */
HMODULE WINAPI LoadLibraryA(
        LPCSTR lpFileName);
HMODULE WINAPI LoadLibraryW(
        LPCWSTR lpFileName);
HMODULE WINAPI LoadLibraryExA(
        LPCSTR lpLibFileName,
        HANDLE hFile,
        DWORD  dwFlags);
HMODULE WINAPI LoadLibraryExW(
        LPCWSTR lpLibFileName,
        HANDLE  hFile,
        DWORD   dwFlags);
FARPROC WINAPI GetProcAddress(
        HMODULE hModule,
        LPCSTR lProcName);
PROC WINAPI wglGetProcAddress(
        LPCSTR lpszProc);
BOOL WINAPI FreeLibrary(
        HMODULE hModule);

/* ========================================================================== */
/* Libc Replacements: */
PVOID SecureZeroMemory(
        PVOID  ptr,
        SIZE_T cnt);

#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_MISC_H */
#endif /* _WINDOWS_ */


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_PROCESS_H
#define WINDOWS_PROCESS_H

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

/* Originally defined in threads.h */
#ifndef INFINITE
#define INFINITE                0xffffffff
#endif

/* Originally defined in file.h */
#ifndef STANDARD_RIGHTS_REQUIRED
#define STANDARD_RIGHTS_REQUIRED 0x000F0000L
#endif
#ifndef SYNCHRONIZE
#define SYNCHRONIZE                 0x00100000L
#endif

/* Process Access Rights: */
#define PROCESS_DUP_HANDLE          (0x0040)
#define PROCESS_QUERY_INFORMATION   (0x0400)
#define PROCESS_SUSPEND_RESUME      (0x0800)
#define PROCESS_TERMINATE           (0x0001)
#define PROCESS_VM_READ             (0x0010)
#define PROCESS_ALL_ACCESS          \
    (STANDARD_RIGHTS_REQUIRED | \
     SYNCHRONIZE | \
     0xFFFF)

/* Tokens: */
#define TOKEN_ASSIGN_PRIMARY        (0x0001)
#define TOKEN_DUPLICATE             (0x0002)
#define TOKEN_IMPERSONATE           (0x0004)
#define TOKEN_QUERY                 (0x0008)
#define TOKEN_QUERY_SOURCE          (0x0010)
#define TOKEN_ADJUST_PRIVILEGES     (0x0020)
#define TOKEN_ADJUST_GROUPS         (0x0040)
#define TOKEN_ADJUST_DEFAULT        (0x0080)
#define TOKEN_ADJUST_SESSIONID      (0x0100)

#define TOKEN_ALL_ACCESS_P (STANDARD_RIGHTS_REQUIRED  | \
                            TOKEN_ASSIGN_PRIMARY      | \
                            TOKEN_DUPLICATE           | \
                            TOKEN_IMPERSONATE         | \
                            TOKEN_QUERY               | \
                            TOKEN_QUERY_SOURCE        | \
                            TOKEN_ADJUST_PRIVILEGES   | \
                            TOKEN_ADJUST_GROUPS       | \
                            TOKEN_ADJUST_DEFAULT)

#define SE_PRIVILEGE_ENABLED_BY_DEFAULT (0x00000001L)
#define SE_PRIVILEGE_ENABLED            (0x00000002L)
#define SE_PRIVILEGE_REMOVED            (0X00000004L)
#define SE_PRIVILEGE_USED_FOR_ACCESS    (0x80000000L)

/* Status */
#define STATUS_WAIT_0                   ((DWORD)0x00000000L)
#define STATUS_TIMEOUT                  ((DWORD)0x00000102L)
#define STATUS_PENDING                  ((DWORD)0x00000103L)
#define STILL_ACTIVE                    STATUS_PENDING

/* Startupinfo */
#define STARTF_USESHOWWINDOW            0x00000001
#define STARTF_USESIZE                  0x00000002
#define STARTF_USEPOSITION              0x00000004
#define STARTF_USECOUNTCHARS            0x00000008
#define STARTF_USEFILLATTRIBUTE         0x00000010
#define STARTF_RUNFULLSCREEN            0x00000020
#define STARTF_FORCEONFEEDBACK          0x00000040
#define STARTF_FORCEOFFFEEDBACK         0x00000080
#define STARTF_USESTDHANDLES            0x00000100


/* Priority Classes / CreateProcess: */
#define NORMAL_PRIORITY_CLASS       0x00000020

/* Job Objects: */
#define JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE 0x00002000
typedef enum _JOBOBJECTINFOCLASS {
    JobObjectBasicAccountingInformation = 1,
    JobObjectBasicLimitInformation,
    JobObjectBasicProcessIdList,
    JobObjectBasicUIRestrictions,
    JobObjectSecurityLimitInformation,  // deprecated
    JobObjectEndOfJobTimeInformation,
    JobObjectAssociateCompletionPortInformation,
    JobObjectBasicAndIoAccountingInformation,
    JobObjectExtendedLimitInformation,
    JobObjectJobSetInformation,
    JobObjectGroupInformation,
    JobObjectNotificationLimitInformation,
    JobObjectLimitViolationInformation,
    JobObjectGroupInformationEx,
    JobObjectCpuRateControlInformation,
    JobObjectCompletionFilter,
    JobObjectCompletionCounter,
    JobObjectReserved1Information = 18,
    JobObjectReserved2Information,
    JobObjectReserved3Information,
    JobObjectReserved4Information,
    JobObjectReserved5Information,
    JobObjectReserved6Information,
    JobObjectReserved7Information,
    JobObjectReserved8Information,
    JobObjectReserved9Information,
    MaxJobObjectInfoClass
} JOBOBJECTINFOCLASS;

/* Process: */
typedef struct _STARTUPINFOA {
    DWORD  cb;
    LPSTR  lpReserved;
    LPSTR  lpDesktop;
    LPSTR  lpTitle;
    DWORD  dwX;
    DWORD  dwY;
    DWORD  dwXSize;
    DWORD  dwYSize;
    DWORD  dwXCountChars;
    DWORD  dwYCountChars;
    DWORD  dwFillAttribute;
    DWORD  dwFlags;
    WORD   wShowWindow;
    WORD   cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;
typedef struct _STARTUPINFOW {
    DWORD  cb;
    LPWSTR lpReserved;
    LPWSTR lpDesktop;
    LPWSTR lpTitle;
    DWORD  dwX;
    DWORD  dwY;
    DWORD  dwXSize;
    DWORD  dwYSize;
    DWORD  dwXCountChars;
    DWORD  dwYCountChars;
    DWORD  dwFillAttribute;
    DWORD  dwFlags;
    WORD   wShowWindow;
    WORD   cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
} STARTUPINFOW, *LPSTARTUPINFOW;

typedef struct _PROC_THREAD_ATTRIBUTE_LIST
*PPROC_THREAD_ATTRIBUTE_LIST, *LPPROC_THREAD_ATTRIBUTE_LIST;
typedef struct _STARTUPINFOEXA {
    STARTUPINFOA                    StartupInfo;
    PPROC_THREAD_ATTRIBUTE_LIST     lpAttributeList;
} STARTUPINFOEXA, *LPSTARTUPINFOEXA;
typedef struct _STARTUPINFOEXW {
    STARTUPINFOW                    StartupInfo;
    PPROC_THREAD_ATTRIBUTE_LIST     lpAttributeList;
} STARTUPINFOEXW, *LPSTARTUPINFOEXW;
typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD  dwProcessId;
    DWORD  dwThreadId;
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION;

/* Job Objects: */
typedef struct _JOBOBJECT_BASIC_LIMIT_INFORMATION {
    LARGE_INTEGER PerProcessUserTimeLimit;
    LARGE_INTEGER PerJobUserTimeLimit;
    DWORD         LimitFlags;
    SIZE_T        MinimumWorkingSetSize;
    SIZE_T        MaximumWorkingSetSize;
    DWORD         ActiveProcessLimit;
    ULONG_PTR     Affinity;
    DWORD         PriorityClass;
    DWORD         SchedulingClass;
} JOBOBJECT_BASIC_LIMIT_INFORMATION, *PJOBOBJECT_BASIC_LIMIT_INFORMATION;

typedef struct _IO_COUNTERS {
    ULONGLONG ReadOperationCount;
    ULONGLONG WriteOperationCount;
    ULONGLONG OtherOperationCount;
    ULONGLONG ReadTransferCount;
    ULONGLONG WriteTransferCount;
    ULONGLONG OtherTransferCount;
} IO_COUNTERS, *PIO_COUNTERS;

typedef struct _JOBOBJECT_EXTENDED_LIMIT_INFORMATION {
    JOBOBJECT_BASIC_LIMIT_INFORMATION BasicLimitInformation;
    IO_COUNTERS                       IoInfo;
    SIZE_T                            ProcessMemoryLimit;
    SIZE_T                            JobMemoryLimit;
    SIZE_T                            PeakProcessMemoryUsed;
    SIZE_T                            PeakJobMemoryUsed;
} JOBOBJECT_EXTENDED_LIMIT_INFORMATION, *PJOBOBJECT_EXTENDED_LIMIT_INFORMATION;


/* ========================================================================== */
/* Process: */
HANDLE WINAPI GetCurrentProcess(void);
DWORD WINAPI GetCurrentProcessId(void);
void WINAPI ExitProcess(UINT uExitCode);
HANDLE WINAPI OpenProcess(
        DWORD                   dwDesiredAccess,
        BOOL                    bInheritHandle,
        DWORD                   dwProcessId);
BOOL WINAPI CreateProcessA(
        LPCSTR                  lpApplicationName,
        LPSTR                   lpCommandLine,
        LPSECURITY_ATTRIBUTES   lpProcessAttributes,
        LPSECURITY_ATTRIBUTES   lpThreadAttributes,
        BOOL                    bInheritHandles,
        DWORD                   dwCreationFlags,
        LPVOID                  lpEnvironment,
        LPCSTR                  lpCurrentDirectory,
        LPSTARTUPINFOA          lpStartupInfo,
        LPPROCESS_INFORMATION   lpProcessInformation);
BOOL WINAPI CreateProcessW(
        LPCWSTR                 lpApplicationName,
        LPWSTR                  lpCommandLine,
        LPSECURITY_ATTRIBUTES   lpProcessAttributes,
        LPSECURITY_ATTRIBUTES   lpThreadAttributes,
        BOOL                    bInheritHandles,
        DWORD                   dwCreationFlags,
        LPVOID                  lpEnvironment,
        LPCWSTR                 lpCurrentDirectory,
        LPSTARTUPINFOW          lpStartupInfo,
        LPPROCESS_INFORMATION   lpProcessInformation);
BOOL WINAPI TerminateProcess(
        HANDLE  hProcess,
        UINT    uExitCode);
BOOL WINAPI EnumProcessModules(
        HANDLE  hProcess,
        HMODULE * lphModule,
        DWORD   cb,
        LPDWORD lpcbNeeded);
DWORD WINAPI WaitForInputIdle(
        HANDLE hProcess,
        DWORD  dwMilliseconds);
BOOL WINAPI GetExitCodeProcess(
        HANDLE  hProcess,
        LPDWORD lpExitCode);

/* ========================================================================== */
/* Jobs: */
HANDLE WINAPI CreateJobObjectA(
        LPSECURITY_ATTRIBUTES   lpJobAttributes,
        LPCSTR                  lpName);
HANDLE WINAPI CreateJobObjectW(
        LPSECURITY_ATTRIBUTES   lpJobAttributes,
        LPCWSTR                 lpName);
BOOL WINAPI SetInformationJobObject(
        HANDLE                  hJob,
        JOBOBJECTINFOCLASS      JobObjectInfoClass,
        LPVOID                  lpJobObjectInfo,
        DWORD                   cbJobObjectInfoLength);
BOOL WINAPI AssignProcessToJobObject(
        HANDLE                  hJob,
        HANDLE                  hProcess);


#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_PROCESS_H */
#endif /* _WINDOWS_ */


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_SYSINFO_H
#define WINDOWS_SYSINFO_H

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

/* Display Devices: */
#define DISPLAY_DEVICE_ACTIVE               0x00000001
#define DISPLAY_DEVICE_ATTACHED             0x00000002
#define DISPLAY_DEVICE_PRIMARY_DEVICE       0x00000004

/* System Metrics */
#define SM_CXSCREEN                         0
#define SM_CYSCREEN                         1
#define SM_CMONITORS                        80

/* Versions */
#define VER_EQUAL                           1
#define VER_GREATER                         2
#define VER_GREATER_EQUAL                   3
#define VER_LESS                            4
#define VER_LESS_EQUAL                      5
#define VER_AND                             6
#define VER_OR                              7

#define _WIN32_WINNT_WINXP                  0x0501
#define _WIN32_WINNT_WS03                   0x0502
#define _WIN32_WINNT_VISTA                  0x0600
#define _WIN32_WINNT_WS08                   0x0600
#define _WIN32_WINNT_WIN7                   0x0601
#define _WIN32_WINNT_WIN8                   0x0602
#define _WIN32_WINNT_WIN81                  0x0603
#define _WIN32_WINNT_WIN10                  0x0A00

#define VER_MINORVERSION                    0x0000001
#define VER_MAJORVERSION                    0x0000002
#define VER_BUILDNUMBER                     0x0000004
#define VER_PLATFORMID                      0x0000008
#define VER_SERVICEPACKMINOR                0x0000010
#define VER_SERVICEPACKMAJOR                0x0000020

/* Registry Key Classes */
#define HKEY_CLASSES_ROOT                   ((HKEY)(ULONG_PTR)((LONG)0x80000000))
#define HKEY_CURRENT_USER                   ((HKEY)(ULONG_PTR)((LONG)0x80000001))
#define HKEY_LOCAL_MACHINE                  ((HKEY)(ULONG_PTR)((LONG)0x80000002))
#define HKEY_USERS                          ((HKEY)(ULONG_PTR)((LONG)0x80000003))

/* Registry Types */
#define REG_NONE                            0
#define REG_SZ                              1
#define REG_EXPAND_SZ                       2

#define REG_BINARY                          3
#define REG_DWORD                           4
#define REG_DWORD_LITTLE_ENDIAN             4
#define REG_DWORD_BIG_ENDIAN                5
#define REG_LINK                            6
#define REG_MULTI_SZ                        7
#define REG_RESOURCE_LIST                   8
#define REG_FULL_RESOURCE_DESCRIPTOR        9
#define REG_RESOURCE_REQUIREMENTS_LIST      10
#define REG_QWORD                           11
#define REG_QWORD_LITTLE_ENDIAN             11


/* Registry Access Rights */
#define KEY_QUERY_VALUE                     0x0001
#define KEY_SET_VALUE                       0x0002
#define KEY_CREATE_SUB_KEY                  0x0004
#define KEY_ENUMERATE_SUB_KEYS              0x0008
#define KEY_NOTIFY                          0x0010
#define KEY_CREATE_LINK                     0x0020
#define KEY_WOW64_32KEY                     0x0200
#define KEY_WOW64_64KEY                     0x0100
#define KEY_WOW64_RES                       0x0300

#define KEY_READ                            \
    ((STANDARD_RIGHTS_READ                  \
      | KEY_QUERY_VALUE                     \
      | KEY_ENUMERATE_SUB_KEYS              \
      | KEY_NOTIFY)                         \
        & (~SYNCHRONIZE))

#define KEY_WRITE                           \
    ((STANDARD_RIGHTS_WRITE                 \
      | KEY_SET_VALUE                       \
      | KEY_CREATE_SUB_KEY)                 \
        & (~SYNCHRONIZE))

#define KEY_EXECUTE                         \
    ((KEY_READ)                             \
        & (~SYNCHRONIZE))

#define KEY_ALL_ACCESS                      \
    ((STANDARD_RIGHTS_ALL                   \
      | KEY_QUERY_VALUE                     \
      | KEY_SET_VALUE                       \
      | KEY_CREATE_SUB_KEY                  \
      | KEY_ENUMERATE_SUB_KEYS              \
      | KEY_NOTIFY                          \
      | KEY_CREATE_LINK)                    \
        & (~SYNCHRONIZE))


/* ========================================================================== */
/* Structures: */
typedef struct _SYSTEM_INFO {
    union {
        DWORD       dwOemId;
        struct {
            WORD    wProcessorArchitecture;
            WORD    wReserved;
        };
    };

    DWORD           dwPageSize;
    LPVOID          lpMinimumApplicationAddress;
    LPVOID          lpMaximumApplicationAddress;
    DWORD_PTR       dwActiveProcessorMask;
    DWORD           dwNumberOfProcessors;
    DWORD           dwProcessorType;
    DWORD           dwAllocationGranularity;
    WORD            wProcessorLevel;
    WORD            wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;

/* Device Context: */
typedef struct _DISPLAY_DEVICEA {
    DWORD cb;
    CHAR  DeviceName[32];
    CHAR  DeviceString[128];
    DWORD StateFlags;
    CHAR  DeviceID[128];
    CHAR  DeviceKey[128];
} DISPLAY_DEVICEA, *PDISPLAY_DEVICEA;
typedef struct _DISPLAY_DEVICEW {
    DWORD cb;
    WCHAR DeviceName[32];
    WCHAR DeviceString[128];
    DWORD StateFlags;
    WCHAR DeviceID[128];
    WCHAR DeviceKey[128];
} DISPLAY_DEVICEW, *PDISPLAY_DEVICEW;

/* Version: */
typedef struct _OSVERSIONINFOEXA {
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    CHAR  szCSDVersion[128];
    WORD  wServicePackMajor;
    WORD  wServicePackMinor;
    WORD  wSuiteMask;
    BYTE  wProductType;
    BYTE  wReserved;
} OSVERSIONINFOEXA, *POSVERSIONINFOEXA, *LPOSVERSIONINFOEXA;
typedef struct _OSVERSIONINFOEXW {
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    WCHAR szCSDVersion[128];
    WORD  wServicePackMajor;
    WORD  wServicePackMinor;
    WORD  wSuiteMask;
    BYTE  wProductType;
    BYTE  wReserved;
} OSVERSIONINFOEXW, *POSVERSIONINFOEXW, *LPOSVERSIONINFOEXW;

/* SysInfo: */
typedef enum _LOGICAL_PROCESSOR_RELATIONSHIP {
    RelationProcessorCore,
    RelationNumaNode,
    RelationCache,
    RelationProcessorPackage,
    RelationGroup,
    RelationAll               = 0xffff
} LOGICAL_PROCESSOR_RELATIONSHIP;
typedef enum _PROCESSOR_CACHE_TYPE {
    CacheUnified,
    CacheInstruction,
    CacheData,
    CacheTrace
} PROCESSOR_CACHE_TYPE;
typedef struct _CACHE_DESCRIPTOR {
    BYTE                 Level;
    BYTE                 Associativity;
    WORD                 LineSize;
    DWORD                Size;
    PROCESSOR_CACHE_TYPE Type;
} CACHE_DESCRIPTOR, *PCACHE_DESCRIPTOR;
typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION {
    ULONG_PTR                      ProcessorMask;
    LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
    union {
      struct {
        BYTE Flags;
      } ProcessorCore;
      struct {
        DWORD NodeNumber;
      } NumaNode;
      CACHE_DESCRIPTOR Cache;
      ULONGLONG        Reserved[2];
    };
} SYSTEM_LOGICAL_PROCESSOR_INFORMATION, *PSYSTEM_LOGICAL_PROCESSOR_INFORMATION;

/* Processor Information Extended */
typedef ULONG_PTR KAFFINITY;
typedef struct _GROUP_AFFINITY {
    KAFFINITY Mask;
    WORD      Group;
    WORD      Reserved[3];
} GROUP_AFFINITY, *PGROUP_AFFINITY;
typedef struct _NUMA_NODE_RELATIONSHIP {
    DWORD          NodeNumber;
    BYTE           Reserved[20];
    GROUP_AFFINITY GroupMask;
} NUMA_NODE_RELATIONSHIP, *PNUMA_NODE_RELATIONSHIP;

typedef struct _PROCESSOR_GROUP_INFO {
    BYTE      MaximumProcessorCount;
    BYTE      ActiveProcessorCount;
    BYTE      Reserved[38];
    KAFFINITY ActiveProcessorMask;
} PROCESSOR_GROUP_INFO, *PPROCESSOR_GROUP_INFO;
typedef struct _GROUP_RELATIONSHIP {
    WORD                 MaximumGroupCount;
    WORD                 ActiveGroupCount;
    BYTE                 Reserved[20];
    PROCESSOR_GROUP_INFO GroupInfo[1];
} GROUP_RELATIONSHIP, *PGROUP_RELATIONSHIP;

typedef struct _CACHE_RELATIONSHIP {
    BYTE                 Level;
    BYTE                 Associativity;
    WORD                 LineSize;
    DWORD                CacheSize;
    PROCESSOR_CACHE_TYPE Type;
    BYTE                 Reserved[20];
    GROUP_AFFINITY       GroupMask;
} CACHE_RELATIONSHIP, *PCACHE_RELATIONSHIP;

typedef struct _PROCESSOR_RELATIONSHIP {
    BYTE           Flags;
    BYTE           EfficiencyClass;
    BYTE           Reserved[21];
    WORD           GroupCount;
    GROUP_AFFINITY GroupMask[1];
} PROCESSOR_RELATIONSHIP, *PPROCESSOR_RELATIONSHIP;

typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX {
    LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
    DWORD                          Size;
    union {
      PROCESSOR_RELATIONSHIP Processor;
      NUMA_NODE_RELATIONSHIP NumaNode;
      CACHE_RELATIONSHIP     Cache;
      GROUP_RELATIONSHIP     Group;
    };
} SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX, *PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX;

typedef struct _PROCESS_MEMORY_COUNTERS {
    DWORD  cb;
    DWORD  PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
} PROCESS_MEMORY_COUNTERS, *PPROCESS_MEMORY_COUNTERS;

/* Memory: */
typedef struct _MEMORYSTATUSEX {
    DWORD     dwLength;
    DWORD     dwMemoryLoad;
    DWORDLONG ullTotalPhys;
    DWORDLONG ullAvailPhys;
    DWORDLONG ullTotalPageFile;
    DWORDLONG ullAvailPageFile;
    DWORDLONG ullTotalVirtual;
    DWORDLONG ullAvailVirtual;
    DWORDLONG ullAvailExtendedVirtual;
} MEMORYSTATUSEX, *LPMEMORYSTATUSEX;

/* Processor: */
typedef struct _PROCESSOR_NUMBER {
  WORD Group;
  BYTE Number;
  BYTE Reserved;
} PROCESSOR_NUMBER, *PPROCESSOR_NUMBER;


/* ========================================================================== */
/* System Info Functions: */
void WINAPI GetSystemInfo(
        LPSYSTEM_INFO lpSystemInfo);
BOOL WINAPI GlobalMemoryStatusEx(
        LPMEMORYSTATUSEX lpBuffer);
BOOL WINAPI GetLogicalProcessorInformation(
        PSYSTEM_LOGICAL_PROCESSOR_INFORMATION Buffer,
        PDWORD ReturnedLength);
BOOL GetLogicalProcessorInformationEx(
        LOGICAL_PROCESSOR_RELATIONSHIP RelationshipType,
        PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Buffer,
        PDWORD ReturnedLength);
BOOL WINAPI GetProcessMemoryInfo(
        HANDLE hProcess,
        PPROCESS_MEMORY_COUNTERS ppsmemCounters,
        DWORD cb);
BOOL WINAPI GetProcessTimes(
        HANDLE hProcess,
        LPFILETIME lpCreationTime,
        LPFILETIME lpExitTime,
        LPFILETIME lpKernelTime,
        LPFILETIME lpUserTime);

/* ========================================================================== */
/* Processor Functions                                                        */
DWORD WINAPI GetCurrentProcessorNumber(void);
void GetCurrentProcessorNumberEx(PPROCESSOR_NUMBER ProcNumber);
#define ALL_PROCESSOR_GROUPS 0xffff
DWORD GetActiveProcessorCount(WORD GroupNumber);


#define MAX_COMPUTERNAME_LENGTH 31
BOOL WINAPI GetComputerNameA(
        LPSTR   lpBuffer,
        LPDWORD lpnSize);
BOOL WINAPI GetComputerNameW(
        LPWSTR  lpBuffer,
        LPDWORD lpnSize);

/* Version: */
BOOL WINAPI VerifyVersionInfoA(
        LPOSVERSIONINFOEXA lpVersionInfo,
        DWORD              dwTypeMask,
        DWORDLONG          dwlConditionMask);
BOOL WINAPI VerifyVersionInfoW(
        LPOSVERSIONINFOEXW lpVersionInfo,
        DWORD              dwTypeMask,
        DWORDLONG          dwlConditionMask);
ULONGLONG WINAPI VerSetConditionMask(
        ULONGLONG ConditionMask,
        DWORD TypeMask,
        BYTE  Condition);

FORCEINLINE BOOL
IsWindowsVersionOrGreater(WORD major, WORD minor, WORD servpack)
{
    OSVERSIONINFOEXW vi = { sizeof(vi), major, minor, 0, 0, {0}, servpack };
    return VerifyVersionInfoW(&vi,
            VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR,
            VerSetConditionMask(
                VerSetConditionMask(
                    VerSetConditionMask(0,
                        VER_MAJORVERSION, VER_GREATER_EQUAL),
                    VER_MINORVERSION,VER_GREATER_EQUAL),
                VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL));
}

FORCEINLINE BOOL
IsWindowsVersionOrLess(WORD major, WORD minor, WORD servpack)
{
    OSVERSIONINFOEXW vi = { sizeof(vi), major, minor, 0, 0, {0}, servpack };
    return VerifyVersionInfoW(&vi,
            VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR,
            VerSetConditionMask(
                VerSetConditionMask(
                    VerSetConditionMask(0,
                        VER_MAJORVERSION, VER_LESS_EQUAL),
                    VER_MINORVERSION,VER_LESS_EQUAL),
                VER_SERVICEPACKMAJOR, VER_LESS_EQUAL));
}

#define GREATER IsWindowsVersionOrGreater
FORCEINLINE void
GetWindowsVersionCUSTOM(PWORD major, PWORD minor, PWORD srvpack)
{
    if (GREATER(HIBYTE(_WIN32_WINNT_WIN10), LOBYTE(_WIN32_WINNT_WIN10), 0)) {
        *major = 10;
        *minor = 0;
        *srvpack = 0;
    } else if (GREATER(HIBYTE(_WIN32_WINNT_WIN81), LOBYTE(_WIN32_WINNT_WIN81), 0)) {
        *major = 6;
        *minor = 3;
        *srvpack = 0;
    } else if (GREATER(HIBYTE(_WIN32_WINNT_WIN8), LOBYTE(_WIN32_WINNT_WIN8), 0)) {
        *major = 6;
        *minor = 2;
        *srvpack = 0;
    } else if (GREATER(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 1)) {
        *major = 6;
        *minor = 1;
        *srvpack = 1;
    } else if (GREATER(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0)) {
        *major = 6;
        *minor = 1;
        *srvpack = 0;
    } else if (GREATER(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 2)) {
        *major = 6;
        *minor = 0;
        *srvpack = 2;
    } else if (GREATER(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 1)) {
        *major = 6;
        *minor = 0;
        *srvpack = 1;
    } else if (GREATER(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 0)) {
        *major = 6;
        *minor = 0;
        *srvpack = 0;
    } else if (GREATER(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 3)) {
        *major = 5;
        *minor = 1;
        *srvpack = 2;
    } else if (GREATER(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 1)) {
        *major = 5;
        *minor = 1;
        *srvpack = 1;
    } else if (GREATER(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0)) {
        *major = 5;
        *minor = 1;
        *srvpack = 0;
    } else {
        *major = 0;
        *minor = 0;
        *srvpack = 0;
    }
}
#undef GREATER


/* ========================================================================== */
/* CPUID: */
void __cpuid(int cpuInfo[4], int function_id);
void __cpuidex(int cpuInfo[4], int function_id, int subfunction_id);

/* ========================================================================== */
/* Device Context: */
BOOL WINAPI EnumDisplayDevicesA(
        LPCSTR  lpDevice,
        DWORD   iDevNum,
        PDISPLAY_DEVICEA lpDisplayDevice,
        DWORD   dwFlags);
BOOL WINAPI EnumDisplayDevicesW(
        LPCWSTR lpDevice,
        DWORD   iDevNum,
        PDISPLAY_DEVICEW lpDisplayDevice,
        DWORD   dwFlags);

/* ========================================================================== */
/* Registry: */
LONG WINAPI RegOpenKeyExA(
    HKEY    hKey,
    LPCSTR  lpSubKey,
    DWORD   ulOptions,
    REGSAM  samDesired,
    PHKEY   phkResult);
LONG WINAPI RegOpenKeyExW(
    HKEY    hKey,
    LPCWSTR lpSubKey,
    DWORD   ulOptions,
    REGSAM  samDesired,
    PHKEY   phkResult);
LONG WINAPI RegQueryValueExA(
    HKEY    hKey,
    LPCSTR  lpValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE  lpData,
    LPDWORD lpcbData);
LONG WINAPI RegQueryValueExW(
    HKEY    hKey,
    LPCWSTR lpValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE  lpData,
    LPDWORD lpcbData);
LONG WINAPI RegCreateKeyExA(
    HKEY                  hKey,
    LPCSTR                lpSubKey,
    DWORD                 Reserved,
    LPSTR                 lpClass,
    DWORD                 dwOptions,
    REGSAM                samDesired,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY                 phkResult,
    LPDWORD               lpdwDisposition);
LONG WINAPI RegCreateKeyExW(
    HKEY                  hKey,
    LPCWSTR               lpSubKey,
    DWORD                 Reserved,
    LPWSTR                lpClass,
    DWORD                 dwOptions,
    REGSAM                samDesired,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY                 phkResult,
    LPDWORD               lpdwDisposition);
LONG WINAPI RegEnumValueA(
    HKEY    hKey,
    DWORD   dwIndex,
    LPSTR   lpValueName,
    LPDWORD lpcchValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE  lpData,
    LPDWORD lpcbData);
LONG WINAPI RegEnumValueW(
    HKEY    hKey,
    DWORD   dwIndex,
    LPWSTR  lpValueName,
    LPDWORD lpcchValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE  lpData,
    LPDWORD lpcbData);
LONG WINAPI RegQueryInfoKeyA(
    HKEY      hKey,
    LPSTR     lpClass,
    LPDWORD   lpcClass,
    LPDWORD   lpReserved,
    LPDWORD   lpcSubKeys,
    LPDWORD   lpcMaxSubKeyLen,
    LPDWORD   lpcMaxClassLen,
    LPDWORD   lpcValues,
    LPDWORD   lpcMaxValueNameLen,
    LPDWORD   lpcMaxValueLen,
    LPDWORD   lpcbSecurityDescriptor,
    PFILETIME lpftLastWriteTime);
LONG WINAPI RegQueryInfoKeyW(
    HKEY      hKey,
    LPWSTR    lpClass,
    LPDWORD   lpcClass,
    LPDWORD   lpReserved,
    LPDWORD   lpcSubKeys,
    LPDWORD   lpcMaxSubKeyLen,
    LPDWORD   lpcMaxClassLen,
    LPDWORD   lpcValues,
    LPDWORD   lpcMaxValueNameLen,
    LPDWORD   lpcMaxValueLen,
    LPDWORD   lpcbSecurityDescriptor,
    PFILETIME lpftLastWriteTime);
LONG WINAPI RegEnumKeyExA(
    HKEY      hKey,
    DWORD     dwIndex,
    LPSTR     lpName,
    LPDWORD   lpcName,
    LPDWORD   lpReserved,
    LPSTR     lpClass,
    LPDWORD   lpcClass,
    PFILETIME lpftLastWriteTime);
LONG WINAPI RegEnumKeyExW(
    HKEY      hKey,
    DWORD     dwIndex,
    LPWSTR    lpName,
    LPDWORD   lpcName,
    LPDWORD   lpReserved,
    LPWSTR    lpClass,
    LPDWORD   lpcClass,
    PFILETIME lpftLastWriteTime);
LONG WINAPI RegCloseKey(
    HKEY hKey);
LONG WINAPI RegFlushKey(
    HKEY hKey);

#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_SYSINFO_H */
#endif /* _WINDOWS_ */


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


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

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

/* MessageBox customizations: */
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_CANCELTRYCONTINUE        0x00000006L
#define MB_HELP                     0x00004000L
#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_RETRYCANCEL              0x00000005L
#define MB_YESNO                    0x00000004L
#define MB_YESNOCANCEL              0x00000003L

#define MB_ICONEXCLAMATION          0x00000030L
#define MB_ICONWARNING              0x00000030L
#define MB_ICONINFORMATION          0x00000040L
#define MB_ICONASTERISK             0x00000040L
#define MB_ICONQUESTION             0x00000020L
#define MB_ICONSTOP                 0x00000010L
#define MB_ICONERROR                0x00000010L
#define MB_ICONHAND                 0x00000010L

#define MB_DEFBUTTON1               0x00000000L
#define MB_DEFBUTTON2               0x00000100L
#define MB_DEFBUTTON3               0x00000200L
#define MB_DEFBUTTON4               0x00000300L

#define MB_APPLMODAL                0x00000000L
#define MB_SYSTEMMODAL              0x00001000L
#define MB_TASKMODAL                0x00002000L

#define MB_DEFAULT_DESKTOP_ONLY     0x00020000L
#define MB_RIGHT                    0x00080000L
#define MB_RTLREADING               0x00100000L
#define MB_SETFOREGROUND            0x00010000L
#define MB_TOPMOST                  0x00040000L
#define MB_SERVICE_NOTIFICATION     0x00200000L

#define IDABORT                     (3)
#define IDCANCEL                    (2)
#define IDCONTINUE                  (11)
#define IDIGNORE                    (5)
#define IDNO                        (7)
#define IDOK                        (1)
#define IDRETRY                     (4)
#define IDTRYAGAIN                  (10)
#define IDYES                       (6)

/* Window Styles: */
#define WS_OVERLAPPED               0x00000000L
#define WS_POPUP                    0x80000000L
#define WS_CHILD                    0x40000000L
#define WS_MINIMIZE                 0x20000000L
#define WS_VISIBLE                  0x10000000L
#define WS_DISABLED                 0x08000000L
#define WS_CLIPSIBLINGS             0x04000000L
#define WS_CLIPCHILDREN             0x02000000L
#define WS_MAXIMIZE                 0x01000000L
#define WS_CAPTION                  0x00C00000L
#define WS_BORDER                   0x00800000L
#define WS_DLGFRAME                 0x00400000L
#define WS_VSCROLL                  0x00200000L
#define WS_HSCROLL                  0x00100000L
#define WS_SYSMENU                  0x00080000L
#define WS_THICKFRAME               0x00040000L
#define WS_GROUP                    0x00020000L
#define WS_TABSTOP                  0x00010000L

#define WS_MINIMIZEBOX              0x00020000L
#define WS_MAXIMIZEBOX              0x00010000L


#define WS_TILED                    WS_OVERLAPPED
#define WS_ICONIC                   WS_MINIMIZE
#define WS_SIZEBOX                  WS_THICKFRAME
#define WS_TILEDWINDOW              WS_OVERLAPPEDWINDOW

/* Common Window Styles: */
#define WS_OVERLAPPEDWINDOW         (WS_OVERLAPPED     | \
                                     WS_CAPTION        | \
                                     WS_SYSMENU        | \
                                     WS_THICKFRAME     | \
                                     WS_MINIMIZEBOX    | \
                                     WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW              (WS_POPUP          | \
                                     WS_BORDER         | \
                                     WS_SYSMENU)
#define WS_CHILDWINDOW              (WS_CHILD)

#define CW_USEDEFAULT               ((int)0x80000000)

/* Class Styles: */
#define CS_OWNDC                        0x0020
#define CS_VREDRAW                      0x0001
#define CS_HREDRAW                      0x0002

/* Messages: */
#define PM_NOREMOVE                 0x0000
#define PM_REMOVE                   0x0001
#define PM_NOYIELD                  0x0002

#define WM_NULL                     0x0000
#define WM_CREATE                   0x0001
#define WM_DESTROY                  0x0002
#define WM_MOVE                     0x0003
#define WM_SIZE                     0x0005
#define WM_SETFOCUS                 0x0007
#define WM_KILLFOCUS                0x0008
#define WM_ENABLE                   0x000A
#define WM_SETREDRAW                0x000B
#define WM_SETTEXT                  0x000C
#define WM_GETTEXT                  0x000D
#define WM_GETTEXTLENGTH            0x000E
#define WM_PAINT                    0x000F
#define WM_CLOSE                    0x0010
#define WM_QUIT                     0x0012
#define WM_ERASEBKGND               0x0014
#define WM_SYSCOLORCHANGE           0x0015
#define WM_SHOWWINDOW               0x0018
#define WM_WININICHANGE             0x001A
#define WM_NCDESTROY                0x0082

#define WM_KEYDOWN                  0x0100
#define WM_KEYUP                    0x0101
#define WM_SYSKEYDOWN               0x0104
#define WM_SYSKEYUP                 0x0105

#define WM_SYSCOMMAND               0x0112

#define WM_ENTERSIZEMOVE            0x0231
#define WM_EXITSIZEMOVE             0x0232

#define WM_ACTIVATE                 0x0006
#define WA_INACTIVE                 0
#define WA_ACTIVE                   1
#define WA_CLICKACTIVE              2

#define SC_KEYMENU                  0xF100

/* Events: */
#define EVENT_ALL_ACCESS            0x1F0003
#define EVENT_MODIFY_STATE          0x0002

/* Virtual Keys: */
#define VK_BACK                         0x08
#define VK_TAB                          0x09
#define VK_SHIFT                        0x10
#define VK_CONTROL                      0x11
#define VK_MENU                         0x12
#define VK_RETURN                       0x0D

#define VK_ESCAPE                       0x1B

#define VK_SPACE                        0x20
#define VK_PRIOR                        0x21
#define VK_NEXT                         0x22
#define VK_END                          0x23
#define VK_HOME                         0x24
#define VK_LEFT                         0x25
#define VK_UP                           0x26
#define VK_RIGHT                        0x27
#define VK_DOWN                         0x28
#define VK_SELECT                       0x29
#define VK_PRINT                        0x2A
#define VK_EXECUTE                      0x2B
#define VK_SNAPSHOT                     0x2C
#define VK_INSERT                       0x2D
#define VK_DELETE                       0x2E
#define VK_HELP                         0x2F

#define VK_LWIN                         0x5B
#define VK_RWIN                         0x5C
#define VK_PROCESSKEY                   0xE5


/* ========================================================================== */
/* Structures:                                                                */
typedef struct _RECT {
    LONG        left;
    LONG        top;
    LONG        right;
    LONG        bottom;
} RECT, *PRECT, *LPRECT;

/* Window: */
typedef LRESULT (CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef struct tagWNDCLASS {
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCTSTR     lpszMenuName;
    LPCTSTR     lpszClassName;
} WNDCLASS, *PWNDCLASS;

/* Messages: */
typedef struct tagPOINT {
  LONG x;
  LONG y;
} POINT, *PPOINT;

typedef struct tagMSG {
    HWND        hwnd;
    UINT        message;
    WPARAM      wParam;
    LPARAM      lParam;
    DWORD       time;
    POINT       pt;
} MSG, *PMSG, *LPMSG;


/* ========================================================================== */
/* Window Functions: */
int WINAPI MessageBoxA(
        HWND    hWND,
        LPCSTR  lpText,
        LPCSTR  lpCaption,
        UINT    uType);
int WINAPI MessageBoxW(
        HWND    hWND,
        LPCWSTR lpText,
        LPCWSTR lpCaption,
        UINT    uType);
ATOM WINAPI RegisterClassA(
        WNDCLASS *lpWndClass);
ATOM WINAPI RegisterClassW(
        WNDCLASS *lpWndClass);
BOOL WINAPI UnregisterClassA(
        LPCSTR  lpClassName,
        HINSTANCE hInstance);
BOOL WINAPI UnregisterClassW(
        LPCWSTR lpClassName,
        HINSTANCE hInstance);
HWND WINAPI CreateWindowExA(
        DWORD   dwExStyle,
        LPCSTR  lpClassName,
        LPCSTR  lpWindowName,
        DWORD   dwStyle,
        int     x,
        int     y,
        int     nWidth,
        int     nHeight,
        HWND    hWndParent,
        HMENU   hMenu,
        HINSTANCE hInstance,
        LPVOID  lpParam);
HWND WINAPI CreateWindowExW(
        DWORD   dwExStyle,
        LPCWSTR lpClassName,
        LPCWSTR lpWindowName,
        DWORD   dwStyle,
        int     x,
        int     y,
        int     nWidth,
        int     nHeight,
        HWND    hWndParent,
        HMENU   hMenu,
        HINSTANCE hInstance,
        LPVOID  lpParam);
BOOL WINAPI ShowWindow(
        HWND    hWnd,
        int     nCmdShow);
BOOL WINAPI UpdateWindow(
        HWND    hWnd);
LRESULT WINAPI DefWindowProcA(
        HWND    hWnd,
        UINT    uMsg,
        WPARAM  wParam,
        LPARAM  lParam);
LRESULT WINAPI DefWindowProcW(
        HWND    hWnd,
        UINT    uMsg,
        WPARAM  wParam,
        LPARAM  lParam);
BOOL WINAPI DestroyWindow(
        HWND    hWnd);
BOOL WINAPI AdjustWindowRectEx(
        LPRECT  lpRect,
        DWORD   dwStyle,
        BOOL    bMenu,
        DWORD   dwExStyle);
BOOL WINAPI GetClientRect(
        HWND    hWnd,
        LPRECT  lpRect);
int WINAPI GetSystemMetrics(
        int     nIndex);

/* ========================================================================== */
/* Message Queue: */
BOOL WINAPI PeekMessageA(
        LPMSG   lpMsg,
        HWND    hWnd,
        UINT    wMsgFilterMin,
        UINT    wMsgFilterMax,
        UINT    wRemoveMsg);
BOOL WINAPI PeekMessageW(
        LPMSG   lpMsg,
        HWND    hWnd,
        UINT    wMsgFilterMin,
        UINT    wMsgFilterMax,
        UINT    wRemoveMsg);
BOOL WINAPI TranslateMessage(
        const MSG *lpMsg);
LRESULT WINAPI DispatchMessageA(
        const MSG *lpMsg);
LRESULT WINAPI DispatchMessageW(
        const MSG *lpMsg);
void WINAPI PostQuitMessage(
        int nExitCode);

/* ========================================================================== */
/* Events: */
HANDLE WINAPI CreateEventA(
        LPSECURITY_ATTRIBUTES lpEventAttributes,
        BOOL    bManualReset,
        BOOL    bInitialState,
        LPCSTR  lpName);
HANDLE WINAPI CreateEventW(
        LPSECURITY_ATTRIBUTES lpEventAttributes,
        BOOL    bManualReset,
        BOOL    bInitialState,
        LPCWSTR lpName);
HANDLE WINAPI OpenEventA(
        DWORD   dwDesiredAccess,
        BOOL    bInheritHandle,
        LPCSTR  lpName);
HANDLE WINAPI OpenEventW(
        DWORD   dwDesiredAccess,
        BOOL    bInheritHandle,
        LPCWSTR lpName);
BOOL WINAPI ResetEvent(
        HANDLE  hEvent);
BOOL WINAPI SetEvent(
        HANDLE  hEvent);
SHORT WINAPI GetKeyState(
        int     nVirtKey);

#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_WINDOW_H */
#endif /* _WINDOWS_ */


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_INTRIN_H
#define WINDOWS_INTRIN_H

/* Disable all warnings */
#if defined(_MSC_VER)
    #pragma warning(push, 0)
#endif

#if defined(__cplusplus)
extern "C" {
#endif


/* ========================================================================== */
/* Intrinsics                                                                 */
/* ========================================================================== */

extern void _mm_pause(void);
#pragma intrinsic(_mm_pause)

extern void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)



#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_INTRIN_H */
#endif /* _WINDOWS_ */


/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
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
#endif /* _WINDOWS_ */


#endif
#endif
#define _WINDOWS_
#endif
