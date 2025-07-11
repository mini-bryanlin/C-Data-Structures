#include <stdlib.h>
#include <string.h>
#include "./linked.h"
struct Node {
    int value;
    struct Node *next;
};

struct Node * create(){
    struct Node * start = NULL;
    return start;
}

void add_to_list (struct Node ** list, int num ){
    
    struct Node * new_node = malloc(sizeof(struct Node));
    new_node -> value = num;
    new_node -> next = *list;
    *list = new_node;
}

void print_list (struct Node * list){
    while (list->value){
        printf("%d", list->value);
        if(list->next){
            printf(" -> ");
        }
        list = list->next;
    }
}


