#include "jaxcache.h"

typedef struct _jaxlist {
	char *URL;
	struct _jaxlist *prev;
	struct _jaxlist *next;
} jaxlist;

struct _jaxcache {
	jaxlist **hash;
	jaxlist *head;
};

jaxcache * jaxcache_create(size_t size)
{
	jaxcache *cache;
	
	cache = malloc(sizeof(*cache));
	if (!cache)
		return NULL;
	
	cache->hash = calloc(size, sizeof(*cache->hash));
	if (!cache->hash)
		return NULL;
	
	cache->head = malloc(sizeof(*cache->head));
	if (!cache->head)
		return NULL;
	
	return cache;
}
