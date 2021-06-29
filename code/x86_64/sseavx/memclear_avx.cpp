#include <cerberus/cerberus.h>
#include <cerberus/memclear.h>

#define AVX_YMM_SIZE 32

void memclear_avx(const void * const m_start, size_t m_count){
    char *data2set = (char*)m_start;
    char *aligned = (char*)cerb::align((size_t)data2set, 5);

    for (; data2set != aligned && m_count != 0; m_count--, data2set++)
        *data2set = 0;

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

    for (; m_count != 0; m_count--)
        *(aligned++) = 0;
}
