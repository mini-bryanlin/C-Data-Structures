struct hm_item {
    char* key;
    char* value;
};

struct hm_table{
    int size;
    int count;
    struct hm_item** items;
    int base_size;
};
struct hm_table * new_hashmap_table (void);

void insert(struct hm_table *, const char* key, const char * value);

char * search (struct hm_table *, const char *key);

void del (struct hm_table *, const char * key);