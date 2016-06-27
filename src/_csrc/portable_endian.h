// "License": Public Domain
// I, Mathias Panzenböck, place this file hereby into the public domain. Use it at your own risk for whatever you like.
// In case there are jurisdictions that don't support putting things in the public domain you can also consider it to
// be "dual licensed" under the BSD, MIT and Apache licenses, if you want to. This code is trivial anyway. Consider it
// an example on how to get the endian conversion functions on different platforms.

#ifndef PORTABLE_ENDIAN_H__
#define PORTABLE_ENDIAN_H__

#if (defined(_WIN16) || defined(_WIN32) || defined(_WIN64)) && !defined(__WINDOWS__)

#   define __WINDOWS__

#endif

#if defined(__linux__) || defined(__CYGWIN__)
/* Define necessary macros for the header to expose all fields. */
#   define _BSD_SOURCE
#   define __USE_BSD
#   define _DEFAULT_SOURCE
#   include <endian.h>
#   include <features.h>
/* See http://linux.die.net/man/3/endian */
#   if !defined(__GLIBC__) || !defined(__GLIBC_MINOR__) || ((__GLIBC__ < 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ < 9)))
#       include <arpa/inet.h>
#       if defined(__BYTE_ORDER) && (__BYTE_ORDER == __LITTLE_ENDIAN)
#           define htobe16(x) htons(x)
#           define htole16(x) (x)
#           define be16toh(x) ntohs(x)
#           define le16toh(x) (x)

#           define htobe32(x) htonl(x)
#           define htole32(x) (x)
#           define be32toh(x) ntohl(x)
#           define le32toh(x) (x)

#           define htobe64(x) (((uint64_t)htonl(((uint32_t)(((uint64_t)(x)) >> 32)))) | (((uint64_t)htonl(((uint32_t)(x)))) << 32))
#           define htole64(x) (x)
#           define be64toh(x) (((uint64_t)ntohl(((uint32_t)(((uint64_t)(x)) >> 32)))) | (((uint64_t)ntohl(((uint32_t)(x)))) << 32))
#           define le64toh(x) (x)
#       elif defined(__BYTE_ORDER) && (__BYTE_ORDER == __BIG_ENDIAN)
#           define htobe16(x) (x)
#           define htole16(x) ((((((uint16_t)(x)) >> 8))|((((uint16_t)(x)) << 8)))
#           define be16toh(x) (x)
#           define le16toh(x) ((((((uint16_t)(x)) >> 8))|((((uint16_t)(x)) << 8)))

#           define htobe32(x) (x)
#           define htole32(x) (((uint32_t)htole16(((uint16_t)(((uint32_t)(x)) >> 16)))) | (((uint32_t)htole16(((uint16_t)(x)))) << 16))
#           define be32toh(x) (x)
#           define le32toh(x) (((uint32_t)le16toh(((uint16_t)(((uint32_t)(x)) >> 16)))) | (((uint32_t)le16toh(((uint16_t)(x)))) << 16))

#           define htobe64(x) (x)
#           define htole64(x) (((uint64_t)htole32(((uint32_t)(((uint64_t)(x)) >> 32)))) | (((uint64_t)htole32(((uint32_t)(x)))) << 32))
#           define be64toh(x) (x)
#           define le64toh(x) (((uint64_t)le32toh(((uint32_t)(((uint64_t)(x)) >> 32)))) | (((uint64_t)le32toh(((uint32_t)(x)))) << 32))
#       else
#           error Byte Order not supported or not defined.
#       endif
#   endif

#elif defined(__APPLE__)

#   include <libkern/OSByteOrder.h>

#   define htobe16(x) OSSwapHostToBigInt16(x)
#   define htole16(x) OSSwapHostToLittleInt16(x)
#   define be16toh(x) OSSwapBigToHostInt16(x)
#   define le16toh(x) OSSwapLittleToHostInt16(x)

#   define htobe32(x) OSSwapHostToBigInt32(x)
#   define htole32(x) OSSwapHostToLittleInt32(x)
#   define be32toh(x) OSSwapBigToHostInt32(x)
#   define le32toh(x) OSSwapLittleToHostInt32(x)

#   define htobe64(x) OSSwapHostToBigInt64(x)
#   define htole64(x) OSSwapHostToLittleInt64(x)
#   define be64toh(x) OSSwapBigToHostInt64(x)
#   define le64toh(x) OSSwapLittleToHostInt64(x)

#   define __BYTE_ORDER    BYTE_ORDER
#   define __BIG_ENDIAN    BIG_ENDIAN
#   define __LITTLE_ENDIAN LITTLE_ENDIAN
#   define __PDP_ENDIAN    PDP_ENDIAN

#elif defined(__OpenBSD__)

#   include <sys/endian.h>

#elif defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__)

#   include <sys/endian.h>

#   if !defined(be16toh)
    #   define be16toh(x) betoh16(x)
    #   define le16toh(x) letoh16(x)
#   endif

#   if !defined(be32toh)
    #   define be32toh(x) betoh32(x)
    #   define le32toh(x) letoh32(x)
#   endif

#   if !defined(be64toh)
    #   define be64toh(x) betoh64(x)
    #   define le64toh(x) letoh64(x)
#   endif

#elif defined(__WINDOWS__)

#   if BYTE_ORDER == LITTLE_ENDIAN

#       define htobe16(x) _byteswap_ushort(x)
#       define htole16(x) (x)
#       define be16toh(x) _byteswap_ushort(x)
#       define le16toh(x) (x)

#       define htobe32(x) _byteswap_ulong(x)
#       define htole32(x) (x)
#       define be32toh(x) _byteswap_ulong(x)
#       define le32toh(x) (x)

#       define htobe64(x) _byteswap_uint64(x)
#       define be64toh(x) _byteswap_uint64(x)
#       define htole64(x) (x)
#       define le64toh(x) (x)

#   elif BYTE_ORDER == BIG_ENDIAN

        /* that would be xbox 360 */
#       define htobe16(x) (x)
#       define htole16(x) __builtin_bswap16(x)
#       define be16toh(x) (x)
#       define le16toh(x) __builtin_bswap16(x)

#       define htobe32(x) (x)
#       define htole32(x) __builtin_bswap32(x)
#       define be32toh(x) (x)
#       define le32toh(x) __builtin_bswap32(x)

#       define htobe64(x) (x)
#       define htole64(x) __builtin_bswap64(x)
#       define be64toh(x) (x)
#       define le64toh(x) __builtin_bswap64(x)

#   else

#       error byte order not supported

#   endif

#   define __BYTE_ORDER    BYTE_ORDER
#   define __BIG_ENDIAN    BIG_ENDIAN
#   define __LITTLE_ENDIAN LITTLE_ENDIAN
#   define __PDP_ENDIAN    PDP_ENDIAN

#else

#   error platform not supported

#endif

#endif
