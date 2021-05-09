# Assignment 5

This assignment is for encoding and decoding hamming codes. To easily do this the encoders and decoders are using Bit Vectors and Bit Matrices.

## Build

    $ make

## Running

### encode

<p> The encode program encodes a file with Hamming (8,4) Encode. You can specify the following command line arguments.</p>

- `-h`: Shows help
- `-i infile`: Input containing graph (default: stdin)
- `-o outfile`: Output of computed path (default: stdout)

### decode

<p> The decode program encodes a file with Hamming (8,4) Decode. You can specify the following command line arguments.</p>

- `-h`: Shows help
- `-i infile`: Input containing graph (default: stdin)
- `-o outfile`: Output of computed path (default: stdout)
- `-v`: Enable verbose printing.

### error

<p> The error program injects noise into files passed to it from stdin. You can specify the following command line arguments.</p>

- `-h`: Shows help
- `-s seed`: Specifies the random seed.
- `-e error_rate`: Specifies the error rate.

### entropy

<p> The entropy program gives the entropy of a file passed from stdin. You can specify the following command line arguments.</p>

- `-h`: Shows help

```
$ ./encode < error.c | ./error -e 0.01 | ./decode -v | diff - error.c
```

The code above encodes the error.c source file, injects an error at a rate of 0.01% and decodes it with the verbose flag enabled<br>
Then the code is passed to diff to see the difference between the original error.c and the decoded error.c

## Cleaning

```
$ make clean
```

## Files

### bv.{c,h}

Source and header files for Bit Vector

### bm.{c,h}

Source and header files for Bit Matrix

### hamming.{c,h}

Source and header file for the Hamming modules.

### decode.c

Source file for the decoder

### encode.c

Source file for the encoder

### error.c

Source file for the error program

### entropy.c

Source file for the entropy program

### Makefile

Makefile has all the commands to compile and clean the files

### DESIGN.pdf

This file contains information about the design/workflow of how the encoder and decoders work.
