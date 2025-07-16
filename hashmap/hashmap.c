#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./hashmap.h"
#include "prime.h"
#define PRIME_1 151
#define PRIME_2 163
#define HM_INIT_SIZE 50
static struct hm_item* new_hashmap_items(const char * key, const char * value){

    struct hm_item *i = malloc(sizeof(struct hm_item));
    i -> key = strdup(key) ;
    i -> value = strdup(value);

    return i;

}
static struct hm_table * new_sized_hm(const int base_size){
    struct hm_table* hashmap = malloc(sizeof(struct hm_table));
    if (hashmap == NULL){return;}
    // hashmap -> base_size = base_size;
    hashmap -> size = next_prime(base_size);
    hashmap -> count = 0;
    hashmap -> items = calloc(hashmap -> size, sizeof(struct hm_item *));
    hashmap -> base_size = base_size;
    return hashmap;
}



struct hm_table * new_hashmap_table (void){
    return new_sized_hm(HM_INIT_SIZE);

}

static void delete_item(struct hm_item *i){
    free (i->key);
    free (i->value);
    free(i);

}

static void delete_hashmap(struct hm_table *table){
    for (int i = 0; i< table->size; i ++){
        struct hm_item * item = *((table->items)+i);
        if (item != NULL && item != &DELETED_ITEM){
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
        hash += (int)pow(a, (len-i-1)) * string[i];
        hash = hash%m;

    }
    return hash;

}
static int get_hash(const char* string, const int bucket_num, const int attempt){
    const int hash_a = hash(string, PRIME_1, bucket_num);
    const int hash_b = hash(string, PRIME_2, bucket_num);
    return (hash_a+(attempt*(hash_b+1)))% bucket_num;
}

void insert (struct hm_table * hashmap, const char * key, const char * value ){
    if (hashmap -> count >= hashmap-> size){
        return;
    }
    const int load = (hashmap->count/ hashmap->size)*100;
    if (load > 70){
        hashmap = size_up(hashmap);
    }
    struct hm_item * new_item = new_hashmap_items(key,value);
    int index = get_hash(new_item->key, hashmap->size, 0);
    struct hm_item * current = hashmap->items[index];
    int i = 1;
    while (current != NULL && current != &DELETED_ITEM){
        index = get_hash(new_item->key, hashmap->size, i);
        current = hashmap -> items[index];
        i++;

    }
    hashmap -> items[index] = new_item;
    hashmap -> count ++;
}
char * search(struct hm_table *hashmap, const char* key){
    int index = get_hash(key, hashmap -> size, 0);
    int i = 1;
    struct hm_item *item = hashmap -> items[index];
    while (item != NULL){
        if (item != &DELETED_ITEM){
            if (strcmp(item->key, key) ==0){
                return item-> value;
            }
    }
        index = get_hash(key, hashmap->size, i);
        item = hashmap -> items[index];
        i++;
    }
    return NULL;
}
static struct hm_item DELETED_ITEM = {NULL,NULL};
void del (struct hm_table * hashmap, const char * key){
    int index = get_hash(key, hashmap->size, 0);
    struct hm_item * item = hashmap -> items[index];
    int i = 1;
    while (item != NULL){
        if (item != &DELETED_ITEM ){
            if (strcmp(item->key, key) == 0){
                delete_item(item);
                hashmap -> items[index] = &DELETED_ITEM;
            }
        }
        index = get_hash(key, hashmap -> size, i);
        item = 
        i++;
    }
    hashmap -> count --;

    const int load = (hashmap->count/ hashmap->size)*100;
    if (load < 10){
        hashmap = size_down(hashmap);
    }
}

void update (struct hm_table * hashmap, char * key , char * new_value){
    int index = get_hash(key, hashmap->size, 0);
    struct hm_item * item = hashmap -> items[index];

    while (item != NULL && item != &DELETED_ITEM){
        if (strcmp(item->key, key) == 0){
            item -> value = new_value;
            return;
        }
    }
    
}
static struct hm_table * resize(struct hm_table * hashmap, const int base_size){
    if (base_size < HM_INIT_SIZE){ // init size also the minimum size
        return hashmap;
    }
    struct hm_table * new_map = new_sized_hm(base_size);
    for (int i = 0; i< hashmap-> size; i++){
        struct hm_item* item = hashmap -> items[i];
        if (item != NULL && item != &DELETED_ITEM){
            insert(new_map,item->key, item->value);
        }

    }

    delete_hashmap(hashmap);
    return new_map;


}

static struct hm_table * size_up(struct hm_table * old_table){
    int new_size = (old_table-> base_size) *2;
    struct hm_table * new_table = resize(old_table, new_size);
    return new_table;
}

static struct hm_table * size_down(struct hm_table * old_table){
    int new_size = (old_table-> base_size)/2;
    struct hm_table * new_table = resize(old_table, new_size);
    return new_table;
}