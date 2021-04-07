# Assignment 1

This program is the implementation of the Left, Right Center Game. 
There can be 1 to 14 players and each player starts off with $3.
The dice have 6 faces. 3×•, 1×L, 1×R or 1×C.
If the player gets a L they give $1 to the player on the left
If the player rolls a R they give $1 to the player on the right
If the player rolls a C they put $1 in the center put
If the player rolls a • nothing happens.
When its your the number of times you roll is equivalent to the amount of money you have unless you have more than $3.
Maximum roll amount is $3

## Build

    $ make

## Running

    $ ./lrc

## Cleaning

    $ make clean

## Files

### lrc.c

This is the C file with the LRC game. This file is compiled by running the command in the build section

### DESIGN.pdf
This file contains information about the design/workflow of lrc.c Reading it should give you a good idea of how the program works

### Makefile
Makefile has all the commands to compile and clean the files

### philos.h
Contains all possible players in the game
