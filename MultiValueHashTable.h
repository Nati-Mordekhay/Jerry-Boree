#ifndef WORK_MULTIVALUEHASHTABLE_H
#define WORK_MULTIVALUEHASHTABLE_H
#include "Defs.h"

typedef struct multiValueHashTable_s* MVhashTable;

//Functions
MVhashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                          CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                          EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
status destroyMultiValueHashTable(MVhashTable);
status addToMultiValueHashTable(MVhashTable, Element key, Element value);
Element lookupInMultiValueHashTable(MVhashTable, Element key);
status removeFromMultiValueHashTable(MVhashTable, Element key, Element value);
status displayMultiValueHashElementsByKey(MVhashTable, Element key);
Element getHash(MVhashTable);

#endif //WORK_MULTIVALUEHASHTABLE_H
