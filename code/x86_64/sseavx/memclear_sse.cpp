#include <cerberus/memclear.h>

#define SSE_XMM_SIZE 16

void cerbMemclear(const void * const m_start, const size_t m_count){
    if (*GetAVXSUPPORT) memclear_avx(m_start, m_count);
    else memclear_sse(m_start, m_count);
}

void memclear_sse(const void * const m_start, size_t m_count){
    char *data2set = (char*)m_start;
    char *aligned = (char*)cerb::align((size_t)data2set, 4);
    auto times = (size_t)(aligned - data2set);
    m_count -= cerb::MIN(times, m_count);

    __asm__(
        "rep stosb"
        :
        : "a"((size_t)(0)), "D"((size_t)data2set), "c"(times  - (m_count==0))
    );

    __asm__ __volatile__(
        "pxor %xmm0, %xmm0	\n"    // set XMM0 to 0
    );

    for(; m_count >= 64; m_count -= 64)
    {
        __asm__ __volatile__(
            " movdqa %%xmm0, 0(%0) 	        \n"    // move 16 bytes from XMM0 to %0 + 0
            " movdqa %%xmm0, 16(%0)	        \n"
            " movdqa %%xmm0, 32(%0)	        \n"
            " movdqa %%xmm0, 48(%0)	        \n"
            :
            : "r"(aligned)
        );
        aligned += 64;
    }

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


void memclear_sse_old(const void * const m_start, const size_t m_count){
    size_t i = 0;
    if (m_count == 0) return;

    while(((size_t)m_start + i) & (SSE_XMM_SIZE - 1) && i < m_count)
    {
        __asm__ (
            "stosb\n"
            :
            :"D"((size_t)m_start + i), "a"(0)
        );
        i++;
    }
    __asm__ __volatile__ (
        " pxor %xmm0, %xmm0  	\n"    // set XMM0 to 0
    );

    for(; i + 64 <= m_count; i += 64)
    {
        __asm__ __volatile__(
            " movdqa %%xmm0, 0(%0) 	\n"    // move 16 bytes from XMM0 to %0 + 0
            " movdqa %%xmm0, 16(%0)	\n"
            " movdqa %%xmm0, 32(%0)	\n"
            " movdqa %%xmm0, 48(%0)	\n"
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
}

size_t strlen_sse(const char * const str){
   size_t index;

   __asm__(
       " mov $-16, %0                     \n"
       " pxor %%xmm0, %%xmm0              \n"
       ".strlen_4_2_start:                \n"
       " add $16, %0                      \n"
       " pcmpistri $0x08, (%0,%1), %%xmm0 \n"
       " jnz .strlen_4_2_start            \n"
       " add %2, %0                       \n"
       : "=a"(index)
       : "d"((size_t)str), "c"((size_t)str)
    );
 
    return index;
}
