#include "Defs.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
#include "HashTable.h"
#include "MultiValueHashTable.h"
#include "Jerry.h"

int main(int argc, char *argv[]) {

    //****************** PHASE 1 : READ FROM FILE NUMBER OF TOTAL LINES ***************************//
    //FILE SOURCE ARGUMENT
    char *fileSource;
    fileSource = argv[2];
    //READ FROM FILE PARAMETERS
    FILE *fileIn = fopen(fileSource, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    //VARIABLES FOR FILE
    int totalNumberOfLines = 0;
    //START LOOPING FILE
    while ((read = getline(&line, &len, fileIn)) != -1) {
        totalNumberOfLines++;
    }
    free(line);
    fclose(fileIn);

    //****************** PHASE 2 : READ FROM FILE NUMBER OF JERRIES ***************************//
    //READ FROM FILE PARAMETERS
    fileIn = fopen(fileSource, "r");
    line = NULL;
    len = 0;
    read;
    //VARIABLES FOR FILE
    int numberOfJerries = 0;
    int currentLine = 0;
    //START LOOPING FILE
    while ((read = getline(&line, &len, fileIn)) != -1) {
        currentLine++; // counts the current line
        //IF FOUND START OF JERRIES
        if (strcmp(line, "Jerries\n") == 0) {
            //START LOOPING TO THE END OF THE FILE
            for (int i = currentLine; i < totalNumberOfLines; i++) {
                //SKIP THE "JERRIES" LINE
                (read = getline(&line, &len, fileIn));
                //IF THE LINE DOES NOT START WITH A TAB /t, COUNT IT INTO NUMBER OF JERRIES
                if (strstr(line, "\t") == NULL) {
                    numberOfJerries++;
                }
            }
        }
    }
    free(line);
    fclose(fileIn);

    //****************** PHASE 3 : SET PARAMETERS FOR NUM OF PLANETS, JERRIES, ORIGINS ***************************//

    planetsNumber = strtol(argv[1], NULL, 10); // Total number of planets
    jerrysNumber = numberOfJerries; // Total number of Jerries
    originsNumber = numberOfJerries; // Total number of origins
    double hashNumber = numberOfJerries * 0.8;
    int hashNumberInt = (int) hashNumber;

    //****************** PHASE 4 : CREATE PLANETS ARRAY ***************************//
    //READ FROM FILE PARAMETERS
    fileIn = fopen(fileSource, "r");
    line = NULL;
    len = 0;
    read;
    //VARIABLES FOR FILE
    currentLine = 0;
    char planetName[301];
    double cordX;
    double cordY;
    double cordZ;
    char *restOfDouble;
    //START LOOPING FILE
    while ((read = getline(&line, &len, fileIn)) != -1) {
        //COUNT CURRENT LINE
        currentLine++;
        //IF PLANETS IS FOUND
        if (strcmp(line, "Planets\n") == 0) {
            //START LOOPING UNTIL THE END OF THE PLANETS
            for (int i = currentLine; i < currentLine + planetsNumber; i++) {
                //SKIP THE "PLANETS" LINE
                read = getline(&line, &len, fileIn);
                //PLANET'S NAME
                char *planetPart = strtok(line, ",");
                strcpy(planetName, planetPart);
                //PLANET'S CORDX + CASTING TO DOUBLE
                planetPart = strtok(NULL, ",");
                cordX = strtod(planetPart, &restOfDouble);
                //PLANET'S CORDT + CASTING TO DOUBLE
                planetPart = strtok(NULL, ",");
                cordY = strtod(planetPart, &restOfDouble);
                //PLANET'S CORDZ + CASTING TO DOUBLE
                planetPart = strtok(NULL, ",");
                cordZ = strtod(planetPart, &restOfDouble);
                //ADDING THE PLANET INTO THE PLANET'S ARRAY
                addplanet(planetName, cordX, cordY, cordZ);
            }
        }
    }
    free(line);
    fclose(fileIn);

    //****************** PHASE 4 : CREATE JERRIES HASH ***************************//
    //READ FROM FILE PARAMETERS
    fileIn = fopen(fileSource, "r");
    line = NULL;
    len = 0;
    read;
    //VARIABLES FOR FILE
    currentLine = 0;
    //CREATING STRUCTS
    physicalJerMHY = createMultiValueHashTable(copyValueJerry, freeValueJerry, printValuePC2, copyKeyJerry, freeKeyJerry,
                                               printKeyPC, equalKeyPC, intoInt, hashNumberInt);
    physicalCMHT = createMultiValueHashTable(copyKeyJerry, freeKeyJerry, printKeyJerry, copyValueJerry, freeValueJerry,
                                             printValuePC, equalKeyJerries, intoInt, hashNumberInt);
    //jerriesHT = createHashTable(copyKeyJerry, freeKeyJerry, printKeyJerry, copyValueJerry, freeValueJerry,
    //                            printValueJerry, equalKeyJerries, intoInt, hashNumberInt);
    jerriesHT = createHashTable(copyKeyJerry, freeKeyJerry, printKeyJerry, copyValueJerry, freeValueJerry,
                                printValueJerry, equalKeyJerries, intoInt, hashNumberInt);
    jerriesLL = createLinkedList(copyValueJerry, freeJerryFunc, printValueJerry, equalKeyJerries, equalKeyJerries);
    originsLL = createLinkedList(copyValueJerry, freeOriginFunc, printValueOrigin, equalKeyJerries, equalKeyJerries);
    //PARAMETERS FOR READING FROM FILE
    char id[301];
    char jerrysOrigin[301];
    char jerrysPlanet[301];
    int jerrysHappiness;
    char jerrysPhysicalc[301];
    double  jerrysPCValue;
    char *jerrysRestOfDouble;
    int currentJerrycount = 0;
    int assignedJerriesNow = 0;
    //START LOOPING FILE
    while ((read = getline(&line, &len, fileIn)) != -1){
        //COUNT CURRENT LINE
        currentLine++;
        //IF FOUND LINE "JERRIES"
        if (strcmp(line, "Jerries\n") == 0){
            for (int i = currentLine; i < totalNumberOfLines; i++){
                read = getline(&line, &len, fileIn);
                //IF LINE HAS NOT TAB "\t": JERRY ITSELF
                if (strstr(line, "\t") == NULL){
                    //JERRY ID
                    char* jerryPart = strtok(line, ",");
                    strcpy(id, jerryPart);
                    //JERRY ORIGIN
                    jerryPart = strtok(NULL, ",");
                    strcpy(jerrysOrigin, jerryPart);
                    //JERRY PLANET
                    jerryPart = strtok(NULL, ",");
                    strcpy(jerrysPlanet, jerryPart);
                    //JARRY HAPPINESS
                    jerryPart = strtok(NULL, ",");
                    jerrysHappiness = strtol(jerryPart, NULL, 10);
                    //ADD JERRY
                    Origin *currentOrigin = addorigin(jerrysOrigin, jerrysPlanet);
                    appendNode(originsLL, currentOrigin);
                    Jerry *currentJerry = addjerry(id, jerrysOrigin, jerrysPlanet, jerrysHappiness);
                    appendNode(jerriesLL, currentJerry);
                    //addToHashTable(jerriesHT, currentJerry->id, currentJerry);
                    currentJerrycount++;
                    assignedJerriesNow++;
                }

                    //IF LINE DOES HAVE TAB "\t"
                else if (strstr(line, "\t") != NULL){
                    //CLEAN TAB
                    char *cleanLine = line;
                    while (isspace(*cleanLine)){
                        ++cleanLine;
                    }
                    //ASSIGGN VALUS
                    //PHYSICALC NAME
                    char* jerryPart = strtok(cleanLine, ":");
                    strcpy(jerrysPhysicalc, jerryPart);
                    //PHYSICALC VALUE
                    jerryPart = strtok(NULL, "\n");
                    jerrysPCValue = strtod(jerryPart, &jerrysRestOfDouble);
                    //ADD NEW PHYSICALC
                    createphysicalc(id, jerrysPhysicalc, jerrysPCValue);
                }
            }
            break;
        }
    }
    //FREE READ
    free(line);
    fclose(fileIn);

    //ADDING ELEMENTS TO HASH TABLES
    Jerry *currentJerry;
    Origin *currentOrigin;
    LinkedList currentLL;
    Node currentNode;
    //ADDING READ ELEMENTS TO STRUCTS
    for (int i = 1; i <= getLenghtList(jerriesLL); i++){
        currentJerry = getDataByIndex(jerriesLL, i);
        addToHashTable(jerriesHT, currentJerry->id, currentJerry);
        for (int j = 0; j < currentJerry->jerrysNumberphysicalc; j++){
            addToMultiValueHashTable(physicalCMHT, currentJerry->id, &currentJerry->physicalcArray[j].name);
            addToMultiValueHashTable(physicalJerMHY, &currentJerry->physicalcArray[j].name, currentJerry->id);
        }
    }

    //****************** PHASE 5 : MENU  ***************************//

    //freopen("/home/ise/Desktop/Semester 3/Adv. Prog/HW/HW3 - C/work/only_input.txt","r",stdin);

    //PARAMETERS
    char ch = '1';
    char ch7 = '1';
    char ch8 = '1';
    char inputedJerrysID[301]; // WILL BE THE JERRYS INPUTED ID TO SCAN
    char inputedJerrysPlanet[301]; // WILL BE THE JERRYS INPUTED PLANET TO SCAN
    char inputedJerrysDimension[301]; // WILL BE THE JERRYS INPUTED DIMENSON=ORIGIN TO SCAN
    int inputedJerrysHappines = 0; // WILL BE THE JERRY'S INPUTED HAPPINESS
    char inputedJerrysHappinesCONVERT[301]; // WILL BE USED TO CONVERT INPUT TO INT
    char inputedJerrysPCname[301];
    char inputedJerrysPCvalueCHAR[301];
    int inputedJerrysPCvalue;
    int statusADDpc = 0;
    int currentJerrysHappiness;
    Jerry *tempJerry;
    Physicalc *currentPhysical;
    while ( ch != '9'){
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");
        scanf(" %c%*[^\n]", &ch);
        switch(ch){
            case '1': // ADD NEW JERRY TO SYSTEM
                //CHECK INPUTED ID
                printf("What is your Jerry's ID ? \n");
                scanf("%s", inputedJerrysID);
                //LOOK FOR ID IN THE JERRIES HASH TABLE
                if (lookupInHashTable(jerriesHT, inputedJerrysID) != NULL){
                    printf("Rick did you forgot ? you already left him here ! \n");
                    break;
                }
                //CHECK INPUTED PLANET
                printf("What planet is your Jerry from ? \n");
                scanf("%s", inputedJerrysPlanet);
                //IF PLANET NOT FOUND
                if (searchplanet(inputedJerrysPlanet) == NULL){
                    printf("%s is not a known planet ! \n", inputedJerrysPlanet);
                    break;
                }
                //CHECK ORIGIN
                printf("What is your Jerry's dimension ? \n");
                scanf("%s", inputedJerrysDimension);
                //CHECK HAPPINESS
                printf("How happy is your Jerry now ? \n");
                scanf("%s", inputedJerrysHappinesCONVERT);
                inputedJerrysHappines = strtol(inputedJerrysHappinesCONVERT, NULL, 10); //Convert to int
                //CREATE ORIGIN + ADD TO ORIGIN'S LINKED LIST
                currentOrigin = addorigin(inputedJerrysDimension, inputedJerrysPlanet);
                appendNode(originsLL, currentOrigin);
                //CREATE JERRY + ADD TO JERRIE'S LINKED LIST + ADD TO JERRIES HASH TABLE
                currentJerry = addjerry(inputedJerrysID, inputedJerrysDimension, inputedJerrysPlanet, inputedJerrysHappines);
                appendNode(jerriesLL, currentJerry);
                addToHashTable(jerriesHT, currentJerry->id, currentJerry);
                //PRINT JERRY
                printjerry(currentJerry);
                break;

            case '2': // ADD PHYSICALC TO JERRY
                //CHECK INPUTED ID
                printf("What is your Jerry's ID ? \n");
                scanf("%s", inputedJerrysID);
                if (lookupInHashTable(jerriesHT, inputedJerrysID) == NULL){
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }
                //LOOK FOR JERRY IN JERRIES HASH TABLE
                currentJerry = lookupInHashTable(jerriesHT, inputedJerrysID);
                //CHECK INPUTED PHYSICAL C
                printf("What physical characteristic can you add to Jerry - %s ? \n", inputedJerrysID);
                scanf("%s", inputedJerrysPCname);
                Physicalc *currentPC;
                //CHECK IF INFORMATION EXISTS
                for (int i = 0; i < currentJerry->jerrysNumberphysicalc; i++){
                    //ITERATE JERRY'S PHYSICAL C
                    if (strcmp(inputedJerrysPCname, currentJerry->physicalcArray[i].name) == 0){
                        printf("The information about his %s already available to the daycare ! \n", inputedJerrysPCname);
                        statusADDpc = 1;
                    }
                }
                //RESET STATUS, BREAK IF STATUS INCORRECT
                if (statusADDpc == 1){
                    statusADDpc = 0;
                    break;
                }
                //INPUT VALUE
                printf("What is the value of his %s ? \n", inputedJerrysPCname);
                scanf("%s", inputedJerrysPCvalueCHAR);
                inputedJerrysPCvalue = strtol(inputedJerrysPCvalueCHAR, NULL, 10); // Convert to int
                //CREATE PHYSICAL C
                currentPC = createphysicalc(currentJerry->id, inputedJerrysPCname, inputedJerrysPCvalue);
                //ADD PHYSICAL C TO MULTI HASH BY JERRY ID + PHYSICAL C NAME
                addToMultiValueHashTable(physicalCMHT, currentJerry->id, currentPC->name);
                addToMultiValueHashTable(physicalJerMHY, currentPC->name, currentJerry->id);
                //PRINT
                printf("%s : \n", inputedJerrysPCname);
                displayMultiValueHashElementsByKey(physicalJerMHY, currentPC->name);
                break;

            case '3': // //DELETE PHYSICALC FROM JERRY
                //CHECK INPUTED ID
                printf("What is your Jerry's ID ? \n");
                scanf("%s", inputedJerrysID);
                //LOOK FOR JERRY IN HASH TABLE
                if (lookupInHashTable(jerriesHT, inputedJerrysID) == NULL){
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }
                //CHECK IF JERRY EXISTS
                currentJerry = lookupInHashTable(jerriesHT, inputedJerrysID);
                tempJerry = currentJerry;
                //INPUT PHYSICAL C NAME TO DELETE
                printf("What physical characteristic do you want to remove from Jerry - %s ? \n", inputedJerrysID);
                scanf("%s", inputedJerrysPCname);
                //CHECK IF EXISTS
                for (int i = 0; i < currentJerry->jerrysNumberphysicalc; i++){
                    if (strcmp(inputedJerrysPCname, currentJerry->physicalcArray[i].name) == 0){
                        statusADDpc = 1;
                    }
                }
                //IF DOES NOT EXIST
                if (statusADDpc == 0){
                    printf("The information about his %s not available to the daycare ! \n", inputedJerrysPCname);
                    break;
                }
                //FIND CURRENT PHYSICAL C
                for (int i = 0; i < currentJerry->jerrysNumberphysicalc; i++){
                    if (strcmp(inputedJerrysPCname, currentJerry->physicalcArray[i].name) == 0){
                        currentPC = &currentJerry->physicalcArray[i];
                    }
                }
                //DELETE PHYSICAL C
                deletephysicalc(currentJerry, currentPC->name);
                //UPDATE HASH TABLE START
                destroyMultiValueHashTable(physicalCMHT);
                destroyMultiValueHashTable(physicalJerMHY);
                physicalCMHT = createMultiValueHashTable(copyKeyJerry, freeKeyJerry, printKeyJerry, copyValueJerry, freeValueJerry,
                                                         printValuePC, equalKeyJerries, intoInt, hashNumberInt);
                physicalJerMHY = createMultiValueHashTable(copyValueJerry, freeValueJerry, printValuePC2, copyKeyJerry, freeKeyJerry,
                                                           printKeyPC, equalKeyPC, intoInt, hashNumberInt);
                for (int i = 1; i <= getLenghtList(jerriesLL); i++){
                    currentJerry = getDataByIndex(jerriesLL, i);
                    for (int j = 0; j < currentJerry->jerrysNumberphysicalc; j++){
                        addToMultiValueHashTable(physicalCMHT, currentJerry->id, &currentJerry->physicalcArray[j].name);
                        addToMultiValueHashTable(physicalJerMHY, &currentJerry->physicalcArray[j].name, currentJerry->id);
                    }
                }
                //PRINT
                printjerry(tempJerry);
                printphysicalc(tempJerry);
                statusADDpc = 0;
                break;

            case '4': //
                //CHECK INPUT ID
                printf("What is your Jerry's ID ? \n");
                scanf("%s", inputedJerrysID);
                //LOOK FOR JERRY IN JERRIES HASH TABLE
                if (lookupInHashTable(jerriesHT, inputedJerrysID) == NULL){
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }
                //FIND CORRECT JERRY
                currentJerry = lookupInHashTable(jerriesHT, inputedJerrysID);
                //DELETE PHYSICAL C OF JERRY
                for (int i = 0; i < currentJerry->jerrysNumberphysicalc; i++){
                    deletephysicalc(currentJerry, currentJerry->physicalcArray[i].name);
                }

                //UPDATE HASH TABLE START
                destroyMultiValueHashTable(physicalCMHT);
                destroyMultiValueHashTable(physicalJerMHY);
                //
                destroyHashTable(jerriesHT);
                //
                physicalCMHT = createMultiValueHashTable(copyKeyJerry, freeKeyJerry, printKeyJerry, copyValueJerry, freeValueJerry,
                                                         printValuePC, equalKeyJerries, intoInt, hashNumberInt);
                physicalJerMHY = createMultiValueHashTable(copyValueJerry, freeValueJerry, printValuePC2, copyKeyJerry, freeKeyJerry,
                                                           printKeyPC, equalKeyPC, intoInt, hashNumberInt);
                //
                jerriesHT = createHashTable(copyKeyJerry, freeKeyJerry, printKeyJerry, copyValueJerry, freeValueJerry,
                                            printValueJerry, equalKeyJerries, intoInt, hashNumberInt);
                //
                for (int i = 1; i <= getLenghtList(jerriesLL); i++){
                    currentJerry = getDataByIndex(jerriesLL, i);
                    addToHashTable(jerriesHT, currentJerry->id, currentJerry);
                    for (int j = 0; j < currentJerry->jerrysNumberphysicalc; j++){
                        addToMultiValueHashTable(physicalCMHT, currentJerry->id, &currentJerry->physicalcArray[j].name);
                        addToMultiValueHashTable(physicalJerMHY, &currentJerry->physicalcArray[j].name, currentJerry->id);
                    }
                }
                //UPDATE HASH TABLE END
                //DELETE JERRY FROM JERRIES LINKED LIST
                deleteNode(jerriesLL, inputedJerrysID);
                //PRINT JERRY
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                break;

            case '5': // GET SIMILAR JERRY
                //INPUT PHYSICAL C
                printf("What do you remember about your Jerry ? \n");
                scanf("%s", inputedJerrysPCname);
                //CHECK IN MULTIVALUE HASH IF PHYSICAL C EXIST
                if (lookupInMultiValueHashTable(physicalJerMHY, inputedJerrysPCname) == NULL){
                    printf("Rick we can not help you - we do not know any Jerry's %s ! \n", inputedJerrysPCname);
                    break;
                }
                //INPUT FOR VALUE
                printf("What do you remember about the value of his %s ? \n", inputedJerrysPCname);
                scanf("%s", inputedJerrysPCvalueCHAR);
                inputedJerrysPCvalue = strtol(inputedJerrysPCvalueCHAR, NULL, 10); //convert to int
                //FIND LINKED LIST INSIDE MULTIVALUE OF JERRYS WHO HOLD THAT SAME PHYSICAL C
                currentLL = lookupInMultiValueHashTable(physicalJerMHY, inputedJerrysPCname);
                //VALUE TO COMPARE
                double smallest = 0;
                //INDEX WILL BE USED TO GET CORRECT JERRY FROM LINKED LIST OF JERRIES WITH THAT SAME PHYSICAL C
                int index = 0;
                //ITERATE LINKED LIST
                for (int i = 1; i <= getLenghtList(currentLL); i++){
                    tempJerry = getDataByIndex(currentLL, i);
                    //ITERATE JERRIES PHYSICAL C
                    for (int j = 0; j < tempJerry->jerrysNumberphysicalc; j++){
                        //IF FOUND SAME PHYSICAL
                        if (strcmp(inputedJerrysPCname, tempJerry->physicalcArray[j].name) == 0){
                            //ASSIGN THE DIFFERENCE
                            smallest = inputedJerrysPCvalue - tempJerry->physicalcArray[j].value;
                            //IF SMALLER THAN 0, * - 1
                            if (smallest <= 0){
                                smallest *= -1;
                                index = i;
                                break;
                            }
                            //ASSIGN INDEX
                            index = i;
                            break;
                        }
                    }
                    break;
                }
                //ITERATE FOR NEXT JERRY WITH SAME PHYSICAL C IF EXISTS
                currentJerry = getDataByIndex(currentLL, index);
                //ITERATE LINKED LIST
                for (int i = index + 1; i <= getLenghtList(currentLL); i++){
                    tempJerry = getDataByIndex(currentLL, i);
                    //ITERATE JERRYS PHYSICAL C
                    for (int j = 0; j < tempJerry->jerrysNumberphysicalc; j++){
                        //IF FOUND PHYSICAL C
                        if (strcmp(inputedJerrysPCname, tempJerry->physicalcArray[j].name) == 0){
                            //TEMP VALUE TO HOLD NEW JERRY'S DIFFERENCE FROM WANTED VALUE
                            double temp = inputedJerrysPCvalue - tempJerry->physicalcArray[j].value;
                            //CORRECT IF WRONG
                            if (temp < 0){
                                temp *= -1;
                            }
                            //IF SMALLER ASSIGN NEW INDEX OF JERRY
                            if (temp < smallest){
                                smallest = temp;
                                index = i;
                                break;
                            }
                            //IF EQUAL, ASSIGN FOR THE ONE WHO WAS ADDED FIRST TO THE DAYCARE
                            Jerry *tempPrevJerry = getDataByIndex(currentLL, index);
                            if (temp <= smallest && tempJerry->inputNumJerry < tempPrevJerry->inputNumJerry){
                                smallest = temp;
                                index = i;
                                break;
                            }
                        }
                    }
                }
                //
                if (index == 0){
                    break;
                }
                //FIND CORRECT JERRY FROM THE LIST
                currentJerry = getDataByIndex(currentLL, index);
                //PRINT JERRY
                printf("Rick this is the most suitable Jerry we found : \n");
                printjerry(currentJerry);
                printphysicalc(currentJerry);
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                //REMOVE JERRY FROM BOTH MULTIVALUE HASH TABLES
                for (int i = 0; i < currentJerry->jerrysNumberphysicalc; i++){
                    removeFromMultiValueHashTable(physicalCMHT, currentJerry->id, &currentJerry->physicalcArray[i].name);
                    removeFromMultiValueHashTable(physicalJerMHY, currentJerry->physicalcArray[i].name, currentJerry->id);
                }
                //DELETE JERRY FROM JERRYS LINKED LIST
                deleteNode(jerriesLL, currentJerry->id);
                //REMOVE JERRY FOR JERRIES HASH TABLE
                removeFromHashTable(jerriesHT, currentJerry->id);
                break;

            case '6': // GET SADDEST JERRY
                //CHECK IF THERE ARE ANY JERRIES AT ALL
                if (getLenghtList(jerriesLL) == 0){
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                //GET FIRST JERRY FROM THE LIST
                currentJerry = getDataByIndex(jerriesLL, 1);
                //ITERATE REST OF THE JERRIES, TO FIND IF THERE IS SOMEONE SADER
                for (int i = 2; i <= getLenghtList(jerriesLL); i++){
                    tempJerry = getDataByIndex(jerriesLL, i);
                    //IF THERE IS SOMEONE SADDER - REPLACE
                    if (tempJerry->happiness < currentJerry->happiness){
                        currentJerry = tempJerry;
                    }
                }
                //PRINT FOUND JERRY
                printf("Rick this is the most suitable Jerry we found : \n");
                printjerry(currentJerry);
                printphysicalc(currentJerry);
                //DELETE FOUND JERRY FROM MULTIVALUE HASH TABLES
                for (int i = 0; i < currentJerry->jerrysNumberphysicalc; i++){
                    removeFromMultiValueHashTable(physicalCMHT, currentJerry->id, &currentJerry->physicalcArray[i].name);
                    removeFromMultiValueHashTable(physicalJerMHY, currentJerry->physicalcArray[i].name, currentJerry->id);
                }
                //DELETE JERRY FROM LINKED LIST OF JERRIES
                deleteNode(jerriesLL, currentJerry->id);
                //REMOVE JERRY FROM JERRIES HASH TABLE
                removeFromHashTable(jerriesHT, currentJerry->id);
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                break;

            case '7': // SHOW INFORMATION
                //GET INPUT
                printf("What information do you want to know ? \n");
                printf("1 : All Jerries \n");
                printf("2 : All Jerries by physical characteristics \n");
                printf("3 : All known planets \n");
                scanf(" %c%*[^\n]", &ch7);
                switch(ch7){
                    case '1': //PRINT ALL JERRIES
                        //CHECK IF THERE ARE ANY JERRIES
                        if (getLenghtList(jerriesLL) == 0){
                            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                            break;
                        }
                        //ITERATE JERRIES LINKED LIST AND PRINT EACH ONE
                        displayList(jerriesLL);
                        break;

                    case '2': // SHOW JERRIES BY PHYSICAL C
                        //INPUT WANTED PHYSICAL C
                        printf("What physical characteristics ? \n");
                        scanf("%s", inputedJerrysPCname);
                        //CHECK IF EXISTS
                        if (lookupInMultiValueHashTable(physicalJerMHY, inputedJerrysPCname) == NULL){
                            printf("Rick we can not help you - we do not know any Jerry's %s ! \n", inputedJerrysPCname);
                            break;
                        }
                        //PRINT PHYSICAL C NAME
                        printf("%s : \n", inputedJerrysPCname);
                        //ITERATE FOR JERRIES WITH SAME PHYSICAL C AND PRINT
                        for (int i = 1; i <= getLenghtList(jerriesLL); i++){
                            currentJerry = getDataByIndex(jerriesLL, i);
                            for (int j = 0; j < currentJerry->jerrysNumberphysicalc; j++){
                                if (strcmp(inputedJerrysPCname, currentJerry->physicalcArray[j].name) == 0){
                                    printjerry(currentJerry);
                                    printphysicalc(currentJerry);
                                    break;
                                }
                            }
                        }
                        break;

                    case '3': //PRINT ALL KNOWN PLANETS
                        for (int i = 0; i < planetsNumber; i++){
                            //GET EACH PLANET, AND PRINT IT
                            Planet *currentPlanet = &pPlanetArray[i];
                            printplanet(currentPlanet->name);
                        }
                        break;

                    default: // DEAFULT
                        printf("Rick this option is not known to the daycare ! \n");
                        break;
                }
                ch7 = '1';
                break;

            case '8': //ACTIVITIES FOR JERRIES
                //CHECK IF THERE ARE ANY JERRIES AT ALL
                if (getLenghtList(jerriesLL) == 0){
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                //GET USER INPUT FOR ACTIVITY
                printf("What activity do you want the Jerries to partake in ? \n");
                printf("1 : Interact with fake Beth \n");
                printf("2 : Play golf \n");
                printf("3 : Adjust the picture settings on the TV \n");
                scanf(" %c%*[^\n]", &ch8);
                switch(ch8){
                    case '1':
                        if (getLenghtList(jerriesLL) == 0){
                            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                            break;
                        }
                        //ITERATE EVERY JERRY
                        for (int i = 1; i <= getLenghtList(jerriesLL); i++){
                            currentJerry = getDataByIndex(jerriesLL, i);
                            //IF HAPPY 20+ ADD 15, IF BIGGER THAN 100, SET TO 100
                            if (currentJerry->happiness >= 20){
                                currentJerry->happiness += 15;
                                if(currentJerry->happiness > 100){
                                    currentJerry->happiness = 100;
                                }
                            }
                            //IF HAPPY 19-, MINUS 5, IF SMALLER THAN 0, SET 0
                            else {
                                currentJerry->happiness -= 5;
                                if (currentJerry->happiness < 0){
                                    currentJerry->happiness = 0;
                                }
                            }
                        }
                        //PRINT ALL JERRIES NOW
                        printf("The activity is now over ! \n");
                        displayList(jerriesLL);
                        break;

                    case '2':
                        if (getLenghtList(jerriesLL) == 0){
                            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                            break;
                        }
                        //ITERATE FOR JERRIES, IF 50+, ADD 10, IF 100+ SET 100
                        for (int i = 1; i <= getLenghtList(jerriesLL); i++){
                            currentJerry = getDataByIndex(jerriesLL, i);
                            if (currentJerry->happiness >= 50){
                                currentJerry->happiness += 10;
                                if(currentJerry->happiness > 100){
                                    currentJerry->happiness = 100;
                                }
                            }
                            //IF 49-, THAN MINUS 10, IF SMALLER THAN 0 SET 0
                            else {
                                currentJerry->happiness -= 10;
                                if (currentJerry->happiness < 0){
                                    currentJerry->happiness = 0;
                                }
                            }
                        }
                        //PRINT JERRIES
                        printf("The activity is now over ! \n");
                        displayList(jerriesLL);
                        break;

                    case '3':
                        if (getLenghtList(jerriesLL) == 0){
                            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                            break;
                        }
                        //ITERATE ALL JERRIES AND ADD 20, IF 100+ SET 100
                        for (int i = 1; i <= getLenghtList(jerriesLL); i++){
                            currentJerry = getDataByIndex(jerriesLL, i);
                            currentJerry->happiness += 20;
                            if (currentJerry->happiness > 100){
                                currentJerry->happiness = 100;
                            }
                        }
                        //PRINT JERRIES
                        printf("The activity is now over ! \n");
                        displayList(jerriesLL);
                        break;

                    default:
                        printf("Rick this option is not known to the daycare ! \n");
                        break;
                }
                ch8 = '1';
                break;

            case '9': // EXIT AND FREE MEMORY
                printf("The daycare is now clean and close ! \n");
                freeplanets();
                destroyList(originsLL);
                freephysicalc();
                destroyList(jerriesLL);
                destroyHashTable(jerriesHT);
                destroyMultiValueHashTable(physicalCMHT);
                destroyMultiValueHashTable(physicalJerMHY);
                break;

            default:
                ch = '1';
                printf("Rick this option is not known to the daycare ! \n");
                break;
        }
    }

}

