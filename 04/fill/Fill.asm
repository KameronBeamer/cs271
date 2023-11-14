// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

// Start of keyboard map
@R24576
D=M
@KBD
M=D

// Start of screen map
@16384
D=M
@SCREEN
M=D

// R0 = 1
@1
D=A
@R0
M=D

(INFINITELOOP)
	// while R0 = 1, forever
	@R0
	D=M
	@END
	D;JLE
	
	// initialize the number of pixels in screen map on loop
	@8192
	D=A
	@i
	M=D
	
	
	(COLORSCREEN)
	// Iterate through screenmap backwards
	@i
	M=M-1
	D=M
	// reset if i > 0
	@INFINITELOOP
	D;JLT
	
	// if KBD = 0 send to WHITESCREEN, else send to BLACKSCREEN
	@KBD
	D=M
	@WHITESCREEN
	D;JEQ
	@BLACKSCREEN
	0;JMP
	
	// here for insurance
	@INFINITELOOP
	0;JMP
	
(END)
	@END
	0;JMP


(WHITESCREEN)
	// set current set of pixels to 1
	@SCREEN
	D=A
	@i
	A=D+M
	M=-1

	@COLORSCREEN
	0;JMP


(BLACKSCREEN)
	// set current set of pixels to 0
	@SCREEN
	D=A
	@i
	A=D+M
	M=0

	@COLORSCREEN
	0;JMP













