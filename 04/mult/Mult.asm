// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.


// r0 and r1 are 16 bits or less
// if is usable here, though its syntax may be different
// I CAN build it with repeated addition, but there is a better way to do it
// build it the simple way if you can't figure out the better way in a timely manner
// come back later and try to find the better way when you're done

// x = R0
@R0
D=M
@x
M=D

// y = R1
@R1
D=M
@y
M=D

// R2 = 0
@0
D=A
@R2
M=D


(WHILE)
	// while y <= 0
	@y
	D=M
	@END
	D;JLE
	
	// R2 = x + R2
	@x
	D=M
	@R2
	M=D+M
	// y--
	@1
	D=A
	@y
	M=M-D
	
	@WHILE
	0;JMP
(END)
	@END
	0;JMP

