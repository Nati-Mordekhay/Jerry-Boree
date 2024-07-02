
#ifndef WORK_DEFS_H
#define WORK_DEFS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum e_bool { false, true } bool;
typedef enum e_status { success, failure } status;

typedef void * Element;

typedef Element(*CopyFunction) (Element);
typedef status(*FreeFunction) (Element);
typedef status(*PrintFunction) (Element);
typedef int(*TransformIntoNumberFunction) (Element);
typedef bool(*EqualFunction) (Element, Element);

#endif //WORK_DEFS_H
