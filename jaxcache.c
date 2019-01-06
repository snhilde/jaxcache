#include "jaxcache.h"

typedef struct _jaxlist {
	char *URL;
	struct _jaxlist *prev;
	struct _jaxlist *next;
} jaxlist;

struct _jaxcache {
	jaxlist **hash;
	jaxlist *head;
	size_t capacity;
};

int jaxcache_create(jaxcache **cache, size_t capacity)
{
	*cache = malloc(sizeof(**cache));
	if (!*cache)
		return 1;
	
	(*cache)->hash = calloc(capacity, sizeof(*(*cache)->hash));
	if (!(*cache)->hash)
		return 1;
	
	(*cache)->head = malloc(sizeof(*(*cache)->head));
	if (!(*cache)->head)
		return 1;
	
	(*cache)->capacity = capacity;
	
	return 0;
}

size_t jaxcache_capacity(jaxcache *cache)
{
	return cache->capacity;
}
