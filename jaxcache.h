#include <stdio.h>
#include <stdlib.h>

typedef struct _jaxcache jaxcache;

int jaxcache_create(jaxcache **cache, size_t max_capacity);
void jaxcache_destroy(jaxcache *cache);

int jaxcache_add(jaxcache *cache, char *URL, void *data, size_t data_size);
int jaxcache_lookup(jaxcache *cache, char *URL);

size_t jaxcache_capacity(jaxcache *cache);
