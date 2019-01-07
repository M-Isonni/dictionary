#include "dictionary.h"
#include <SDL.h>

dictionary_t *new_dict(const size_t hash_map_size)
{
    dictionary_t *new_dict = malloc(sizeof(dictionary_t));
    if (!new_dict)
        return NULL;
    size_t hash_map_memory_size = sizeof(struct aiv_dict_item *) * hash_map_size;
    new_dict->hash_map = malloc(hash_map_memory_size);
    if (!new_dict->hash_map)
    {
        free(new_dict);
        return NULL;
    }
    memset(new_dict->hash_map, 0, hash_map_memory_size);
    new_dict->hash_map_size = hash_map_size;
    return new_dict;
}

int add_to_dictionary(dictionary_t *dict,const char *key, size_t key_len, void *value)
{
    int hash = hashing(key, dict->hash_map_size);
    key_value_pair_t *current = dict->hash_map[hash];
    key_value_pair_t *last_current = current;

    while (current)
    {
        if (current->key_length == key_len && !memcmp(current->key, key, key_len))
        {
            current->value = value;
            return 0;
        }
        last_current = current;
        current = current->next;
    }

    key_value_pair_t *new_key_value_pair = malloc(sizeof(key_value_pair_t));
    if (new_key_value_pair == NULL)
    {
        return -1;
    }
    new_key_value_pair->key = key;
    new_key_value_pair->key_length = key_len;
    new_key_value_pair->next = NULL;
    new_key_value_pair->value = value;

    if (last_current != NULL)
        last_current->next = new_key_value_pair;
    else
    {
        dict->hash_map[hash] = new_key_value_pair;
    }

    return 0;
}

void *get_value(dictionary_t *dict, const char *key, size_t key_len)
{
    int hash = hashing(key, dict->hash_map_size);
    key_value_pair_t *current = dict->hash_map[hash];
    while (current)
    {
        if (current->key_length == key_len && !memcmp(current->key, key, key_len))
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void *remove_key_value_pair(dictionary_t *dict, const char *key, size_t key_len)
{
    int hash = hashing(key, dict->hash_map_size);
    key_value_pair_t *current = dict->hash_map[hash];
    while (current)
    {
        if (current->key_length == key_len && !memcmp(current->key, key, key_len))
        {
           memset(current,0,sizeof(key_value_pair_t));
           return 0;
        }
        current = current->next;
    }
    return NULL;
}

unsigned int hashing(const void* key, unsigned int hashsize){
    unsigned hashval;
    const char* key_string=key;
    for (hashval = 0; *key_string != '\0'; key_string++)
        hashval = *key_string + HASH_MODIFIER * hashval;    
    return hashval % hashsize;
}