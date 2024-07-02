#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
#include "Jerry.h"

struct multiValueHashTable_s{
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
    TransformIntoNumberFunction intoNum;
    int hashNumber;
    hashTable* array;
};


//Function 1: createMultiValueHashTable
//This functions recieves 2 elemets: key and value and creats a new hash
MVhashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                                      CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                                      EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
    //CHECK INPUTS ARE VALID
    if (copyKey == NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL ||
        printValue == NULL || equalKey == NULL || transformIntoNumber == NULL) {
        return NULL;
    }
    //CREATE NEW MV HASH TABLE
    MVhashTable currentMHT = malloc(sizeof(struct multiValueHashTable_s));
    if (currentMHT == NULL) {
        return NULL;
    }
    //ALLOCATE MEMORY FOR HASH ARRAY
    currentMHT->array = malloc(sizeof(hashTable));
    if (currentMHT->array == NULL){
        free(currentMHT);
        return NULL;
    }
    //CREATE THE HASH INSIDE THE MHT POINTS TO
    *currentMHT->array = createHashTable(copyKey, freeKey, printKey, copyValue, freeValue, printValue, equalKey,
                                         transformIntoNumber, hashNumber);
    //ASSIGN VALUES
    currentMHT->copyKey = copyKey;
    currentMHT->freeKey = freeKey;
    currentMHT->printKey = printKey;
    currentMHT->copyValue = copyValue;
    currentMHT->freeValue = freeValue;
    currentMHT->printValue = printValue;
    currentMHT->equalKey = equalKey;
    currentMHT->intoNum = transformIntoNumber;
    currentMHT->hashNumber = hashNumber;
    return currentMHT;
}

//Function 2: destroyMultiValueHashTable
//This function deletes and frees the entire content of the MHT.
status destroyMultiValueHashTable(MVhashTable currentMHT){
    //CHECK IF INPUTS ARE VALID
    if (currentMHT == NULL){
        return failure;

    }
    /*
    for (int i = 0; i < currentMHT->hashNumber; i++){
        LinkedList currentLL = getFromHashByIndex(*currentMHT->array, i);
        for (int j = 1; j <= getLenghtList(currentLL); j++){
            KeyValuePair currentKVP = getDataByIndex(currentLL, j);
            KeyValuePair innerKVP = getValue(currentKVP);
            LinkedList innerLL = getValue(innerKVP);
            destroyList(innerLL);
            destroyKeyValuePair(innerKVP);
        }
    }
     */
    destroyHashTable(*currentMHT->array);
    free(currentMHT->array);
    free(currentMHT);
    currentMHT = NULL;
    return success;
}


//Function 3: addToMultiValueHashTable
//This functions recieves a pointer to a MHT, and 2 elemts: a key and a value.
//if key exists, adds the value to the rest of it's values, if not - creates a new one.
status addToMultiValueHashTable(MVhashTable currentMHT, Element key, Element value){
    //CHECK IF INPUTS ARE VALID
    if (currentMHT == NULL || key == NULL || value == NULL){
        return failure;
    }
    //IF KEY DOES NOT EXIST
    KeyValuePair currentKVP = lookupInHashTable(*currentMHT->array, key);
    if (currentKVP == NULL){
        //CREATE A NEW LINKED LIST
        LinkedList currentLL = createLinkedList(currentMHT->copyValue, currentMHT->freeValue, currentMHT->printValue,
                                                currentMHT->equalKey, currentMHT->equalKey);
        if (currentLL == NULL){
            return failure;
        }
        //ADD NEW VALUE TO THE NEWLY CREATED LINKED LIST
        appendNode(currentLL, value);
        //
        //
        //CREATE A NEW KEY PAIR VALUE
        //********************
        currentKVP = createKeyValuePair(key, currentLL, currentMHT->copyKey, currentMHT->freeKey, currentMHT->printKey,
                                        currentMHT->equalKey, currentMHT->copyValue, currentMHT->freeValue, currentMHT->printValue);
        if (currentKVP == NULL) {
            destroyList(currentLL);
            return failure;
        }
        //*********************
        //ADD NEW KEY-VALUE PAIR TO THE HASH TABLE
        addToHashTable(*currentMHT->array, key, currentKVP);
        return success;
    }
    //IF KEY DOES EXIST
    LinkedList currentLL = getValue(currentKVP);
    //ADD NEW VALUE TO THE EXISTING LINKED LIST
    appendNode(currentLL, value);
    return success;
}

//Function 4: lookupInMultiValueHashTable
//This function recieves a MHT and a key element, returens all the values hold by the key
Element lookupInMultiValueHashTable(MVhashTable currentMHT, Element key){
    //CHECK INPUTS ARE VALID
    if (currentMHT == NULL || key == NULL){
        return NULL;
    }
    //IF KEY DOES NOE EXIST
    KeyValuePair currentKVP = lookupInHashTable(*currentMHT->array, key);
    if (currentKVP == NULL){
        return NULL;
    }
    //IF KEY DOES EXIST
    LinkedList currentLL = getValue(currentKVP);
    return currentLL;
}

//Function 5: removeFromMultiValueHashTable
//This function recieves a MHT and 2 elements a key and a value (or part of it). if the key exists,
//deletes the value from the key's linked list. if list stays empty after the node delete, the key will also
//be deleted. If key does not exist, return failure status.
status removeFromMultiValueHashTable(MVhashTable currentMHT, Element key, Element value){
    //CHECK IF INPUTS ARE VALID
    if (currentMHT == NULL || key == NULL || value == NULL){
        return failure;
    }
    //CHECK IF KEY EXISTS
    KeyValuePair currentKVP = lookupInHashTable(*currentMHT->array, key);
    if (currentKVP == NULL){
        return failure;
    }
    //IF KEY DOES EXIST
    LinkedList currentLL = getValue(currentKVP);
    deleteNode(currentLL, value);
    if (getLenghtList(currentLL) == 0){
        removeFromHashTable(*currentMHT->array, key);
        destroyList(currentLL);
        destroyKeyValuePair(currentKVP);
    }
    return success;
}

//Function 6: displayMultiValueHashElementsByKey(MVhashTable, Element key)
//This functions recieves a MHT and an element key, and returns the key and all the values stored in by that key.
status displayMultiValueHashElementsByKey(MVhashTable currentMHT, Element key){
    //CHECK INPUTS ARE VALID
    if (currentMHT == NULL || key == NULL){
        return failure;
    }
    //CHECK IF KEY EXISTS
    if (lookupInHashTable(*currentMHT->array, key) == NULL){
        return failure;
    }
        //IF KEY EXISTS
    else {
        KeyValuePair currentKVP = lookupInHashTable(*currentMHT->array, key);
        LinkedList currentLL = getValue(currentKVP);
        //displayKey(currentKVP);
        displayList(currentLL);
        return success;
    }
}

Element getHash(MVhashTable currentMHT){
    if (currentMHT == NULL){
        return NULL;
    }
    return currentMHT->array;
}