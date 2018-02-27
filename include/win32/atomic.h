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

