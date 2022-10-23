#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node* start = NULL;

//I dont want to traverse for add an item last position, i will use last->next
struct node* last = NULL;
struct node* temp;

struct node* nodeInit(int x)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

void addtoLast(int y)
{
    struct node* hailLinus = nodeInit(y);
    if(start == NULL)
    {
        start = hailLinus;
        last = hailLinus;
    }
    else
    {
        last->next = hailLinus;
        last = hailLinus;
    }
}

void prntLinkedList()
{
    temp = start;
    while(temp->next != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);
}

void init(int size)
{
    int i, number;
    for( i = 0; i < size; i++ )
    {
        number = rand()%10000;
        addtoLast(number);
    }
}

void slctionLinkedList()
{
    struct node* key;
    key = start;

    while(key != NULL)
    {
        temp = key->next;
        while(temp != NULL)
        {
            if(key->data > temp->data)
            {
                nodeSwapper(key, temp);
            }
            temp = temp->next;
        }
        key = key->next;
    }
}

void nodeSwapper(struct node *x, struct node *y)
{
    int temp = x->data;
    x->data = y->data;
    y->data = temp;
}

int main()
{
    int myChoice;
    while( 1 == 1)
    {
        printf("\n Enter the the number of elements you want to add to the linked list: ");
        scanf("%d", &myChoice);
        init(myChoice);
        slctionLinkedList();
        prntLinkedList();
    }

}
