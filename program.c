
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node
{
    char data[100];    // The data in this node
    struct node* next; // Pointer to the next node
    struct node* prev; // Pointer to the previous node
} Node;

Node* head;
Node* tail;

Node* createEmptyList() // function to create empty list
{
    head = NULL;
    tail = NULL;
}

bool isEmpty() // check function list is empty or not
{
    return (head == NULL && tail == NULL); // return list is empty or not
}

Node* createNode(char newdata[])
{
    Node* nd = (Node*)malloc(sizeof(Node));
    strcpy(nd->data, newdata); // Put the value in the node
    nd->next = NULL;           // Next pointer is null for now
    nd->prev = NULL;           // Prev pointer is null for now
    return nd;                 // Return a pointer to the new node
}
void addNode(char newdata[])
{
    Node* nd = createNode(newdata); // Allocate new node 'nd'
    if (tail == NULL) {              // If list is empty
        tail = nd; // New node is the tail (and head)
    }
    else {
        head->prev = nd; // Old head node points back at new one
        nd->next = head; // New node points at old head
    }
    head = nd; // New node becomes the new head
}
void appendNode(char newdata[])
{
    Node* nd = createNode(newdata); // Allocate new node 'nd'
    if (head == NULL) {              // If list is empty
        head = nd; // New node is the head (and tail)
    }
    else {
        tail->next = nd; // Make old tail node point at new one
        nd->prev = tail; // Make new node point back at old tail
    }
    tail = nd; // New node becomes the new tail
}

void insertNode(Node *loc, char newdata[])
{
    Node* nd = createNode(newdata); // Allocate new node 'nd'
    if (loc->next != NULL) {
        loc->next->prev = nd; // Node after loc points back to nd
    }
    nd->next = loc->next; // New node points to node after loc
    loc->next = nd;       // loc now points to the new node
    nd->prev = loc;       // New node points back to loc
    if (loc == tail) { // If at end, new node becomes new tail
        tail = nd;
    }
}

void insertSort(char newdata[])
{
    Node *temp = head;
    if (temp == NULL) { // if list is empty
        addNode(newdata); // adding first string
    }
    while (temp != NULL) { // when list is not empty
        if (strcmp(temp->data, newdata) == 1 && temp->prev == NULL) { // comapre strings && determine position to add node
            addNode(newdata); // add node to front in list
            break;            //exit loop 
        }
        else if (strcmp(temp->data, newdata) == -1) { // comapre strings
            if (temp->next == NULL) { // determine position to add node
                appendNode(newdata); // add node to end in list
                break;               //exit loop
            }
            else if(strcmp(temp->data, newdata) == -1 && strcmp(temp->next->data, newdata) == 1) { // comapre strings
                insertNode(temp, newdata); // add node to anywhere in list
                break;                     //exit loop
            }
        }
        temp = temp->next; // Go on to the next node
    }
}

void printList(Node *nd)
{
    // Loop as long as there are more nodes
    Node *temp = nd;
    while (temp != NULL) {
        printf("%s\n", temp->data);
        temp = temp->next; // Go to the next node
    }
}

int main(int argc, char **argv)
{

    char str1[] = "Done";
    char str[20];

    createEmptyList(); //create empty list

    printf("Enter a Name or Enter 'Done' to stop: \n");

    if (isEmpty()) { //check list is empty or not
        while (strcasecmp(str, str1) != 0) { // compare string with "Done"
            printf("Enter a Name: ");
            scanf("%s", str); // get string

            if (strcasecmp(str, str1) == 0) { // compare string with "Done"
                break; // if match end loop
            }
            else {
                insertSort(str); // insert sort function
            }
        }
    }

    printf("\nThe Name list:\n");
    printList(head); // printing list
}
