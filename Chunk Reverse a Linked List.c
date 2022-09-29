#include<stdio.h>
#include<stdlib.h>
#include<time.h>



struct Node{
    int val;
    struct Node * next;
};
typedef struct Node * NodeAddress;  




NodeAddress revChunk(NodeAddress head, int k){
    NodeAddress curr = head;            
    NodeAddress prev = NULL;            
    NodeAddress forward = NULL;         
    if(k==0){                            
        return head;
    }
    for(int i=0; i<k && curr!=NULL; i++){    
        forward = curr->next;                
        curr->next = prev;                   
        prev = curr;                         
        curr = forward;                      
    }
    head->next = curr;                       
    head = prev;                             
    return head;
}


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


void prntLinkedLst(NodeAddress head, int n){
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
    int n,k;
    printf("Enter the number of elements in the Linked List: ");
    scanf("%d", &n);
    NodeAddress list, chunk;         
    srand(time(NULL));                  
    list = genLinkedLst(n);       
    prntLinkedLst(list, n);           

    printf("Enter the value of k: ");
    scanf("%d", &k);

    chunk = revChunk(list, k);
    
    prntLinkedLst(chunk, n);            

    delLinkedLst(list);                         
    delLinkedLst(chunk);                         
    return 0;
}
