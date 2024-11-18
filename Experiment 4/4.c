// Aim : Binary Search Tree

#include <stdio.h>
#include <stdlib.h>

struct node
{
        struct node *left;
        struct node *right;
        int data;
}*root;


// struct node *root;


struct node *newnode(int value)
{
        struct node *newnode = (struct node*)malloc(sizeof(struct node));
        newnode->data = value;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
}


struct node *insert(struct node *root, int value)
{
        if (root == NULL)
        {
                return newnode(value);
        }
        else if (value == root->data)
        {
                printf("Same data can't be stored !\n");
                return root;
        }
        else if (value > root->data)
        {
                root->right = insert(root->right, value);
        }
        else
        {
                root->left = insert(root->left, value);
        }
        return root;
}

void inorderTraversal(struct node *root)
{
        if (root == NULL)
        {
                return;
        }
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
}



void preorderTraversal(struct node *root)
{
        if (root == NULL)
        {
                return;
        }
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
}



void postorderTraversal(struct node *root)
{
        if (root == NULL)
        {
                return;
        }
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
}




struct node *searchNode(struct node *root, int value)
{
        if (root == NULL)
        {
                printf("Item does not Found!\n");
                return NULL;
        }
        else if (root->data == value)
        {
                printf("Item Found in Tree!\n");
                return root;
        }
        else if (root->data < value)
        {
                return searchNode(root->right, value);
        }
        else
        {
                return searchNode(root->left, value);
        }
}




struct node *minValueNode(struct node *root)
{
        struct node *temp = root;
        while (temp && temp->left != NULL)
        {
                temp = temp->left;
        }
        return temp;
}




struct node *deleteNode(struct node *root, int value)
{
        if (root == NULL)
        {
                printf("tree is Empty !\n");
                return root;
        }
        if (value < root->data)
        {
                root->left = deleteNode(root->left, value);
        }
        else if (value > root->data)
        {
                root->right = deleteNode(root->right, value);
        }
        else
        {
                if (root->left == NULL)
                {
                        struct node *temp = root->right;
                        free(root);
                        return temp;
                }
                else if (root->right == NULL)
                {
                        struct node *temp = root->left;
                        free(root);
                        return temp;
                }
                struct node *temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
        }
        return root;
}




int main()
{
        int choice;
        int value, search, key;
        do {
                printf("\n1.Insert Node\n2.Search Node\n3.Inorder Traversal\n4.preorder Traversal");
                printf("\n5.Postorder Traversal\n6.Delete Node\n7.Exit\n");
                printf("Select an Option : ");
                scanf("%d", &choice);
                switch (choice)
                {
                        case 1:
                                printf("Enter a Number :");
                                scanf("%d", &value);
                                root = insert(root, value);
                                printf("Value Inserted !\n");
                                break;
                        case 2:
                                printf("Enter the Value :");
                                scanf("%d", &value);
                                searchNode(root, value);
                                break;
                        case 3:
                                printf("Inorder : ");
                                inorderTraversal(root);
                                printf("\n");
                                break;
                        case 4:
                                printf("Preorder : ");
                                preorderTraversal(root);
                                printf("\n");
                                break;
                        case 5:
                                printf("Postorder : ");
                                postorderTraversal(root);
                                printf("\n");
                                break;
                        case 6:
                                printf("Enter Value to be Deleted :");
                                scanf("%d", &value);
                                deleteNode(root, value);
                                printf("Value Deleted !\n");
                                break;
                        case 7:
                                printf("Exiting...\n");
                                break;
                        default:
                                printf("Invalid Option!,Try Again!\n");
                }
        } while (choice != 7);
        return 0;
}
