#pragma once
#include "variable.h"
#include <string.h>

///<summary>
///An entry in the hashtable containing a variable field, a key string and a pointer to the next entry in the same bucket.
///<seealso cref="HashTable"/>
///</summary>
typedef struct {
	Variable* v;
	char* key; //TODO: This is nice to have, but it is sort of redundant due to it being the same as v->key;
	struct HTEntry* next;
} HTEntry;

///<summary>A hashtable is an efficient way of storing a pair of (key,value) where the key is unique.</summary>
typedef struct{
	int size;
	HTEntry** table;
} HashTable;

typedef HashTable Dictionary; // A dictionary is a hashtable

//TODO: create a global variables dictionary
//TODO: create a stack of dictionaries (each dictionary is a new function stack frame with local variables).

///<summary>Creates a hashtable with the specified size</summary>
///	<param name="size"> the size of the bucket array of the hashtable </param>
/// <returns> A pointer to the created hash table </returns>
HashTable* ht_create(int size);

void ht_free(HashTable* hashTable);

///<summary>
///Hashes a string using a defined algorithm and caps the resulting value to the hash table size.
///<para>By default the funtion uses the Jenkins one-at-a-time hash algorithm</para>
///<para>Use #define HASHTABLE_HASH_DJB2 to change the algorithm to DJB2</para>
///</summary>
///	<param name="key"> The string to hash </param>
///	<param name="hashTableMax"> The size of the bucket array of the hashtable </param>
size_t ht_hash(char *key, size_t hashTableMax);

///<summary>If the key doesn't exist in the dictionary, the function adds a new entry. If the key exist it modifies the value.</summary>
///	<param name="hashtable"> A pointer to the hashtable </param>
///	<param name="key"> The key for the hashtable (ensure that it is the same as the variable name) </param>
///	<param name="entry"> Entry to add/modify </param>
void ht_set(HashTable* hashtable, char* key, HTEntry* entry);

///<summary>
///	If the key exists in the dictionary, the function returns the value associated with it.
///</summary>
///	<param name="hashtable"> A pointer to the hashtable </param>
///	<param name="key"> Key to find </param>
Variable* ht_get(HashTable* hashtable, char* key);

///<summary>
///	If the key exists in the dictionary, the function removes the entry.
///</summary>
///	<param name="hashtable"> A pointer to the hashtable </param>
///	<param name="key"> Key to remove </param>
void ht_remove(HashTable* hashtable, char* key);
