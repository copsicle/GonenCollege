; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
num dw 42069
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax

	mov ax, num
	mov bx, 10
	xor cx, cx

l1:
	xor dx, dx
	div bx
	add cx, dx
	test ax, ax
	jnz l1
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


