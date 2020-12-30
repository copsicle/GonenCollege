; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
a dw 1234h
b dw 5678h
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA

swap PROC
	mov bp, sp
	mov ax, word ptr [bp + 2]
	mov bx, word ptr [bp + 4]
	mov word ptr [bp + 2], bx
	mov word ptr [bp + 4], ax
	ret
swap ENDP

start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	push a
	push b
	
	CALL swap

	pop b
	pop a
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start