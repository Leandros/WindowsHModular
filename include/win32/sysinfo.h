/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
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

