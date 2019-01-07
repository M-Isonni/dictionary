#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASH_MODIFIER 31

typedef struct key_value_pair{
    const void* key;
    void* value;
    size_t key_length;
    struct key_value_pair* next;
} key_value_pair_t;

typedef struct dictionary{
    unsigned long size;
    size_t hash_map_size;
    key_value_pair_t** hash_map;
} dictionary_t;

dictionary_t *new_dict(const size_t hash_map_size);
unsigned int hashing(const void* key, unsigned int hashsize);
int add_to_dictionary(dictionary_t *dict,const char *key, size_t key_len, void *value);
void *get_value(dictionary_t *dict, const char *key, size_t key_len);
void *remove_key_value_pair(dictionary_t *dict, const char *key, size_t key_len);
