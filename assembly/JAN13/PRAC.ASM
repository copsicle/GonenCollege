; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
M db 'AB'
db 'C'
X dw 'G', 'KH'
Z db 'ASSEMBLY$'
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	mov Z + 4, 'W'
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start