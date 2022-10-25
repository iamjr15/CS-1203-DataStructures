#include <stdio.h>
#include <stdlib.h>
struct node {
   int data;
   struct node* next;
};
struct node* head = NULL;
struct node* sorted = NULL;
void push(int val)
{
   struct node* newnode
       = (struct node*)malloc(sizeof(struct node));
   newnode->data = val;
   newnode->next = head;
   head = newnode;
}
void sortedInsert(struct node* newnode)
{
   if (sorted == NULL || sorted->data >= newnode->data) {
       newnode->next = sorted;
       sorted = newnode;
   }
   else {
       struct node* current = sorted;
       while (current->next != NULL
              && current->next->data < newnode->data) {
           current = current->next;
       }
       newnode->next = current->next;
       current->next = newnode;
   }
}
void insertionsort()
{
   struct node* current = head;
   while (current != NULL) {
       struct node* next = current->next;
       sortedInsert(current);
       current = next;
   }
   head = sorted;
}
void printlist(struct node* head)
{
   while (head != NULL) {
       printf("%d->", head->data);
       head = head->next;
   }
   printf("NULL");
}
int main()
{
   push(5);
   push(20);
   push(4);
   push(306);
   push(30);
   printf("Linked List before sorting:\n");
   printlist(head);
   printf("\n");
   insertionsort(head);
   printf("Linked List after sorting:\n");
   printlist(head);
}
