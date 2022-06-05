# Spell checker and hash table

## First part 

Implementing two duplicate-free hash table structures :

- The first with resolution of collisions by chaining 
-  The second by Linear probing

These two structures must offer at least the following methods to the client, including their complexities must all be O(1) amortized: 

- `size` : The number of elements in the hash table 
- `insert`: Allows you to insert a key 
- `contains`: Checks if a key is present in the hash table 
- `erase`:  Deletes the key from the hash tab

## Second part

In this second part you will have to implement a spell checker in English allowing to find spelling errors in the words composing a given text using a dictionary.

A word is considered correctly spelled if it is found in the dictionary of reference. If a word is not in the dictionary, your program will have to offer a set of possible corrections and validate them using the dictionary.