#include <stdlib.h>
#include <string.h>
#include "./linked.h"
#include <stdio.h>
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

void del (struct Node ** list, int num){

    struct Node * prev = NULL;
    struct Node * curr = *list;
    while (curr != NULL){
        if (curr->value == num){
            if (prev == NULL){
                *list = curr->next;
            }
            else{
            prev->next = curr->next;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;


    }

}

int len (struct Node *list){
    int length = 0;
    while (list != NULL){
        length ++;
        list = list->next;

    }
    return length;
}



void print_list (struct Node * list){
    while (list!=NULL){
        printf("%d", list->value);
        
        printf(" -> ");
        
        list = list->next;
    }
    puts("NULL");
}




