#include <cerberus/io.h>

int AVX_SUPPORT = 0;
u64 FLAGS_OF_SSE = 0;
int const * const GetAVXSUPPORT = &AVX_SUPPORT;
u64 const * const GetFlagsOfSSE = &FLAGS_OF_SSE;

void scan4SSE(){
    CPUID_RESULT_t page1 = CPU_ID(1, 0);

    if (page1.rdx & (1<<26U))    FLAGS_OF_SSE |= SSE2;
    if (page1.rcx & (1<<0U))     FLAGS_OF_SSE |= SSE3;
    if (page1.rcx & (1<<19U))    FLAGS_OF_SSE |= SSE4_1;
    if (page1.rcx & (1<<20U))    FLAGS_OF_SSE |= SSE4_2;
    if (page1.rcx & (1<< 6U))    FLAGS_OF_SSE |= SSE4_A;
    if (page1.rcx & (1<<11U))    FLAGS_OF_SSE |= XOP;
    if (page1.rcx & (1<<16U))    FLAGS_OF_SSE |= FMA4;
    if (page1.rcx & (1<<29U))    FLAGS_OF_SSE |= CVT16;
    if (page1.rcx & (1<<28U))    FLAGS_OF_SSE |= AVX;
    if (page1.rcx & (1<<26U))    FLAGS_OF_SSE |= XSAVE;

    CPUID_RESULT_t page7_0 = CPU_ID(7, 0);
    if (page7_0.rdx & (1<<26U))  FLAGS_OF_SSE |= AVX2;

    if (GetSSEFlag(AVX) == 1 && GetSSEFlag(XSAVE) == 1)
        AVX_SUPPORT = 1;
}

void setSSE(u64 __value){
    FLAGS_OF_SSE = __value;

    if (GetSSEFlag(AVX) && GetSSEFlag(XSAVE))
        AVX_SUPPORT = 1;
}
