#include "ht.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

HashTable* create_ht() {
    HashTable* ht = malloc(sizeof(HashTable));
    ht->capacity = INITIAL_CAPACITY;
    ht->occupancy = 0;
    ht->entries = malloc(sizeof(Entry) * ht->capacity);
    return ht;
}

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static uint64_t hash_func(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

int set_kv(HashTable* ht, const char* key, int val) {
    // Todo: Implement open addressing
    uint64_t hash = hash_func(key);
    int mod_hash = hash % ht->capacity;
    ht->entries[mod_hash] = (Entry){.key = key, .val = val};

    // TODO: if anything goes wrong indicate using return code
    return 0;
}

int get_v(HashTable* ht, const char* key) {
    // Todo: Implement open addressing
    uint64_t hash = hash_func(key);
    int mod_hash = hash % ht->capacity;

    return ht->entries[mod_hash].val;
}
