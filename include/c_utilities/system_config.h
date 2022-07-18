#ifndef C_UTILITIES_SYSTEM_CONFIG_H
#define C_UTILITIES_SYSTEM_CONFIG_H

#include <assert.h> // static_assert
#include <stdalign.h> // alignof
#include <stddef.h> // max_align_t, ptrdiff_t, size_t
#include <stdint.h> // PTRDIFF_MAX, SIZE_MAX

#include <c_utilities/bit.h> // IS_POWER_OF_TWO

#ifndef LEVEL1_DCACHE_LINESIZE
#define LEVEL1_DCACHE_LINESIZE (SIZE_MAX & 64U)
#endif // LEVEL1_DCACHE_LINESIZE
static_assert(
    LEVEL1_DCACHE_LINESIZE >= (ptrdiff_t) alignof(max_align_t) &&
        LEVEL1_DCACHE_LINESIZE <= PTRDIFF_MAX &&
        IS_POWER_OF_TWO(LEVEL1_DCACHE_LINESIZE),
    "LEVEL1_DCACHE_LINESIZE shall be a power of 2, "
    "not less than alignof(max_align_t) and not greater than PTRDIFF_MAX"
);

#ifndef LEVEL1_ICACHE_LINESIZE
#define LEVEL1_ICACHE_LINESIZE (SIZE_MAX & 64U)
#endif // LEVEL1_ICACHE_LINESIZE
static_assert(
    LEVEL1_ICACHE_LINESIZE >= (ptrdiff_t) alignof(max_align_t) &&
        LEVEL1_ICACHE_LINESIZE <= PTRDIFF_MAX &&
        IS_POWER_OF_TWO(LEVEL1_ICACHE_LINESIZE),
    "LEVEL1_ICACHE_LINESIZE shall be a power of 2, "
    "not less than alignof(max_align_t) and not greater than PTRDIFF_MAX"
);

#ifndef LEVEL2_CACHE_LINESIZE
#define LEVEL2_CACHE_LINESIZE (SIZE_MAX & 64U)
#endif // LEVEL2_CACHE_LINESIZE
static_assert(
    LEVEL2_CACHE_LINESIZE >= (ptrdiff_t) alignof(max_align_t) &&
        LEVEL2_CACHE_LINESIZE <= PTRDIFF_MAX &&
        IS_POWER_OF_TWO(LEVEL2_CACHE_LINESIZE),
    "LEVEL2_CACHE_LINESIZE shall be a power of 2, "
    "not less than alignof(max_align_t) and not greater than PTRDIFF_MAX"
);

#ifndef LEVEL3_CACHE_LINESIZE
#define LEVEL3_CACHE_LINESIZE (SIZE_MAX & 64U)
#endif // LEVEL3_CACHE_LINESIZE
static_assert(
    LEVEL3_CACHE_LINESIZE == 0U || (
        LEVEL3_CACHE_LINESIZE >= (ptrdiff_t) alignof(max_align_t) &&
        LEVEL3_CACHE_LINESIZE <= PTRDIFF_MAX &&
        IS_POWER_OF_TWO(LEVEL3_CACHE_LINESIZE)
    ),
    "LEVEL3_CACHE_LINESIZE shall either be equal to 0 or be a power of 2, "
    "not less than alignof(max_align_t) and not greater than PTRDIFF_MAX"
);

#ifndef LEVEL4_CACHE_LINESIZE
#define LEVEL4_CACHE_LINESIZE (SIZE_MAX & 0U)
#endif // LEVEL4_CACHE_LINESIZE
static_assert(
    LEVEL4_CACHE_LINESIZE == 0U || (LEVEL3_CACHE_LINESIZE != 0U &&
        LEVEL4_CACHE_LINESIZE >= (ptrdiff_t) alignof(max_align_t) &&
        LEVEL4_CACHE_LINESIZE <= PTRDIFF_MAX &&
        IS_POWER_OF_TWO(LEVEL4_CACHE_LINESIZE)
    ),
    "LEVEL4_CACHE_LINESIZE shall either be equal to 0 or be a power of 2, "
    "not less than alignof(max_align_t) and not greater than PTRDIFF_MAX. "
    "If LEVEL3_CACHE_LINESIZE is equal to 0, "
    "then LEVEL4_CACHE_LINESIZE shall be equal to 0 too"
);

#endif // C_UTILITIES_SYSTEM_CONFIG_H
