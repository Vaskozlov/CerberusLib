#ifndef memclear_h
#define memclear_h

#include <stddef.h>
#include <inttypes.h>
#include <cerberus/cerberus.h>

#if defined(__x86_64__)

__BEGIN_DECLS

enum SSE_FLAGS {
    SSE2    = 1<<0U,
    SSE3    = 1<<1U,
    SSE4_1  = 1<<2U,
    SSE4_2  = 1<<3U,
    SSE4_A  = 1<<4U,
    XOP     = 1<<5U,
    FMA4    = 1<<6U,
    CVT16   = 1<<7U,
    AVX     = 1<<8U,
    XSAVE   = 1<<9U,
    AVX2    = 1<<10U,
    AVX512  = 1<<11U // Cerberus will not support AVX512
};

#define GetSSEFlag(flag) ((*GetFlagsOfSSE & (flag)) > 0)

typedef struct{
    u64 rax;
    u64 rcx;
    u64 rdx;
} __attribute__((packed)) CPUID_RESULT_t;

extern u64 const * const GetFlagsOfSSE;
extern int const * const GetAVXSUPPORT;

void memset8 (void *__address, u8  __value, size_t __times);
void memset16(void *__address, u16 __value, size_t __times);
void memset32(void *__address, u32 __value, size_t __times);
void memset64(void *__address, u64 __value, size_t __times);

void memcpy8  (void *__dest, const void *__src, size_t __times);
void memcpy16 (void *__dest, const void *__src, size_t __times);
void memcpy32 (void *__dest, const void *__src, size_t __times);
void memcpy64 (void *__dest, const void *__src, size_t __times);

void scan4SSE();
void setSSE(u64 __value);
extern void DO_NOT_OPTIMIZE(i64);

void EnableSSEIN();
void EnableAVXIN();
void EnableXSAVEIN();
CPUID_RESULT_t CPU_ID(u64 page, u64 subpage);

size_t strlen_sse(const char * const str);
void memclear_sse(const void * const m_start, size_t m_count);
void memclear_avx (const void * const m_start, size_t m_count);
void cerbMemclear(const void * const m_start, const size_t m_count);

__END_DECLS

#if defined(__cplusplus)

namespace cerb{
    always_inline static void memset8(void *__address, u8 __value, size_t __times){
        __asm__ __volatile__ (
            "rep stosb"
            :
            : "a"(__value), "D"(__address), "c"(__times)
        );
    }

    always_inline static void memset16(void *__address, u16 __value, size_t __times){
        __asm__ __volatile__ (
            "rep stosw"
            :
            : "a"(__value), "D"(__address), "c"(__times)
        );
    }

    always_inline static void memset32(void *__address, u32 __value, size_t __times){
        __asm__ __volatile__ (
            "rep stosl"
            :
            : "a"(__value), "D"(__address), "c"(__times)
        );
    }

    always_inline void memset64(void *__address, u64 __value, size_t __times){
        __asm__ __volatile__ (
            "rep stosq"
            :
            : "a"(__value), "D"(__address), "c"(__times)
        );
    }
}

#endif /* __cplusplus */
#endif /* __x86_64__ */
#endif /* memclear_h */
