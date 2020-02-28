#ifndef JWINWIN_JNI_HASHTABLE_H
#define JWINWIN_JNI_HASHTABLE_H

#include <jni.h>

typedef struct hashnode_t {
	jlong key;
	jlong value;
	struct hashnode_t *next;
} hashnode_t;

typedef struct hashtable_t {
	unsigned modulus;
	hashnode_t **table;
	hashnode_t *pending_deletion;
} hashtable_t;

int init_hashtable(hashtable_t *table, unsigned modulus);
int put_hashtable(hashtable_t *table, jlong key, jlong value);
int get_hashtable(hashtable_t *table, jlong key, jlong *value);
int erase_hashtable(hashtable_t *table, jlong key);

#endif /* JWINWIN_JNI_HASHTABLE_H */
