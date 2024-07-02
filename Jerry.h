#ifndef WORK_JERRY_H
#define WORK_JERRY_H
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

MVhashTable physicalCMHT;
hashTable jerriesHT;
MVhashTable physicalJerMHY;
LinkedList jerriesLL;
LinkedList originsLL;


//****************************************--PLANET--START************************************************//
//-----------------------------------------
/*
 * START OF PLANET STRUCT
 */

//PLANET STRUCT
typedef struct Planet_t
{
    char name[301];
    double cordX;
    double cordY;
    double cordZ;
    int status;
}Planet;

//DEFINING VARIABLES
int planetsNumber; // Actual number of planets in total
int assignedPlanets; // Will be used to count the number of number already added to the pPlanetArray
Planet *pPlanetArray; // Declaring a pointer to the pPlanetArray

//PLANET METHODS
Planet* addplanet(char*, double, double, double); // Used to add another planet to pPlanetArray
void printplanet(char*); // Prints a specific planet by inputting it's name
Planet* searchplanet(char*); // Returns a pointer to the searched planet by name
void freeplanets(); // Frees allocated memory of planets


/*
 * END OF PLANET STRUCT
 */
//-----------------------------------------
//****************************************--PLANET--END************************************************//
//****************************************--ORIGIN--START**********************************************//
/*
 * START OF ORIGIN STRUCT
 */
//Origin struct
typedef struct Origin_t
{
    char name[301];
    Planet *planetName;
    int status;
}Origin;

//DEFINING VARIABLES
int originsNumber; // Actual number of origins in total
int assignedOrigins; // Will be used to count the number of number already added to the pOriginsArray
Origin *pOriginArray; // Declaring a pointer to the pOriginsArray

//Origin methods
Origin* addorigin(char*, char*); // Used to add another origin to pOriginsArray
Origin* searchorigin(char *); //Search for an origin's pointer by it's name
void freeorigins(); // Frees memory allocated for Origins

/*
 * END OF ORIGIN STRUCT
 */
//-----------------------------------------
//****************************************--ORIGIN--END************************************************//
//******************************--PHYSICALCHARACTERISTICS--START***************************************//
//-----------------------------------------
/*
 * START OF PhysicalCharacteristics STRUCT
 */
//PhysicalCharacteristics struct
//Origin struct
typedef struct PhysicalCharacteristics_t
{
    char name[301];
    double value;
    int assigned;
}Physicalc;

//DEFINING VARIABLES
//**These variables were not used in the assignment, but for tests. Left if needed for next assignment **//
int physicalcnumber; // Actual number of PhysicalC in total
int assignedphysicalc; // Will be used to count the number of number already added to the pPhysicalcArray

//PhysicalCharacteristics methods
void printphysicalc(); // Prints a Physicalc
void freephysicalc(); // Frees allocated memory for PhysicalC

/*
 * END OF PhysicalCharacteristics STRUCT
 */
//-----------------------------------------
//******************************--PHYSICALCHARACTERISTICS--END***************************************//
//***********************************--JERRY--START**************************************************//
//-----------------------------------------
/*
 * START OF JERRY STRUCT
 */
//Jerry struct
typedef struct Jerry_t
{
    char id[301];
    int happiness;
    Planet *jerrysPlanet;
    Origin *jerrysOrigins;
    Physicalc physicalcStruct;
    Physicalc *physicalcArray;
    int jerrysNumberphysicalc;
    int inputNumJerry;
}Jerry;

//DEFINING VARIABLES
int jerrysNumber; // Actual number of jerrys in total
int assignedJerrys; // Will be used to count the number of number already added to the pJerrysArray
Jerry *pJerrysArray; // Declaring a pointer to the pJerrysArray
int inputNumJerryCounter;



//Jerry methods
Jerry *addjerry(char*, char*, char*, int); // Used to add another Jerry to pJerrysArray (ID, ORIGIN, PLANET, HAPPINNES)
void printjerry(Jerry*); // Used to print a specific Jerry
Physicalc * createphysicalc (char*, char*, double); // Creates a physicalc for a specific Jerry
void printphysicalc(Jerry*); // Prints the physicalc's of a specific Jerry
void deletephysicalc(Jerry*, char*); // Finds and deletes a physicalc from a specific Jerry


/*
 * END OF JERRY STRUCT
 */
//-----------------------------------------
//-----------------------------------------
//***********************************--JERRY--END**************************************************//


//ETC FUNCTIONS
void uppercase(char*); // Transformed a string into all upper case

// COPY // FREE // PRINT // EQUAL // TRANSFORM FUNCTIONS
Element copyKeyJerry(Element elem);
status freeKeyJerry(Element elem);
status printKeyJerry(Element elem);
status printKeyPC(Element elem);
Element copyValueJerry(Element elem);
status freeValueJerry(Element elem);
status printValueJerry(Element elem);
bool equalKeyJerries(Element elem1, Element elem2);
bool equalKeyPC(Element elem1, Element elem2);
int intoInt(Element elem);
status printValuePC(Element elem);
status printValuePC2(Element elem);
status freeOriginFunc(Element elem);
status freePCFunc(Element elem);
status printValueOrigin(Element elem);
status freeJerryFunc(Element elem);


//END FUNCTIONS
status freeLLkvp(Element elem);
status freePointer(Element elem);


#endif //WORK_JERRY_H


