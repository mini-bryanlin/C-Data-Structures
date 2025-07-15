#include <stdlib.h>
#include <string.h>

#include "./hashmap.h"

static struct hm_item* new_hashmap_items(const char * key, const char * value){

    struct hm_item *i = malloc(sizeof(struct hm_item));
    i -> key = strdup(key) ;
    i -> value = strdup(value);

    return i;

}

struct hm_table * new_hashmap_table (void){
    struct hm_table * hashmap = malloc(sizeof(struct hm_table));

    hashmap ->size = 53;
    hashmap -> count = 0;
    hashmap -> items = calloc(hashmap->size, sizeof(struct hm_item*));
    
    return hashmap;

}

static void delete_item(struct hm_item *i){
    free (i->key);
    free (i->value);
    free(i);

}

static void delete_hashmap(struct hm_table *table){
    for (int i = 0; i< table->size; i ++){
        struct hm_item * item = *((table->items)+i);
        if (item != NULL){
            delete_item(item);
        }

    }
    free (table->items);
    free (table);
}