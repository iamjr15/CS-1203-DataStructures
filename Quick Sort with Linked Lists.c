#include <stdio.h>
#include <stdlib.h>
 
struct Node {
    int data;
    struct Node* next;
};
 
void insertFunc(struct Node** head, int value)
{
    struct Node* node
        = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Memory Overflow\n");
    }
    else {
        node->data = value;
        node->next = NULL;
        if (*head == NULL) {
            *head = node;
        }
        else {
            struct Node* temp = *head;
 
            while (temp->next != NULL) {
                temp = temp->next;
            }
 
            temp->next = node;
        }
    }
}
 
void display(struct Node* head)
{
    if (head == NULL) {
        printf("The Linked List is Empty!\n");
        return;
    }
    struct Node* temp = head;
    printf("\n Linked List :");
    while (temp != NULL) {
        printf("  %d", temp->data);
        temp = temp->next;
    }
}
 
struct Node* last_node(struct Node* head)
{
    struct Node* temp = head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}
 

struct Node* parition(struct Node* first, struct Node* last)
{
    struct Node* pivot = first;
    struct Node* front = first;
    int temp = 0;
    while (front != NULL && front != last) {
        if (front->data < last->data) {
            pivot = first;
 
            temp = first->data;
            first->data = front->data;
            front->data = temp;
 
            first = first->next;
        }
         front = front->next;
    }
     temp = first->data;
    first->data = last->data;
    last->data = temp;
    return pivot;
}
 
void quick_sort(struct Node* first, struct Node* last)
{
    if (first == last) {
        return;
    }
    struct Node* pivot = parition(first, last);
 
    if (pivot != NULL && pivot->next != NULL) {
        quick_sort(pivot->next, last);
    }
 
    if (pivot != NULL && first != pivot) {
        quick_sort(first, pivot);
    }
}
 

int main()
{
    struct Node* head = NULL;
     insertFunc(&head, 41);
    insertFunc(&head, 5);
    insertFunc(&head, 7);
    insertFunc(&head, 22);
    insertFunc(&head, 24);
    insertFunc(&head, 63);
    insertFunc(&head, 41);
    insertFunc(&head, 80);
    insertFunc(&head, 23);
    insertFunc(&head, 11);
    printf("\n Before Sorting :");
    display(head);
 
    quick_sort(head, last_node(head));
    printf("\n After Sorting :");
    display(head);
    return 0;
}
