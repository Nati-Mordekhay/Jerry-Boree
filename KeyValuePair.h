#include "Defs.h"

#ifndef WORK_KEYVALUEPAIR_H
#define WORK_KEYVALUEPAIR_H

typedef struct KeyValuePair_t* KeyValuePair;

//KeyPairValueFunctions
KeyValuePair createKeyValuePair(Element, Element, CopyFunction, FreeFunction, PrintFunction, EqualFunction,
                                CopyFunction, FreeFunction, PrintFunction);
status destroyKeyValuePair(KeyValuePair);
status displayValue(KeyValuePair);
status displayKey(KeyValuePair);
Element getValue(KeyValuePair);
Element getKey(KeyValuePair);
bool isEqualKey(KeyValuePair, Element);


#endif //WORK_KEYVALUEPAIR_H
