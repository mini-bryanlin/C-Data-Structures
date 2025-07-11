#include "./linked.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void){
    
    struct Node * head = create();
    while (1){
        printf("(1) Add Node \n(2) Delete Node\n");
        int command;
        scanf("%d", &command);
        switch (command){
            case 1:
            {   
                int num;

                printf("Add new number: ");
                scanf("%d", &num);
                add_to_list(&head, num);
            
                break;
            
            }

            case 2:
            {   
                int num;
                printf("Delete Node: ");
                scanf("%d", &num);
                del(&head, num);
                break;
                

            }

        }
        
        
        
        print_list(head);
        if (command == 100){
            return 0;
        }


        


    }
}