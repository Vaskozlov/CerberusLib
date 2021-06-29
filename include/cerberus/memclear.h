#ifndef memclear_h
#define memclear_h

#include <stddef.h>
#include <inttypes.h>
#include <cerberus/cerberus.h>

#if defined(__x86_64__)

__BEGIN_DECLS

size_t strlen_sse(const char * const str);

void cerbMemclear(const void * const m_start, const size_t m_count);
void memclear_sse(const void * const m_start, size_t m_count);
void memclear_sse_old(const void * const m_start, const size_t m_count);
void memclear_avx (const void * const m_start, size_t m_count);

__END_DECLS

#endif /* __x86_64__ */

#endif /* memclear_h */
