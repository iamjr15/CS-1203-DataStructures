
#include<stdio.h>
#include<stdlib.h>
#include<time.h>



struct Node{
    int val;
    struct Node * next;
};
typedef struct Node * NodeAddress;  

void prntHalfLinkedLst(NodeAddress head){
    
    NodeAddress slow_pointer = head;
    NodeAddress fast_pointer = head;
    while(fast_pointer != NULL && fast_pointer->next != NULL){
        slow_pointer = slow_pointer->next;
        fast_pointer = fast_pointer->next->next;
    }
   
    NodeAddress temp = head;
    int i=0;
    printf("Half Linked List = ");
    while(temp != slow_pointer){
        printf(i?", %d":"%d", temp->val);
        temp = temp->next;
        i++;
    }
}


NodeAddress linkedLstGenerate(int n){
    int i;
    NodeAddress head = NULL;
    NodeAddress temp = NULL;
    if(n>0){
        head = malloc(sizeof(struct Node));
        head->val = rand()%1000;            
        head->next = NULL;                  
        temp = head;
    }
    // general case
    for(i=1; i<n; i++){
        temp->next = malloc(sizeof(struct Node));
        temp = temp->next;
        temp->val = rand()%1000;            
        temp->next = NULL;                  
    }
    return head;                            
}

void prtLinkedLst(NodeAddress head, int n){
    NodeAddress temp = head;
    printf("Complete Linked List = ");
    for(int i=0; i<n; i++){
        printf(i?", %d":"%d", temp->val);
        temp = temp->next;
    }
    printf(".\n");
}

void delLinkedLst(NodeAddress head){
    NodeAddress prev;
	while(head){                
		prev = head;
		head = head->next;
		free(prev); 
	}
}

int main(int argc, char const *argv[])
{
    int n;
    printf("Enter the no. of elements in the Linked List: ");
    scanf("%d", &n);
    NodeAddress list, tail;         
    srand(time(NULL));                  
    list = linkedLstGenerate(n);       
    prtLinkedLst(list, n);           

    prntHalfLinkedLst(list);           
    
    delLinkedLst(list);                         
    return 0;
}