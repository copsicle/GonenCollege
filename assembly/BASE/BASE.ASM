; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT

DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start