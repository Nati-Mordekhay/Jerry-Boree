#include "LinkedList.h"

struct Node_t{
    Element data;
    Node next;
    int filledStatus;
};

struct LinkedList_t{
    Node head;
    int filledStatus;
    CopyFunction llcopyFunc;
    FreeFunction llfreeFunc;
    PrintFunction llprintFunc;
    EqualFunction llequalFunc;
    EqualFunction llequalKeyFunc;
};

//Function 1: createLinkedList
//Recieves all needed functions and creates a generic linked list.
LinkedList createLinkedList(CopyFunction llcopyFunc, FreeFunction llfreeFunc, PrintFunction llprintFunc,
                            EqualFunction llequalFunc, EqualFunction llequalKeyFunc){
    //CHECK INPUTS ARE VALID
    if (llcopyFunc == NULL || llfreeFunc == NULL || llprintFunc == NULL || llequalFunc == NULL){
        return NULL;
    }
    //CREATE A NEW LINKED LIST
    LinkedList newLinkedList = malloc(sizeof(struct LinkedList_t));
    if (newLinkedList == NULL){
        return NULL;
    }
    //ASSIGN VALUES
    newLinkedList->head = NULL;
    newLinkedList->filledStatus = 0;
    newLinkedList->llcopyFunc = llcopyFunc;
    newLinkedList->llfreeFunc = llfreeFunc;
    newLinkedList->llprintFunc = llprintFunc;
    newLinkedList->llequalFunc = llequalFunc;
    newLinkedList->llequalKeyFunc = llequalKeyFunc;
    //RETURN
    return newLinkedList;
}

//Function 2: destroyList
//This function recieves a pointer to a linked list and frees all it's memory.
status destroyList(LinkedList currentLL){
    //CHECK IF INPUTS ARE VALID
    if (currentLL == NULL){
        return failure;
    }
    int listLength = getLenghtList(currentLL);
    //FREE EACH ELEMENT THATS BEING HELD AT THE NODES
    for (int i = listLength; i > 0; i--){
        currentLL->llfreeFunc(getDataByIndex(currentLL, i));
    }
    //FREE EACH NODE
    Node currentNode = currentLL->head;
    for (int i = 0; i < listLength; i++){
        Node temp = currentNode->next;
        if (currentNode != NULL){
            free(currentNode);
        }
        currentNode = temp;
    }
    //FREE LINKED LIST
    free(currentLL);
}


//Function 3: appendNode
//This functions recieves a linkedlist, and an element, and appends a new node with that same element
//to the linked list.
status appendNode(LinkedList currentLL, Element elem){
    //CHECK IF INPUTS ARE VALID
    if (currentLL == NULL || elem == NULL){
        return failure;
    }
    //CREATE NEW NODE
    Node newNode = malloc(sizeof(struct Node_t));
    if (newNode == NULL){
        return failure;
    }
    //ASSIGN VALUES
    Element newElement = currentLL->llcopyFunc(elem);
    if (newElement == NULL){
        return failure;
    }
    newNode->data = newElement;
    newNode->filledStatus = 1;
    newNode->next = NULL;
    //IF INSERT IS TO NODE
    if (currentLL->head == NULL){
        currentLL->head = newNode;
        return success;
    }
    //IF REGULAR ADD
    else {
        Node currentNode = currentLL->head;
        while (currentNode->next != NULL){
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
        return success;
    }
}

//Function 4: deleteNode
//This function recieves a linked list, and an element, and deletets that same node from the linked list
status deleteNode(LinkedList currentLL, Element elem){
    //CHECK INPUTS ARE VALID
    if (currentLL == NULL || elem == NULL){
        return failure;
    }
    //DEFINE VARIABLES
    Node currentNode = currentLL->head;
    Node previousNode = NULL;
    //FIND CORRECT NODE
    while (currentNode != NULL && currentLL->llequalFunc(currentNode->data, elem) == false){
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    //ELEMENT NOT FOUND
    if (currentNode == NULL){
        return failure;
    }
    //IF FOUND NODE IS HEAD NODE
    if (previousNode == NULL){
        //ASSIGN NEW HEAD FOR LINKED LIST
        currentLL->head = currentNode->next;
    }
    //ELSE, UPDATE WITH SKIP NODE
    else {
        previousNode->next = currentNode->next;
    }
    //DELETE AND FREE OLD NODE AND IT'S DATA
    currentLL->llfreeFunc(currentNode->data);
    free(currentNode);
    return success;
}

//Function 5: displayList
//This function recieves a linked list and prints it's nodes
status displayList(LinkedList currentLL){
    //CHECK INPUTS ARE VALID
    if (currentLL == NULL){
        return failure;
    }
    //PRINT EACH NODE
    Node currentNode = currentLL->head;
    while (currentNode != NULL){
        currentLL->llprintFunc(currentNode->data);
        currentNode = currentNode->next;
    }
    return success;
}

//Function 6: getDataByIndex
//This function recieves and index (int) and a pointer to the linked list, returns the element saved in that node.
Element getDataByIndex(LinkedList currentLL, int index){
    //CHECK IF INPUTS ARE VALID
    if (currentLL == NULL){
        return NULL;
    }
    //FIND ELEMENT
    Node currentNode = currentLL->head;
    for (int i = 1; i <= getLenghtList(currentLL); i++){
        if (index == i){
            return currentNode->data;
        }
        currentNode = currentNode->next;
    }
}


//Function 7: getLenghtList
//This function recieves a linked list and returns an integer which is it's number.
int getLenghtList(LinkedList currentLL){
    //CHECK INPUTS ARE VALID
    if (currentLL == NULL){
        return failure;
    }
    //FIND LENGTH
    int counter = 0;
    Node currentNode = currentLL->head;
    while (currentNode != NULL){
        currentNode = currentNode->next;
        counter++;
    }
    return counter;
}

//Function 8: searchByKeyInList
//This function recieves a linkedlist, and and element or part of it. The function tests to see if a part of that element
//exists. If so, returns . Else, returns NULL. Will return first found if there a few equals.
Element searchByKeyInList(LinkedList currentLL, Element elem){
    //CHECK INPUTS ARE VALID
    if (currentLL == NULL || elem == NULL){
        return NULL;
    }
    //ASSIGN VARIABLES
    Node currentNode = currentLL->head;
    //SEARCH FOR CORRECT VALUE
    while (currentNode != NULL){
        if (currentLL->llequalKeyFunc(currentNode->data, elem) == true){
            return currentNode->data;
        }
        currentNode = currentNode->next;
    }
    return NULL;
}

status setValue(Element currentNodeData, Element elem){
    if (currentNodeData == NULL || elem == NULL){
        return failure;
    }
    currentNodeData = elem;
    return success;
}