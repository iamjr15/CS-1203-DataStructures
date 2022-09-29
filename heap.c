#include <stdio.h>
#include <limits.h>

int array[100], n;

void display()
{
    int i;
    if (n == 0)
    {
        printf("The Heap Is Empty! \n");
        return;
    }
    for (i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void insertFunc(int num, int location)
{
    int parentnode;
    while (location > 0)
    {
        parentnode = (location - 1) / 2;
        if (num <= array[parentnode])
        {
            array[location] = num;
            return;
        }
        array[location] = array[parentnode];
        location = parentnode;
    }
    array[0] = num;
}
int extract_min()
{
    if (n <= 0)
        return INT_MAX;
    if (n == 1)
    {
        n = n - 1;
        return array[0];
    }

    int root = array[0];
    array[0] = array[n - 1];
    n = n - 1;
    return root;
}
void main()
{
    int choice, num, a;
    n = 0;
    while (1)
    {
        printf("1.Insert an element \n");
        printf("2.Extract the min \n");
        printf("3.Display all elements \n");
        printf("4.Exit \n");
        printf("Please enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the element to be inserted to the list : ");
            scanf("%d", &num);
            insertFunc(num, n);
            n = n + 1;
            break;
        case 2:

            a = extract_min(num);
            printf("\n\n%d\n\n", a);
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
        default:
            printf("That's an Invalid choice \n");
        }
    }
}