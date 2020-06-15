#include "winmac.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "hashtable.h"

int init_hashtable(hashtable_t *table, unsigned modulus) {
	size_t size;
	table->modulus = modulus;
	size = (size_t)modulus * sizeof(hashnode_t*);
	table->table = (hashnode_t**)malloc(size);
	if(!table->table)
		return 0;
	memset(table->table, 0, size);
	table->pending_deletion = NULL;
	return 1;
}

int put_hashtable(hashtable_t *table, jlong key, jlong value) {
	hashnode_t *new_node;
	unsigned index;
	if(table->pending_deletion) {
		new_node = table->pending_deletion;
		table->pending_deletion = NULL;
	}
	else {
		new_node = (hashnode_t*)malloc(sizeof(hashnode_t));
		if(!new_node)
			return 0;
	}
	new_node->key = key;
	new_node->value = value;
	index = (unsigned)((uint64_t)key % (uint64_t)table->modulus);
	new_node->next = table->table[index];
	table->table[index] = new_node;
	return 1;
}

int get_hashtable(hashtable_t *table, jlong key, jlong *value) {
	unsigned index;
	const hashnode_t *node;
	index = (unsigned)((uint64_t)key % (uint64_t)table->modulus);
	node = table->table[index];
	for(; node; node = node->next) {
		if(node->key == key) {
			*value = node->value;
			return 1;
		}
	}
	return 0;
}

int erase_hashtable(hashtable_t *table, jlong key) {
	unsigned index;
	hashnode_t *node, **link;
	index = (unsigned)((uint64_t)key % (uint64_t)table->modulus);
	for(link = table->table + index; (node = *link); link = &node->next) {
		if(node->key == key)
			break;
	}
	if(!node)
		return 0;
	node->value = (jlong)0;
	if(table->pending_deletion)
		free(table->pending_deletion);
	table->pending_deletion = node;
	*link = node->next;
	return 1;
}
