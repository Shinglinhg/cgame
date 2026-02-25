// CC0 Simple dynamic arrays in C. 
// Doesn't require STB style implementation nor linking, 
// include this header wherever you need and start using it!

#ifndef SDA_H
#define SDA_H

#ifndef NO_STANDARD_LIBRARY
#   include <stddef.h>
#   include <stdlib.h>
#endif

// Initial capacity of an empty array
#ifndef SDA_INITIAL_CAPACITY
#   define SDA_INITIAL_CAPACITY 8
#endif

// Which realloc and free function should be used
#ifndef SDA_FUNC_REALLOC
#   define SDA_FUNC_REALLOC realloc
#endif
#ifndef SDA_FUNC_FREE
#   define SDA_FUNC_FREE free
#endif

// What the library should do when out of memory for reallocations
#ifndef SDA_ON_OOM
#   ifndef NO_STANDARD_LIBRARY
#       include <stdio.h>
#   endif
#   define SDA_ON_OOM do { fprintf(stderr, "Out of memory\n"); exit(EXIT_FAILURE); } while (0)
#endif

#define dynamic_array(type) struct { \
    type *items; \
    size_t count; \
    size_t capacity; \
}

#define sda_push(array, ...) do { \
    if ((array).count >= (array).capacity) { \
        (array).capacity = (array).capacity ? (array).capacity * 2 : SDA_INITIAL_CAPACITY; \
        void *tmp = SDA_FUNC_REALLOC((array).items, (array).capacity * sizeof(*(array).items)); \
        if (!tmp) SDA_ON_OOM; \
        (array).items = tmp; \
    } \
    (array).items[(array).count++] = (__VA_ARGS__); \
} while (0)

#define sda_allocate(array) ({ \
    if ((array).count >= (array).capacity) { \
        (array).capacity = (array).capacity ? (array).capacity * 2 : SDA_INITIAL_CAPACITY; \
        void *tmp = SDA_FUNC_REALLOC((array).items, (array).capacity * sizeof(*(array).items)); \
        if (!tmp) SDA_ON_OOM; \
        (array).items = tmp; \
    } \
    &(array).items[(array).count++]; \
})

#define sda_get(array, index) (&(array).items[(index)])
#define sda_back(array) ((array).count > 0 ? (array).items[(array).count - 1] : 0)
#define sda_free(array) do { SDA_FUNC_FREE((array).items); (array).items = NULL; (array).count = (array).capacity = 0; } while (0)

#define sda_pop(array, out_ptr) \
    do { \
        if ((array).count > 0) \
            *(out_ptr) = (array).items[--(array).count]; \
    } while (0)

#endif // SDA_H