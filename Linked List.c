#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node* next;

};
struct Node* head;



void insertAtBeggining(int x)
{
	struct Node* temp;
	temp = (struct Node*)malloc(sizeof(struct Node));

	temp->data = x;
	temp->next = head;
	head = temp;
}

void insertAtEnd(int x)
{
	struct Node *temp,*p;
	temp = (struct Node*)malloc(sizeof(struct Node));
	p = (struct Node*)malloc(sizeof(struct Node));

	temp->data = x;
	temp->next = NULL;
	p = head;

	while(p->next!=NULL)
	{
		p = p->next;
	}
	p->next = temp;
}

void printList(struct Node* temp)
{
	if(temp==NULL)
		return;

	printf("%d ",temp->data);
	printList(temp->next);
}

void inseratn(int x , int n)
{
	int i;
	struct Node *temp,*p,*temp1;

	if(n==1)
	{
		insertAtBeggining(x);
		return;
	}

	temp = (struct Node*)malloc(sizeof(struct Node));
	p = (struct Node*)malloc(sizeof(struct Node));
	temp1 = (struct Node*)malloc(sizeof(struct Node));

	temp1->data = x;

	p = head;
	temp = head;

	for(i=0;i<n;i++)
		temp = temp->next;

	for(i=0;i<n-2;i++)
		p = p->next;

	p->next = temp1;
	temp1->next = temp;

}
void deleteatn(int n)
{
	struct Node *temp,*p;
	int i;
	temp = (struct Node*)malloc(sizeof(struct Node));
	p = (struct Node*)malloc(sizeof(struct Node));

	p = head;
	temp = head;
    if(n==1)
    {
    	head = temp->next;
    	return;
    }
	for(i=0;i<n;i++)
		temp= temp->next;
	
	for(i=0;i<n-2;i++)
		p = p->next;

	p->next = temp;
}

void reverse(struct Node* temp)
{
	if(temp->next==NULL)
	{
		head = temp;
		return;
	}

	reverse(temp->next);
	struct Node *q;
	q = temp->next;
	q->next = temp;
	temp->next = NULL;


}

void printrev(struct Node* temp)
{
	if(temp==NULL)
		return;

	printrev(temp->next);
	printf("%d ",temp->data);
}

int main()
{
	int i,n,x,c;

	head=NULL;

	printf("How many numbers?: ");
	scanf("%d",&n);

	printf("Enter %d numbers: ",n);
	scanf("%d",&x);
	insertAtBeggining(x);

	for(i=0;i<n-1;i++)
	{
		scanf("%d",&x);
		insertAtEnd(x);
	}
	printf("LIST : ");printList(head);

	printf("\nWhat would you like to perform among these \n");
	printf("1.Add and element at nth position\n");
	printf("2.Delete an element from nth position\n");
	printf("3.Reverse the list\n");
	printf("4.Print Reverse list(original list will remain same)\n");
	printf("Your choice: ");

	scanf("%d",&c);

	switch(c)
	{
		case 1:
			printf("Enter number and its position: ");
			scanf("%d %d",&x,&n);
			inseratn(x,n);
			printf("LIST : ");printList(head);
			break;

		case 2:
			printf("Enter postion to be deleted: ");
			scanf("%d",&n);
			deleteatn(n);
			printf("LIST : ");printList(head);
			break;

		case 3:
			reverse(head);
			printf("LIST : ");printList(head);
			break;

		case 4:
			printf("LIST: ");
			printrev(head);
			break;
	}
}