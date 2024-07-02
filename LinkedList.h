
#include "Defs.h"

#ifndef WORK_LINKEDLIST_H
#define WORK_LINKEDLIST_H

typedef struct Node_t* Node;
typedef struct LinkedList_t* LinkedList;

//LinkedList functions
LinkedList createLinkedList(CopyFunction, FreeFunction, PrintFunction, EqualFunction, EqualFunction);
status destroyList(LinkedList);
status appendNode(LinkedList, Element);
status deleteNode(LinkedList, Element);
status displayList(LinkedList);
Element getDataByIndex(LinkedList, int);
int getLenghtList(LinkedList);
Element searchByKeyInList(LinkedList, Element);
status setValue(Element currentNodeData, Element elem);

#endif //WORK_LINKEDLIST_H
