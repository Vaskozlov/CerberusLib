#ifndef cerberus_h
#define cerberus_h

#ifndef STRX
#  define STRX(x) #x
#  define STR(x) STRX(x)
#endif /* STRX */

#if defined(__clang__)
#  define COMPILER_NAME "clang"
#elif defined(__GNUC__)
#  define COMPILER_NAME "gcc"
#endif

#include <cerberus/cerbMath.h>

#if defined(__cplusplus)
#  include <cerberus/cerberusc++.hpp>
#else
#  include <cerberus/cerberusc.h>
#endif /* __cplusplus */

__BEGIN_DECLS

extern int AVX_SUPPORT;

__END_DECLS

#endif /* cerberus_h */
