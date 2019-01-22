// Program 11.7 Sorting integers using a binary tree
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node Node;

struct Node
{
    long item;
    int count;
    Node *pLeft;
    Node *pRight;
};

Node *create_node(long value);
Node *add_node(long value, Node *pNode);
void list_nodes(Node *pNode);
void free_nodes(Node *pNode);

int main(void)
{
    long newvalue = 0;
    Node *pRoot = NULL;
    char answer = 'n';
    do
    {
        printf_s("Enter the node value:");
        scanf_s(" %ld", &newvalue);
        if(!pRoot)
            pRoot = create_node(newvalue);
        else
            add_node(newvalue, pRoot);
        printf_s("Do you want to enter another (y or n)? ");
        scanf_s(" %c", &answer, sizeof(answer));
    } while(tolower(answer) == 'y');

    printf_s("The values in ascending swquence are:\n");
    list_nodes(pRoot);
    free_nodes(pRoot);

    return 0;
}

Node *create_node(long value)
{
    Node *pNode = (Node*)malloc(sizeof(Node));
    pNode->item = value;
    pNode->count = 1;
    pNode->pLeft = pNode->pRight = NULL;
    return pNode;
}

Node *add_node(long value, Node *pNode)
{
    if(!pNode)
        return create_node(value);
    
    if(value == pNode->item)
    {
        ++pNode->count;
        return pNode;
    }

    if(value < pNode->item)
    {
        if(!pNode->pLeft)
        {
            pNode->pLeft = create_node(value);
            return pNode->pLeft;
        }
        else
            return add_node(value, pNode->pLeft);
    }
    else
    {
        if(!pNode->pRight)
        {
            pNode->pRight = create_node(value);
            return pNode->pRight;
        }
        else
            return add_node(value, pNode->pRight);
    }
}

void list_nodes(Node *pNode)
{
    if(pNode->pLeft)
        list_nodes(pNode->pLeft);

    printf_s("%10d x %10ld\n", pNode->count, pNode->item);

    if(pNode->pRight)
        list_nodes(pNode->pRight);
}

void free_nodes(Node *pNode)
{
    if(!pNode)
        return;

    if(pNode->pLeft)
        free_nodes(pNode->pLeft);
    
    if(pNode->pRight)
        free_nodes(pNode->pRight);

    free(pNode);
}