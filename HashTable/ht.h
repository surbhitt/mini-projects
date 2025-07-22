
#define INITIAL_CAPACITY 16
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct Entry {
    const char* key;
    int val;
} Entry;

typedef struct HashTable {
    Entry* entries;
    int capacity;
    int occupancy;
} HashTable;

HashTable* create_ht();
