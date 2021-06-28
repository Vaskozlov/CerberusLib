#ifndef cerbMath_h
#define cerbMath_h

#include <float.h>
#include <stddef.h>
#include <inttypes.h>

#if !defined(__cplusplus) && (__cplusplus < 202002L)
    float cerbABSf(float x);
    double cerbABS(double x);    
#else

namespace cerb{
    #include <bit>

    constexpr float ABS(float x){
        uint32_t mask = std::bit_cast<uint32_t>(x);
        mask &= INT32_MAX;
        return std::bit_cast<float>(mask);
    }

    constexpr double ABS(double x){
        uint64_t mask = std::bit_cast<uint64_t>(x);
        mask &= INT64_MAX;
        return std::bit_cast<double>(mask);
    }
}

#endif /* __cplusplus */

#endif /* cerbMath_h */
