#include "../include/uniform_container.h"

uobj uobj_unify(const void *p, size_t size, char type[TYPENAME_SIZE]) {
    uobj uo;
    uo.container = malloc(size);

    if (uo.container == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    memcpy(uo.container, p, size);
    strncpy(uo.type, type, TYPENAME_SIZE);

    return uo;
}

void* uobj_make_unique(const uobj *uo) {
    return uo->container;
}

void uobj_free(uobj *uo) {
    free(uo->container);
    return;
}