// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

// Implementation of Redhawk PAL inline functions

FORCEINLINE Int32 PalInterlockedIncrement(_Inout_ _Interlocked_operand_ Int32 volatile *pDst)
{
    return __sync_add_and_fetch(pDst, 1);
}

FORCEINLINE Int32 PalInterlockedDecrement(_Inout_ _Interlocked_operand_ Int32 volatile *pDst)
{
    return __sync_sub_and_fetch(pDst, 1);
}

FORCEINLINE UInt32 PalInterlockedOr(_Inout_ _Interlocked_operand_ UInt32 volatile *pDst, UInt32 iValue)
{
    return __sync_or_and_fetch(pDst, iValue);
}

FORCEINLINE UInt32 PalInterlockedAnd(_Inout_ _Interlocked_operand_ UInt32 volatile *pDst, UInt32 iValue)
{
    return __sync_and_and_fetch(pDst, iValue);
}

FORCEINLINE Int32 PalInterlockedExchange(_Inout_ _Interlocked_operand_ Int32 volatile *pDst, Int32 iValue)
{
    return __sync_swap(pDst, iValue);
}

FORCEINLINE Int64 PalInterlockedExchange64(_Inout_ _Interlocked_operand_ Int64 volatile *pDst, Int64 iValue)
{
    return __sync_swap(pDst, iValue);
}

FORCEINLINE Int32 PalInterlockedCompareExchange(_Inout_ _Interlocked_operand_ Int32 volatile *pDst, Int32 iValue, Int32 iComperand)
{
    return __sync_val_compare_and_swap(pDst, iComperand, iValue);
}

FORCEINLINE Int64 PalInterlockedCompareExchange64(_Inout_ _Interlocked_operand_ Int64 volatile *pDst, Int64 iValue, Int64 iComperand)
{
    return __sync_val_compare_and_swap(pDst, iComperand, iValue);
}

#if defined(_AMD64_)
FORCEINLINE UInt8 PalInterlockedCompareExchange128(_Inout_ _Interlocked_operand_ Int64 volatile *pDst, Int64 iValueHigh, Int64 iValueLow, Int64 *pComperand)
{
    return __sync_val_compare_and_swap((__int128_t volatile*)pDst, *(__int128_t*)pComperand, ((__int128_t)iValueHigh << 64) + iValueLow);
}
#endif // _AMD64_

#ifdef BIT64

#define PalInterlockedExchangePointer(_pDst, _pValue) \
    ((void *)PalInterlockedExchange64((Int64 volatile *)(_pDst), (Int64)(size_t)(_pValue)))

#define PalInterlockedCompareExchangePointer(_pDst, _pValue, _pComperand) \
    ((void *)PalInterlockedCompareExchange64((Int64 volatile *)(_pDst), (Int64)(size_t)(_pValue), (Int64)(size_t)(_pComperand)))

#else // BIT64

#define PalInterlockedExchangePointer(_pDst, _pValue) \
    ((void *)PalInterlockedExchange((Int32 volatile *)(_pDst), (Int32)(size_t)(_pValue)))

#define PalInterlockedCompareExchangePointer(_pDst, _pValue, _pComperand) \
    ((void *)PalInterlockedCompareExchange((Int32 volatile *)(_pDst), (Int32)(size_t)(_pValue), (Int32)(size_t)(_pComperand)))

#endif // BIT64


FORCEINLINE void PalYieldProcessor()
{
#if defined(_X86_) || defined(_AMD64_)
    __asm__ __volatile__(
        "rep\n"
        "nop"
        );
#endif
}

FORCEINLINE void PalMemoryBarrier()
{
    __sync_synchronize();
}
