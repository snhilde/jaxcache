#include <stdio.h>
#include <stdlib.h>

typedef struct _jaxcache jaxcache;

int jaxcache_create(jaxcache **cache, size_t max_capacity);
void jaxcache_destroy(jaxcache *cache);

size_t jaxcache_capacity(jaxcache *cache);
