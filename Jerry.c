#include "Jerry.h"
#include "MultiValueHashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"


/*
 * START OF STRUCT PLANET FUNCTIONS
 */

// ** ------------------------------------------------- ** //
//Function 1: addplanet
//This function recieves the information of the planet, and assinges it the current free
//space in the array of planets.
//Inputs: char* Planet Name, double X cord, double Y cord, double Z coud
Planet *addplanet(char *planetName, double cordX, double cordY, double cordZ){
    //ALLOCATE MEMORY IN THE HEAP FOR THE PLANETS ARRAY
    if (assignedPlanets == 0){ // If this is the first planet, need to malloc for planet's array
        pPlanetArray = (Planet*) malloc(planetsNumber * sizeof(Planet));
        //CHECK IF MEMORY IS ALLOCATED
        if (pPlanetArray == NULL){
            exit(1);
        }
    }
    Planet *currentPlanet; //Define pointer to current planet
    //CHECK IF PLANET WITH SAME NAME ALREADY EXISTS
    for (int i = 0; i < planetsNumber; i++){
        if (strcmp(pPlanetArray[i].name, planetName) == 0){
            break; // Exit function
        }
    }
    //ASSIGNING CURRENT PLANET ADDRESS
    currentPlanet = &pPlanetArray[assignedPlanets];
    //ASSIGNING VALUES OF CURRENT PLANET ADDED
    strcpy(currentPlanet->name, planetName); // Assign name
    currentPlanet->cordX = cordX; // Assign X
    currentPlanet->cordY = cordY; // Assign Y
    currentPlanet->cordZ = cordZ; // Assign Z
    currentPlanet->status = 1; // Assign status 1: current place is assign
    assignedPlanets++;
}

//Function 2: printplanet
//This function recieves an input of a planet's name and prints all it's information
//Inputs: char* Planet Name
void printplanet(char *planetName){
    for (int i = 0; i < planetsNumber; i++){
        Planet *currentPlanet = &pPlanetArray[i];
        if (strcmp(currentPlanet->name, planetName) == 0){
            printf("Planet : %s (%.2f,%.2f,%.2f) \n", currentPlanet->name, currentPlanet->cordX,
                   currentPlanet->cordY, currentPlanet->cordZ);
        }
    }
}

//Function 3: searchplanet
//This function recieves a planet's name and returns the pointer to that same planet
//Inputs: char* Planet Name
Planet *searchplanet(char* planetName){
    for (int i = 0; i < planetsNumber; i++){
        Planet *currentPlanet = &pPlanetArray[i];
        if (strcmp(currentPlanet->name, planetName) == 0){
            return currentPlanet;
        }
    }
    return NULL;
}

//Function 4: freeplanets
//This function frees the allocated memory for the planets
void freeplanets(){
    free(pPlanetArray);
    pPlanetArray = NULL; // POINTER SETS TO NULL
}

/*
 * END OF PLANET STRUCT
 */
//****************************************--PLANET--END************************************************//
//****************************************--ORIGIN--START**********************************************//
/*
 * START OF ORIGIN STRUCT
 */
// TO DO IN ORIGIN:
// 1: ERROR IF FUNCTION ALREADY EXISTS
// 2: IS FREE WORKING CORRECTLY?
//Function 1: addorigin
//This function recieves a name of an origin, and adds it into the array of origins.
//Inputs: char* Origin Name, char* Planet Name
Origin *addorigin(char *originName, char *planetName){
    //CURRENT ORIGIN
    Origin *currentOrigin = malloc(sizeof(Origin));
    Planet *currentPlanet = searchplanet(planetName); // Declaring pointer to current planet
    strcpy(currentOrigin->name, originName); // Assign origin's name
    currentOrigin->planetName = currentPlanet; // Assign origin's pointer to it's planet
    currentOrigin->status = 1; //current origin status now set to 1
    assignedOrigins++;
    return currentOrigin;
}

//Function 2: searchorigin
//THis function recieves an origin name and returns it's pointer
//Inputs: char* Origin Name
Origin *searchorigin(char* originName){
    for (int i = 1; i <= getLenghtList(originsLL); i++){
        Origin *currentOrigin = getDataByIndex(originsLL, i);
        if (strcmp(currentOrigin->name, originName) == 0){
            return currentOrigin;
        }
    }
    return NULL;
}

/*
 * END OF ORIGIN STRUCT
 */
//****************************************--ORIGIN--END************************************************//
//****************************************--PC--START**********************************************//
/*
 * START OF PC STRUCT
 */


void freephysicalc(){
    Jerry *currentJerry;
    for (int i = 1; i <= getLenghtList(jerriesLL); i++){
        currentJerry = getDataByIndex(jerriesLL, i);
        Physicalc *currentPhysicalc = &currentJerry->physicalcArray[0];
        free(currentPhysicalc);
    }
}



//****************************************--PC--END************************************************//
//****************************************--JERRY--START**********************************************//
/*
 * START OF JERRY STRUCT
 */
// TO DO IN JERRY:
// 1: ERROR IF FUNCTION ALREADY EXISTS
// 2: IS FREE WORKING CORRECTLY?
// 3: ADD PHYSICALC

//Function: add Jerry
//This function recieves an id, origin, planet, and happiness, to create a new Jerry
//Inputs: char* Jerry's ID, char* Origin Name, char* Planet Name, int Happiness Level
Jerry *addjerry(char* id, char* originName, char* planetName, int happinessLevel){
    //CURRENT JERRY
    //ID
    Jerry *currentJerry = malloc(sizeof(Jerry)); // The current jerry pointer
    strcpy(currentJerry->id, id); // Assign Jerry's ID
    //ORIGIN
    //addorigin(originName, planetName); // Add origin to origin's array
    Origin *currentOrigin = searchorigin(originName); // currentOrigin
    currentJerry->jerrysOrigins = currentOrigin;
    //PLANET
    Planet *currentPlanet = searchplanet(planetName); // currentPlanet
    currentJerry->jerrysPlanet = currentPlanet;
    //HAPPINESS
    currentJerry->happiness = happinessLevel;
    //
    currentJerry->jerrysNumberphysicalc = 0;
    //
    currentJerry->inputNumJerry = inputNumJerryCounter;
    inputNumJerryCounter++;
    assignedJerrys++;
    return currentJerry;
}

//Function: printjerry
//This function recieves an id and prints that same jerry and it's information
//Inputs: char* Jerry's ID
void printjerry(Jerry* currentJerry){
    printf("Jerry , ID - %s : \n"
           "Happiness level : %d \n"
           "Origin : %s \n",
           currentJerry->id,currentJerry->happiness,currentJerry->jerrysOrigins->name);
    printplanet(currentJerry->jerrysPlanet->name);
    //printphysicalc(currentJerry->id);
}

//Function: create a physicalc.
//This adds a new physicalc with it's value to the array.
//Inputs: char* Jerry's ID, char* PhysicalC Name, double, PhysicalC Value
Physicalc * createphysicalc(char* jerryID, char* physicalcName, double physicalcValue){
    Jerry *currentJerry;
    for (int i = 1; i <= getLenghtList(jerriesLL); i++){
        Jerry *searchJerry = getDataByIndex(jerriesLL, i);
        if (strcmp(searchJerry->id, jerryID) == 0){
            currentJerry = searchJerry;
        }
    }
    //CHECK IF MEMORY IS ALLOCATED
    if (currentJerry->jerrysNumberphysicalc == 0){
        currentJerry->physicalcArray = (Physicalc*) malloc(sizeof(currentJerry->physicalcStruct));
    }
        //IF THERE IS A NEED FOR REALLOCATION
    else
    {
        currentJerry->physicalcArray = (Physicalc*) realloc(
                currentJerry->physicalcArray,
                ((currentJerry->jerrysNumberphysicalc)+1)* sizeof(currentJerry->physicalcStruct));
    }
    //POINTER TO PHYSICALC STRUCT, TO THE CURRENT JERRY'S PHYSICALC
    Physicalc *currentPhysical = &currentJerry->physicalcArray[currentJerry->jerrysNumberphysicalc];
    //ASSIGN VALUES
    strcpy(currentPhysical->name, physicalcName); // Assign Physicalc name
    currentPhysical->value = physicalcValue; // ASsign Physicalc value
    currentJerry->jerrysNumberphysicalc++;
    return currentPhysical;
}

//Function: printphysicalc
//This function prints a jerry's entire physical c
//Inputs: char* Jerry's ID
void printphysicalc(Jerry* currentJerry){
    //PRINT TITLE FOR JERRY'S PHYSICALC
    if (currentJerry->jerrysNumberphysicalc > 0){
        printf("Jerry's physical Characteristics available : \n");
    }
    //FOR LOOP FOR PRINTING EACH PHYSICALC
    for (int i = 0; i < currentJerry->jerrysNumberphysicalc; i++){
        //IF IT'S THE FIRST VALUE AND ONLY VALUE, NO ',' AND NEEDS \n
        if (i == 0 && currentJerry->jerrysNumberphysicalc == 1){
            Physicalc *currentPhysical = &currentJerry->physicalcArray[i];
            printf("\t%s : %.2f \n", currentPhysical->name, currentPhysical->value);
        }
            //IF IT'S THE FIRST VALUE, NEEDS A TAB
        else if (i == 0){
            Physicalc *currentPhysical = &currentJerry->physicalcArray[i];
            printf("\t%s : %.2f , ", currentPhysical->name, currentPhysical->value);
        }
            //IF IT'S THE LAST VALUE, NO ',' AND THERE IS \N
        else if (i == currentJerry->jerrysNumberphysicalc - 1){
            Physicalc *currentPhysical = &currentJerry->physicalcArray[i];
            printf("%s : %.2f \n", currentPhysical->name, currentPhysical->value);
        }
            //MIDDLE VALUES
        else {
            Physicalc *currentPhysical = &currentJerry->physicalcArray[i];
            printf("%s : %.2f , ", currentPhysical->name, currentPhysical->value);
        }
    }
}


//Function: deletephysicalc
//This function recieves a Jerry and a PHysicalc and deletes that one
//Inputs: char* Jerry's ID, char* PhysicalC Name
void deletephysicalc(Jerry* currentJerry, char* physicalcName){
    //Jerry *currentJerry = searchjerry(id);

    for (int i = 0; i < currentJerry->jerrysNumberphysicalc; i++){
        Physicalc *currentPhysical = &currentJerry->physicalcArray[i];
        if (strcmp(currentPhysical->name, physicalcName) == 0){
            for (int j = i; j < currentJerry->jerrysNumberphysicalc; j++){
                strcpy(currentPhysical->name, currentJerry->physicalcArray[j+1].name);
                currentPhysical->value = currentJerry->physicalcArray[j+1].value;
                currentPhysical = &currentJerry->physicalcArray[j+1];
            }
            break;
        }
    }
    //SHORTEN MEMORY ALLOCATION BY 1
    currentJerry->jerrysNumberphysicalc--;
    currentJerry->physicalcArray = realloc(currentJerry->physicalcArray,(currentJerry->jerrysNumberphysicalc) * (sizeof(Physicalc)));
}

/*
 * END OF JERRY STRUCT
 */

/*
 * EXTRA ETC FUNCTION TO BE USED
 */

// COPY // FREE // PRINT // EQUAL // TRANSFORM FUNCTIONS
//Function: copyKeyJerry
//This function recieves a pointer to a jerry's struct, and returns it's id string
Element copyKeyJerry(Element elem){
    if (elem == NULL){
        exit(0);
    }
    Jerry *currentJerry = elem;
    return currentJerry->id;
}

//Function: freeKeyJerry
//This functions recieves a pointer to a jerry's struct, and free's it's key
status freeKeyJerry(Element elem){
    if (elem == NULL){
        exit(0);
    }
    return success;
};

//Function: printKeyJerry
status printKeyJerry(Element elem){
    if (elem == NULL){
        exit(0);
    }
    Jerry *currentJerry = elem;
    printf("%s", currentJerry->id);
    return success;
}

//Function: copyValueJerry
//This function recieves a pointer to a jerry's struct, and returns the element pointer
Element copyValueJerry(Element elem){
    if (elem == NULL){
        exit(0);
    }
    return elem;
}

//Function: freeValueJerry
//This functions recieves a pointer to a jerry's struct, and free's it's value
status freeValueJerry(Element elem){
    if (elem == NULL){
        exit(0);
    }
    return success;
};

//Function: printValueJerry
status printValueJerry(Element elem){
    if (elem == NULL){
        exit(0);
    }
    Jerry *currentJerry = elem;
    printjerry(currentJerry);
    printphysicalc(currentJerry);
    return success;
}

//function: equalKeyJerries
bool equalKeyJerries(Element elem1, Element elem2){
    if (elem1 == NULL || elem2 == NULL){
        exit(0);
    }
    Jerry *currentJerry = elem1;
    if (strcmp(currentJerry->id, elem2) == 0){
        return true;
    }
    return false;
}

bool equalKeyPC(Element elem1, Element elem2){
    if (elem1 == NULL || elem2 == NULL){
        exit(0);
    }
    Physicalc *currentPC = elem1;
    if (strcmp(currentPC->name, elem2) == 0){
        return true;
    }
    return false;
}

//Function: intoInt
//This functions recieves an element which points to a string, and transforms it into it's ascii code int
int intoInt(Element elem){
    if (elem == NULL){
        exit(0);
    }
    int answer = 0;
    int length = strlen((char*)elem);
    for (int i = 0; i < length; i++) {
        char letter = ((char*)elem)[i];
        answer += (int)letter;
    }
    return answer;
}

//Function: printValuePC
status printValuePC(Element elem){
    if (elem == NULL){
        exit(0);
    }
    Physicalc *currentPC = elem;
    printf("%s :", currentPC->name);
    printf(" %.2f ", currentPC->value);
    return success;
}

//Function: printKeyPC
status printKeyPC(Element elem){
    if (elem == NULL){
        exit(0);
    }
    Jerry *currentJerry = elem;
    printjerry(currentJerry);
    printphysicalc(currentJerry);
    return success;
}

status printValuePC2(Element elem){
    if (elem == NULL){
        exit(0);
    }
    printf("*************************\n");
    printf("1");
    return success;
}

//*********************************************************
status freeOriginFunc(Element elem){
    if (elem == NULL){
        return failure;
    }
    Origin *currentOrigin = elem;
    free(currentOrigin);
    return success;
}

status printValueOrigin(Element elem){
    if (elem == NULL){
        return failure;
    }
    return success;
}

status freeJerryFunc(Element elem){
    if (elem == NULL){
        return failure;
    }
    Jerry *currentJerry = elem;
    free(currentJerry);
    return success;
}

