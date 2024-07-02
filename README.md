# Jerry-Boree
C-based day care management system implementing Abstract Data Types like LinkedList, KeyValuePair, HashTable, and MultiValueHashTable. Don't worry, your Jerry is in good hands!

Main
----
Running the compiled program will require 2 arguments, number of planets and configuration file.
Example: "./JerryBoree 4 example_config.txt"
The main will read from the file (example-config) the needed inputs, and create 5 structs:
* JerriesLL: A linked list holding all the current Jerries (will store the actual Jerry struct)
* OriginsLL: A linked list holding all the current Jerries (will store the actual Origin Struct)
* JerriesHT: A hashtable holding all the current Jerries (will store a pointer to Jerry struct)
* physicalcMHT: A multivaluehashtable holding physical name by jerry key.
* physicalJerMHT: A multivaluehashtable holding jerry struct by physical name key.

![JerryBoree](https://github.com/Nati-Mordekhay/Jerry-Boree/assets/72460220/c95c6747-75d2-4d7a-83f8-4c9ec4e261b3)

Structure
=========

Linked-List:
------------
The linked list struct holds within it a pointer to it's head, which is a 'Node' struct by itself.
The node's act as the linked-list, where as the 'LinkedList' struct holds the head.

Key-Value-Pair:
---------------
The key-value-pair struct holds it's key and a value.

HashTable:
----------
The hash table holds a linkedlist in each of it's cells, where as every linked list's node holds a key value pair.
When appending to the hash table, it inputs the value into a key-value pair, and adds it to the needed linked list.

Multi-Value-HashTable
---------------------
The Multi-Value-HashTable holds a pointer to a hashtable, and whenever appending into it, it created a Key-Value-Pair holding a linked list, and appending it.

![1](https://github.com/Nati-Mordekhay/Jerry-Boree/assets/72460220/8923eb4e-2419-44d9-8a85-4d1f3e16a00d)
![2](https://github.com/Nati-Mordekhay/Jerry-Boree/assets/72460220/68100287-5a30-4062-83d5-0fed8244c9e3)
![3](https://github.com/Nati-Mordekhay/Jerry-Boree/assets/72460220/6e67e96f-28f1-4278-8ad0-6468053f2c1b)

