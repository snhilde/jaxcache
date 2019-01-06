#include "jaxcache.h"

typedef struct _jaxlist {
	char *URL;
	struct _jaxlist *prev;
	struct _jaxlist *next;
} jaxlist;

typedef struct _jaxhash {
	jaxlist **list;
} jaxhash;

struct _jaxcache {
	jaxhash *hash;
};

jaxcache * jaxcreate_cache(size_t size)
{
	jaxcache *cache;
	
	cache = malloc(sizeof(*cache));
	
	return cache;
}
