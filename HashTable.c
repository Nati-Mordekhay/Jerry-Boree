#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

struct hashTable_s{
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
    TransformIntoNumberFunction intoNum;
    int hashNumber;
    int addedHash;
    LinkedList* array;
};

//Function 1: createHashTable
//This function recieves all needed functions and the size of the hash table, and creates a hash table,
//where each cell holds a linked list.
hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                          CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                          EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber) {
    //CHECK INPUTS ARE VALID
    if (copyKey == NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL ||
        printValue == NULL || equalKey == NULL || transformIntoNumber == NULL) {
        return NULL;
    }
    //CREATE NEW REG HASH TABLE
    hashTable currentHT = malloc(sizeof(struct hashTable_s));
    if (currentHT == NULL) {
        return NULL;
    }
    //ASSIGN VALUES
    currentHT->copyKey = copyKey;
    currentHT->freeKey = freeKey;
    currentHT->printKey = printKey;
    currentHT->copyValue = copyValue;
    currentHT->freeValue = freeValue;
    currentHT->printValue = printValue;
    currentHT->equalKey = equalKey;
    currentHT->intoNum = transformIntoNumber;
    currentHT->hashNumber = hashNumber;
    currentHT->addedHash = 0;
    //ALLOCATE MEMORY FOR THE ARRAY
    currentHT->array = malloc(hashNumber * sizeof(LinkedList));
    if (currentHT->array == NULL) {
        free(currentHT);
        return NULL;
    }
    //CREATE LIST IN EVERY ARRAY
    for (int i = 0; i < hashNumber; i++) {
        currentHT->array[i] = createLinkedList(copyValue, freeValue, printValue, equalKey, equalKey);
        if (currentHT->array[i] == NULL) {
            //FREE PREVIOUS
            for (int j = 0; j < i; j++) {
                destroyList(currentHT->array[j]);
            }
            //FREE HASH
            free(currentHT);
            return NULL;
        }
    }
    return currentHT;
}

//Function 2: destroyHashTable
//This function recieves a hashtable, and frees all it's memory
status destroyHashTable(hashTable currentHT){
    //CHECK IF INPUTS ARE VALID
    if (currentHT == NULL){
        return failure;
    }
    //LOOK FOR VALUE
    LinkedList currentLL;
    KeyValuePair currentKVP;
    for (int i = 0; i < currentHT->hashNumber; i++){
        for (int j = 1; j <= getLenghtList(currentHT->array[i]); j++){
            //FREE EACH KVP
            currentKVP = getDataByIndex(currentHT->array[i], j);
            destroyKeyValuePair(currentKVP);
            currentKVP = NULL;
        }
        //FREE EACH LINKED LIST
        currentLL = currentHT->array[i];
        destroyList(currentLL);
        currentLL = NULL;
    }
    //FREE HASH TABLE
    free(currentHT->array);
    free(currentHT);
    currentHT = NULL;
    return success;
}

//Function 3: addToHashTable
//This function recives 2 elements: a key and a value, and appends it to the needed node nesting inside the
//linked lists which are in the hash table
status addToHashTable(hashTable currentHT, Element key,Element value){
    //CHECK IF INPUTS ARE VALID
    if (currentHT == NULL || key == NULL || value == NULL){
        return failure;
    }
    //CREATE ELEMENTS
    int intKey = currentHT->intoNum(key) % currentHT->hashNumber;
    //int intKey = currentHT->intoNum(key);
    KeyValuePair newKVP = createKeyValuePair(key, value, currentHT->copyKey ,currentHT->freeKey ,currentHT->printKey ,currentHT->equalKey,
                                             currentHT->copyValue, currentHT->freeValue, currentHT->printValue);
    if (newKVP == NULL){
        return failure;
    }
    appendNode(currentHT->array[intKey], newKVP);
    currentHT->addedHash++;
    return success;
}

//Function 4: lookupInHashTable
//This function recieves a hash table and an element's key, and returns the value element
Element lookupInHashTable(hashTable currentHT, Element key){
    //CHECK IF INPUTS ARE VALID
    if (currentHT == NULL || key == NULL){
        return NULL;
    }
    //LOOK FOR VALUE
    Element currentKVP;
    for (int i = 0; i < currentHT->hashNumber; i++){
        for (int j = 1; j <= getLenghtList(currentHT->array[i]); j++){
            currentKVP = getDataByIndex(currentHT->array[i], j);
            //
            //
            if (isEqualKey(currentKVP, key) == true){
                return getValue(currentKVP);
            }
        }
    }
    return NULL;
}

//Function 5: removeFromHashTable
//This function recieves a pointer to a hash table and a key element. if that same value is found in the hash,
//it deletes and frees it's memory. Else, returns failure status
status removeFromHashTable(hashTable currentHT, Element key){
    //CHECK IF INPUTS ARE VALID
    if (currentHT == NULL || key == NULL){
        return failure;
    }
    //LOOK FOR KEY
    Element currentKVP;
    for (int i = 0; i < currentHT->hashNumber; i++){
        for (int j = 1; j <= getLenghtList(currentHT->array[i]); j++){
            currentKVP = getDataByIndex(currentHT->array[i], j);
            if (isEqualKey(currentKVP, key) == true){
                deleteNode(currentHT->array[i], currentKVP);
                //
                free(currentKVP);
                //
                return success;
            }
        }
    }
    return failure;
}

//Function 6: displayHashElements
//This function recieves a hashtable, and prints all the elements inside the hash by their order.
//First the key is printed, than the value
status displayHashElements(hashTable currentHT){
    //CHECK INPUTS ARE VALID
    if (currentHT == NULL){
        return failure;
    }
    //LOOP INPUTING VALUES
    //OUTER LOOP RUNS THOURGH EVERY CELL IN HASH TABLE
    for (int i = 0; i < currentHT->hashNumber; i++){
        if (getLenghtList(currentHT->array[i]) > 0){
            //INNER LOOP RUNS THOURGH EVERY NODE IN THE LINKED LIST
            for (int j = 1; j <= getLenghtList(currentHT->array[i]); j++){
                //GET THE KVP INSIDE THE NODE->DATA
                Element currentKVP = getDataByIndex(currentHT->array[i], j);
                if (currentKVP == NULL){
                    return failure;
                }
                //DISPLAY KEY + VALUE OF THE KVP
                //displayKey(currentKVP);
                displayValue(currentKVP);
            }
        }
    }
    return success;
}

Element getFromHashByIndex(hashTable currentHT, int index){
    //CHECK INPUTS ARE VALID
    if (currentHT == NULL){
        return NULL;
    }
    return currentHT->array[index];
}

