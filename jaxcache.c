#include "jaxcache.h"

typedef struct _jaxlist {
	char *URL;
	struct _jaxlist *prev;
	struct _jaxlist *next;
} jaxlist;

struct _jaxcache {
	jaxlist **hash;
	jaxlist *list;
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
	
	(*cache)->list = malloc(sizeof(*(*cache)->list));
	if (!(*cache)->list)
		return 1;
	
	(*cache)->capacity = capacity;
	
	return 0;
}

static void list_delete(jaxlist *head)
{
	jaxlist *node;
	jaxlist *next;
	
	for (node = head; node; node = next) {
		next = node->next;
		free(node->URL);
		free(node);
	}
}

void jaxcache_destroy(jaxcache *cache)
{
	list_delete(cache->list);
	
	free(cache->hash);
	free(cache->list);
	free(cache);
}

size_t jaxcache_capacity(jaxcache *cache)
{
	return cache->capacity;
}
