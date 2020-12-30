; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
response dw 3C7h
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	xor bx, bx
	mov cx, 10
L1:
	ror response, 1
	jnc L2
	inc bl
L2:
	loop L1

	ror response, 6

exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start