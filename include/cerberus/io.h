#ifndef cerbIO_h
#define cerbIO_h

#include <cerberus/cerberus.h>

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

void EnableSSEIN();
void EnableAVXIN();
void EnableXSAVEIN();
CPUID_RESULT_t CPU_ID(u64 page, u64 subpage);

__END_DECLS

#if defined(__cplusplus)

namespace cerb{

    static always_inline void outb(unsigned short __port, unsigned char __val){
        __asm__ volatile ("outb %0,%1" : : "a" (__val), "dN" (__port));
    }

    static always_inline void outw(unsigned short __port, unsigned short __val){
        __asm__ volatile ("outw %0,%1" : : "a" (__val), "dN" (__port));
    }

    static always_inline void outl(unsigned short __port, unsigned int __val){
        __asm__ volatile ("outl %0,%1" : : "a" (__val), "dN" (__port));
    }

    static always_inline unsigned char inb(unsigned short __port){
        unsigned char __val;
        __asm__ volatile ("inb %1,%0" : "=a" (__val) : "dN" (__port));
        return __val;
    }

    static always_inline unsigned short inw(unsigned short __port){
        unsigned short __val;
        __asm__ volatile ("inw %1,%0" : "=a" (__val) : "dN" (__port));
        return __val;
    }

    static always_inline unsigned int inl(unsigned short __port){
        unsigned int __val;
        __asm__ volatile ("inl %1,%0" : "=a" (__val) : "dN" (__port));
        return __val;
    }

    static always_inline void outsb(unsigned short __port, const void *__buf, unsigned long __n){
        __asm__ volatile (
                "cld\n"
                "rep\n"
                "outsb"
            : "+S" (__buf), "+c" (__n)
            : "d" (__port)
        );
    }

    static always_inline void outsw(unsigned short __port, const void *__buf, unsigned long __n){
        __asm__ volatile (
                "cld\n"
                "rep\n"
                "outsw"
            : "+S" (__buf), "+c" (__n)
            : "d" (__port)
        );
    }

    static always_inline void outsl(unsigned short __port, const void *__buf, unsigned long __n){
        __asm__ volatile (
                "cld\n"
                "rep\n"
                "outsl"
            : "+S" (__buf), "+c"(__n)
            : "d" (__port)
        );
    }

    static always_inline void insb(unsigned short __port, void *__buf, unsigned long __n){
        __asm__ volatile (
                "cld\n"
                "rep\n"
                "insb"
            : "+D" (__buf), "+c" (__n)
            : "d" (__port)
        );
    }

    static always_inline void insw(unsigned short __port, void *__buf, unsigned long __n){
        __asm__ volatile (
                "cld\n"
                "rep\n"
                "insw"
            : "+D" (__buf), "+c" (__n)
            : "d" (__port)
        );
    }

    static always_inline void insl(unsigned short __port, void *__buf, unsigned long __n){
        __asm__ volatile (
                "cld\n"
                "rep\n"
                "insl"
            : "+D" (__buf), "+c" (__n)
            : "d" (__port)
        );
    }

    always_inline static void io_wait(){
        __asm__ __volatile__ ("outb %%al, $0x80" : : "a"(0));
    }
    
    always_inline static void hlt() {
        __asm__ __volatile__ ("hlt");
    }

    always_inline static void enableINT(){
        __asm__ __volatile__ ("sti");
    }

    always_inline static void disableINT(){
        __asm__ __volatile__ ("cli");
    }

    always_inline static void Go2Sleep() {
        while (1) { hlt();}
    }

    always_inline static void memset8(void *__address, u8 __value, size_t __times){
        ::memset8(__address, __value, __times);
    }

    always_inline static void memset64(void *__address, u16 __value, size_t __times){
        ::memset16(__address, __value, __times);
    }

    always_inline static void memset32(void *__address, u32 __value, size_t __times){
        ::memset32(__address, __value, __times);
    }

    always_inline static void memset64(void *__address, u64 __value, size_t __times){
        ::memset64(__address, __value, __times);
    }
}

#endif /* __cplusplus */ 

#endif /* cerbIO_h */
