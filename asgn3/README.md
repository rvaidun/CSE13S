# Assignment 3

This program is an implementation of different sorting algorithms

## Build

    $ make

## Running

<p>In order to run the program you need to specify which test to run via Command Line Arguments.</p>

- `-h`: Shows help
- `-a`: runs tests for all sorting algorithms
- `-b`: runs tests for bubble sort
- `-s`: runs tests for shell sort
- `-q`: runs tests for quick sort (Stack)
- `-Q`: runs tests for quick sort (Queue)
- `-r [num]`: sets seed to generate random array. Default is 13371453
- `-p [num]`: sets how many elements of the array to print. Default is 100
- `-n [num]`: changes the size of the array. Default is 100

```
$ ./sorting -a
```

The code above runs all tests with the defaults

## Cleaning
```
$ make clean
```

## Files

###bubble.{c,h}

Source and header files for bubble sort

###shell.{c,h}

Source and header files for shell sort

###quick.{c,h}

Source and header files for quick sort

###set.{c,h}

Source and header files for the set implementation

###gaps.h

Contains gap sequence used by shell sort

### stack.{c,h}

Source and header file for stack

### queue.{c,h}

Source and header files for queue

### sorting.c

Test harness for the sorting algorithms

### Makefile

Makefile has all the commands to compile and clean the files

### DESIGN.pdf

This file contains information about the design/workflow of mathlib.c Reading it should give you a good idea of how the program works

### WRITEUP.pdf

This file contains is an analysis of the results of the tests produced by mathlib-tests
