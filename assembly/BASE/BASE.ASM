; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT

DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	push DATA
	pop ds
	
	
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start