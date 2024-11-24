// Aim : Circular Queue

#include<stdio.h>
#include<stdlib.h>

int front = -1, rear = -1, *queue, item, i, size;


int enqueue() 
{
    if (front == -1 && rear == -1)
    {
        front = 0;
        rear = 0;
        printf("Enter Element to Insert : ");
        scanf("%d", &item);
        queue[front] = item;
    } 
    else if (((rear + 1) % size) == front) 
    {
        printf("\nQueue is Full\n");
    } 
    else 
    {
        printf("Enter Element to Insert : ");
        scanf("%d", &item);
        rear = (rear + 1) % size;
        queue[rear] = item;
    }
}



int dequeue() 
{
    if (front == -1 && rear == -1) 
    {
        printf("\nQueue Underflow\n");
    } 
    else if (front == rear)
    {
        printf("Deleted Element %d\n", queue[front]);
        front = rear = -1;
    } 
    else 
    {
        printf("Deleted Element %d\n", queue[front]);
        front = (front + 1) % size;
    }
}



int display() 
{
    if (front == -1 && rear == -1) 
    {
        printf("\nNothing to Display\n");
    } 
    else 
    {
        printf("\nElements are: ");
        for (i = front; i != rear; i = (i + 1) % size) 
        {
            printf("%d ", queue[i]);
        }
        printf(" %d ", queue[i]);
    }
}




int search() 
{
    if (front == -1 && rear == -1) 
    {
        printf("\nQueue is Empty\n");
    } 
    else 
    {
        int item, flag = 0;
        printf("Enter Element to Search: ");
        scanf("%d", &item);
        for (i = front; i != rear; i = (i + 1) % size) 
        {
            if (queue[i] == item) 
            {
                flag = 1;
                break;
            }
        }
        if (queue[i] == item) 
        {
            flag = 1;
        }
        if (flag) 
        {
            printf("Element %d found in the queue\n", item);
        } 
        else 
        {
            printf("Element %d not found in the queue\n", item);
        }
    }
}


int main() 
{
    int choice;
    printf("Enter the size of the circular queue: ");
    scanf("%d", &size);

/*
    if (size <= 0) 
    {
        printf("Invalid size. Size must be greater than 0. Exiting program.");
        exit(1);
    }
*/

    queue = (int*) malloc(size * sizeof(int));


    if (queue == NULL) 
    {
        printf("Memory allocation failed. Exiting program.");
        exit(1);
    }

    while(1) 
    {
        printf("\n1.Enqueue\n2.Dequeue\n3.Display\n4.Search\n5.Exit");
        printf("\nSelect Operation : ");
        scanf("%d", &choice);
        switch(choice) 
        {
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                search();
                break;
            case 5:
                free(queue);
                printf("Exiting...");
                exit(0);
            default:
                printf("Invalid Option\n");
                break;
        }
    }
}