# arithmancer
A calculator built in C to try out the shunting yard algorithm.

# Description 
The calculator uses the Shunting Yard Algorithm, developed by Edsger Dijkstra in 1961, it takes a string input and parses it into reverse Polish notation. 
The input is tokenized first into numbers and operators, then organized by operator precedence and left/right association. In this case the only right associative operation being exponents. 
The ordered tokens are then processed left to right and passed into an answer stack.

# Installation 
## Requirements 
The only requirement is to have gcc installed on your system
## Building 
Run the build.bat file if working on a windows machine
or for building from terminal on any system run.
```bash
gcc -g main.c src/token.c src/stack.c src/queue.c src/arithmancer.c -o arithmancer -lm
```
Then run the arithmancer executable.

# Features
The program can handle addition, subtraction, multiplication, division, and exponentiation. Sections can be encapsulated in brackets for altering the order of operations. The program also supports floating point notation. While white space between tokens (numbers and operation symbols) is ignored.
```bash
> (8*(4/8)+6-7)^2
9.000000

> 3.14159 * 2.5 ^ 2 # area of a circle with a radius of 2.5
19.634937
```
## Size restriction.
The program by default has a max array size of 256, which is set in globals.h. Memory is preallocated in the run function, and consists of an input buffer `char input[MAX_SIZE]`, two Queues, and two Stacks. The static memory allocation in function `run` with a max size of 256 ends up being ~16.77 Kb.
The memory usage is going to be roughly `stack_memory = 128 + 65 * MAX_SIZE`. Something to keep in mind if needing an input larger than 256 bytes. Give or take some bytes for local variables within functions, but this is the main usage.
For more information on static memory use:
```bash
gcc -g -fstack-usage -o arithmancer .\src\token.c .\src\stack.c .\src\queue.c .\src\arithmancer.c main.c
```

# Usage
Type in the equation you want the answer to and hit `Enter ↵`
## Symbols 
- Add = '+'
- Subtract = '-'
- Multiply = '*'
- Divide = '/'
- Power = '^'
- Left Bracket = '('
- Right Bracket = ')'
## Unsupported Symbols 
Currently does not support any functions like Sin or Floor.

