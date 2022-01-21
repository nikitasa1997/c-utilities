#include <stdalign.h> // alignas
#include <stddef.h> // size_t
#include <stdio.h> // printf
#include <stdlib.h> // free, malloc, rand
#include <string.h> // memset

#include <c_utilities/error_handling.h> // EXIT_IF
#include <c_utilities/types.h> // uchar

#define LEVEL1_DCACHE_LINESIZE ((size_t) 64U)

static inline size_t min(register const size_t x, register const size_t y) {
    return y < x ? y : x;
}

// ???
// ???
static inline void *memSwap(
    register void * const restrict s1,
    register void * const restrict s2,
    register const size_t n
) {
    register const uchar * const end1 = (uchar *) s1 + n;
    for (register uchar
        * restrict ptr1 = (uchar *) s1, * restrict ptr2 = (uchar *) s2;
        ptr1 < end1;
    ) {
        alignas(LEVEL1_DCACHE_LINESIZE) uchar buffer[LEVEL1_DCACHE_LINESIZE];
        register const size_t offset =
            min(LEVEL1_DCACHE_LINESIZE, (size_t) (end1 - ptr1));
        memcpy(buffer, ptr1, offset);
        memcpy(ptr1, ptr2, offset);
        memcpy(ptr2, buffer, offset);
        ptr1 += offset;
        ptr2 += offset;
    }
    return s1;
}

#define SIZE (1ULL << 30)

int main(void) {
    void * const restrict first = malloc(SIZE),
        * const restrict second = malloc(SIZE);
    EXIT_IF(first == NULL || second == NULL, "malloc");

    memset(first, rand(), SIZE);
    memset(second, rand(), SIZE);
    memSwap(first, second, SIZE);
    printf("first[0] = %hhu, second[0] = %hhu\n",
        *(const uchar *) first,
        *(const uchar *) second
    );
    free(first);
    free(second);

    return 0;
}
