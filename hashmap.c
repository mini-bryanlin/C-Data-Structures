#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./hashmap.h"
#define PRIME_1 151
#define PRIME_2 163

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

static int hash(const char *string, const int a, const int m){
    long hash = 0;
    int len = strlen(string);
    for (int i = 0; i < len; i++){
        hash += pow(a, (len-i-1)) * string[i];
        hash = hash%m;

    }
    return (int)hash;

}
static int get_hash(const char* string, const int bucket_num, const int attempt){
    const int hash_a = hash(string, PRIME_1, bucket_num);
    const int hash_b = hash(string, PRIME_2, bucket_num);
    return (hash_a+(attempt*(hash_b+1)))% bucket_num;
}

void insert (struct hm_table * hashmap, char * key, char * value ){
    struct hm_item * new_item = new_hashmap_items(key,value);
    int index = get_hash(new_item->key, hashmap->size, 0);
    struct hm_item * current = hashmap->items[index];
    int i = 1;
    while (current != NULL){
        index = get_hash(new_item->key, hashmap->size, i);
        current = hashmap -> items[index];
        i++;

    }
    hashmap -> items[index] = new_item;
    hashmap -> count ++;
}
char * search(struct hm_table *hashmap, char* key){
    int index = get_hash(key, hashmap -> size, 0);
    int i = 1;
    struct hm_item *item = hashmap -> items[index];
    while (item != NULL){
        if (strcmp(item->key, key) ==0){
            return item-> value;
        }
        index = get_hash(key, hashmap->size, i);
        item = hashmap -> items[index];
        i++;
    }
    return NULL;
}
void del (struct hm_table *, const char * key){
    
}