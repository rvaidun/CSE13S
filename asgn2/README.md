# Assignment 2

This program is an implementation of the inverse trig functions and log functions.

## Build

    $ make

## Running

<p>In order to run the program you need to specify which test to run via Command Line Arguments.</p>

- <code>-s</code>: runs all sin tests
- <code>-c</code>: runs all cos tests
- <code>-t</code>: runs all tan tests
- <code>-l</code>: runs all log tests
- <code>-a</code>: runs all tests for all functions

```
$ ./mathlib-tests -a
```

The code above runs all tests.

## Cleaning

    $ make clean

## Files

### mathlib.c

This is the C file with the implementation of my math library. This math library can do arcsin arccos arctan and log

### mathlib-test.c

This file is the test harness for mathlib.c

### Makefile

Makefile has all the commands to compile and clean the files

### mathlib.h

The header file for mathlib.c Exports all functions that mathlib-test needs

### DESIGN.pdf

This file contains information about the design/workflow of mathlib.c Reading it should give you a good idea of how the program works

### WRITEUP.pdf

This file contains is an analysis of the results of the tests produced by mathlib-tests
