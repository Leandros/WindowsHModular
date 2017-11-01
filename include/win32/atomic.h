/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef WINDOWS_ATOMIC_H
#define WINDOWS_ATOMIC_H

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

/* ========================================================================== */
/* Atomic Functions: */
short _InterlockedDecrement16(
        short volatile *Addend);
short _InterlockedIncrement16(
        short volatile *Addend);

long _InterlockedExchange(
        long volatile *Target,
        long Value);
long _InterlockedExchangeAdd(
        long volatile *Addend,
        long Value);
long _InterlockedCompareExchange(
        long volatile *Destination,
        long Exchange,
        long Comparand);
long _InterlockedCompareExchange_HLEAcquire(
        long volatile *Destination,
        long Exchange,
        long Comparand);

#define InterlockedDecrement16      _InterlockedDecrement16
#define InterlockedIncrement16      _InterlockedIncrement16
#define InterlockedExchange         _InterlockedExchange
#define InterlockedExchangeAdd      _InterlockedExchangeAdd
#define InterlockedCompareExchange  _InterlockedCompareExchange
#define InterlockedCompareExchangeAcquire  _InterlockedCompareExchange

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

