JerryBoree:Defs.o HashTable.o Jerry.o JerryBoreeMain.o KeyValuePair.o LinkedList.o MultiValueHashTable.o
	gcc Defs.o HashTable.o Jerry.o JerryBoreeMain.o KeyValuePair.o LinkedList.o MultiValueHashTable.o -o prog
HashTable.o:HashTable.c HashTable.h LinkedList.h KeyValuePair.h Defs.h
	gcc -c HashTable.c
Jerry.o: Jerry.c Jerry.h MultiValueHashTable.h LinkedList.h KeyValuePair.h Defs.h
	gcc -c Jerry.c
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
MultiValueHashTable.o: MultiValueHashTable.c MultiValueHashTable.h HashTable.h LinkedList.h KeyValuePair.h Defs.h
	gcc -c MultiValueHashTable.c
