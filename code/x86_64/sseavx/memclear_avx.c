#include <cerberus/memclear.h>

#define AVX_YMM_SIZE 32

const void * memclear_avx(const void * const m_start, const size_t m_count){
    __volatile__ size_t i = 0;
    if (m_count == 0) return m_start;

    while(((size_t)m_start + i) & (AVX_YMM_SIZE - 1) && i < m_count)
    {
        __asm__ __volatile__("stosb\n" :: "D"((size_t)m_start + i), "a"(0));
        i++;
    }
   
    // clear 64-byte chunks of memory (4 32-byte operations)
    for(; i + 128 <= m_count; i += 128)
    {
        __asm__ __volatile__(
            "vpxor %%ymm0, %%ymm0, %%ymm0           \n"    // set YMM0 to 0
            " vmovdqa %%ymm0, 0(%0)	                \n"    // move 32 bytes from YMM0 to %0 + 0
            " vmovdqa %%ymm0, 32(%0)	            \n"
            " vmovdqa %%xmm0, 64(%0)	            \n"
            " vmovdqa %%ymm0, 96(%0)	            \n"
            :
            : "r"((size_t)m_start + i)
        );
    }
    
    // copy the remaining bytes (if any)
    __asm__(
        "rep stosb"
        :
        : "a"((size_t)(0)), "D"(((size_t)m_start) + i), "c"(m_count - i)
    );

    // "i" will contain the total amount of bytes that were actually transfered
    i += m_count - i;

    // we return "m_start" + the amount of bytes that were transfered
    return (void *)(((size_t)m_start) + i);
}
