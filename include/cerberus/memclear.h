#ifndef memclear_h
#define memclear_h

#include <stddef.h>
#include <inttypes.h>
#include <cerberus/cerberus.h>

__BEGIN_DECLS

size_t strlen_sse(const char * const str);

const char *cerbMemclear(const void * const m_start, const size_t m_count);
const void * memclear_sse(const void * const m_start, const size_t m_count);
const void * memclear_avx (const void * const m_start, const size_t m_count);

__END_DECLS

#endif /* memclear_h */
