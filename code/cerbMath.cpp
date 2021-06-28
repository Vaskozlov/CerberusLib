#include <bit>
#include <cerberus/cerbMath.h>


extern "C" float cerbABSf(float x){
    uint32_t mask = std::bit_cast<uint32_t>(x);
    mask &= INT32_MAX;
    return std::bit_cast<float>(mask);
}

extern "C" double cerbABS(double x){
    uint64_t mask = std::bit_cast<uint64_t>(x);
    mask &= INT64_MAX;
    return std::bit_cast<double>(mask);
}
