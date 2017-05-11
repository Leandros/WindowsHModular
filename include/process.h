#ifndef WINDOWS_PROCESS_H
#define WINDOWS_PROCESS_H

#include "windows_base.h"
#if defined(__cplusplus)
extern "C" {
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

#endif /* WINDOWS_PROCESS_H */

