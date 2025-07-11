#include "./linked.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void){
    
    struct Node * head = create();
    while (1){
        int command;
        printf("Add new number: ");
        scanf("%d", &command);
        add_to_list(&head, command);
        print_list(head);
        if (command == 100){
            return 0;
        }


        


    }
}