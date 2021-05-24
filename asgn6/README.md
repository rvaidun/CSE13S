# Assignment 6

This assignment is for compressing files. To easily do this the encoders and decoders are using Stacks, Priority Queues,

## Build

    $ make

## Running

### encode

<p> The encode program encodes a file with Hamming (8,4) Encode. You can specify the following command line arguments.</p>

- `-h`: Shows help
- `-i infile`: Input containing graph (default: stdin)
- `-o outfile`: Output of computed path (default: stdout)
- `-v`: Enable verbose printing.

### decode

<p> The decode program decodes a file with Hamming (8,4) Decode. You can specify the following command line arguments.</p>

- `-h`: Shows help
- `-i infile`: Input containing graph (default: stdin)
- `-o outfile`: Output of computed path (default: stdout)
- `-v`: Enable verbose printing.

## Cleaning

```
$ make clean
```

## Files

### bitlib.{c,h}

Source and header files for bitlibrary

### code.{c,h}

Source and header files for code

### decode.c

Source file for decoder

### defines.h

Header file with default definitions

### DESIGN.pdf

Pseudocode for the assignment

### encode.c

Source file for the encoder

### entropy.c

Source file for the entropy program

### header.h

Header file for the header structure

### huffman.{c,h}

Source and header file for the huffmann tree module

### io.{c,h}

Source and header file for the IO module

### Makefile

Makefile has all the commands to compile and clean the files

### node.{c,h}

Source and header file for the nodes

### pq.{c,h}

Source and header files for the priority queues
