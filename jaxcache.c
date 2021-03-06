#include "jaxcache.h"

typedef struct _jaxlist {
	char *URL;
	void *data;
	struct _jaxlist *prev;
	struct _jaxlist *next;
} jaxlist;

struct _jaxcache {
	jaxlist **hash_table;
	jaxlist *head;
	jaxlist *tail;
	size_t num_elem;
	size_t capacity;
};

int jaxcache_create(jaxcache **cache, size_t capacity)
{
	*cache = malloc(sizeof(**cache));
	if (!*cache)
		return 1;
	
	(*cache)->hash_table = calloc(capacity, sizeof(*(*cache)->hash_table));
	if (!(*cache)->hash_table)
		return 1;
	
	(*cache)->head = NULL;
	(*cache)->tail = NULL;
	
	(*cache)->num_elem = 0;
	(*cache)->capacity = capacity;
	
	return 0;
}

static void node_delete(jaxlist *node)
{
	free(node->URL);
	free(node->data);
	free(node);
}

static void list_delete(jaxlist *head)
{
	jaxlist *node;
	jaxlist *next;
	
	for (node = head; node; node = next) {
		next = node->next;
		node_delete(node);
	}
}

void jaxcache_destroy(jaxcache *cache)
{
	list_delete(cache->head);
	
	free(cache->hash_table);
	free(cache);
}

static void node_link_head(jaxcache *cache, jaxlist *node)
{
	node->prev = NULL;
	node->next = cache->head;
	if (node->next)
		node->next->prev = node;
	else
		cache->tail = node;
	
	cache->head = node;
}

static size_t get_index(jaxcache *cache, char *URL, uintmax_t hash)
{
	size_t index;
	
	index = hash / cache->capacity;
	while(cache->hash_table[index] && strcmp(URL, cache->hash_table[index]->URL) != 0) {
		index++;
		if (index == cache->capacity)
			index = 0;
	}
	
	return index;
}

static uintmax_t get_hash(char *URL)
{
	// placeholder function
	
	return 1UL << 16;
}

static void node_insert(jaxcache *cache, jaxlist *node)
{
	uintmax_t hash;
	size_t index;
	
	hash = get_hash(node->URL);
	index = get_index(cache, node->URL, hash);
	cache->hash_table[index] = node;
}

static int node_new(jaxlist **node_ptr, char *URL, void *data, size_t data_size)
{
	jaxlist *node;
	
	node = malloc(sizeof(*node));
	if (!node)
		return 1;
	
	node->URL = strdup(URL);
	
	node->data = malloc(data_size);
	if (!node->data) {
		free(node->URL);
		free(node);
		return 1;
	}
	memcpy(node->data, data, data_size);
	
	*node_ptr = node;
	
	return 0;
}

static void remove_cold(jaxcache *cache)
{
	jaxlist *node;
	uintmax_t hash;
	size_t index;
	
	node = cache->tail;
	cache->tail = node->prev;
	
	hash = get_hash(node->URL);
	index = get_index(cache, node->URL, hash);
	cache->hash_table[index] = NULL;
	
	node_delete(node);
}

static void splice_hot(jaxcache *cache, jaxlist *node)
{
	if (node->prev) {
		if (node->next) {
			node->next->prev = node->prev;
			node->prev->next = node->next;
		} else
			cache->tail = node->prev;
	
	node->next = cache->head;
	node->prev = NULL;
	
	cache->head = node;
	}
}

int jaxcache_add(jaxcache *cache, char *URL, void *data, size_t data_size)
{
	jaxlist *node;
	
	if (cache->num_elem == cache->capacity)
		remove_cold(cache);
	
	if (node_new(&node, URL, data, data_size) != 0)
		return 1;
	
	node_insert(cache, node);
	node_link_head(cache, node);
	cache->num_elem++;
	
	return 0;
}

void * jaxcache_lookup(jaxcache *cache, char *URL)
{
	uintmax_t hash;
	size_t index;
	jaxlist *node;
	
	hash = get_hash(URL);
	index = get_index(cache, URL, hash);
	node = cache->hash_table[index];
	
	splice_hot(cache, node);
	
	return node->data;
}

size_t jaxcache_num(jaxcache *cache)
{
	return cache->num_elem;
}

size_t jaxcache_capacity(jaxcache *cache)
{
	return cache->capacity;
}
