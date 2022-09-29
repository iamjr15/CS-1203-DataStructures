// Reverse a Linked List 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>


struct Node{
    int val;
    struct Node * next;
};

typedef struct Node * NodeAddress;  

NodeAddress genLinkedLst(int n){
    int i;
    NodeAddress head = NULL;
    NodeAddress temp = NULL;

    if(n>0){
        head = malloc(sizeof(struct Node));
        head->val = rand()%1000;            
        head->next = NULL;                  
        temp = head;
    }
    
    for(i=1; i<n; i++){
        temp->next = malloc(sizeof(struct Node));
        temp = temp->next;
        temp->val = rand()%1000;            
        temp->next = NULL;                  
    }
    return head;                            
}



NodeAddress revLinkedLst(NodeAddress head){
    NodeAddress prev, curr, forward;
    curr = head; 
    prev = NULL; 
    forward = NULL;
    while(curr != NULL){
        forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    head = prev;
    return head;
}

void prtLinkedLst(NodeAddress head, int n){
    NodeAddress temp = head;
    printf("Linked List = ");
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
    scanf("%d", &n);
    NodeAddress list, list_rev;         
    srand(time(NULL));                  
    list = genLinkedLst(n);       
    prtLinkedLst(list, n);           
    list_rev = revLinkedLst(list);         
    prtLinkedLst(list_rev, n);                   
    delLinkedLst(list);                         
    delLinkedLst(list_rev);                     
    return 0;
}