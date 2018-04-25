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

