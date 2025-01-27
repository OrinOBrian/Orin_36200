#
# Makefile for Chapter 01
#
# Type  make    to compile all the programs
# in the chapter 
#
all: Hw1

clean:
	rm -f Hw1


Hw1: Hw1.c 
	cc -o Hw1 	Hw1.c 

	cc -o more02 more02.c 
