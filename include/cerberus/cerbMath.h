#ifndef cerbMath_h
#define cerbMath_h

#include <float.h>
#include <stddef.h>
#include <inttypes.h>

#if !defined(__cplusplus) && (__cplusplus < 202002L)

    typedef union {
        uint64_t value;
        double floatingPoint;
    } IEEE754u64_t; 

    typedef union {
        uint32_t value;
        float floatingPoint;
    } IEEE754u32_t; 

    float cerbABSf(float x);
    double cerbABS(double x);
    
#else

namespace cerb{

    union IEEE754u32_t{
        uint32_t value;
        float floatingPoint;

        constexpr IEEE754u32_t(uint32_t v) : value(v) {};
        constexpr IEEE754u32_t(float f) : floatingPoint(f) {};
    };

    union IEEE754u64_t{
        uint64_t value;
        double floatingPoint;

        constexpr IEEE754u64_t(uint32_t v) : value(v) {};
        constexpr IEEE754u64_t(double f) : floatingPoint(f) {};
    };

    constexpr float ABS(float x){
        IEEE754u32_t ieee754(x);
        ieee754.floatingPoint = x;
        ieee754.value &= (~((uint32_t)0) ^ ((uint32_t)1 << 31));
        return ieee754.floatingPoint;
    }

    constexpr double ABS(double x){
        IEEE754u64_t ieee754(x);
        ieee754.value &= (~((uint64_t)0) ^ ((uint64_t)1 << 63));
        return ieee754.floatingPoint;
    }
}

#endif /* __cplusplus */

#endif /* cerbMath_h */
