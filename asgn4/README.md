# Assignment 4

This program is an implementation of Depth first search

## Build

    $ make

## Running

<p>In order to run the program you need to specify which test to run via Command Line Arguments.</p>

- `-h`: Shows help
- `-u`: Use undirected graph.
- `-v`: Enable verbose printing.
- `-i infile`: Input containing graph (default: stdin)
- `-o outfile`: Output of computed path (default: stdout)

```
$ ./tsp -v -i graphs/texas.graph
```

The code above finds the shortest hamiltonian path for the texas graph with verbose

## Cleaning

```
$ make clean
```

## Files

### graph.{c,h}

Source and header files for graph

### path.{c,h}

Source and header files for path

### stack.{c,h}

Source and header file for stack

### tsp.c

Driver program to find shortest hamiltonian path

### Makefile

Makefile has all the commands to compile and clean the files

### DESIGN.pdf

This file contains information about the design/workflow of tsp.c Reading it should give you a good idea of how the program works
