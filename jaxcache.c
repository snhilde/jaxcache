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

jaxcache * jaxcreate_cache(size_t size)
{
	jaxcache *cache;
	
	cache = malloc(sizeof(*cache));
	
	return cache;
}
