#include <cerberus/cerberus.h>
#include <cerberus/memclear.h>

#define AVX_YMM_SIZE 32

void memclear_avx(const void * const m_start, size_t m_count){
    char *data2set = (char*)m_start;
    char *aligned = (char*)cerb::align((size_t)data2set, 5);
    auto times = (size_t)(aligned - data2set);
    m_count -= cerb::MIN(times, m_count);

    __asm__(
        "rep stosb"
        :
        : "a"((size_t)(0)), "D"((size_t)data2set), "c"(times - (m_count==0))
    );

    __asm__ __volatile__(
        "vpxor %ymm0, %ymm0, %ymm0  	\n"    // set XMM0 to 0
    );

    for(; m_count >= 128; m_count -= 128)
    {
        __asm__ __volatile__(
            " vmovdqa %%ymm0, 0(%0) 	        \n"    // move 16 bytes from XMM0 to %0 + 0
            " vmovdqa %%ymm0, 32(%0)	        \n"
            " vmovdqa %%ymm0, 64(%0)	        \n"
            " vmovdqa %%ymm0, 96(%0)	        \n"
            :
            : "r"(aligned)
        );
        aligned += 128;
    }
    
    if (m_count == 0) [[unlikely]] return;

    __asm__(
        "rep stosl"
        :
        : "a"((size_t)(0)), "D"((size_t)aligned), "c"(m_count / 4)
    );

    __asm__(
        "rep stosb"
        :
        : "a"((size_t)(0)), "D"((size_t)aligned + (m_count & (~3))), "c"(m_count & 3)
    );
}
