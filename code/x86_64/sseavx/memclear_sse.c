#include <cerberus/io.h>
#include <cerberus/memclear.h>

#define SSE_XMM_SIZE 16

const char *cerbMemclear(const void * const m_start, const size_t m_count){
    if (*GetAVXSUPPORT) return memclear_avx(m_start, m_count);
    return memclear_sse(m_start, m_count);
}

const void * memclear_sse(const void * const m_start, const size_t m_count){
    size_t i = 0;
    if (m_count == 0) return m_start;

    while(((size_t)m_start + i) & (SSE_XMM_SIZE - 1) && i < m_count)
    {
        __asm__ (
            "stosb\n"
            :
            :"D"((size_t)m_start + i), "a"(0)
        );
        i++;
    }
  
    for(; i + 64 <= m_count; i += 64)
    {
        __asm__ __volatile__(
            " pxor %%xmm0, %%xmm0  	\n"    // set XMM0 to 0
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

    // we return "m_start" + the amount of bytes that were transfered
    return (void *)(((size_t)m_start) + i);
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
