#ifndef cerbIO_h
#define cerbIO_h

#include <cerberus/cerberus.h>

#if defined(__cplusplus)

namespace cerb{
    namespace IO{
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
    } // namespace  io
} //namespace cerb

#endif /* __cplusplus */ 

#endif /* cerbIO_h */
