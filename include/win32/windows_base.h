/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
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
#define _WIN32_WINNT 0x0600

/* Magic: */
#define _CRTALLOC(x)        __declspec(allocate(x))
#define DECLSPEC_ALIGN(x)   __declspec(align(x))

/* Basic Defines: */
#define NTAPI __stdcall
#define WINAPI __stdcall
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
typedef HANDLE              HMENU;
typedef HANDLE *            PHANDLE;

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
#define ERROR_SUCCESS           0L
#define ERROR_NO_MORE_FILES     18L
#define ERROR_MORE_DATA         234L


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

