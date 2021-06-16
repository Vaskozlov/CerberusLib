#include <cerberus/cerbMath.h>

float cerbABSf(float x){
    IEEE754u32_t ieee754;
    ieee754.floatingPoint = x;
    ieee754.value &= (~((uint32_t)0) ^ ((uint32_t)1 << 31));
    return ieee754.floatingPoint;
}

double cerbABS(double x){
    IEEE754u64_t ieee754;
    ieee754.floatingPoint = x;
    ieee754.value &= (~((uint64_t)0) ^ ((uint64_t)1 << 63));
    return ieee754.floatingPoint;
}
