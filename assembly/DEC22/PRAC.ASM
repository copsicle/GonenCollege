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

	mov al, 3
	shl al, 2

	mov al, 120
	shr al, 3

	mov al, 10
	mov ah, al
	shl al, 4
	shl ah, 2
	add al, ah
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start