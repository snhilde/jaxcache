#include <stdio.h>
#include <stdlib.h>

typedef struct _jax_list {
	char *URL;
	struct _jax_list *prev;
	struct _jax_list *next;
} jax_list;

typedef struct _jax_hash {
	jax_list **list;
} jax_hash;

typedef struct _jax_cache {
	jax_hash *hash;
} jax_cache;
