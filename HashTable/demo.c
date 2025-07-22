#include <stdio.h>
#include "ht.c"

int main(void) {
    HashTable* ht = create_ht();
    set_kv(ht, "hehellelooohello", 12);
    printf("%d", get_v(ht, "hehellelooohello"));
    return 0;
}
