// Aim : Singly linked list


#include<stdio.h>
#include<stdlib.h>

struct node
{
        int data;
        struct node * next;
};

struct node * head=NULL;


struct node * createnode(int item)
{
    struct node * newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = item;
    newnode->next = NULL;
    return newnode;
}

void insertAtFront(int item)
{
        struct node * newnode=createnode(item);
        newnode->next=head;
        head=newnode;
}



void insertAtBack(int item)
{
        struct node * newnode=createnode(item);
        if(head == NULL)
        {
                head = newnode;
        }
        struct node* temp = head;
        while(temp->next != NULL)
                temp = temp->next;
                temp->next = newnode;
}





void insertAtPosition(int item,int position)
{
        if(position<1)
        {
                printf("Position cannot be <1.\n");
                return;
        }
        if(position == 1)
        {
                insertAtFront(item);
                return;
        }

        struct node * newnode = createnode(item);
        struct node * temp = head;

        for (int i = 1; i < position - 1 && temp != NULL; i++)
        {
                temp = temp->next;
        }
        if (temp == NULL)
        {
                printf("Not available.\n");
                free(newnode);
        }
        else
        {
                newnode->next = temp->next;
                temp->next = newnode;
        }
}





void deleteFromFront()
{
        if(head == NULL)
        {
                printf("List is empty!\n");
                return;
        }

        struct node* temp = head;
        head = head->next;
        free(temp);
}







void deleteFromPosition(int position)
{
        if (head == NULL)
        {
                printf("List is empty.\n");
                return;
        }
        if (position < 1)
        {
                printf("Position cannot be <1.\n");
                return;
        }
        if (position == 1)
        {
                deleteFromFront();
                return;
        }
        
        struct node* temp = head;
        struct node* prev = NULL;

        for (int i = 1; i < position && temp != NULL; i++)
        {
                prev = temp;
                temp = temp->next;
        }
        if (temp == NULL)
        {
                printf("Not available.\n");
        }
        else
        {
                prev->next = temp->next;
                free(temp);
        }
}



void deleteFromBack()
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    struct node* temp = head;
    
    if (temp->next == NULL)
    {
        free(temp);
        head = NULL;
        return;
    }

    struct node* prev = NULL;
    
    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }
    
    prev->next = NULL;
    free(temp);
}




void display()
{
        struct node* temp = head;
        if(temp == NULL)
        {
                printf("List is empty.\n");
                return;
        }
        printf("Head -> ");
        while(temp != NULL)
        {
                printf("%d -> ", temp->data);
                temp = temp->next;
        }
        printf("NULL\n");
}




int main()
{
        int choice,item,position;
        do{
                printf("\n1.Insert at front\n2.Insert at position\n3.Insert at back\n4.Delete from front\n5.Delete from postion\n");
                printf("6.Delete from back\n7.Display\n8.Exit\nEnter your choice :");
                scanf("%d",&choice);
                switch(choice)
                {
                        case(1):
                                printf("Enter item to insert at front :");
                                scanf("%d",&item);
                                insertAtFront(item);
                                break;
                        case(2):
                                printf("Enter item to be inserted :");
                                scanf("%d",&item);
                                printf("Enter the position :");
                                scanf("%d",&position);
                                insertAtPosition(item,position);
                                break;
                        case(3):
                                printf("Enter item to insert at back :");
                                scanf("%d",&item);
                                insertAtBack(item);
                                break;
                        case(4):
                                deleteFromFront();
                                break;
                        case(5):
                                printf("Enter the position :");
                                scanf("%d",&position);
                                deleteFromPosition(position);
                                break;
                        case(6):
                                deleteFromBack();
                                break;
                        case(7):
                                display();
                                break;
                        case(8):
                                printf("Exiting...\n");
                                break;
                        default:
                                printf("Invalid choice!Try again.");
                                break;
                }
        } while(choice!=8);

        return 0;

}

