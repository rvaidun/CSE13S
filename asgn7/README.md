# Assignment 7

This assignment is for regulating the people of Santa Cruz. The assignment uses bloom filters and hash tables

## Build

    $ make

## Running

### banhammer

The banhammer program is the main program. The current working directory needs to have the files `badspeak.txt` and `goodspeak.txt`

- `-h`: Program usage and help
- `-s`: Prints program statistics
- `-m`: Enable move-to-front rule
- `-t size`: Specify hash table size (default: 10000).
- `-f size`: Specify Bloom filter size (default: 2^20).

## Cleaning

```
$ make clean
```

## Files

### bf.{c,h}

Source and header files for Bloom Filter

### bv.{c,h}

Source and header files for Bit Vector

### DESIGN.pdf

Pseudocode for the assignment

### ht.{c,h}

Source and header file for Hash Table

### ll.{c,h}

Sorce and header file for the LinkedList

### Makefile

Makefile has all the commands to compile and clean the files

### messages.h

Header file containing all the messages

### node.{c,h}

Source and header file for the nodes

### parser.{c,h}

Source and header file for the parser

### speck.{c,h}

Source and header file for the speck hash function

### WRITEUP.pdf

PDF containing the writeup
