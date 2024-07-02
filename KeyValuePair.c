#include "KeyValuePair.h"

struct KeyValuePair_t{
    Element key;
    Element value;
    CopyFunction copyKeyFunc;
    FreeFunction freeKeyFunc;
    PrintFunction printKeyFunc;
    EqualFunction equalKeyFunc;
    CopyFunction copyValueFunc;
    FreeFunction freeValueFunc;
    PrintFunction printValueFunc;
};

//Function 1: createKeyValuePair
//This functions recieves a key element and a value element, and creates a KVP with their functions.
KeyValuePair createKeyValuePair(Element key, Element value, CopyFunction copyKeyFunc, FreeFunction freeKeyFunc,
                                PrintFunction printKeyFunc, EqualFunction equalKeyFunc, CopyFunction copyValueFunc,
                                FreeFunction freeValueFunc, PrintFunction printValueFunc){
    //CHECK IF INPUTS ARE VALID
    if (key == NULL || value == NULL || copyKeyFunc == NULL || freeKeyFunc == NULL || printKeyFunc == NULL ||
        equalKeyFunc == NULL || copyValueFunc == NULL || freeValueFunc == NULL || printValueFunc == NULL){
        return NULL;
    }
    //CREATE AND MALLOC FOR NEW KVP
    KeyValuePair newKVP = malloc(sizeof(struct KeyValuePair_t));
    if (newKVP == NULL){
        return NULL;
    }
    //ASSIGN FUNCTIONS
    newKVP->copyKeyFunc = copyKeyFunc;
    newKVP->freeKeyFunc = freeKeyFunc;
    newKVP->printKeyFunc = printKeyFunc;
    newKVP->equalKeyFunc = equalKeyFunc;
    newKVP->copyValueFunc = copyValueFunc;
    newKVP->freeValueFunc = freeValueFunc;
    newKVP->printValueFunc = printValueFunc;
    //NEW ELEMENTS
    Element newKey = newKVP->copyKeyFunc(key);
    Element newValue = newKVP->copyValueFunc(value);
    if (newKey == NULL || newValue == NULL){
        return NULL;
    }
    //ASSIGN VALUES
    newKVP->key = newKey;
    newKVP->value = newValue;
    //RETURN
    return newKVP;
}

//Function 2: destroyKeyValuePair
//This function recieves a KVP and deletets it with freeing it's memory
status destroyKeyValuePair(KeyValuePair currentKVP){
    //CHECK INPUTS ARE VALID
    if (currentKVP == NULL){
        return failure;
    }
    //FREE ELEMENTS AND KVP
    currentKVP->freeKeyFunc(currentKVP->key);
    currentKVP->key = NULL;
    currentKVP->freeValueFunc(currentKVP->value);
    currentKVP->value = NULL;
    free(currentKVP);
    currentKVP = NULL;
    return success;
}

//Function 3: displayValue
//This function recieves a KVP and prints out it's value.
status displayValue(KeyValuePair currentKVP){
    //CHECK IF INPUTS ARE VALID
    if (currentKVP == NULL){
        return failure;
    }
    //PRINT
    currentKVP->printValueFunc(currentKVP->value);
    return success;
}

//Function 4: displayKey
//This function recieves a KVP and prints out it's key.
status displayKey(KeyValuePair currentKVP){
    //CHECK IF INPUTS ARE VALID
    if (currentKVP == NULL){
        return failure;
    }
    //PRINT
    currentKVP->printKeyFunc(currentKVP->key);
    return success;
}

//Function 5: getValue
//This function recieves a KVP and returns a pointer (Element) to it's value
Element getValue(KeyValuePair currentKVP){
    //CHECK IF INPUTS ARE VALID
    if (currentKVP == NULL){
        return NULL;
    }
    //RETURN VALUE
    return currentKVP->value;
}

//Function 6: getKey
//This function recieves a KVP and returns a pointer (Element) to it's key
Element getKey(KeyValuePair currentKVP){
    //CHECK IF INPUTS ARE VALID
    if (currentKVP == NULL){
        return NULL;
    }
    //RETURN KEY
    return currentKVP->key;
}

//Function 7: isEqualKey
//This function recieves a KVP and a key element, and returns a bool indicating if they are equal.
bool isEqualKey(KeyValuePair currentKVP, Element elem){
    //CHECK IF INPUTS ARE VALID
    if (currentKVP == NULL || elem == NULL){
        return false;
    }
    if (currentKVP->equalKeyFunc(currentKVP->key, elem) == true){
        return true;
    }
    else{
        return false;
    }
}

