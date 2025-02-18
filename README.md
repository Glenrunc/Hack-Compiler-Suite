# Assembler, VM for Hack Architecture

The Hack computer is described in Chapter 5 of the [Nand2Tetris book](https://github.com/jherskow/nand2tetris/blob/master/nand2tetris%20BOOK.pdf). This assembler is not optimized. Feel free to clone the repo and submit a PR.

## Overview assembler

> The Hack computer consists of a **ROM32K** for storing instructions, a **CPU**, and **RAM** for data storage. The RAM also includes memory-mapped I/O devices, such as a **screen** and **keyboard**.

> This architecture supports only two types of instructions:
> - **A-instruction** (Address instruction)
> - **C-instruction** (Compute instruction)

> The assembler converts Hack assembly code (A and C instructions) into a binary machine code file. Each architecture requires a specific assembler, as instruction formats differ between systems.

## Example

### Assembly Code (Input)

```assembly
// If (R0 <= 0) goto END else n = R0
@R0
D=M
@END
D;JLE 
@n
M=D
// addr = base address of first screen row
@SCREEN
D=A
@addr
M=D
(LOOP)
    // RAM[addr] = -1
    @addr
    A=M
    M=-1
    // addr = base address of next screen row
    @addr
    D=M
    @32
    D=D+A
    @addr
    M=D
    // decrements n and loops
    @n
    MD=M-1
    @LOOP
    D;JGT
(END)
    @END
    0;JMP
```

### Machine Code (Output after Assembly)

```
0000000000000000
1111110000010000
0000000000011000
1110001100000110
0000000000010001
1110001100001000
0100000000000000
1110110000010000
0000000000010010
1110001100001000
0000000000010010
1111110000100000
1110111010001000
0000000000010010
1111110000010000
0000000000100000
1110000010010000
0000000000010010
1110001100001000
0000000000010001
1111110010011000
0000000000001010
1110001100000001
0000000000011000
1110101010000111
```

This program reads a value from `R0`, checks if it is non-positive, and jumps to `(END)` if necessary. Otherwise, it initializes `n = R0` and performs operations related to screen memory, decrementing `n` in a loop.

## Overview VM translator