#ifndef C_UTILITIES_COMMON_H
#define C_UTILITIES_COMMON_H

#include <limits.h> // CHAR_BIT
#include <stddef.h> // ptrdiff_t, size_t
#include <stdint.h> // intmax_t
#include <string.h> // memcpy

#include "arithmetic.h"
#include "types.h"

inline int arr_compare(
    register const void * const restrict arr, // restrict ???
    register const size_t index1,
    register const size_t index2,
    register const size_t size,
    register int (* const compare)(const void *, const void *)
) {
    return compare(
        ptr_offset(arr, index1, size),
        ptr_offset(arr, index2, size)
    );
}

inline void *arr_swap(
    register void * const restrict arr, // restrict ???
    register const size_t index1,
    register const size_t index2,
    register const size_t size
) {
    return mem_swap(
        ptr_offset(arr, index1, size),
        ptr_offset(arr, index2, size)
    );
}

inline void *mem_swap(
    void * const restrict s1,
    void * const restrict s2,
    register size_t n
) {
#   ifdef NDEBUG
    for (register uchar
        * restrict ptr1 = (uchar *) s1, * restrict ptr2 = (uchar *) s2;
        n-- > 0; ++ptr1, ++ptr2
    ) {
        register const uchar buffer = *ptr1;
        *ptr1 = *ptr2;
        *ptr2 = buffer;
    }
#   else
    uchar buffer[CHAR_BIT * sizeof(intmax_t)];
    static const size_t size = sizeof buffer;
    for (register uchar
        * restrict ptr1 = (uchar *) s1, * restrict ptr2 = (uchar *) s2;
        n > 0;
    ) {
        register const size_t offset = min(size, n);
        memcpy(buffer, ptr1, offset);
        memcpy(ptr1, ptr2, offset);
        memcpy(ptr2, buffer, offset);
        n -= offset;
        ptr1 += offset;
        ptr2 += offset;
    }
#   endif // NDEBUG
    return s1;
}

// restrict ???
inline ptrdiff_t ptr_diff(
    register const void * const ptr1,
    register const void * const ptr2,
    register const size_t size
) {
    return ((const char *) ptr1 - (const char *) ptr2) / (ptrdiff_t) size;
}

inline void *ptr_offset(
    register const void * const ptr,
    register const size_t index,
    register const size_t size
) {
#   if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wcast-qual"
#   elif defined(__GNUC__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wcast-qual"
#   endif
    return (char *) ptr + index * size;
#   if defined(__clang__)
#   pragma clang diagnostic pop
#   elif defined(__GNUC__)
#   pragma GCC diagnostic pop
#   endif
}

#endif // C_UTILITIES_COMMON_H
