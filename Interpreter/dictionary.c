#include "dictionary.h"

HashTable* ht_create(int size){

	HashTable* hashtable = NULL;
	int i;

	if (size < 1) return NULL;

	/* Allocate the table itself. */
	if ((hashtable = malloc(sizeof(HashTable))) == NULL) {
		return NULL;
	}

	/* Allocate pointers to the head nodes. */
	if ((hashtable->table = malloc(sizeof(HashTable *) * size)) == NULL) {
		free(hashtable);
		return NULL;
	}
	for (i = 0; i < size; i++) {
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;
}

void ht_free(HashTable* hashTable)
{
	for (int i = 0; i < hashTable->size; i++) {
		HTEntry* entry = hashTable->table[i];
		while (entry != NULL) {
			varFree(entry->v);
			free(entry->key);
			HTEntry* oldEntry = entry;
			entry = entry->next;
			free(oldEntry);
		}
	}
}

size_t ht_hash(char *key, size_t hashTableMax) {

	size_t hashval = 0;
	size_t i = 0;
	size_t keyLength = strlen(key);
	//#define HASHTABLE_HASH_DJB2

#ifdef HASHTABLE_HASH_DJB2
	hashval = 5381;
	int c;
	while (c = *key++)
		hashval = ((hashval << 5) + hashval) + c; /* hash * 33 + c */
#else
	//Jenkins one-at-a-time hash
	for (hashval = i = 0; i < keyLength; ++i) {
		hashval += key[i];
		hashval += (hashval << 10);
		hashval ^= (hashval >> 6);
	}
	hashval += (hashval << 3);
	hashval ^= (hashval >> 11);
	hashval += (hashval << 15);
#endif


	return hashval % hashTableMax;
}

void ht_set(HashTable* hashtable, char* key, HTEntry* entry) {
	if (hashtable == NULL) return;
	if (strcmp(key, key)) return; //ensure that the key is same as the variable name
	size_t bucket = 0;
	HTEntry* next = NULL;

	bucket = ht_hash(key, hashtable->size);

	next = hashtable->table[bucket];

	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
		next = next->next;
	}

	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
		// There's already an entry.
		Variable* old = next->v;
		next->v = entry->v;

		if(old != entry->v)
			free(old);
	}
	else {
		// No entry found. Insert this entry as the first one in the bucket.
		entry->next = hashtable->table[bucket];
		hashtable->table[bucket] = entry;
	}

}

Variable* ht_get(HashTable* hashtable, char* key) {
	if (hashtable == NULL)return;

	size_t bucket = 0;
	HTEntry* next = NULL;

	bucket = ht_hash(key, hashtable->size);

	next = hashtable->table[bucket];

	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
		next = next->next;
	}

	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
		return next->v;
	}

	return NULL;
}

void ht_remove(HashTable* hashtable, char* key) {
	if (hashtable == NULL)return;

	size_t bucket = 0;
	HTEntry* next = NULL;
	HTEntry* last = NULL;

	bucket = ht_hash(key, hashtable->size);

	next = hashtable->table[bucket];

	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
		last = next;
		next = next->next;
	}

	/* If the entry exists delete it from this bucket */
	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
		last->next = next->next;
	}
}